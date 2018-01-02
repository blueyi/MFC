// GLDouglasDoc.h : interface of the CGLDouglasDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDOUGLASDOC_H__C4A73F41_2C97_483E_814E_8194271B9F46__INCLUDED_)
#define AFX_GLDOUGLASDOC_H__C4A73F41_2C97_483E_814E_8194271B9F46__INCLUDED_

#include "..\DOUGLAS\DPHullGL.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGLDouglasDoc : public CDocument
{
protected: // create from serialization only
	CGLDouglasDoc();
	DECLARE_DYNCREATE(CGLDouglasDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLDouglasDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDPHullGL& GetHull();
	double GetShrink() const			{	return m_dShrink;};
	void SetShrink( double dShrink)	{	m_dShrink=__min(1, __max(0, dShrink)); };
	void GetLimits(double pExt[4]);
	void Animate();
	void Draw(CWGL& wgl);
	virtual ~CGLDouglasDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	long m_lCount;
	CDPHullGL m_dp;
	double m_dShrink;

	//{{AFX_MSG(CGLDouglasDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLDOUGLASDOC_H__C4A73F41_2C97_483E_814E_8194271B9F46__INCLUDED_)
