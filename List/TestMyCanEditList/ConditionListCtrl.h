#if !defined(AFX_CONDITIONLISTCTRL_H__78D44B29_DCD2_42DE_86A4_F631FCD5706E__INCLUDED_)
#define AFX_CONDITIONLISTCTRL_H__78D44B29_DCD2_42DE_86A4_F631FCD5706E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConditionListCtrl.h : header file
//
#include "MyCanEditListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CConditionListCtrl window

class CConditionListCtrl : public CMyCanEditListCtrl
{
// Construction
public:
	CConditionListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConditionListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL InitListCtrl();
	void InitItem();
	BOOL CreateChild();
	void OnComboBoxSetFocus(const int &item, const int &subitem);
	void InitColumn();
	virtual ~CConditionListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConditionListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDITIONLISTCTRL_H__78D44B29_DCD2_42DE_86A4_F631FCD5706E__INCLUDED_)
