// SpinnerTBDoc.h : interface of the CSpinnerTBDoc class
//
/////////////////////////////////////////////////////////////////////////////

/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinner Toolbars
  History:	22.07.2000 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Idea and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/

#if !defined(AFX_SpinnerTBDOC_H__D8FEDCED_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
#define AFX_SpinnerTBDOC_H__D8FEDCED_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSpinnerTBDoc : public CDocument
{
protected: // create from serialization only
	CSpinnerTBDoc();
	DECLARE_DYNCREATE(CSpinnerTBDoc)

// Attributes
public:
	
	// Red, Green & Blue value holders
	UINT m_nRed,
		 m_nGreen,
		 m_nBlue; 

	// Value for the gradient components (RGB)
	UINT m_nGradValue;

	// Color for the text
	COLORREF m_clrTextClr;
	
	// Color for the Gradient fill
	COLORREF m_clrGradient;

	// The text string
	CString m_strText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinnerTBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpinnerTBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpinnerTBDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SpinnerTBDOC_H__D8FEDCED_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
