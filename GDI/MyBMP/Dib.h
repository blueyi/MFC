#ifndef _DIB_H
#define _DIB_H

//用于显示BMP的CDib类
class CDib: public CObject
{
public:
	CDib();
	CDib(const char* fileName);				//以文件名为参数的构造函数
	~CDib();
	BOOL LoadFromFile(LPCTSTR fileName);	//从文件读入位图

	DWORD ImageSize();						//获得位图的实际大小
	int Width();							//获得位图的宽度
	int Height();							//获得位图的高度
	UINT UsedColors();						//获得位图用到的颜色数
	
	LPBITMAPINFOHEADER GetInfoHeaderPtr();	//获得信息头指针
	LPBITMAPINFO GetInfoPtr();				//获得信息指针
	LPRGBQUAD GetRGBTablePtr();				//获得颜色查找表指针
	BYTE* GetBmBitsPtr();					//获得点数组的指针

	BOOL NeedPalette();						//返回是否需要调色板
	HPALETTE GetDibPalette();				//返回位图的调色板
private:
	void Initialize();						//初始化函数
	void Empty();							//清空函数
	DWORD ImageDataSize();					//计算图像数据字节数
	HPALETTE CreateDibPalette();			//创建调色板，返回其句柄
private:
	LPBITMAPINFO m_pBmInfo;					//位图信息指针
	LPBITMAPINFOHEADER m_pBmInfoHeader;		//位图信息头指针
	RGBQUAD * m_pRGBTable;					//位图颜色查找表指针
	BYTE * m_pDibBits;						//位图点数组
	BOOL m_bNeedPalette;					//位图是否需要调色板
	HPALETTE m_hPalette;					//位图的调色板
};

//显示由CDib封装的位图
ShowDib(CDC * pDC,CDib * pDib,CRect& rect,BOOL bStretch=TRUE);

#endif
