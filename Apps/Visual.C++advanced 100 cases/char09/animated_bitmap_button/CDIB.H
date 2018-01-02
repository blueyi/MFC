// CDIB.H - Class header for DIB object


#ifndef _CDIB_H__
#define _CDIB_H__

class CDIB
{
protected:
    CBitmap   m_bmBitmap;   // The bitmap's pixel data

    CPalette* m_pPalette;   // The bitmap's palette
    BOOL      m_bPalLoaded; // Error flag
    int       m_nWidth;     // Bitmap's width in pixels
    int       m_nHeight;    // Bitmap's height in pixels

public:

    CDIB ();                       // Default Constructor
    CDIB (const char* szFilename); // Constructor to load from a file
    CDIB (UINT nResID);            // Constructor to load from resources

   virtual ~CDIB(); // Destructor

    // Accessors
    CBitmap&     GetBits()          {return m_bmBitmap;}
    LONG         GetWidth()         {return m_nWidth;}
    LONG         GetHeight()        {return m_nHeight;}
    CPalette*    GetPalette()       {return m_pPalette;}
    BOOL         IsPaletteLoaded()  {return m_bPalLoaded;}

    // Implementation Functions
    BOOL LoadFromFile(const char* szFilename); // Load Bitmap from File
    BOOL LoadFromResource(UINT nResID);        // Load Bitmap from Resource
    void ConvertColor(int x, int y, COLORREF cr);

    // Drawing functions
    void Draw(CDC* pDC, int nX, int nY, 
              int nWidth,int nHeight, int nXSrc, int nYSrc);
    void Stretch (CDC* pDC, int dx, int dy, 
                  int sw, int sh, int sx, int sy, int nW, int nH);
};


#endif
