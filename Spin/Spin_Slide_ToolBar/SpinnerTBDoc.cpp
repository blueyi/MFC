// SpinnerTBDoc.cpp : implementation of the CSpinnerTBDoc class
//

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

#include "stdafx.h"
#include "SpinnerTB.h"
#include "SpinnerTBDoc.h"
#include "SpinnerTBView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBDoc

IMPLEMENT_DYNCREATE(CSpinnerTBDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpinnerTBDoc, CDocument)
	//{{AFX_MSG_MAP(CSpinnerTBDoc)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBDoc construction/destruction

CSpinnerTBDoc::CSpinnerTBDoc()
{
	// TODO: add one-time construction code here

	m_nRed		= 255;
	m_nGreen	= 255;
	m_nBlue		= 255;

	m_clrTextClr = RGB(m_nRed, m_nGreen, m_nBlue);
	m_strText = _T("¿ Hi everybody, ha ya doen ? \n\n Eth'pinners and Eth'liders in Toolbar.");

	m_nGradValue = 255;
	m_clrGradient = RGB(m_nGradValue, m_nGradValue, m_nGradValue);


}

CSpinnerTBDoc::~CSpinnerTBDoc()
{
}

BOOL CSpinnerTBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBDoc serialization

void CSpinnerTBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_clrGradient << m_clrTextClr << m_strText;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_clrGradient >> m_clrTextClr >> m_strText;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBDoc diagnostics

#ifdef _DEBUG
void CSpinnerTBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpinnerTBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBDoc commands




