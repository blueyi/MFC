#if !defined(AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_)
#define AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NeuListCtrl.h : header file
//
#define MESSAGE_NONE 909090

#include <afxcoll.h>
#include <afxtempl.h>

enum enCONTROLTYPE { EDITBOX,COMBOBOX,LISTBOX,CHECKBOX,BUTTON,NONE} ;

struct ControlMessageInfo
{
	int m_iMessageID;
	void (* pEventHandler)(LPVOID lpVoid);
	ControlMessageInfo()
	{
		m_iMessageID = MESSAGE_NONE;
	}
};
struct SubItemControlsInfo
{
	enCONTROLTYPE m_enControlType;
	int m_iItemIndex;
	CWnd * m_pWnd;
	COLORREF m_BKColor;
	SubItemControlsInfo()
	{
		m_enControlType = NONE;
		m_iItemIndex = -1;
		m_pWnd = NULL;
		m_BKColor = RGB(255,255,255);//GetSysColor(COLOR_BTNFACE);
	}
	CArray<ControlMessageInfo,ControlMessageInfo> m_arrControlMessageInfo;
};


/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl window

class CNeuListCtrl : public CListCtrl
{
// Construction
public:
	CNeuListCtrl();

// Attributes
public:

// Operations
public:
		void MapControlsForSubItems();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeuListCtrl)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReleaseControls();
	void AdjustControlsAccordingToHeaderWidth(HD_NOTIFY * pNotify);
	void AttachEvent_HandlerForItemControl(int iIndex,UINT unMessage,void (*pEventHandler)(LPVOID lpvoid));
	BOOL AddToControlsData(int iIndex, CString strData);
	void ShowControls(BOOL bShow);
	void EnableControls(BOOL bEnable);
	void SetItemControl(enCONTROLTYPE enControlType,int iIndex);
	void SetControlBKColor(int index ,COLORREF col);
	virtual ~CNeuListCtrl();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

	// Generated message map functions
protected:
	CString m_strMinVal;
	//{{AFX_MSG(CNeuListCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
protected:
	CPtrArray *m_pControlPtrArray;
private:
	BOOL DetachControl(int index);
	int ControlIndexDuplicating(int iIndex);
	void GetAndDisplayControlsData();
	
	void SetListItemsDataToControls();
	int m_iCurSelctedItemIndex;
	int m_iSubItem;
	int m_iControlIDCounter;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_)
