/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// ObjInfo.h : interface of the ObjInfo class                              //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#if !defined(_OBJINFO_H_INCLUDED_)
#define _OBJINFO_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CObjInfo class

class CObjInfo
{
// Construction/Destruction
public:
	CObjInfo();
	CObjInfo(LPCTSTR lpszFileName, DWORD dwType);
	CObjInfo(LPCTSTR lpszFileName, DWORD dwType, CBitmap* pImage);
	CObjInfo(LPCTSTR psFileName, DWORD dwType, HICON hImage);
	CObjInfo(LPCTSTR lpszFileName, DWORD dwType, LPCTSTR lpszHead);
	~CObjInfo();

// Member variables
private:
	CString		m_sName;		// file name (without path)
	DWORD		m_dwFormat;		// file format
	CBitmap*	m_pThumb;		// thumbnail image
	HICON		m_hIcon;		// icon image
	CString		m_sText;		// file header

// Operations
public:
	void		SetName			(LPCTSTR lpszName, DWORD dwFormat);
	void		SetBitmap		(CBitmap* pBitmap);
	void		SetIcon			(HICON hIcon);
	void		SetText			(LPCTSTR lpszText);

	LPCTSTR		GetName			() {return (LPCSTR)m_sName;}
	DWORD		GetFormat		() {return m_dwFormat;}
	CBitmap*	GetBitmap		() {return m_pThumb;}
	HICON		GetIcon			() {return m_hIcon;}
	LPCTSTR		GetText			() {return (LPCTSTR)m_sText;}

};


/////////////////////////////////////////////////////////////////////////////
// CClrInfo class

class CClrInfo
{
// Construction/Destruction
public:
	CClrInfo();
	CClrInfo(COLORREF dwRGB, COLORREF dwHSB);
	~CClrInfo();

// Member variables
private:
	COLORREF	m_dwRGB;		// color value (RGB color-space)
	COLORREF	m_dwHSB;		// color value (HSB color-space)

// Operations
public:
	COLORREF	GetRGBColor		() {return m_dwRGB;}
	COLORREF	GetHSBColor		() {return m_dwHSB;}

};


#endif // !defined(_OBJINFO_H_INCLUDED_)
