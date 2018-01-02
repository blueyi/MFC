

#ifndef _CRGBSURFACE_H_
#define _CRGBSURFACE_H_

// Make integer i divideable by integer a
#define ALIGN(i, a) (((i) + ((a) - 1))/(a)*(a))

// Convert from COLORREF to DIB's BGRA
inline DWORD COLORREFtoBGRA(COLORREF cr, BYTE bAlpha = 255)
{
	return ((DWORD(bAlpha)) << 24) + RGB(GetBValue(cr), GetGValue(cr), GetRValue(cr));
}

inline DWORD ReverseRGB(COLORREF cr, BYTE bAlpha = 255)
{
	return COLORREFtoBGRA(cr, bAlpha);
}

#define RGBA(b,g,r,a)       ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(a))<<24))

// 24 and 32 bit DIB's pixelformat
#define BGR(b,g,r)          ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#define BGRA(b,g,r,a)       ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16))|(((DWORD)(BYTE)(a))<<24))


/*! \brief A wraper to a 24 bit or 32 bit RGB DIB section GDI object.

\ingroup OGLToolsGroup
CRGBSurface is a wraper to a 24 bit or 32 bit RGB
DIB section GDI object.
After creating a RGB surface with one of its Create() methods,
use GetDC() to access a surface thrugh it's DC or
GetPixels() to directly access the surface RGB pixels.
Use Draw() for easy drawing of RGB DIB section
and CopyToClipboard() for copying or seting RGB DIB section
to clipboard.

Call DeleteDC() if you no longer need the surface's DC
(Draw() and Blt() functions don't need it).


 With CRGBSurface you can:
<ol>
<li> Create an empty 24 or 32 bit RGB DIB section.
<li> Convert a device dependent bitmap, passed as
     HBITMAP or CBitmap, to 24 or 32 RGB DIB section.
<li> Create a 24 or 32 RGB DIB section from
     a DIB or JPEG file on disk.
<li> Save a DIB section to disk in bitmap or JPEG format.
<li> Draw() and Blt() a DIB section to a DC.
</ol>

\sa CGLImage
\sa CWGL
\author (c) W.Weyna 'Voytec', http://shiptech.tuniv.szczecin.pl/~weyna/OpenGL/
*/
class CRGBSurface
{
// Construction
public:
	//! Default constructor
	CRGBSurface();
	/*! Destructor. 
	
	\sa DeleteDC
	\sa Delete
	*/
	virtual ~CRGBSurface();

// Attributes
public:
	/*! Attributes:*/
	//@{
	//! returns device context associated with DIB section object selected into it.
	CDC* GetDC() const {return m_pDC;}	      
	//! returns a handle to DIB section GDI object
	HBITMAP GetHandle() const {return m_hDIBSection;}  
	//! returns a pointer for a direct access to 24 or 32 bit RGB pixels of DIB section
	BYTE* GetPixels() const {GdiFlush(); return m_pDIBits; } 

	/*! \name  Image sizes in pixels*/
	//@{
	//! returns a CSize structure containing size of DIB
	CSize GetSize() const {return CSize(m_bih.biWidth, m_bih.biHeight); };
	//! width (in pixels) of DIB
	int GetWidth() const {return m_bih.biWidth; };
	//! height (in pixels) of DIB
	int GetHeight() const {return m_bih.biHeight; };
	//@}

	/*! \name  Image sizes in bytes*/
	//@{
	//! returns number of bytes per row of DIB
	DWORD GetRowSize_Bytes() const { return m_bih.biWidth * m_bih.biBitCount / 8; }
	//! returns number of aligned bytes per row of DIB
	DWORD GetAlignedRowSize_Bytes() const { return ALIGN(GetRowSize_Bytes(), 4); }
	//! returns size (in bytes) of DIB
	DWORD GetSize_Bytes() const { return GetAlignedRowSize_Bytes() * m_bih.biHeight; }

	//! Image size in bytes for m_bih.biBitCount = 24.
	DWORD GetSize24_Bytes() const { return ALIGN(m_bih.biWidth * 3, 4) * m_bih.biHeight; }
	//@}

	/*! \name  Image sizes in logical units*/
	//@{
	//! returns Size log
	CSize GetSizeLog(CDC* pDC) const {
		CSize imageSize(m_bih.biWidth, m_bih.biHeight);
		pDC->DPtoLP(&imageSize);
		return imageSize; }
	//@}

	//! Get bitmap info of DIB
	const BITMAPINFOHEADER* GetBIH() const {return &m_bih; }
	//! returns size in pixels
	int GetPixelSize_Bytes() {return m_bih.biBitCount / 8; }
	//! internal.
	bool CheckSaveError_FileExists(){ return m_bSaveFile_FileExists; }
	//@}

protected:
	HBITMAP m_hDIBSection;
	HBITMAP m_hDIBSectionOld;
	BYTE* m_pDIBits;	

	CDC* m_pDC;
	BITMAPINFOHEADER m_bih;

	bool m_bSaveFile_FileExists;

// Operations
public:    
	/*! @name Operations: */
	//@{
	//! Copy constructor.
	bool Create(CRGBSurface* const pSourceSurface);
	/*! \brief Create/recreate a DIB section.
	
	\sa CGLImage::Create
	*/
	bool Create(int cx, int cy, int nBitsPerPixel = 24);
	/*! \brief Create DIB from buffer pDIB
	
	Create a 24 bit (default) or 32 bit DIB section and 
	initialize it using memory DIB pointed by pDIB.
	\sa CGLImage::Create
	*/
	bool Create(BYTE* pDIB, int nBitsPerPixel = 24);
	/*! \brief CreateDIB from file.

	Create a 24 bit (default) or 32 bit DIB section and 
	initialize this DIB section using opened DIB file on disk.
	\sa CGLImage::Create
	*/
	bool Create(HANDLE hFile, int nBitsPerPixel = 24);
	/*! \brief Create DIB from file.
	
	Create a 24 bit (default) or 32 bit DIB section and 
	initialize this DIB section using DIB or JPEG file on disk.
	\sa CGLImage::Create
	*/
	bool Create(const char* szPath, int nBitsPerPixel = 24);
	/*! \brief Create DIB from bitmap

	Create/recreate a 24 bit (default) or 32 bit
	DIB section and convert given DDB to this DIB section.
	\sa CGLImage::Create
	*/
	bool Create(HBITMAP hBitmap, int nBitsPerPixel = 24, CDC* pBitmapDC = NULL);
	//! Create DIB using Create(HBITMAP,int,CDC*)
	bool Create(CBitmap* pBitmap, int nBitsPerPixel = 24, CDC* pBitmapDC = NULL) {return Create(HBITMAP(*pBitmap), nBitsPerPixel, pBitmapDC); }
	//! Create DIB using Create(HBITMAP,int,CDC*)
	bool Create(const CBitmap& bitmap, int nBitsPerPixel = 24, CDC* pBitmapDC = NULL) {return Create(HBITMAP(bitmap), nBitsPerPixel, pBitmapDC); }

	/*! \brief Draw DIB to DC
	
	Draw DIB section to the pDestDC into the
	(\a x, \a y, \a destWidth, \a destHeight) rectangle.
	Rectangle coordinates may be in logical units.
	For a simple blit, use Blt() instead.
	\sa Blt()
	*/
	void Draw(CDC* pDestDC, int x, int y, int destWidth = -1, int destHeight  = -1) const; 

	/*! \brief Draw DIB to DC
	
	Draw (\a srcx, \a srcy, \a srcWidth, \a srcHeight)
	region of DIB section to the pDestDC into the
	(\a destx, \a desty, \a destWidth, \a destHeight) rectangle.
	Rectangle coordinates may be in logical units.
	For a simple blit, use Blt() instead.
	\sa Blt
	\sa StretchDIBits
	*/
	void Draw(CDC* pDestDC, int srcx, int srcy, int srcWidth, int srcHeight,int destx, int desty, int destWidth =-1, int destHeight=-1)  const;
	//! Blit DIB section to the pDestDC. 
	void Blt(CDC* pDestDC,int destWidth = -1, int destHeight = -1) const;
	//! Blit DIB section to the pDestDC. 
	void Blt(CDC* pDestDC, int srcX, int srcY, int destX, int destY, int destWidth=-1, int destHeight=-1) const;
	//! Copy Surface to another CRGBSurface object
	bool CopyTo(CRGBSurface* pDestSurface, DWORD dwDestX = 0, DWORD dwDestY = 0) const;
	/*! \brief Copy DIB to clipboard.
	
	Ifb NoCopy is true, no copy of DIB before SetClipboardData()
	is made, and if CopyToClipboard() is successfull,
	we will no longer own this DIB section object.
	*/
	bool CopyToClipboard(bool bNoCopy = false); 
	//! Saves DIB to file (in JPEG or BMP)
	bool SaveToFile(const CString& strPath, bool bAllowOverwrite = false, int nQuality = -1); 
	

	/*! \brief Create DIB from this pointer.
	
	Creates a 24bit memory DIB from this DIB section
	and returns a pointer to the newly created DIB.
	\sa CGLImage::Create
	*/
	BYTE* CreateDIB();
	/*! \brief Create 24 bits DIB (useful with SetClipboardData())
	
	Creates a 24bit memory DIB from this DIB section
	and returns a memory handle.
	Useful for functions like SetClipboardData()
	which need Win16 memory handles to memory DIBs.
	*/
	HGLOBAL CreateDIB_Win16();

	//! Delete dib section GDI object.
	void Delete();
	//! Delete a DC for this dib section GDI object.
	void DeleteDC();
	//! Rebuild DC
	bool RecreateDC();
	
	/*! \brief Create a memory DIB from a file.
	
	Creates a memory DIB from a DIB file on disk.
	A pointer to created memory DIB is returned
	or NULL if function failed to load a DIB.
	*/
	BYTE* LoadDIB(const CString& strPath);
	/*! \brief Create a memory DIB from opened file.
	
	Creates a memory DIB from a DIB file on disk.
	A pointer to created memory DIB is returned
	or NULL if function failed to load a DIB.
	It needs a valid handle to a file.
	*/
	BYTE* LoadDIBFromOpenedFile(HANDLE hFile);
	//! Save a DIB to a opened file. It needs a valid handle to a file.
	bool SaveDIBToOpenedFile(HANDLE hFile);
	//! Save a DIB to a file.
	bool SaveDIB(const CString& strPath, bool bAllowOverwrite = false);
	//! Save DIB in JPEG file.
	bool SaveAsJPEGFile(const CString& strPath, int nQuality = -1, bool bAllowOverwrite = false);
	/*! \brief Create DIB from JPEG file.
	
	Create a 24 bit (default) or 32 bit DIB section and 
	initialize this DIB section using JPEG file on disk.
	*/
	bool CreateFromJPEGFile(const CString& strPath, int nBitsPerPixel = 24);
	/*! \brief Create DIB from JPEG file.
	
	Create a 24 bit (default) or 32 bit DIB section and 
	initialize this DIB section using infile openend file.
	*/
	bool CreateFromOpenedStdioJPEGFile(FILE* infile, int nBitsPerPixel = 24);
	/*! \brief Create DIB from DIB file.
	
	Create a 24 bit (default) or 32 bit DIB section and 
	initialize this DIB section using DIB file on disk.
	*/
	bool CreateFromDIBFile(const CString& strPath, int nBitsPerPixel = 24);
	//@}


// Operations that directly manipulate the DIB bits
public:
	/*! @name Operations that directly manipulate the DIB bits: */
	//@{
	/*! Clear DIB
	GDI:
	
	Fast surface fill with BGRA color value
	Default fill is white.
	Use ClearCR() if you want to clear with COLORREF (RGBA) value.

	Other implementations:
	Fast 24 or 32 bit surface fill with DWORD value.
	Use ClearCR() if you want to swap byte 0 and byte 2 in 
	supplied DWORD color value.
	*/
	void Clear(DWORD dwBGRA = BGRA(255, 255, 255, 255));
	/*! \brief Fast surface fill with COLORREF (RGBA) color value.
	Default fill is white. */
	void ClearCR(DWORD dwRGBA = RGBA(255, 255, 255, 255));
	//! Set brightness from 0 (dark) to 255 (bright)
	void Brightness(double dBrightness);
	//@}	
// Validity check
public:

#ifdef _DEBUG
	void AssertValid() const {
		ASSERT_VALID(m_pDC);
		ASSERT(m_hDIBSection);
		ASSERT(m_pDIBits);
		ASSERT(m_bih.biBitCount == 24 || m_bih.biBitCount == 32);
		ASSERT(m_bih.biWidth > 0);
		ASSERT(m_bih.biHeight > 0);
		ASSERT(GetObjectType(m_hDIBSection) == OBJ_BITMAP); }
#else
	void AssertValid() {};
#endif
	
// Helpers
private:
	//! returns a pointer to memory DIB bits.
	BYTE* GetPointerToDIBits(BYTE* pDIB);

// Friends
	friend bool operator==(const CRGBSurface& l, const CRGBSurface& r);
	friend bool operator!=(const CRGBSurface& l, const CRGBSurface& r);

};

inline bool operator>(const CRGBSurface& l, const CRGBSurface& r)
{
	return l.GetWidth() > r.GetWidth() &&
		l.GetHeight() > r.GetHeight();
}

inline bool operator>=(const CRGBSurface& l, const CRGBSurface& r) 
{
	return l.GetWidth() >= r.GetWidth() &&
		l.GetHeight() >= r.GetHeight();
}

inline bool operator<(const CRGBSurface& l, const CRGBSurface& r) 
{
	return l.GetWidth() < r.GetWidth() &&
		l.GetHeight() < r.GetHeight();
}

inline bool operator<=(const CRGBSurface& l, const CRGBSurface& r)
{
	return l.GetWidth() <= r.GetWidth() &&
		l.GetHeight() <= r.GetHeight();
}

inline bool operator==(const CRGBSurface& l, const CRGBSurface& r) 
{
	return l.GetWidth() == r.GetWidth() &&
		l.GetHeight() == r.GetHeight() && 
		l.m_bih.biBitCount == r.m_bih.biBitCount;
}

inline bool operator!=(const CRGBSurface& l, const CRGBSurface& r) 
{
	return l.GetWidth() != r.GetWidth() ||
		l.GetHeight() != r.GetHeight() ||
		l.m_bih.biBitCount != r.m_bih.biBitCount;
}

#endif 


//////////////////////////////////////////////////////////////////////