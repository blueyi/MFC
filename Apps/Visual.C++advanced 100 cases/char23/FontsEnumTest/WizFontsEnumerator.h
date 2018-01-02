// WizFontsEnumerator.h: interface for the CWizFontsEnumerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZFONTSENUMERATOR_H__0DB85CA3_8800_11D1_92BB_006097AEFD47__INCLUDED_)
#define AFX_WIZFONTSENUMERATOR_H__0DB85CA3_8800_11D1_92BB_006097AEFD47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
struct Font_EnumStep;

class CWizFontsEnumerator  
{
public:
	class Font
	{
	friend class CWizFontsEnumerator;
	public:
		enum
			{
			normal = 1,
			italics = (normal >> 1),
			bold = (italics >> 1),
			underline = (bold >> 1)
			};
		Font() : m_bInited(false) {} // Only for ARRAY!!!
		Font(const LOGFONT& lf, DWORD fontType, LPCTSTR Script);
		Font(LPCTSTR Name, bool bItalics = true, bool bBold = true, bool bUnderline = true, DWORD fontType = TRUETYPE_FONTTYPE, LPCTSTR Script = _T(""))
			: m_Name (Name) , m_bItalics(bItalics), m_bBold(bBold), m_bUnderline(bUnderline),
			  m_dwFontType(fontType),  m_bInited(false)
				{
				if (Script && *Script)
					AddScript(Script);
				}

		const CString&	Name			() const { return m_Name; }

		bool			CanBeItalics	() const;
		bool			CanBeBold		() const;
		bool			CanBeUnderline	() const;
		bool			CanBeRegular	() const;
		bool			MustBeItalics	() const;
		bool			MustBeBold		() const;
		bool			MustBeUnderline	() const;
		bool			MustBeRegular	() const;
		void			FillSizes(CWordArray& sizes) const;

		DWORD			FontType		() const { return m_dwFontType	; }

		BOOL			IsTrueType		() const { return (m_dwFontType & TRUETYPE_FONTTYPE); }
		int				GetScriptsCount	() const { return m_Script.GetSize(); }
		CString			GetScript(int i) const	 { return m_Script[i]; }


		void operator=(const Font& f);
		int DoEnumStep (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType, Font_EnumStep& data);
	private:
		CString			m_Name;
		CStringArray	m_Script;
		bool		m_bRegular,
					m_bItalics, 
					m_bBold, 
					m_bUnderline;
		DWORD		m_dwFontType;	//	DEVICE_FONTTYPE
									//	RASTER_FONTTYPE
									//	TRUETYPE_FONTTYPE 
		CWordArray	m_sizes;
		mutable int	m_bInited;

	private:
		void AddScript(LPCTSTR Script);
		void AddSize(int pp_size, int lf_height = 0);
		void Initialize() const;
		void DoInit();
	};

	CWizFontsEnumerator();
	virtual ~CWizFontsEnumerator();

	void	Enumerate (HDC hdc);
	void	Enumerate (CDC* pdc);
	void	Enumerate (CWnd* pWnd);

	int		GetFontsCount() const { return m_aFonts.GetSize(); }
	const	Font* GetFont(int i)		const;
	int		FindFont(LPCTSTR Name) const;
	const	Font* GetFont(LPCTSTR Name) const;
protected:
	// Real functions
	void	DoEnumerate (HDC hdc);
	void	InternalEnumerate (CDC* pdc,	bool bWayBack);
	void	InternalEnumerate (CWnd* pWnd,	bool bWayBack);
	void	InternalEnumerate (HDC hdc,		bool bWayBack);
	// Function called from callback in EnumProc
friend int CALLBACK EnumProc (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType, LPARAM lParam);
	int		DoEnumStep (const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme, unsigned long FontType); 
protected:
	CArray<Font, Font&>	m_aFonts;
};
//////////////////////////////////////////////////////////////////////
inline const	CWizFontsEnumerator::Font* CWizFontsEnumerator::GetFont(int i) const
{
	return &(const_cast<CWizFontsEnumerator*>(this)->m_aFonts.ElementAt(i));
}

inline int		CWizFontsEnumerator::FindFont(LPCTSTR Name) const
{
	for (int i = 0; i < GetFontsCount(); i++)
		{
		const Font *p = GetFont(i);
		if (p->Name() == Name)
			return i;
		}
	return -1;
}


inline const	CWizFontsEnumerator::Font* CWizFontsEnumerator::GetFont(LPCTSTR Name) const
{
	int i = FindFont(Name);
	if (i >= 0)
		return GetFont(i);
	return NULL;
}
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_WIZFONTSENUMERATOR_H__0DB85CA3_8800_11D1_92BB_006097AEFD47__INCLUDED_)
