//////////////////////////////////////////////////////////
//
//  만든이 : 서우석
// ----------------------------------------------------
//  이 소스는 공개 소스이며, 이 소스를 사용할 경우
//  반드시 저의 이름을 같이 올려주시면 감사하겠습니다. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////


#if !defined(AFX_THUMBBTN_H__29B1A498_9ED1_4DEA_9E92_B309E995BEA7__INCLUDED_)
#define AFX_THUMBBTN_H__29B1A498_9ED1_4DEA_9E92_B309E995BEA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThumbBtn.h : header file
//

#define IDC_THUMB			33333		// ThumbCtl을 위한 컨트롤 상수

//////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////
class CThumbCtl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CThumbCtl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x1d2b4f40, 0x1f10, 0x11d1, { 0x9e, 0x88, 0x0, 0xc0, 0x4f, 0xdc, 0xab, 0x92 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	BOOL displayFile(LPCTSTR bsFileName);
	BOOL haveThumbnail();
	CString FreeSpace();
	CString UsedSpace();
	CString TotalSpace();
};
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CThumbBtn window

class CThumbBtn : public CButton
{
// Construction
public:
	CThumbBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetURL(CString strURL);
	virtual ~CThumbBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CThumbBtn)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

// 변수들
protected:
	CThumbCtl	m_ctrThumb;		// CThumbCtl 객체 생성.
	CString		m_strURL;		// CThumbCtl 에서 사용하게될 URL 주소 변수
};





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBBTN_H__29B1A498_9ED1_4DEA_9E92_B309E995BEA7__INCLUDED_)
