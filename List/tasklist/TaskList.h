//*******************************************************************
//* TASKLIST.H - CTaskList interface                                *
//*                                                                 *
//*	Implements a priority based drop down task list using an	    *
//* ownerdrawn CComboBox. The listbox is sorted by priority level   *
//*														            *
//* October 06 / 2002										        *
//*														            *
//* Copyright PCSpectra 2002 (Free for any purpose, except to sell) *
//* Website: www.pcspectra.ca                                       *
//*														            *
//* Public methods:                                                 *
//* ===============                                                 *
//* AddTask() - Adds a task with a specified priority level to list *
//* GetTask() - Returns the indexed task text comment use           *
//*             GetPriority() to return the priority level          *
//*                                                                 *
//* SetCheck() - Set currently indexed item check state             *
//* GetCheck() - Returns check state of item at index               *
//*                                                                 *
//* SetColors() - Sets all priority colors                          *
//* GetColorLevelX() - Returns color for X priority level           *
//*                                                                 *
//* SetPriority() - Changes an items priority and "should" resort   *
//* GetPriority() - Returns an items current priority level         *
//*                                                                 *
//*                                                                 *
//* Notes:                                                          *
//* ======															*
//*	None   														    *
//*                                                                 *
//* History:														*
//*	========														*
//* Month dd/yyyy - None so far                             		*
//*******************************************************************

#ifndef AFX_TASKLIST_H_INCLUDED_
#define AFX_TASKLIST_H_INCLUDED_

// Compile this inclusion file only once
#pragma once

// Interface

class CTaskList : public CComboBox
{
public:
	CTaskList();	
	virtual ~CTaskList(){}

	// Content management
	void AddTask(UINT nLevel, CString strComment);
	CString GetTask(UINT nIndex) const;

	// Get and Set items priority levels
	UINT GetPriority(UINT nIndex) const;
 	void SetPriority(UINT nIndex, UINT nLevel=1 /* LOW_PRIORITY */);

	// Set and Get items check state
	void SetCheck(UINT nIndex, BOOL bChecked=TRUE){	SetItemData(nIndex, bChecked ? TRUE : FALSE); }
	BOOL GetCheck(UINT nIndex) const { return GetItemData(nIndex); }

	// Set and Get priority colors
	void SetColors(COLORREF clrNormal, COLORREF clrUrgent, COLORREF clrHigh)
	{ m_clrLevel1=clrNormal; m_clrLevel2=clrUrgent; m_clrLevel3=clrHigh; }

	COLORREF GetColorLevel1() const { return m_clrLevel1; }
	COLORREF GetColorLevel2() const { return m_clrLevel2; }
	COLORREF GetColorLevel3() const { return m_clrLevel3; }

	// Overloaded functions
	int FindString(int nStartAfter, LPCTSTR lpszString) const
	{
		CString buff(lpszString);

		// Find string but ignore priority code
		return CComboBox::FindString(nStartAfter, buff.Mid(1));
	}
protected:
	//{{AFX_VIRTUAL(CTaskList)
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
	// Allow variable size to be checked (HAS no effect other to avoid assertion)
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS){} 
	//}}AFX_VIRTUAL
protected:
	static LRESULT ComboBoxListBoxProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CTaskList)
	afx_msg void OnDropdown(){ 	RecalcDropWidth();	}
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	
	// Recalculate the width required to display all text inside listbox
	void RecalcDropWidth();

	// Allow subclassing of the drop down listbox
	LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);

	// You cannot use this function, use AddTask() instead
	int AddString(LPCTSTR lpszString){ return CComboBox::AddString(lpszString); }
	int InsertString(int nIndex, LPCTSTR lpszString){ return CComboBox::InsertString(nIndex, lpszString); }
	int DeleteString(UINT nIndex){ return CComboBox::DeleteString(nIndex); }
	int Dir(UINT attr, LPCTSTR lpszWildCard){ return CComboBox::Dir(attr, lpszWildCard); }
	int SetItemData(int nIndex, DWORD dwItemData){ return CComboBox::SetItemData(nIndex, dwItemData); }
	DWORD GetItemData( int nIndex ) const { return CComboBox::GetItemData(nIndex); }
	void SetHorizontalExtent(UINT nExtent){ CComboBox::SetHorizontalExtent(nExtent); }
	int SetDroppedWidth(UINT nWidth){ return CComboBox::SetDroppedWidth(nWidth); }
	int SetItemHeight(int nIndex, UINT cyItemHeight){ return CComboBox::SetItemHeight(nIndex, cyItemHeight); }
	void ShowDropDown(BOOL bShowIt=TRUE){ CComboBox::ShowDropDown(bShowIt); }
	int SetExtendedUI(BOOL bExtended=TRUE){ return CComboBox::SetExtendedUI(bExtended); }

private:
	// priority colors
	COLORREF m_clrLevel1, m_clrLevel2, m_clrLevel3;

	// Subclassed drop down listbox
	HWND m_hListBox;
};

//{{AFX_INSERT_LOCATION}}
#endif // AFX_TASKLIST_H_INCLUDED_
