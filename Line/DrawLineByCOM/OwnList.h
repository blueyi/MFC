// OwnList.h : header file
//

#ifndef __OWNLIST_H__
#define __OWNLIST_H__

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox window

class COwnerDrawListBox : public CListBox
{
// Construction
public:
	COwnerDrawListBox();

// Attributes
private:
	COLORREF m_nColor;
	CString  m_szName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnerDrawListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COwnerDrawListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(COwnerDrawListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif __OWNLIST_H__	// end define of COwnerDrawListBox
