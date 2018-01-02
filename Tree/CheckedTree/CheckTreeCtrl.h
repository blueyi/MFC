//#######################################################################################
//## CheckTreeCtrl.h : header file
//## [Magerusan G. Cosmin] 20-apr-2002
//#######################################################################################
#if !defined(__CHECKTREECTRL_H__)
#define __CHECKTREECTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//## ====================================================================================
#define IMG_OPEN	0L
#define IMG_CLOSE	1L
#define IMG_ITEM	2L
//#######################################################################################
class CCheckTreeCtrl : public CTreeCtrl
{
//## CONSTRUCTOR
public:
	CCheckTreeCtrl();
	virtual ~CCheckTreeCtrl();

//## STATE
private:
	CWnd *m_pwndParentCombo;
	BOOL m_bUpdateNeeded;

//## MESSAGES
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

//## UPDATE methods
private:
	void UpdateItemImage(HTREEITEM hItem);
	void RecursiveUpdateFromState(HTREEITEM hParentItem);
	void UpdateParentWnd();
public:
	void UpdateToState();
	void UpdateFromState();

//## METHODS
public:
	void Populate();
	void SetParentCombo(CWnd *pwnd){ m_pwndParentCombo = pwnd; };

//## TREE Specific
private:
	BOOL GetItemExpanded(HTREEITEM hItem);
};
//#######################################################################################
#endif // !defined(__CHECKTREECTRL_H__)
//#######################################################################################
