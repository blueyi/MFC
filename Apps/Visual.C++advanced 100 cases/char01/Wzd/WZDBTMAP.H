#ifndef WZDBITMAP_H
#define WZDBITMAP_H

class CWzdBitmap : public CBitmap
{
public:
	DECLARE_DYNAMIC(CWzdBitmap)

// Constructors
	CWzdBitmap();

	void LoadBitmapEx(UINT nID, BOOL bIconBkgrd );
	CPalette *GetPalette(){return m_pPalette;};

// Implementation
public:
	virtual ~CWzdBitmap();

// Attributes
	int	m_Width;
	int m_Height;
// Operations

private:
	CPalette *m_pPalette;
};
#endif
