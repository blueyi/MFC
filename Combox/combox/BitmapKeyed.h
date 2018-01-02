#if !defined(AFX_BITMAPKEYED_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_BITMAPKEYED_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_
// Download by http://www.codefans.net
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBitmapKeyed window

void AFXAPI DDX_KeyedBitmap(CDataExchange *pDX, int nIDC, int idBitmap, int idBitmapKey);

/////////////////////////////////////////////////////////////////////////////
// CBitmapKeyed window

class CBitmapKeyed : public CStatic
{
// Construction
public:
    DECLARE_DYNCREATE(CBitmapKeyed);

// Attributes
public:
    int idBitmap;
    int idBitmapKey;

    CBitmap Bitmap;
    CBitmap BitmapKey;

   CString m_tooltipOverride;

// Operations
public:

// Overrides
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBitmapKeyed)
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    void Init (CWnd *pParent, int nIDC, int idBitmap, int idBitmapKey);

protected:
	 CToolTipCtrl m_ToolTip;				// The link tooltip	
    void SetWindowSize();

    // Generated message map functions
protected:
    //{{AFX_MSG(CBitmapKeyed)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint(void);
    //}}AFX_MSG
    afx_msg UINT OnNcHitTest(CPoint point);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPKEYED_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
