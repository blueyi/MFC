#if !defined(AFX_MYCANEDITLISTCTRL_H__4CB83AA6_356A_4A64_9E2B_7D71C8D7410A__INCLUDED_)
#define AFX_MYCANEDITLISTCTRL_H__4CB83AA6_356A_4A64_9E2B_7D71C8D7410A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCanEditListCtrl.h : header file
//
#include "Afxtempl.h"
#include "MyListCtrl.h"

#include <afxtempl.h>
#define QUERY_SETNEXTITEMPHFOCUS WM_USER+15
#define QUERY_MESSAGE_EDIT_MOVED WM_USER+16
#define QUERY_MESSAGE_EDIT_ESC	 WM_USER+17
#define QUERY_MESSAGE_EDIT_RETURN WM_USER+18
#define ID_VALUE   50000
#define ID_COMBOBOX   50000
/////////////////////////////////////////////////////////////////////////////
// CCMyChildComboBox window

class CMyChildComboBox : public CComboBox
{
// Construction
public:
	CMyChildComboBox();

// Attributes
public:
	CFont m_ComboBoxfont;
	BOOL m_bSelectValid;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChildComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyChildComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyChildComboBox)
	afx_msg void OnKillfocus();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetfocus();
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASELIST_H__74D65B38_5927_45EB_BA9A_52C17672BF06__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
// CMyChildEdit window

class CMyChildEdit : public CEdit
{
// Construction
public:
	CMyChildEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyChildEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont		m_font;
	BOOL		m_breturn;
	BOOL		m_besc;
	

	long		m_dSetFocusValue;
	long		m_dKillFocusValue;
	long		kc_number;
	BOOL m_bInputValid;
	virtual ~CMyChildEdit();

	// Generated message map functions
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CMyChildEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChange();
	
	//afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

/////////////////////////////////////////////////////////////////////////////
// CMyCanEditListCtrl window

class CMyCanEditListCtrl : public CMyListCtrl
{
public:
	
	BOOL m_bIsEdit,m_bIsComboBox;
	CStringArray m_strArrColumnFmt;
	BOOL m_bValueChanged;//后来加的,用来判断ListCtrl是否被编辑过
	CDocument *m_pDocument;
public:
	
	CMyChildComboBox m_ComboBox;
	CMyChildEdit m_edit;//值
	CMyChildComboBox m_relation;

	int m_nItem;				//被编辑表项的行号
	int m_nSubItem;				//被编辑表项的列号
	int m_iEditedIndex;
protected:
								//编辑控件
	int CountCanEdited;
	bool			m_bSetValue;
	int				m_iStopDestroy;
	BOOL m_Next;
	CList<int,int>	m_iColumnEdited;
	enum KILL{NORMALKILL=0,ESCKILL=1,RETURNKILL=2};

	CString			m_sSetFocus;

	CList<int,int>	m_iColumnComboBox;

protected:
	CRect			m_rectWindow;


	KILL			m_Kill;
// Construction
public:
	CMyCanEditListCtrl();
	virtual ~CMyCanEditListCtrl();
	void EndEdit( BOOL bValidate ,int nSubItem);
	BOOL BeginEdit(int nitem,int nSubItem);
	bool			m_bWaitPopList;

	CFont m_Listfont;
// Attributes
public:
	friend class CMyChildEdit;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCanEditListCtrl)
	protected:
	virtual void PreSubclassWindow();
	virtual	BOOL PreTranslateMessage(MSG* pMsg) ;
	//}}AFX_VIRTUAL

// Implementation
public:
	bool SetSubItemUnListBox(const int& subitem);
	bool SetSubItemCanListBox(const int& subitem);
	bool IsTheSubItemCanListBox(const int& subitem);
	void DeleteSelectedByVK_DELETE();
	virtual bool DeleteSelected();
	bool Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID);
	void SetValueUnChange(CString sql,int nSubItem);
	bool SetTheEditFocus(const int& item,const int& subitem);
	bool IsTheSubItemCanEdited(const int& subitem);
	bool SetSubItemUnEdited(const int& subitem);
	int GetCountCanEdited();
	int GetSubItemNumber();
	bool SetSubItemCanEdited(const int& subitem);
	virtual void PreOnEditChar(const int& item, const int& subitem,UINT& key);

	// Generated message map functions
//protected:
public:
	void SetChildComboBoxFontSize(int fontsize);
	void SetChildEditFontSize(int fontsize);
	void SetListCtrlFontSize(int fontsize);
	CFont* GetChildComboBoxFont();
	CFont* GetChildEditFont();
	CFont* GetListCtrlFont();
	void SetChildComboBoxFont(LOGFONT logfont);
	void SetChildEditFont(LOGFONT logfont);
	void SetListCtrlFont(LOGFONT logfont);
	CDocument* GetDocument();
	void SetDocument(CDocument *pDocument);
	BOOL IsModified();
	void SetModifiedFlag(BOOL bModified);
	virtual BOOL InitListCtrl();
	virtual void InitColumn();
	virtual BOOL CreateChild();
	BOOL IsInt(CString szInt);
	BOOL IsNumber(CString szNum);
	BOOL BeginSelect(int nItem,int nSubItem);
	void EndSelect(BOOL bValidate,int nSubItem);
	virtual void InitItem();
	virtual void OnEditUDNPMessage(const int& item,const int& subitem,UINT key);
	virtual void OnESC(const int& item, const int& subitem);
	virtual bool OnEditReturn(const int& item,const int& subitem);
	virtual void OnEditSetFocus(const int& item,const int& subitem);
	virtual void OnEditKillFocus(const int& item,const int& subitem);
	virtual void OnNewEditChange(const int& item,const int& sub_item);
	virtual void OnComboBoxSetFocus(const int& item,const int& subitem);
	//{{AFX_MSG(CMyCanEditListCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	virtual afx_msg LRESULT SetNextItemFocus(WPARAM wParam,LPARAM lParam);
	virtual afx_msg LRESULT OnParentMoved(WPARAM wParam,LPARAM lParam);
	//注意,自定义消息的处理函数，必须定义如下：
    //afx_msg LRESULT OnMyMessage(WPARAM, LPARAM);
    //返回值必须是LRESULT型，否则Debug会过，而Release出错、同时，WPARAM,LPARAM这两个参数一定要申明，否则Release版本能运行，但肯定错误。切记。


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
