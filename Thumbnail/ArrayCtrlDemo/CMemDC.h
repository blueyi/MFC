/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// CMemDC.h : interface of the Memory DC class                             //
//                                                                         //
// Class used by CArrayCtrl for internal memory DC objects                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#if !defined(_CMEMDC_H_INCLUDED_)
#define _CMEMDC_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CMemDC object

class CMemDC
{
// Constructor/Destroyer
public:
	CMemDC		();
	CMemDC		(int nWidth, int nHeight, COLORREF crBack = RGB(255,255,255));
	~CMemDC		();

// Member variables
private:
	CDC*			m_pDC;			// memory DC
	CBitmap*		m_pOrigBitmap;	// original bitmap (saved object)
	CBrush*			m_pOrigBrush;	// original brush (saved object)
	int				m_nWidth;		// current width
	int				m_nHeight;		// current height
	COLORREF		m_crBack;		// background color

// Operations
public:
	BOOL	Create			(int nWidth, int nHeight, COLORREF crBack);
	CDC*	GetDC			() {return m_pDC;}
	void	Resize			(int width, int height);
	void	SetColor		(COLORREF crBack);
	void	Erase			();
	void	Copy			(int nDestX, int nDestY, int nDestW, int nDestH, CMemDC* pSrc, int nSrcX, int nSrcY); 

};

#endif // !defined(_CMEMDC_H_INCLUDED_)
