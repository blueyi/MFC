/* File custom.c
 * (custom control implementation)
 */

#include "custom.h"

#include <windows.h>
#include <windowsx.h>
#include <wingdi.h>
#include <uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <shlwapi.h>


// The theming class we use for painting of this control:
#define CUSTOM_THEME_CLASS    L"BUTTON"


// Pointers to the few UXTHEME.DLL functions we use. If we decide to not use UXTHEME.DLL
// we just make fn_OpenThemeData to point to our dummy implementation, returning NULL.
// This consrquently guarantees we never attempt to call the other UXTHEME functions:
static HMODULE hDllUxTheme = NULL;
static HTHEME  (WINAPI* fn_OpenThemeData)(HWND,const WCHAR*) = NULL;
static HTHEME  (WINAPI* fn_CloseThemeData)(HTHEME) = NULL;
static HRESULT (WINAPI* fn_DrawThemeBackground)(HTHEME,HDC,int,int,const RECT*,const RECT*) = NULL;
static HRESULT (WINAPI* fn_DrawThemeParentBackground)(HWND,HDC,RECT*) = NULL;
static HRESULT (WINAPI* fn_DrawThemeText)(HTHEME,HDC,int,int,const WCHAR*,int,DWORD,DWORD,const RECT*) = NULL;
static HRESULT (WINAPI* fn_GetThemeBackgroundContentRect)(HTHEME,HDC,int,int,const RECT*,RECT*) = NULL;
static BOOL    (WINAPI* fn_IsThemeBackgroundPartiallyTransparent)(HTHEME,int,int) = NULL;


// Custom control's data
typedef struct CustomData {
    HWND hwnd;
    HTHEME hTheme;
    HFONT hFont;

    // Control-specific 16-bits of style:
    DWORD dwStyle          : 16;

    // Various flags for internal state:
    DWORD fNoRedraw        : 1;
    DWORD fPushedWithMouse : 1;
    DWORD fPushedWithKey   : 1;
    DWORD fMouseDown       : 1;
    DWORD fHot             : 1;
    DWORD fFocus           : 1;
} CustomData;


static void
CustomPaint(CustomData* pData, HDC hDC, RECT* rcDirty, BOOL bErase)
{
    WCHAR szBuffer[64];
    DWORD dwUiState;
    RECT rcClient;
    RECT rcContent;
    DWORD dtFlags;

    GetClientRect(pData->hwnd, &rcClient);
    dwUiState = SendMessage(pData->hwnd, WM_QUERYUISTATE, 0, 0);
    GetWindowTextW(pData->hwnd, szBuffer, sizeof(szBuffer) / sizeof(WCHAR));

    dtFlags = DT_SINGLELINE | DT_CENTER | DT_VCENTER;
    if(dwUiState & UISF_HIDEACCEL)
        dtFlags |= DT_HIDEPREFIX;

    /* We set this even for themed code path. If the current theme definition
     * does not specify a font, DrawThemeText() fallbacks to this. */
    if(pData->hFont)
        SelectObject(hDC, pData->hFont);

    if(pData->hTheme) {
        /* Themed code path */
        int iPart = BP_PUSHBUTTON;
        int iState;

        if(!IsWindowEnabled(pData->hwnd))
            iState = PBS_DISABLED;
        else if(pData->fPushedWithMouse || pData->fPushedWithKey)
            iState = PBS_PRESSED;
        else if(pData->fHot)
            iState = PBS_HOT;
        else if(pData->fFocus  ||  (pData->dwStyle & XXS_DEFAULT))
            iState = PBS_DEFAULTED;
        else
            iState = PBS_NORMAL;

        if(fn_IsThemeBackgroundPartiallyTransparent(pData->hTheme, iPart, iState))
            fn_DrawThemeParentBackground(pData->hwnd, hDC, &rcClient);
        fn_DrawThemeBackground(pData->hTheme, hDC, iPart, iState, &rcClient, &rcClient);

        fn_GetThemeBackgroundContentRect(pData->hTheme, hDC, iPart, iState, &rcClient, &rcContent);

        fn_DrawThemeText(pData->hTheme, hDC, iPart, iState, szBuffer, -1, dtFlags, 0, &rcContent);
    } else {
        /* Unthemed code path */
        UINT uState = DFCS_BUTTONPUSH;

        if(pData->dwStyle & XXS_DEFAULT) {
            Rectangle(hDC, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
            InflateRect(&rcClient, -1, -1);
        }

        if(!IsWindowEnabled(pData->hwnd))
            uState |= DFCS_INACTIVE;
        else if(pData->fPushedWithMouse || pData->fPushedWithKey)
            uState |= DFCS_PUSHED;
        else if(pData->fHot || pData->fFocus)
            uState |= DFCS_HOT;
        DrawFrameControl(hDC, &rcClient, DFC_BUTTON, uState);

        SetRect(&rcContent, 4, 4, rcClient.right - 3, rcClient.bottom - 3);

        SetBkMode(hDC, TRANSPARENT);
        DrawTextW(hDC, szBuffer, -1, &rcClient, dtFlags);
    }

    /* Paint focus rect */
    if(pData->fFocus && !(dwUiState & UISF_HIDEFOCUS))
        DrawFocusRect(hDC, &rcContent);
}

static void
CustomDoubleBuffer(CustomData* pData, PAINTSTRUCT* pPaintStruct)
{
    int cx = pPaintStruct->rcPaint.right - pPaintStruct->rcPaint.left;
    int cy = pPaintStruct->rcPaint.bottom - pPaintStruct->rcPaint.top;
    HDC hMemDC;
    HBITMAP hBmp;
    HBITMAP hOldBmp;
    POINT ptOldOrigin;

    hMemDC = CreateCompatibleDC(pPaintStruct->hdc);
    hBmp = CreateCompatibleBitmap(pPaintStruct->hdc, cx, cy);
    hOldBmp = SelectObject(hMemDC, hBmp);

    OffsetViewportOrgEx(hMemDC, -(pPaintStruct->rcPaint.left),
                        -(pPaintStruct->rcPaint.top), &ptOldOrigin);
    CustomPaint(pData, hMemDC, &pPaintStruct->rcPaint, TRUE);
    SetViewportOrgEx(hMemDC, ptOldOrigin.x, ptOldOrigin.y, NULL);

    BitBlt(pPaintStruct->hdc, pPaintStruct->rcPaint.left, pPaintStruct->rcPaint.top,
           cx, cy, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBmp);
    DeleteObject(hBmp);
    DeleteDC(hMemDC);
}

static LRESULT CALLBACK
CustomProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CustomData* pData = (CustomData*) GetWindowLongPtr(hwnd, 0);

    switch(uMsg) {
        case WM_ERASEBKGND:
            return FALSE;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if(pData->dwStyle & XXS_DOUBLEBUFFER)
                CustomDoubleBuffer(pData, &ps);
            else
                CustomPaint(pData, ps.hdc, &ps.rcPaint, ps.fErase);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_PRINTCLIENT:
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            CustomPaint(pData, (HDC) wParam, &rc, TRUE);
            return 0;
        }

        case WM_SETREDRAW:
            pData->fNoRedraw = !wParam;
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_MOUSEMOVE:
        {
            DWORD dwPos;
            POINT pt;
            RECT rect;
            BOOL fInside;

            GetClientRect(hwnd, &rect);
            dwPos = GetMessagePos();
            pt.x =  GET_X_LPARAM(dwPos);
            pt.y =  GET_Y_LPARAM(dwPos);
            ScreenToClient(hwnd, &pt);
            fInside = PtInRect(&rect, pt);

            if(pData->fMouseDown) {
                if(pData->fPushedWithMouse != fInside) {
                    pData->fPushedWithMouse = fInside;
                    if(!pData->fNoRedraw)
                        InvalidateRect(hwnd, NULL, TRUE);
                }
            } else {
                if(pData->fHot != fInside) {
                    pData->fHot = fInside;
                    if(!pData->fNoRedraw)
                        InvalidateRect(hwnd, NULL, TRUE);

                    if(fInside) {
                        /* Ask for tacking WM_MOUSELEAVE */
                        TRACKMOUSEEVENT tme = { 0 };
                        pData->fHot = TRUE;
                        tme.cbSize = sizeof(TRACKMOUSEEVENT);
                        tme.dwFlags = TME_LEAVE;
                        tme.hwndTrack = hwnd;
                        TrackMouseEvent(&tme);
                    }
                }
            }
            return 0;
        }

        case WM_MOUSELEAVE:
            pData->fHot = FALSE;
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
            pData->fFocus = (uMsg == WM_SETFOCUS);
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_LBUTTONDOWN:
            pData->fPushedWithMouse = TRUE;
            pData->fMouseDown = TRUE;
            SetFocus(hwnd);
            SetCapture(hwnd);
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_LBUTTONUP:
            if(pData->fPushedWithMouse)
                SendMessage(GetParent(hwnd), WM_COMMAND, GetWindowLong(hwnd, GWL_ID), 0);
            pData->fMouseDown = FALSE;
            pData->fPushedWithMouse = FALSE;
            ReleaseCapture();
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_CAPTURECHANGED:
            pData->fPushedWithMouse = FALSE;
            pData->fMouseDown = FALSE;
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_KEYDOWN:
            if(wParam == VK_SPACE) {
                pData->fPushedWithKey = TRUE;
                if(!pData->fNoRedraw)
                    InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;

        case WM_KEYUP:
            if(wParam == VK_SPACE) {
                SendMessage(GetParent(hwnd), WM_COMMAND, GetWindowLong(hwnd, GWL_ID), 0);
                pData->fPushedWithKey = FALSE;
                if(!pData->fNoRedraw)
                    InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;

        case WM_SETFONT:
            pData->hFont = (HFONT) wParam;
            if((BOOL) lParam  &&  !pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_GETFONT:
            return (LRESULT) pData->hFont;

        case WM_STYLECHANGED:
            if(wParam == GWL_STYLE) {
                STYLESTRUCT* ss = (STYLESTRUCT*) lParam;
                pData->dwStyle = ss->styleNew;
            }
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_UPDATEUISTATE:
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            break;

        case WM_THEMECHANGED:
            if(pData->hTheme)
                fn_CloseThemeData(pData->hTheme);
            pData->hTheme = fn_OpenThemeData(hwnd, CUSTOM_THEME_CLASS);
            if(!pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_GETDLGCODE:
            if(pData->dwStyle & XXS_DEFAULT)
                return DLGC_BUTTON | DLGC_DEFPUSHBUTTON;
            else
                return DLGC_BUTTON | DLGC_UNDEFPUSHBUTTON;

        /* Using DLGC_BUTTON in WM_GETDLGCODE makes a dialog to try switching
         * between BS_DEFPUSHBUTTON and BS_PUSHBUTTON to reflect focus. */
        case BM_SETSTYLE:
            if(wParam & BS_DEFPUSHBUTTON)
                pData->dwStyle |= XXS_DEFAULT;
            else
                pData->dwStyle &= ~XXS_DEFAULT;
            if(lParam  &&  !pData->fNoRedraw)
                InvalidateRect(hwnd, NULL, TRUE);
            break;

        case WM_CREATE:
            DefWindowProc(hwnd, uMsg, wParam, lParam);
            pData->hTheme = fn_OpenThemeData(hwnd, CUSTOM_THEME_CLASS);
            return 0;

        case WM_DESTROY:
            if(pData->hTheme) {
                fn_CloseThemeData(pData->hTheme);
                pData->hTheme = NULL;
            }
            break;

        case WM_NCCREATE:
            if(!DefWindowProc(hwnd, uMsg, wParam, lParam))
                return FALSE;
            pData = (CustomData*) malloc(sizeof(CustomData));
            if(pData == NULL)
                return FALSE;
            ZeroMemory(pData, sizeof(CustomData));
            pData->hwnd = hwnd;
            pData->dwStyle = ((CREATESTRUCT*)lParam)->style;
            SetWindowLongPtr(hwnd, 0, (LONG_PTR)pData);
            return TRUE;

        case WM_NCDESTROY:
            if(pData != NULL)
                free(pData);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static BOOL
ShouldUseUxThemeDll(void)
{
    HMODULE hDll;
    DWORD dwMajorVersion = 0;

    hDll = LoadLibrary(_T("COMCTL32.DLL"));
    if(hDll != NULL) {
        DLLGETVERSIONPROC fn_DllGetVersion;
        DLLVERSIONINFO vi;

        fn_DllGetVersion = (DLLGETVERSIONPROC) GetProcAddress(hDll, "DllGetVersion");
        if(fn_DllGetVersion != NULL) {
            vi.cbSize = sizeof(DLLVERSIONINFO);
            fn_DllGetVersion(&vi);
            dwMajorVersion = vi.dwMajorVersion;
        }
        FreeLibrary(hDll);
    }

    return (dwMajorVersion >= 6);
}

static HTHEME WINAPI
dummy_OpenThemeData(HWND hwnd, const WCHAR* pswzClassName)
{
    return NULL;
}

static void
LoadUxThemeDll(void)
{
    fn_OpenThemeData = NULL;

    if(ShouldUseUxThemeDll())
        hDllUxTheme = LoadLibrary(_T("UXTHEME.DLL"));
    else
        hDllUxTheme = NULL;

    if(hDllUxTheme) {
        fn_OpenThemeData = (HTHEME (WINAPI*)(HWND,const WCHAR*))
                    GetProcAddress(hDllUxTheme, "OpenThemeData");
        fn_CloseThemeData = (HTHEME (WINAPI*)(HTHEME))
                    GetProcAddress(hDllUxTheme, "CloseThemeData");
        fn_DrawThemeBackground = (HRESULT (WINAPI*)(HTHEME,HDC,int,int,const RECT*,const RECT*))
                    GetProcAddress(hDllUxTheme, "DrawThemeBackground");
        fn_DrawThemeParentBackground = (HRESULT (WINAPI*)(HWND,HDC,RECT*))
                    GetProcAddress(hDllUxTheme, "DrawThemeParentBackground");
        fn_DrawThemeText = (HRESULT (WINAPI*)(HTHEME,HDC,int,int,const WCHAR*,int,DWORD,DWORD,const RECT*))
                    GetProcAddress(hDllUxTheme, "DrawThemeText");
        fn_IsThemeBackgroundPartiallyTransparent = (BOOL (WINAPI*)(HTHEME,int,int))
                    GetProcAddress(hDllUxTheme, "IsThemeBackgroundPartiallyTransparent");
        fn_GetThemeBackgroundContentRect = (HRESULT (WINAPI*)(HTHEME,HDC,int,int,const RECT*,RECT*))
                    GetProcAddress(hDllUxTheme, "GetThemeBackgroundContentRect");

        if(fn_OpenThemeData == NULL || fn_CloseThemeData == NULL || fn_DrawThemeText == NULL ||
           fn_DrawThemeBackground == NULL || fn_DrawThemeParentBackground == NULL ||
           fn_IsThemeBackgroundPartiallyTransparent == NULL ||
           fn_GetThemeBackgroundContentRect == NULL)
        {
            FreeLibrary(hDllUxTheme);
            hDllUxTheme = NULL;
        }
    }

    if(hDllUxTheme == NULL)
        fn_OpenThemeData = dummy_OpenThemeData;
}

void WINAPI
CustomRegister(void)
{
    WNDCLASS wc = { 0 };

    LoadUxThemeDll();

    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CustomProc;
    wc.cbWndExtra = sizeof(CustomData*);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = CUSTOM_WC;
    RegisterClass(&wc);
}

void WINAPI
CustomUnregister(void)
{
    UnregisterClass(CUSTOM_WC, NULL);
    if(hDllUxTheme != NULL) {
        FreeLibrary(hDllUxTheme);
        hDllUxTheme = NULL;
    }
}
