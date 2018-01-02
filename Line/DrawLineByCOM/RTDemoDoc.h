// RTDemoDoc.h : interface of the CRTDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTDemoDOC_H__12551281_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
#define AFX_RTDemoDOC_H__12551281_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRTDemoView;
class CRTDemoDoc : public CDocument
{
protected: // create from serialization only
	CRTDemoDoc();
	DECLARE_DYNCREATE(CRTDemoDoc)

// Attributes
public:
	bool	 m_bMemDraw;
	bool	 m_bTitle;
	bool	 m_bBoundary;
	bool	 m_bGrid;
	bool	 m_bVertical;
	COLORREF m_nBkColor;

	CRTDemoView* pView;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRTDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRTDemoDoc)
	afx_msg void OnTypeGrid();
	afx_msg void OnUpdateTypeGrid(CCmdUI* pCmdUI);
	afx_msg void OnTypeBoundary();
	afx_msg void OnUpdateTypeBoundary(CCmdUI* pCmdUI);
	afx_msg void OnTypeBackcolor();
	afx_msg void OnUpdateTypeBackcolor(CCmdUI* pCmdUI);
	afx_msg void OnTypeTitle();
	afx_msg void OnUpdateTypeTitle(CCmdUI* pCmdUI);
	afx_msg void OnTypeMemorydraw();
	afx_msg void OnUpdateTypeMemorydraw(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTDemoDOC_H__12551281_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
