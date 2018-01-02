// ListImageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ListImage.h"
#include "ListImageCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define THUMWIDTH 75
#define THUMHEIGHT 75
CString ConvertDoubleToString(double dvTmp);
void DoEvents(void);
/////////////////////////////////////////////////////////////////////////////
// CListImageCtrl

CListImageCtrl::CListImageCtrl()
{
}

CListImageCtrl::~CListImageCtrl()
{
}


BEGIN_MESSAGE_MAP(CListImageCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CListImageCtrl)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListImageCtrl message handlers
// This funtion is used to load the Window dropped files into the listview

void CListImageCtrl::OnDropFiles(HDROP hDropInfo) 
{
	WORD wNumFilesDropped = DragQueryFile(hDropInfo, -1, NULL, 0);

	CString firstFile="";
	CFile Cf;
	DWORD TmpVal;
	char szText[MAX_PATH];
	int kk=0;
	int tTot=(int)wNumFilesDropped;
	int m_TotCount;

	for (WORD x = 0 ; x < wNumFilesDropped; x++) 
	{
		kk++;
		// Get the number of bytes required by the file's full pathname
		WORD wPathnameSize = DragQueryFile(hDropInfo, x, NULL, 0);

		// Allocate memory to contain full pathname & zero byte
		char * npszFile = (char *) LocalAlloc(LPTR, wPathnameSize += 1);

		// If not enough memory, skip this one
		if (npszFile == NULL) continue;
		DragQueryFile(hDropInfo, x, npszFile, wPathnameSize);

		if (firstFile=="")
			firstFile=npszFile;

		CString nFileText;
		CString nPath;
		CString pItemText=npszFile;
		CFile Cf;

		int i=pItemText.ReverseFind('\\');

		nFileText=pItemText.Mid(i+1);
		nPath=pItemText.Left(i+1);
		i=nFileText.Find("%");
		if (i==-1)
		{
			i=pItemText.Find(_T(".jpg"),0);
			if (i==-1)
				i=pItemText.Find(_T(".jpeg"),0);
			if (i==-1)
				i=pItemText.Find(_T(".JPG"),0);
			if (i==-1)
				i=pItemText.Find(_T(".JPEG"),0);

			if (i!=-1)
			{
				//Creating thumbnail image for the file
				HBITMAP bitm=LoadPicture(pItemText);
				if (bitm!=NULL)
				{
					//List item index
					m_TotCount=GetItemCount();
					//Adding Bitmap to the Imagelist
					CBitmap*    pImage = NULL;	
					pImage = new CBitmap();		 
					pImage->Attach(bitm);
					int imgP=m_imageList.Add(pImage,RGB(0,0,0));
					//Link to the added listview item 
					InsertItem(m_TotCount,nFileText,imgP);

					SetItemText(m_TotCount, 1, nPath);
					//Get File size
					DoEvents();
					if (Cf.Open(pItemText,0,0)==TRUE)
					{
						TmpVal = Cf.GetLength();
						wsprintf(szText, "%lu", TmpVal);
						if (TmpVal>1024)
						{
							double kTmpVal=TmpVal;
							double kdvTmp=kTmpVal/1024;
							TmpVal=TmpVal/1024;
							if (TmpVal>1024)
							{
								double dTmpVal=TmpVal;
								double dvTmp=dTmpVal/1024;
								CString szT=ConvertDoubleToString(dvTmp) + _T(" MB"); 
								wsprintf(szText, "%s", szT);
							}
							else
							{
								CString kszT=ConvertDoubleToString(kdvTmp) + _T(" KB"); 
								wsprintf(szText, "%s", kszT);
							}
						}
						else
							wsprintf(szText, "%lu BYTES", TmpVal);

						SetItemText(m_TotCount, 2, szText);
					}
					Cf.Close();
				}
			}
		}

		// clean up
		LocalFree(npszFile);
	}

	// Free the memory block containing the dropped-file information
	DragFinish(hDropInfo);

	// if this was a shortcut, we need to expand it to the target path
	int result=GetItemCount();
	SetItemState(result, LVIS_SELECTED | 
    LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING); 
	//m_ProgList.SetActiveItem(k);
	//m_ProgList.SetFocus();
	result--;
	EnsureVisible(result, TRUE);
	SetFocus();
	SetRedraw(TRUE);
	RedrawWindow(NULL,NULL);
	
	CListCtrl::OnDropFiles(hDropInfo);
}

CString ConvertDoubleToString(double dvTmp)
{
	CString strValue,strInt, strDecimal;
	int decimal,sign;
	double dValue = dvTmp;
	strValue = _fcvt(dValue,6,&decimal,&sign); 
		// Now decimal contains 1 because there is 
		// only one digit before the .

	strInt = strValue.Left(decimal); // strInt contains 4
	strDecimal = strValue.Mid(decimal,2); // strDecimal contains 125

	CString strFinalVal;
	strFinalVal.Format("%s.%s",strInt,strDecimal); 
	return strFinalVal;
}

void CListImageCtrl::CreateColumn()
{
	InsertColumn(0,_T("Filename"),LVCFMT_LEFT,125,-1);
	InsertColumn(1,_T("Path"),LVCFMT_LEFT,125,-1);
	InsertColumn(2,_T("Size"),LVCFMT_LEFT,75,-1);

	HIMAGELIST hScreens = ImageList_Create(THUMWIDTH, THUMHEIGHT, ILC_COLOR32, 0, 1);
	m_imageList.Attach(hScreens);

	SetImageList(&m_imageList, LVSIL_NORMAL);
	SetImageList(&m_imageList, LVSIL_SMALL);
}

HBITMAP CListImageCtrl::LoadPicture(CString mFile)
{
	CString pFSize;
    WCHAR wpath[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, mFile, -1, wpath, MAX_PATH);

    IPicture* pPic;
    OleLoadPicturePath(wpath, NULL, NULL, NULL, IID_IPicture,(LPVOID*)&pPic);
	
	if (pPic==NULL) return NULL;
    HBITMAP hPic = NULL;
    pPic->get_Handle((UINT*)&hPic);

	long nWidth=THUMWIDTH;
	long nHeight=THUMHEIGHT;

	long mWid,mHei;
	pPic->get_Height(&mHei);
	pPic->get_Width(&mWid);

	HBITMAP hPicRet = (HBITMAP)CopyImage(hPic, IMAGE_BITMAP, nWidth, nHeight , LR_COPYDELETEORG);	

	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMWIDTH;
	rcBorder.bottom=THUMHEIGHT;

	const float fRatio=(float)THUMHEIGHT/THUMWIDTH;

	int XDest, YDest, nDestWidth, nDestHeight;
	// Calculate Rect to fit to canvas
	const float fImgRatio=(float)mHei/mWid;
	if(fImgRatio > fRatio)
	{
		nDestWidth=(THUMHEIGHT/fImgRatio);
		XDest=(THUMWIDTH-nDestWidth)/2;
		YDest=0;
		nDestHeight=THUMHEIGHT;
	}
	else
	{
		XDest=0;
		nDestWidth=THUMWIDTH;
		nDestHeight=(THUMWIDTH*fImgRatio);
		YDest=(THUMHEIGHT-nDestHeight)/2;
	}

	CClientDC cdc(this);
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
	HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMWIDTH, THUMHEIGHT);
	HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
	// Draw Background
	::FillRect(hDC, &rcBorder, hBrushBk);

	// Draw Border
	::FrameRect(hDC, &rcBorder, hBrushBorder);

	HBITMAP hBmReturn= (HBITMAP)::SelectObject(hDC, pOldBitmapImage);

	CDC hdcSrc, hdcDst;

   hdcSrc.CreateCompatibleDC(NULL);
   hdcDst.CreateCompatibleDC(NULL);

   // Load the bitmaps into memory DC
   CBitmap* hbmSrcT = (CBitmap*) hdcSrc.SelectObject(hPicRet);
   CBitmap* hbmDstT = (CBitmap*) hdcDst.SelectObject(hBmReturn);

   // This call sets up the mask bitmap.
   hdcDst.BitBlt(XDest,YDest,nDestWidth, nDestHeight, &hdcSrc,0,0,SRCCOPY);	
   //hdcDst.StretchBlt(XDest,YDest,nDestWidth, nDestHeight, &hdcSrc,0,0,48,48,SRCCOPY);

	pOldBitmapImage = (HBITMAP)SelectObject(hdcDst.m_hDC,bm);

	// Release used DC and Object
	DeleteDC(hDC);
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);

    return pOldBitmapImage;

}
// this function is used to enable the system messages
// this is mainly used to display the multiple images dropped on the list control

void DoEvents(void)
{
    MSG Symsg;
    
    while(PeekMessage(&Symsg,NULL,0,0,PM_REMOVE))
    {
    TranslateMessage(&Symsg);
    DispatchMessage(&Symsg);
    }
}
