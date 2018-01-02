// ButtonMine.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonMine.h"

#include<afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

ButtonMine::ButtonMine()
{
	p_Tip=0;
}

ButtonMine::~ButtonMine()
{
	delete p_Tip;
}

void ButtonMine::P_GetColorToByte3(COLORREF clr, BYTE *pb)
{
	BYTE*p=(BYTE*)&clr;
	pb[0]=p[2];
	pb[1]=p[1];
	pb[2]=p[0];
}

BEGIN_MESSAGE_MAP(ButtonMine, CButton)
	//{{AFX_MSG_MAP(ButtonMine)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ENABLE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL ButtonMine::SetImage(int iBmpID,LPCSTR pszToolTip,COLORREF clrBkgnd,BOOL bAutoSize,BOOL bNormalDisable)
{
	BOOL b=SetImage(iBmpID,clrBkgnd,bAutoSize,bNormalDisable);
	if(b==0)	return 0;
	SetToolTip(pszToolTip);
	return 1;
}
BOOL ButtonMine::SetImage(LPCSTR pszFile,LPCSTR pszToolTip,COLORREF clrBkgnd,BOOL bAutoSize,BOOL bNormalDisable)
{
	BOOL b=SetImage(pszFile,clrBkgnd,bAutoSize,bNormalDisable);
	if(b==0)	return 0;
	SetToolTip(pszToolTip);
	return 1;
}

BOOL ButtonMine::SetImage(LPCSTR pszFile,COLORREF clrBkgnd,BOOL bAutoSize,BOOL bNormalDisable)
{
	USES_CONVERSION;
	IPicture*pPicture=0;
	COLORREF clrBk=RGB(255,255,255);

	//return hr
	BOOL b=::OleLoadPicturePath(T2OLE(pszFile),0,0,clrBkgnd,IID_IPicture,(LPVOID*)&pPicture)?0:1;
	if(pPicture==0)	b=0;
	if(b)
	{
		TheScreenDC dcScreen;
		if(dcScreen.Create()==0)	return 0;
		TheMemDC	dcMem;

		b=dcMem.CreateCompatibleDC(dcScreen.hDC);

		if(b)
		{
			long iW;
			long iH;

			pPicture->get_Width(&iW);
			pPicture->get_Height(&iH);
			
			int iMdW=MulDiv(iW,::GetDeviceCaps(dcScreen.hDC,LOGPIXELSX),2540);
			int iMdH=MulDiv(iH,::GetDeviceCaps(dcScreen.hDC,LOGPIXELSY),2540);

			b=dcMem.CreateBitmap(dcScreen.hDC,iMdW,iMdH);
			//return hr
			b=pPicture->Render(dcMem.dc.m_hDC,0,0,iMdW,iMdH,0,iH,iW,-iH,0)?0:1;
			if(b)
			{
			HBITMAP hBmpSrc=(HBITMAP)dcMem.bmp.GetSafeHandle();
				b=P_CreateBuffers(dcMem.dc.m_hDC,hBmpSrc,clrBkgnd,bNormalDisable);
				
			}
		}
		pPicture->Release();
	}
	return b;
}

BOOL ButtonMine::SetImage(int iBmpID,COLORREF clrBkgnd,BOOL bAutoSize,BOOL bNormalDisable)
{
	inf.bAutoSize=bAutoSize;

	//------------------------------- create 24 bits bitmaps
	CBitmap bmp;
	if(bmp.LoadBitmap(iBmpID)==0)	return 0;

	TheScreenDC dcScreen;
	if(dcScreen.Create()==0)	return 0;
	TheMemDC	dcMem;
	if(dcMem.CreateCompatibleDC(dcScreen.hDC)==0)	return 0;
	if(dcMem.SelectObject(&bmp)==0)	return 0;

	HBITMAP hBmpSrc=(HBITMAP)bmp.GetSafeHandle();

	BOOL b=P_CreateBuffers(dcMem.dc.m_hDC,hBmpSrc,clrBkgnd,bNormalDisable);
	if(b)	P_InitButton();
	return b;
}


BOOL ButtonMine::P_CreateBuffers(HDC hDC, HBITMAP hBmp,COLORREF clrBkgnd,BOOL bNormalDisable)
{
	BITMAP bp;
	::GetObject(hBmp,sizeof(BITMAP),&bp);
	const CSize siSrc(bp.bmWidth,bp.bmHeight);

	BITMAPINFO bi;
	memset(&bi,0,sizeof(BITMAPINFO));
	BITMAPINFOHEADER&bh=bi.bmiHeader;
	bh.biSize=sizeof(BITMAPINFOHEADER);

	int iScan=::GetDIBits(hDC,hBmp,0,siSrc.cy,0,&bi,DIB_RGB_COLORS);

	if(iScan==0)	return 0;

	int i=siSrc.cx*3;
	while(i%4)	i++;

	const int iRowByteSrc=i;
	const int iSizeBufSrc=iRowByteSrc*siSrc.cy;

	BYTE*pbBufSrc=new BYTE[iSizeBufSrc];
	if(pbBufSrc==0)	return 0;

	bh.biClrUsed=0;
	bh.biCompression=0;
	bh.biBitCount=24;
	bh.biSizeImage=iSizeBufSrc;
	iScan=::GetDIBits(hDC,hBmp,0,siSrc.cy,pbBufSrc,&bi,DIB_RGB_COLORS);
	
	if(iScan!=siSrc.cy)	
	{
		delete []pbBufSrc;
		return 0;
	}

	//make button image 2x2 pixels larger than source image,
	//so disabled images are nicer
	const int iBtnW=siSrc.cx+2;
	const int iBtnH=siSrc.cy+2;

	i=iBtnW*3;
	while(i%4)	i++;
	const int iRowByteTgt=i;
	const int iSizeBufTgt=iRowByteTgt*iBtnH;

	if(	(bmp_Nml.CreateBuffer(iSizeBufTgt)==0)||
		(bmp_Dis.CreateBuffer(iSizeBufTgt)==0))
	{
		delete []pbBufSrc;
		return 0;
	}

	//referece colors
	BYTE btBack[3],btFace[3];
	P_GetColorToByte3(clrBkgnd,btBack);
	P_GetColorToByte3(::GetSysColor(COLOR_BTNFACE),btFace);

	int iy,ix;
	BYTE*pbY0,*pb0;
	BYTE*pbY1,*pb1;

	//clear bkgnd
	pbY0=bmp_Nml.pbBuf;
	pbY1=bmp_Dis.pbBuf;

	for(iy=0;iy<iBtnH;iy++)
	{
		pb0=pbY0;
		pb1=pbY1;
		for(ix=0;ix<iBtnW;ix++)
		{
			pb0[0]=pb1[0]=btFace[0];
			pb0[1]=pb1[1]=btFace[1];
			pb0[2]=pb1[2]=btFace[2];

			pb0+=3;
			pb1+=3;
		}
		pbY0+=iRowByteTgt;
		pbY1+=iRowByteTgt;
	}

	//copy source bitmap into normal buffer
	pbY0=pbBufSrc;
	pbY1=bmp_Nml.pbBuf+iRowByteTgt;
	int ix1;

	for(iy=0;iy<siSrc.cy;iy++)
	{
		pb0=pbY0;
		pb1=pbY1;

		pb1+=3;
		//source button width
		for(ix1=0;ix1<siSrc.cx;ix1++)
		{
			if((pb0[0]!=btBack[0])||(pb0[1]!=btBack[1])||(pb0[2]!=btBack[2]))
			{
				pb1[0]=pb0[0];
				pb1[1]=pb0[1];
				pb1[2]=pb0[2];
			}

			pb0+=3;
			pb1+=3;
		}

		pbY0+=iRowByteSrc;
		pbY1+=iRowByteTgt;
	}

	//end of copy
	delete []pbBufSrc;

	//modify bitmap-info-header
	bh.biWidth		=iBtnW;
	bh.biHeight		=iBtnH;
	bh.biSizeImage	=iSizeBufTgt;

	//set to classes
	memcpy(&inf.bih,&bh,sizeof(BITMAPINFOHEADER));

	//-------------- make disabled bitmap
	pbY0=bmp_Nml.pbBuf+iRowByteTgt;
	pbY1=bmp_Dis.pbBuf+iRowByteTgt;
	
	BYTE*pt;

	//make white first
	for(iy=1;iy<iBtnH-1;iy++)
	{
		pb0=pbY0+3;
		pb1=pbY1+3;
		for(ix=1;ix<iBtnW-1;ix++)
		{
			if((pb0[0]!=btFace[0])||(pb0[1]!=btFace[1])||(pb0[2]!=btFace[2]))
			{
				if(bNormalDisable)
				{
					pt=pb1+3;
					pt-=iRowByteTgt;
					pt[0]=255;
					pt[1]=255;
					pt[2]=255;
				}
				else
				{
					pt=pb1-3;
					pt+=iRowByteTgt;
					pt[0]=255;
					pt[1]=255;
					pt[2]=255;
				}
			}
			pb0+=3;
			pb1+=3;
		}
		pbY0+=iRowByteTgt;
		pbY1+=iRowByteTgt;
	}

	//simple math: iMax=dbK*Value+iMin, where Value is from 0 to 255
	int iv=(btFace[0]+btFace[1]+btFace[2])/3;
		
	const int iMin=(iv+64)/2;
	const int iMax=235;
	const double dbK=(iMax-iMin)/255.00;

	pbY0=bmp_Nml.pbBuf+iRowByteTgt;
	pbY1=bmp_Dis.pbBuf+iRowByteTgt;
	for(iy=1;iy<iBtnH-1;iy++)
	{
		pb0=pbY0;
		pb1=pbY1;
		for(ix=0;ix<iBtnW;ix++)
		{
			if((pb0[0]!=btFace[0])||(pb0[1]!=btFace[1])||(pb0[2]!=btFace[2]))
			{
				iv=(pb0[0]+pb0[1]+pb0[2])/3;
				iv=(int)(dbK*iv+iMin);

				pb1[0]=iv;
				pb1[1]=iv;
				pb1[2]=iv;
			}
			pb0+=3;
			pb1+=3;
		}
		pbY0+=iRowByteTgt;
		pbY1+=iRowByteTgt;
	}

	return 1;
}

void ButtonMine::P_InitButton()
{
	if(inf.bInit!=0)			return;
	if(inf.bAutoSize==0)		return;
	if(::IsWindow(m_hWnd)==0)	return;
	inf.bInit=1;

	CRect rc;

	const BITMAPINFOHEADER&bih=inf.bih;
	GetWindowRect(&rc);
	rc.right	=rc.left+bih.biWidth+6;
	rc.bottom	=rc.top+bih.biHeight+6;
	::MapWindowPoints(0,GetParent()->m_hWnd,(POINT*)&rc,2);
	MoveWindow(&rc);
	RedrawWindow();
}

void ButtonMine::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	RedrawWindow();	
}

void ButtonMine::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	RedrawWindow();	
}

void ButtonMine::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	RedrawWindow();	
}

void ButtonMine::P_Draw3dRect(CDC &dc, const CRect &rc, CPen &penTL, CPen &penBR)
{
	dc.MoveTo(rc.left,rc.bottom);
	dc.SelectObject(&penTL);
	dc.LineTo(rc.left,rc.top);
	dc.LineTo(rc.right,rc.top);
	dc.SelectObject(&penBR);
	dc.LineTo(rc.right,rc.bottom);
	dc.LineTo(rc.left,rc.bottom);
}

void ButtonMine::OnPaint() 
{
	P_InitButton();
	
	CPaintDC dc(this);

	BITMAPINFOHEADER&bih=inf.bih;

	CRect rc;
	GetClientRect(&rc);

	int iX0=(rc.Width()-bih.biWidth)/2;
	int iY0=(rc.Height()-bih.biHeight)/2;

	if(inf.bBtnDn)
	{
		iX0++;
		iY0++;
	}

	BYTE*pb;
	const BOOL bEnable=IsWindowEnabled();
	if(bEnable)	pb=bmp_Nml.pbBuf;
	else	pb=bmp_Dis.pbBuf;

	::StretchDIBits(dc.m_hDC,
					iX0,iY0,bih.biWidth,bih.biHeight,
					0,	0,	bih.biWidth,bih.biHeight,
					pb,(BITMAPINFO*)&bih,
					DIB_RGB_COLORS,
					SRCCOPY);

	CPen penB(PS_SOLID,1,RGB(0,0,0));
	CPen penW(PS_SOLID,1,RGB(255,255,255));

	CPen*pPenOld=dc.SelectObject(&penB);

	if(inf.bBtnDn==0)
	{
		P_Draw3dRect(dc,rc,penW,penB);
		if(inf.bWeaker==0)	
		{
			rc.DeflateRect(1,1);
			P_Draw3dRect(dc,rc,penW,penB);
		}
	}
	else
	{
		P_Draw3dRect(dc,rc,penB,penW);
		if(inf.bWeaker==0)	
		{
			rc.DeflateRect(1,1);
			P_Draw3dRect(dc,rc,penB,penW);
		}
	}

	if(inf.bShowFocus&&(GetFocus()==this))
	{
		rc.DeflateRect(2,2,3,3);

		int iV=64;
		LOGBRUSH lp;
		lp.lbStyle=BS_SOLID;
		lp.lbColor=RGB(iV,iV,iV);
		lp.lbHatch=0;

		CPen pen(PS_GEOMETRIC|PS_DOT,1,&lp);
		P_Draw3dRect(dc,rc,pen,pen);
	}

	dc.SelectObject(pPenOld);
}

void ButtonMine::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CButton::OnLButtonDown(nFlags, point);
	if(IsWindowEnabled()==0)	return;
	SetCapture();
	inf.bBtnDn=1;
	RedrawWindow();
}

void ButtonMine::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CButton::OnLButtonUp(nFlags, point);

	if(inf.bBtnDn==0)	return;
	ReleaseCapture();

	inf.bBtnDn=0;
	RedrawWindow();

	CRect rc;
	GetClientRect(&rc);
	if(rc.PtInRect(point)==0)	return;
	P_PostMessage(0);
}

BOOL ButtonMine::PreTranslateMessage(MSG*pMsg) 
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			inf.bBtnDn=1;
			RedrawWindow();
			P_PostMessage(pMsg->wParam==VK_SPACE);
			break;
		}
		break;
	case WM_KEYUP:
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			inf.bBtnDn=0;
			RedrawWindow();
			break;
		}
		break;
	case WM_MOUSEMOVE:
		if(p_Tip)
		{
			p_Tip->RelayEvent(pMsg);
		}
		break;
	}
	return CButton::PreTranslateMessage(pMsg);
}

void ButtonMine::P_PostMessage(BOOL bKeySpace)
{
	UINT wParam=::GetWindowLong(m_hWnd,GWL_ID);
	if(bKeySpace)	wParam|=(1L<<16);
	GetParent()->PostMessage(WM_COMMAND,wParam,(UINT)m_hWnd);
}

void ButtonMine::SetToolTip(LPCSTR pszToolTip)
{
	CWnd*pMum=GetParent();

	delete p_Tip;
	p_Tip=new CToolTipCtrl;
	p_Tip->Create(pMum);
	
	CString cs=' ';
	cs+=pszToolTip;
	cs+=' ';
	p_Tip->AddTool(this,cs);
}
