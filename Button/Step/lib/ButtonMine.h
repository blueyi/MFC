#if !defined(AFX_BUTTONMINE_H__19D7B86D_FF95_45A6_8BA2_FBC66A6AD0EF__INCLUDED_)
#define AFX_BUTTONMINE_H__19D7B86D_FF95_45A6_8BA2_FBC66A6AD0EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonMine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ButtonMine window

class ButtonMine : public CButton
{
// Construction
public:
	ButtonMine();
	virtual ~ButtonMine();

	BOOL SetImage(int iBmpID,COLORREF clrBkgnd=RGB(192,192,192),BOOL bAutoSize=TRUE,BOOL bNormalDisable=TRUE);
	BOOL SetImage(int iBmpID,LPCSTR pszToolTip,COLORREF clrBkgnd=RGB(192,192,192),BOOL bAutoSize=TRUE,BOOL bNormalDisable=TRUE);

	BOOL SetImage(LPCSTR pszFile,COLORREF clrBkgnd,BOOL bAutoSize=TRUE,BOOL bNormalDisable=TRUE);
	BOOL SetImage(LPCSTR pszFile,LPCSTR pszToolTip,COLORREF clrBkgnd,BOOL bAutoSize=TRUE,BOOL bNormalDisable=TRUE);

	void SetToolTip(LPCSTR pszToolTip);

	BOOL GetShowFocus()
	{
		return inf.bShowFocus;
	}
	void SetShowFocus(BOOL bShowFocus)
	{
		inf.bShowFocus=bShowFocus;
		RedrawWindow();
	}
	BOOL GetWeaker()	
	{
		return inf.bWeaker;
	}
	void SetWeaker(BOOL bWeaker)	
	{
		inf.bWeaker=bWeaker;
		RedrawWindow();
	}

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ButtonMine)
	public:
	virtual BOOL PreTranslateMessage(MSG*pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(ButtonMine)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnSetFocus(CWnd*pOldWnd);
	afx_msg void OnKillFocus(CWnd*pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	//******************************************
	class TheBitmap
	{
	public:
		TheBitmap()
		{
			pbBuf=0;
		}
		~TheBitmap()
		{
			delete []pbBuf;
		}
		BOOL CreateBuffer(int iSize)
		{
			delete []pbBuf;
			pbBuf=new BYTE[iSize];
			return pbBuf?1:0;
		}

	public:
		BYTE*pbBuf;

	}bmp_Nml,bmp_Dis;	//normal and disabled bitmaps

private:
	class TheInf
	{
	public:
		TheInf()
		{
			bInit	=0;
			bBtnDn	=0;
			bWeaker	=0;
			bShowFocus	=1;
		}
		BYTE	bInit;
		BYTE	bAutoSize;
		BYTE	bBtnDn;
		BYTE	bWeaker;
		BYTE	bShowFocus;
		
		BITMAPINFOHEADER bih;
	}inf;

	CToolTipCtrl*p_Tip;

private:
	BOOL P_CreateBuffers(HDC hDC,HBITMAP hBmp,COLORREF clrBkgnd,BOOL bNormalDisable);
	void P_PostMessage(BOOL bKeySpace);
	void P_Draw3dRect(CDC&dc,const CRect&rc,CPen&penTL,CPen&penBR);
	void P_InitButton();
	void P_GetColorToByte3(COLORREF clr,BYTE*pb);

	//-------- DCs,just for easy
	class TheScreenDC
	{
	public:
		BOOL Create()
		{
			hDC=::GetDC(0);
			return hDC?1:0;
		}
		~TheScreenDC()
		{
			if(hDC)	::ReleaseDC(0,hDC);
		}
		HDC hDC;
	};

	class TheMemDC
	{
	public:
		TheMemDC()
		{
			pBmpOld=0;
		}
		~TheMemDC()
		{
			if(pBmpOld)	dc.SelectObject(pBmpOld);
		}

		BOOL CreateCompatibleDC(HDC hDC)
		{
			CDC*pDC=CDC::FromHandle(hDC);
			return dc.CreateCompatibleDC(pDC);
		}

		BOOL SelectObject(CBitmap*pBmp)
		{
			pBmpOld=dc.SelectObject(pBmp);
			return pBmpOld?1:0;
		}
		BOOL CreateBitmap(HDC hDC,int iW,int iH)
		{
			CDC*pDC=CDC::FromHandle(hDC);
			BOOL b=bmp.CreateCompatibleBitmap(pDC,iW,iH);
			if(b)
			{
				pBmpOld=dc.SelectObject(&bmp);
			}
			return pBmpOld?1:0;
		}

		CDC dc;
		CBitmap bmp,*pBmpOld;
	};

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONMINE_H__19D7B86D_FF95_45A6_8BA2_FBC66A6AD0EF__INCLUDED_)
