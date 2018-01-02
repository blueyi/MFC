// WizFontsEnumerator.cpp: implementation of the CWizFontsEnumerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizFontsEnumerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace
{
UCHAR TTDefaults[] = { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
const int TTDefaultsSize =  sizeof(TTDefaults)/sizeof(TTDefaults[0]);
}
//////////////////////////////////////////////////////////////////////

CWizFontsEnumerator::Font::Font(const LOGFONT& lf, DWORD fontType, LPCTSTR Script)
	: m_Name(lf.lfFaceName) ,  m_bItalics(false), m_bBold(false), 
	  m_bUnderline(false),  m_bRegular(false),
	  m_dwFontType(fontType),  m_bInited(false)
{
	if (Script && *Script)
		AddScript(Script);
}

void CWizFontsEnumerator::Font::operator=(const Font& f)
{
	m_Name		= f.m_Name		;
	m_bItalics	= f.m_bItalics	; 
	m_bBold		= f.m_bBold		; 
	m_bUnderline= f.m_bUnderline;
	m_bRegular	= f.m_bRegular;
	m_dwFontType= f.m_dwFontType;

	m_Script.RemoveAll();
	for (int i = 0; i < f.m_Script.GetSize(); i++)
		m_Script.Add(f.m_Script[i]);

	m_sizes.SetSize(f.m_sizes.GetSize());
	for (i = 0; i < f.m_sizes.GetSize(); i++)
		m_sizes[i] = f.m_sizes[i];

	m_bInited = f.m_bInited;
}

struct Font_EnumStep
{
	Font_EnumStep(CWizFontsEnumerator::Font& f, CDC& dc)
		: rTHIS(f) , r_dc(dc) 
		{
		cyPixelsPerInch = dc.GetDeviceCaps(LOGPIXELSY);
		}

	CWizFontsEnumerator::Font& rTHIS;
	CDC& r_dc;
	int	cyPixelsPerInch;
};

int CALLBACK DetailsEnumProc (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType, LPARAM lParam) 
{
	Font_EnumStep* p = reinterpret_cast<Font_EnumStep*>(lParam);
	/*
	CWizFontsEnumerator::Font* pTHIS = reinterpret_cast<CWizFontsEnumerator::Font*>(lParam);
	return pTHIS->DoEnumStep (lpelfe, lpntme, FontType);
	*/
	return p->rTHIS.DoEnumStep (lpelfe, lpntme, FontType, *p);
}

int CWizFontsEnumerator::Font::DoEnumStep (const ENUMLOGFONTEX *lpelf, const NEWTEXTMETRICEX *lpntm, unsigned long FontType, Font_EnumStep& data)
{
	ASSERT(&(data.rTHIS) == this);

	if (FontType & TRUETYPE_FONTTYPE)
	{
		if (!(lpntm->ntmTm.ntmFlags & (NTM_BOLD | NTM_ITALIC)))
			{
			TRACE("\n\tFont %s add regular", lpelf->elfLogFont.lfFaceName);
			m_bRegular = true;
			}

		if (lpntm->ntmTm.ntmFlags & NTM_ITALIC)
			{
			TRACE("\n\tFont %s add Italics", lpelf->elfLogFont.lfFaceName);
			m_bItalics = true;
			}

		if (lpntm->ntmTm.ntmFlags & NTM_BOLD)
			{
			TRACE("\n\tFont %s add Bold", lpelf->elfLogFont.lfFaceName);
			m_bBold = true;
			}
	}
	else
	{
		if (FontType & RASTER_FONTTYPE)
		{
			int height = lpntm->ntmTm.tmHeight - lpntm->ntmTm.tmInternalLeading;
			int size_pp = MulDiv(height, 72, data.cyPixelsPerInch); //, height);
			TRACE("\n\tFont %s add size %d", lpelf->elfLogFont.lfFaceName, size_pp);
			AddSize(size_pp, height);
		}

		if (lpelf->elfLogFont.lfWeight >= FW_BOLD && lpelf->elfLogFont.lfItalic)
			{
			TRACE("\n\tFont %s add bold & italics", lpelf->elfLogFont.lfFaceName);
			m_bItalics = true;
			m_bBold = true;
			}
		else if (lpelf->elfLogFont.lfWeight >= FW_BOLD)
			{
			TRACE("\n\tFont %s add bold", lpelf->elfLogFont.lfFaceName);
			m_bBold = true;
			}
		else if (lpelf->elfLogFont.lfItalic)
			{
			TRACE("\n\tFont %s add italics", lpelf->elfLogFont.lfFaceName);
			m_bItalics = true;
			}
		else
			{
			TRACE("\n\tFont %s add regular", lpelf->elfLogFont.lfFaceName);
			m_bRegular = true;
			}
	}

	return 1;
	
}

void CWizFontsEnumerator::Font::DoInit() 
{
	// Init flags
	m_bRegular = m_bItalics = m_bBold = m_bUnderline = false;

	// Init for enumeration
	CClientDC dc(NULL);
	LOGFONT lf;
	memset (&lf, 0, sizeof(lf));
	lf.lfCharSet	= DEFAULT_CHARSET;
	strcpy(lf.lfFaceName, m_Name);
	Font_EnumStep temp(const_cast<Font&>(*this), dc);
	// Enumeration procedure
	EnumFontFamiliesEx (dc.m_hAttribDC, &lf, (FONTENUMPROC)::DetailsEnumProc, reinterpret_cast<LPARAM>(&temp), 0);
	// Finish init:
	m_bUnderline = true; // Always availible so far
	// Allow for "synthesized" italic && bold variants
	if (m_bRegular)
		m_bItalics = m_bBold = true;
}

void CWizFontsEnumerator::Font::Initialize() const
{
	if (m_bInited)
		return;
	const_cast<Font*>(this)->DoInit();
	m_bInited = true;
}


void CWizFontsEnumerator::Font::FillSizes(CWordArray& sizes) const
{
	sizes.SetSize(0);
	if (m_dwFontType != RASTER_FONTTYPE)
		{
		sizes.SetSize(TTDefaultsSize);
		for (int i = 0; i < TTDefaultsSize; i++)
			sizes[i] = TTDefaults[i];
		}
	else
		{
		Initialize();
		sizes.SetSize(m_sizes.GetSize());
		for (int i = 0; i < m_sizes.GetSize(); i++)
			sizes[i] = m_sizes[i];
		}
}

bool CWizFontsEnumerator::Font::CanBeItalics	() const
{
	Initialize();
	return m_bItalics;
}

bool CWizFontsEnumerator::Font::CanBeBold		() const
{
	Initialize();
	return m_bBold;
}

bool CWizFontsEnumerator::Font::CanBeUnderline	() const
{
	Initialize();
	return m_bUnderline;
}

bool CWizFontsEnumerator::Font::CanBeRegular	() const
{
	Initialize();
	return m_bRegular;
}

bool CWizFontsEnumerator::Font::MustBeRegular	() const
{
	Initialize();
	return (m_bRegular && !(m_bItalics || m_bUnderline || m_bBold));
}

bool CWizFontsEnumerator::Font::MustBeItalics	() const
{
	Initialize();
	return (m_bItalics && !(m_bRegular /*|| m_bUnderline || m_bBold*/));
}

bool CWizFontsEnumerator::Font::MustBeBold	() const
{
	Initialize();
	return (m_bBold && !(m_bRegular /*|| m_bItalics  || m_bUnderline*/));
}

bool CWizFontsEnumerator::Font::MustBeUnderline	() const
{
	Initialize();
	return false;// (m_bUnderline && !(m_bRegular || m_bItalics || m_bBold));
}


void CWizFontsEnumerator::Font::AddSize(int pp_size, int lf_height)
{
	m_sizes.Add(WORD(pp_size));
}

void CWizFontsEnumerator::Font::AddScript(LPCTSTR Script)
{ 
	m_Script.Add(Script);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizFontsEnumerator::CWizFontsEnumerator()
{
}

CWizFontsEnumerator::~CWizFontsEnumerator()
{

}

int	CWizFontsEnumerator::DoEnumStep (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType)
{
	CString script = lpelfe->elfScript;

TRACE("\nFont %s", lpelfe->elfLogFont.lfFaceName);

	// If font exists yet
	int nFont = FindFont(lpelfe->elfLogFont.lfFaceName);
	if (nFont >= 0)
		{
		m_aFonts.ElementAt(nFont).AddScript(script);

TRACE(" Add script %s", (LPCTSTR)script);

		return 1;
		}
	// add font to list
	Font f (lpelfe->elfLogFont, FontType, script);
	int i = m_aFonts.Add(f);

	if (i < 0)
		{ ASSERT(0); AfxThrowMemoryException(); }

TRACE(" Script %s", (LPCTSTR)script);

	return 1;
}

int CALLBACK EnumProc (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType, LPARAM lParam) 
{
	CWizFontsEnumerator* pTHIS = reinterpret_cast<CWizFontsEnumerator*>(lParam);
	return pTHIS->DoEnumStep (lpelfe, lpntme, FontType);
}

void	CWizFontsEnumerator::DoEnumerate (HDC hdc)
{
	ASSERT(NULL != hdc);
	m_aFonts.RemoveAll();

	LOGFONT lf;
	memset (&lf, 0, sizeof(lf));
	lf.lfCharSet	= DEFAULT_CHARSET;
	lf.lfFaceName[0]= 0;
	EnumFontFamiliesEx (hdc, &lf, (FONTENUMPROC)::EnumProc, reinterpret_cast<LPARAM>(this), 0);

#ifdef _DEBUG
	TRACE("\nFound %d fonts:", m_aFonts.GetSize());
	for (int i = 0; i < m_aFonts.GetSize(); i++)
	{
		const Font* p = GetFont(i);
		TRACE("\n %s", (LPCTSTR)(p->Name()));
		for (int j = 0; j < p->GetScriptsCount(); j++)
			TRACE("\n\t %s", (LPCTSTR)(p->GetScript(j)));
	}
#endif

}

void	CWizFontsEnumerator::InternalEnumerate (HDC hdc, bool bWayBack)
{
	// If no valid DC supplied
	if (NULL == hdc && bWayBack)
		{
		TRACE0("Warning! NULL hDC at CWizFontsEnumerator::Enumerate"); 
		// Get main app window (hopefully)
		CClientDC some(NULL);
		//CWnd* pSomeWnd = AfxGetMainWnd();
		InternalEnumerate(some, false); // No way back here again
		}
	else
		DoEnumerate (hdc);
}


void	CWizFontsEnumerator::InternalEnumerate (CDC* pdc,	bool bWayBack)
{
	if (NULL != pdc)
		InternalEnumerate(pdc->m_hAttribDC, bWayBack);
	else
		{
		TRACE0("Warning! NULL pDC at CWizFontsEnumerator::Enumerate");
		if (bWayBack) // try to figure up something
			InternalEnumerate ((HDC)NULL, bWayBack);
		}
}

void	CWizFontsEnumerator::InternalEnumerate (CWnd* pWnd,	bool bWayBack)
{
	if (NULL == pWnd)
		{
		TRACE0("Warning! NULL Window at CWizFontsEnumerator::Enumerate"); 
		if (bWayBack) // try to figure up something
			InternalEnumerate((HDC)NULL, bWayBack);
		}
	else
		{
		// Two attempts to get DC: client DC and, if fails,
		// window DC
		// BLOCK
			{
			CClientDC dc(pWnd);
			if (dc.m_hAttribDC != NULL)
				{
				InternalEnumerate(&dc, bWayBack);
				return;
				}
			}
		// BLOCK
			{
			CWindowDC dc(pWnd);
			InternalEnumerate(&dc, bWayBack);
			}
		}
}

void	CWizFontsEnumerator::Enumerate (HDC hdc)
{
	InternalEnumerate(hdc, true);
}

void	CWizFontsEnumerator::Enumerate (CDC* pdc)
{
	InternalEnumerate(pdc, true);
}

void	CWizFontsEnumerator::Enumerate (CWnd* pWnd)
{
	InternalEnumerate(pWnd, true);
}

