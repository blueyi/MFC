#include "stdafx.h"
#include "windows.h"
#include "windowsx.h"
#include "Dib.h"
// Download by http://www.codefans.net
CDib::CDib()
{
	Initialize();
}

CDib::CDib(const char* fileName)
{
	Initialize();
	LoadFromFile(fileName);		//读入位图并做初始化
}
//初始化
void CDib::Initialize()
{
	m_pBmInfo		= 0;
	m_pBmInfoHeader = 0;
	m_pRGBTable		= 0;
	m_pDibBits		= 0;
	m_bNeedPalette	= FALSE;
	m_hPalette		= NULL;
}

CDib::~CDib()
{
	Empty();
}
//清空函数
void CDib::Empty()
{
	if(m_pBmInfo)
		GlobalFreePtr(m_pBmInfo);		//释放位图占用的内存
	if(m_bNeedPalette && m_hPalette)	//释放调色板
		DeleteObject(m_hPalette);
}
//从文件读入位图
BOOL CDib::LoadFromFile (LPCTSTR fileName)
{
	CFile file;
	//打开位图文件
	if(file.Open(fileName, CFile::modeRead|CFile::shareDenyWrite)!=TRUE)
	{
		CString errorStr;
		errorStr.Format(_T("打开%s错误"), (LPCTSTR)fileName);
		AfxMessageBox(errorStr);
		file.Close();
		return FALSE;
	}
	//读入位图文件头
	BITMAPFILEHEADER bmFileHeader;
	file.Read((void*)&bmFileHeader, sizeof(bmFileHeader));
	//检查是否是位图标识符,如果不是,显示错误信息,并返回
	if (bmFileHeader.bfType != 0x4d42)
	{
		CString errorStr;
		errorStr.Format("%s 不是位图文件!!!", (LPCTSTR)fileName);
		AfxMessageBox(errorStr);
		file.Close();
		return FALSE;
	}
	//计算位图数据的大小,等于文件长度-文件头长度
	DWORD fileLength = file.GetLength();
	DWORD dibSize = fileLength - sizeof(bmFileHeader);
	//为位图数据分配内存
	BYTE* pDib = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, dibSize);
	//把位图数据读入内存并关闭文件
	file.Read((void*)pDib, dibSize);
	file.Close();
	//初始化位图信息头指针和位图信息指针
	m_pBmInfo = (LPBITMAPINFO) pDib;
	m_pBmInfoHeader = (LPBITMAPINFOHEADER) pDib;
	//如果BITMAPINFOHEADER的biSizeImage不正确,改正
	if (m_pBmInfoHeader->biSizeImage == 0)
		m_pBmInfoHeader->biSizeImage 
			= m_pBmInfoHeader->biWidth * m_pBmInfoHeader->biHeight;
	//如果biClrUsed为0,且不是真彩色图,返回2的biBitCount次方,否则直接返回已有值
	if(m_pBmInfoHeader->biClrUsed == 0)
		m_pBmInfoHeader->biClrUsed = DWORD(1 << m_pBmInfoHeader->biBitCount);
	//判断是否需要调色板
	if(m_pBmInfoHeader->biClrUsed <= 256)
	{
		m_bNeedPalette = TRUE;
		//计算颜色查找表的偏移量,并给其指针赋值
		m_pRGBTable = (RGBQUAD*)(pDib + m_pBmInfoHeader->biSize);
		m_hPalette = CreateDibPalette();
	}
	//计算位图点数组的偏移量,并给其指针赋值
	DWORD clrTableSize = m_bNeedPalette ? UsedColors() * sizeof(RGBQUAD) : 0;
	m_pDibBits = pDib + m_pBmInfoHeader->biSize + clrTableSize;
	return TRUE;
}
//返回位图的大小(高度*宽度)
DWORD CDib::ImageSize()
{
	return m_pBmInfoHeader->biSizeImage;
}
//返回位图的宽度
int CDib::Width()
{
	return m_pBmInfoHeader->biWidth;
}
//返回位图的高度
int CDib::Height()
{
	return m_pBmInfoHeader->biHeight;
}
//返回位图使用的颜色数
UINT CDib::UsedColors()
{
	return (int) m_pBmInfoHeader->biClrUsed;
}
//返回位图的信息头指针
LPBITMAPINFOHEADER CDib::GetInfoHeaderPtr()
{
	return m_pBmInfoHeader;
}
//返回位图的信息块指针
LPBITMAPINFO CDib::GetInfoPtr()
{
	return m_pBmInfo;
}
//返回位图的颜色查找表指针
LPRGBQUAD CDib::GetRGBTablePtr()
{
	return m_pRGBTable;
}
//返回位图的点数组
BYTE* CDib::GetBmBitsPtr()
{
	return m_pDibBits;
}
//返回是否需要调色板
BOOL CDib::NeedPalette()
{
	return m_bNeedPalette;
}
//返回调色板句柄
HPALETTE CDib::GetDibPalette()
{
	return m_hPalette;
}
//计算图像数据字节数
DWORD CDib::ImageDataSize()
{
	return (Width()*Height()*m_pBmInfoHeader->biBitCount)/8;
}
//创建调色板，返回其句柄
HPALETTE CDib::CreateDibPalette()
{
	//获得颜色数
	UINT numColors = UsedColors();
	//定义逻辑调色板
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	}	logicalPalette = { 0x300, 256 };
	//把RGBTable中的数据转入调色板中
	for(UINT i=0; i<numColors; ++i)
	{
		logicalPalette.aEntries[i].peRed	= m_pRGBTable[i].rgbRed;
		logicalPalette.aEntries[i].peGreen	= m_pRGBTable[i].rgbGreen;
		logicalPalette.aEntries[i].peBlue	= m_pRGBTable[i].rgbBlue;
		logicalPalette.aEntries[i].peFlags	= 0;
	}
	//生成调色板句柄
	HPALETTE hPalette = ::CreatePalette((LPLOGPALETTE)&logicalPalette);
	return hPalette;
}
//显示显示由CDib封装的位图，bStretch为是否拉伸
ShowDib(CDC * pDC,CDib * pDib,CRect& rect,BOOL bStretch)
{
	BYTE* pBmBits			= pDib->GetBmBitsPtr();
	LPBITMAPINFO pBmInfo	= pDib->GetInfoPtr();
	UINT bmWidth			= pDib->Width();
	UINT bmHeight			= pDib->Height();
	//根据是否拉伸，决定显示的矩形
	CRect drawRect;
	if(bStretch==TRUE)
		drawRect = rect;
	else
	{
		drawRect.left = rect.left;
		drawRect.top = rect.top;
		drawRect.right = rect.left+bmWidth;
		drawRect.bottom = rect.top+bmHeight;
	}
	//如果需要调色板，生成调色板
	HPALETTE hPalette = NULL;
	HPALETTE hOldPalette = NULL;
	if(pDib->NeedPalette())
	{
		hPalette = pDib->GetDibPalette();
		hOldPalette = SelectPalette(pDC->m_hDC,hPalette, FALSE);
		RealizePalette(pDC->m_hDC);
	}
	//使用StretchDIBits显示
	::StretchDIBits(pDC->m_hDC,
		drawRect.left,drawRect.top,drawRect.Width(),drawRect.Height(),
		0, 0, bmWidth, bmHeight,
		pBmBits, pBmInfo, DIB_RGB_COLORS, SRCCOPY);
	//释放调色板
	if(pDib->NeedPalette())
	{
		::SelectPalette(pDC->m_hDC,hOldPalette,FALSE);
		::DeleteObject(hPalette);
	}
	return 0;
}