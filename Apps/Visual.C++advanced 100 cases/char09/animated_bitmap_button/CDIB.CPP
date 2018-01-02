#include "stdafx.h"
#include "cdib.h"
#include <io.h>


// Default Constructor
CDIB::CDIB()
{
    m_pPalette   = NULL;
    m_bPalLoaded = FALSE;
    m_nWidth     = 0;
    m_nHeight    = 0;
}


// Constructor to load from a file
CDIB::CDIB(const char* szFilename)
{
    m_pPalette   = NULL;
    m_bPalLoaded = FALSE;
    m_nWidth     = 0;
    m_nHeight    = 0;

    LoadFromFile(szFilename);
}


// Constructor to load from app resources
CDIB::CDIB(UINT nResID)
{
    m_pPalette   = NULL;
    m_bPalLoaded = FALSE;
    m_nWidth     = 0;
    m_nHeight    = 0;

    LoadFromResource(nResID);
}


// Destructor
CDIB::~CDIB()
{
    if(m_pPalette) delete m_pPalette;
}


// Load Bitmap data from a File
BOOL CDIB::LoadFromFile(const char* szFilename)
{
    // 1. Read bits from file
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,
                                         szFilename,
                                         IMAGE_BITMAP,
                                         0, 0, 
                                         LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    m_bmBitmap.Attach(hBitmap);


    // 2. Get palette from the file
    // Open the file
    int nFile = _lopen(szFilename, OF_READ);


    // Only proceed if file could be opened
    if (nFile != -1)
    {
        BITMAPINFOHEADER bminfo;
        BITMAPFILEHEADER bmfile;
        PALETTEENTRY     PalEntries[256];
        int              nNumEntries;
        HANDLE           hlogpal;
        LPLOGPALETTE     lplogpal;


        // Read headers and palette entries out of file
        _lread (nFile, &bmfile, sizeof(bmfile));
        _lread (nFile, &bminfo, sizeof(bminfo));
        _lread (nFile, &PalEntries, sizeof(PalEntries));


        if ((bminfo.biSize != sizeof(BITMAPINFOHEADER)) || 
            (bminfo.biBitCount > 8))
        {
            _lclose (nFile);
            return FALSE;   
            // Bad header or more than 256 colors - can't go on
        }


        // if biClrUsed is 0, palette is using max number of
        // entries for its bitwidth.  Otherwise, biClrUsed
        // specifies the actual number of palette entries in use.
        if (bminfo.biClrUsed == 0)
        {
            nNumEntries = 1 << bminfo.biBitCount;
        }
        else
        {
            nNumEntries = bminfo.biClrUsed;
        }


        // Remember the bitmap's width and height
        m_nWidth = bminfo.biWidth;
        m_nHeight = bminfo.biHeight;


        LONG lInfoSize = sizeof(BITMAPINFO) +
                         sizeof(RGBQUAD)*nNumEntries;

        HANDLE hInfo = GlobalAlloc (GHND, lInfoSize);

        if (!hInfo)
        {
            _lclose(nFile);
            return FALSE;
        }

        LPBITMAPINFO lpInfo = (LPBITMAPINFO)GlobalLock(hInfo);

        if (!lpInfo)
        {
            _lclose(nFile);
            GlobalFree(hInfo);
            return FALSE;
        }

        // Rewind file and read whole BITMAPINFO for later use
        _lseek (nFile, 0, SEEK_SET);
        _lread (nFile, lpInfo, lInfoSize);
        _lclose(nFile);

        // Allocate storage for the LOGPALETTE
        hlogpal = GlobalAlloc (GHND, sizeof(LOGPALETTE) +
                                     sizeof(PALETTEENTRY)*nNumEntries);

        if (!hlogpal)
        {
            GlobalUnlock(hInfo);
            GlobalFree(hInfo);
            return FALSE;
        }

        lplogpal = (LPLOGPALETTE)GlobalLock (hlogpal);

        lplogpal->palVersion = 0x300;
        lplogpal->palNumEntries = nNumEntries;


        // Copy entries into LOGPALETTE
        for (int i=0; i < nNumEntries; i++)
        {
            lplogpal->palPalEntry[i].peRed   = PalEntries[i].peBlue;
            lplogpal->palPalEntry[i].peGreen = PalEntries[i].peGreen;
            lplogpal->palPalEntry[i].peBlue  = PalEntries[i].peRed;
            lplogpal->palPalEntry[i].peFlags = 0;
        }


        // Create the palette
        m_pPalette = new CPalette;
        m_pPalette->CreatePalette (lplogpal);

        // Clean up
        GlobalUnlock(hlogpal);
        GlobalFree(hlogpal);
        GlobalUnlock(hInfo);
        GlobalFree(hInfo);

        m_bPalLoaded = TRUE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}


// Load bitmap data from app resources
BOOL CDIB::LoadFromResource(UINT nResID)
{
    HBITMAP hBitmap;

    // 1. Read bits from resource
    hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(nResID),
                                 IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    m_bmBitmap.Attach(hBitmap);


    // 2. Get palette from file or resource

    m_bPalLoaded = FALSE;
    m_pPalette = 0;

    // Load palette from resource
    HRSRC	hbmres = FindResource (NULL, MAKEINTRESOURCE(nResID), RT_BITMAP);

    if (hbmres)
    {
        LPBITMAPINFOHEADER lpbminfo =
                   (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL,hbmres));

        int               nNumEntries;
        HANDLE            hlogpal;
        LPLOGPALETTE      lplogpal;


        if (lpbminfo && 
            (lpbminfo->biSize >= sizeof(BITMAPINFOHEADER)) &&
            (lpbminfo->biBitCount <= 8))
        {
            RGBQUAD*  PalEntries = (RGBQUAD*)((BYTE*)lpbminfo
                                            + lpbminfo->biSize);

            // if biClrUsed is 0, palette is using max number of
            // entries for its bitwidth.  Otherwise, biClrUsed
            // specifies the actual number of palette entries 
            // in use.
            if (lpbminfo->biClrUsed == 0)
            {
                nNumEntries = 1 << lpbminfo->biBitCount;
            }
            else
            {
                nNumEntries = lpbminfo->biClrUsed;
            }


            // Remember the bitmap's width and height
            m_nWidth = lpbminfo->biWidth;
            m_nHeight = lpbminfo->biHeight;

            LONG lInfoSize = sizeof(BITMAPINFO) + 
                             sizeof(RGBQUAD)*nNumEntries;

            HANDLE hInfo = GlobalAlloc (GHND, lInfoSize);

            if (!hInfo)
            {
                return FALSE;
            }

            LPBITMAPINFO lpInfo = (LPBITMAPINFO)GlobalLock(hInfo);

            if (!lpInfo)
            {
                GlobalFree(hInfo);
                return FALSE;
            }

            // Copy BITMAPINFO
            memcpy(lpInfo, lpbminfo, lInfoSize);


            // Allocate storage for the LOGPALETTE
            hlogpal = GlobalAlloc (GHND, sizeof(LOGPALETTE) +
                                         sizeof(PALETTEENTRY)*nNumEntries);

            if (!hlogpal)
            {
                GlobalUnlock(hInfo);
                GlobalFree(hInfo);
                return FALSE;
            }

            lplogpal = (LPLOGPALETTE)GlobalLock (hlogpal);

            lplogpal->palVersion = 0x300;
            lplogpal->palNumEntries = nNumEntries;


            // Copy entries into LOGPALETTE
            for (int i=0; i<nNumEntries; i++)
            {
                lplogpal->palPalEntry[i].peBlue  = PalEntries[i].rgbBlue;
                lplogpal->palPalEntry[i].peGreen = PalEntries[i].rgbGreen;
                lplogpal->palPalEntry[i].peRed   = PalEntries[i].rgbRed;
                lplogpal->palPalEntry[i].peFlags = 0;
            }

            // Create the palette
            m_pPalette = new CPalette;
            m_pPalette->CreatePalette (lplogpal);

            // Clean up
            GlobalUnlock(hlogpal);
            GlobalFree(hlogpal);
            GlobalUnlock(hInfo);
            GlobalFree(hInfo);

            m_bPalLoaded = TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}


// Convert all pixels with the same color as the pixel at point (x,y).
// All pixels will be converted to the given color (cr).
void CDIB::ConvertColor(int x, int y, COLORREF cr)
{
    // Get a DC for BitBlt purposes (anyone will do).
    HDC hdc = ::GetDC(NULL);
    CDC dc;
    dc.Attach(hdc);
    
    // Now create a memory DC for the Bitmap and select it into the DC.
    CDC dcBitmap;
    dcBitmap.CreateCompatibleDC(&dc);
    dcBitmap.SelectObject(&m_bmBitmap);

    // create a mask device context
    CDC dcMask;
    dcMask.CreateCompatibleDC(&dc);
    CBitmap bmMask;

    // Create the monochrome mask bitmap and select it into the DC.
    bmMask.CreateBitmap(m_nWidth, m_nHeight, 1, 1, NULL);
    dcMask.SelectObject(&bmMask);

    // Set the Bitmap DC's background color to the desired color to change.
    dcBitmap.SetBkColor( dcBitmap.GetPixel(x,y) );
    
    //
    // Now BitBlt the Plane DC (which is color) to the Mask DC 
    // (which is monochrome).  The BitBlt method will convert any
    // bit with a color equal to the transparent color (which has
    // been set to the background color) to WHITE and any other color
    // to BLACK.  Thus creating a perfect mask for the source bitmap!
    //
    dcMask.BitBlt(0, 0, m_nWidth, m_nHeight, &dcBitmap, 0, 0, SRCCOPY);

    //
    // We need to set the Bitmap DC's Background color to WHITE
    // and it's Foreground color to BLACK.  Then do a BitBlt using
    // the SRCPAINT Raster-operation.  Then we need to set the
    // Bitmap DC's Background color to (cr) the desired color and
    // it's Foreground color to WHITE.  Then do a BitBlt using
    // the SRCAND Raster-operation.  This will change the all pixels
    // of the color of pixel (x,y) to now be color (cr). Whew!
    //
    int nBkColor   = dcBitmap.SetBkColor( RGB(255,255,255) ); // White
    int nForeColor = dcBitmap.SetTextColor( RGB(0,0,0) ); // Blace
    
    dcBitmap.BitBlt(0, 0, m_nWidth, m_nHeight, &dcMask, 0, 0, SRCPAINT);

    dcBitmap.SetBkColor(cr);
    dcBitmap.SetTextColor( RGB(255,255,255) ); // White

    dcBitmap.BitBlt(0, 0, m_nWidth, m_nHeight, &dcMask, 0, 0, SRCAND);

    // Reset the device context.
    dcBitmap.SetBkColor(nBkColor);
    dcBitmap.SetTextColor(nForeColor);

    dc.Detach();
    ReleaseDC(NULL, hdc);
}


// Draw the DIB to the given Device Context.
// Basically Realize the palette and do a BitBlt.
void CDIB::Draw(CDC* pDC, int nX, int nY, 
                int nWidth,int nHeight, int nXSrc, int nYSrc)
{
    ASSERT(m_bPalLoaded);

    //
    // Select the palette into the screen DC and realize it  
    // Force background, because palette should already be realized in 
    // foreground if necessary
    //
    CPalette* pOldPalette = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

    // Create a memory DC compatible with the screen DC
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);

    // Put the bitmap bits into the memory DC
    CBitmap* pOldBitmap = dcMem.SelectObject(&m_bmBitmap);

    // Copy the bitmap bits to the screen DC
    pDC->BitBlt(nX, nY, nWidth, nHeight, &dcMem, nXSrc, nYSrc, SRCCOPY);

    // Put the original bitmap back
    dcMem.SelectObject(pOldBitmap);

    // Put the original palette back
    pDC->SelectPalette(pOldPalette, TRUE);
    pDC->RealizePalette();
}


// Stretch (fit) the DIB to the given Device Context.
// Basically Realize the palette and do a StretchBlt.
void CDIB::Stretch (CDC* pDC, int nX, int nY, int nWidth, int nHeight,
                    int nXSrc, int nYSrc, int nSrcWidth, int nSrcHeight)
{
    ASSERT(m_bPalLoaded);

    //
    // Select the palette into the screen DC and realize it  
    // Force background, because palette should already be realized in 
    // foreground if necessary
    //
    CPalette* pOldPalette = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

    // Create a memory DC compatible with the screen DC
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);

    // Put the bitmap bits into the memory DC
    CBitmap* pOldBitmap = dcMem.SelectObject(&m_bmBitmap);

    // Copy the bitmap bits to the screen DC
    pDC->StretchBlt(nX, nY, nWidth, nHeight, &dcMem,
                    nXSrc, nYSrc, nSrcWidth, nSrcHeight, SRCCOPY);

    // Put the original bitmap back
    dcMem.SelectObject(pOldBitmap);

    // Put the original palette back
    pDC->SelectPalette(pOldPalette, TRUE);
    pDC->RealizePalette();
}

