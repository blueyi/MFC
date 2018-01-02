#define STRICT
#include <windows.h>
#include <commctrl.h>

#define KEYHOOK_DLL
#include "KeyHook.h"

//-- Shared global data ---------------------------------------------

#pragma data_seg("SHARDATA")
WORD wMyHotkey = 0; // Must be set to something!!
WORD wMyModkey = 0;
HWND hwndZoom = NULL;
HHOOK hHook = NULL;
BOOL bEnabled = FALSE;
BOOL bPersist = FALSE;
int aiOldMouseParams[3] = { 0, 0, 0 };
BOOL bSlowMouse = TRUE;
BOOL bMouseIsSlow = FALSE;
HPALETTE hpalMyPal = NULL;
#pragma data_seg()

//-- Instance-specific global data ----------------------------------

HINSTANCE MyInst;
int MyRate, MyWidth, MyHeight, MyZoom;

//-- Exported functions ---------------------------------------------

void KHAttachHookDLL(HWND hwndParentWindow)
{
	if (hwndParentWindow)
	{
		CreateZoomWindow(hwndParentWindow);
		hHook = SetWindowsHookEx(WH_KEYBOARD,
			(HOOKPROC)MyKeyboardProc, (HINSTANCE)MyInst, NULL);
	}
	else
	{
		RestoreMouse();
		CloseZoomWindow();
		UnhookWindowsHookEx(hHook);
	}
}

void KHShowZoomWindow(BOOL bTrue)
{
	if (bTrue && bEnabled)
	{
		ShowWindow(hwndZoom, SW_SHOWNOACTIVATE);
		SlowMouse();
	}
	else
	{
		ShowWindow(hwndZoom, SW_HIDE);
		RestoreMouse();
	}
}

BOOL KHIsWindowVisible()
{
	return IsWindowVisible(hwndZoom);
}

void KHEnableZoomWindow(BOOL bState)
{
	bEnabled = bState;
	if (!bEnabled)
		KHShowZoomWindow(FALSE);
}

void KHSetZoomParams(int Width, int Height, WORD HotKey, WORD ModKey,
	int Rate, int Zoom, BOOL Persist)
{
	MyWidth = Width;
	MyHeight = Height;
	wMyHotkey = HotKey;
	wMyModkey = ModKey;
	bPersist = Persist;

	if(MyRate != Rate)
	{
		MyRate = Rate;
		if(hwndZoom)
		{
			KillTimer(hwndZoom, ID_TIMER);
			SetTimer(hwndZoom, ID_TIMER, MyRate, NULL);
		}
	}

	MyZoom = Zoom;
}

//-- Implementation functions ---------------------------------------

BOOL AreModifiersOn(WORD wMod)
{
	if(wMod & HOTKEYF_SHIFT)
		if(!(GetKeyState(VK_SHIFT) & 0x80))
			return FALSE;
	if(wMod & HOTKEYF_CONTROL)
		if(!(GetKeyState(VK_CONTROL) & 0x80))
			return FALSE;
	if(wMod & HOTKEYF_ALT)
		if(!(GetKeyState(VK_MENU) & 0x80))
			return FALSE;
	return TRUE;
}

LRESULT CALLBACK MyKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode == HC_ACTION && bEnabled)
	{
		if((GetKeyState(wMyHotkey) & 0x80) && AreModifiersOn(wMyModkey))
		{
			if (bPersist && IsWindowVisible(hwndZoom))
				KHShowZoomWindow(FALSE);
			else
				KHShowZoomWindow(TRUE);
			return TRUE; // Don't allow other apps to process key.
		}
		else if (!bPersist)
			KHShowZoomWindow(FALSE);
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void SetupPalette()
{
	if(hpalMyPal)
		DeleteObject(hpalMyPal);
	HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL);
	if((GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE))
	{
		int cColors = 1 << GetDeviceCaps(hdcScreen, BITSPIXEL);
		LOGPALETTE *plgpl;
		plgpl = (LOGPALETTE *)malloc(sizeof(LOGPALETTE) + cColors * sizeof(PALETTEENTRY));
		plgpl->palNumEntries = cColors;
		plgpl->palVersion = 0x300; // Windows version number for the structure
		GetSystemPaletteEntries(hdcScreen, 0, cColors, plgpl->palPalEntry);
		hpalMyPal = CreatePalette(plgpl);
		free(plgpl);
	}
	else
		hpalMyPal = NULL;
	DeleteDC(hdcScreen);
}

LRESULT CALLBACK ZoomWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bVisible = FALSE;
	switch(wMsg)
	{
		case WM_CREATE:
			SetTimer(hWnd, ID_TIMER, MyRate, NULL);
			SetupPalette();
			return TRUE;
		case WM_SHOWWINDOW:
			bVisible = (BOOL)wParam;
			if(bVisible)
				UpdateZoomWindow();
			break;
		case WM_TIMER:
			if(bVisible)
				UpdateZoomWindow();
			return TRUE;
		case WM_ERASEBKGND:
			return TRUE;
		case WM_PALETTECHANGED:
			SetupPalette();
			return TRUE;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return TRUE;
		case WM_DESTROY:
			KillTimer(hWnd, ID_TIMER);
			if(hpalMyPal)
				DeleteObject(hpalMyPal);
			return TRUE;
	}

	return(DefWindowProc(hWnd, wMsg, wParam, lParam));
}

void CreateZoomWindow(HWND hwndParentWindow)
{
	if(hwndZoom)
		return;
	static BOOL bClassRegistered = FALSE;
	if(!bClassRegistered)
	{
		WNDCLASS ZoomClass;
		ZoomClass.style         = 0;//CS_SAVEBITS;
		ZoomClass.lpfnWndProc   = ZoomWndProc;
		ZoomClass.cbClsExtra    = 0;
		ZoomClass.cbWndExtra    = 0;
		ZoomClass.hInstance     = MyInst;
		ZoomClass.hIcon         = NULL;
		ZoomClass.hCursor       = NULL;
		ZoomClass.hbrBackground = NULL;
		ZoomClass.lpszMenuName  = NULL;
		ZoomClass.lpszClassName = ZOOMCLASSNAME;
		RegisterClass(&ZoomClass);
		bClassRegistered = TRUE;
	}
	POINT pt;
	GetCursorPos(&pt);
	hwndZoom = CreateWindow
	(
		ZOOMCLASSNAME,
		ZOOMWINDOWNAME,
		WS_POPUP | WS_BORDER,
		pt.x + CURSORXOFFSET + MyWidth,
		pt.y + CURSORYOFFSET + MyHeight,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		hwndParentWindow,
		NULL,
		(HINSTANCE)MyInst,
		NULL
	);
	KHShowZoomWindow(FALSE);
}

void CloseZoomWindow()
{
	if(!hwndZoom)
		return;
	PostMessage(hwndZoom, WM_CLOSE, 0, 0);
	hwndZoom = NULL;
}

void UpdateZoomWindow()
{
	HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL);
	POINT pt;
	static BOOL flash;

	GetCursorPos(&pt);
	int maxx = GetDeviceCaps(hdcScreen, HORZRES) - MyWidth;
	int maxy = GetDeviceCaps(hdcScreen, VERTRES) - MyHeight;
	int sourcex = pt.x + CURSORXOFFSET;
	int sourcey = pt.y + CURSORYOFFSET;
	if(sourcex < 0)
		sourcex = 0;
	if(sourcex > maxx)
		sourcex = maxx;
	if(sourcey < 0)
		sourcey = 0;
	if(sourcey > maxy)
		sourcey = maxy;
	int windowx = sourcex + MyWidth;
	int windowy = sourcey + MyHeight;
	maxx = GetDeviceCaps(hdcScreen, HORZRES) - WINDOWWIDTH;
	maxy = GetDeviceCaps(hdcScreen, VERTRES) - WINDOWHEIGHT;
	if(windowx > maxx)
	{
		windowx = maxx;
		if(windowy > maxy)
			windowy = sourcey - WINDOWHEIGHT;
	}
	if(windowy > maxy)
		windowy = maxy;
	SetWindowPos(hwndZoom, HWND_TOPMOST, windowx, windowy, WINDOWWIDTH, WINDOWHEIGHT, SWP_NOACTIVATE);
	HDC hdcWindow = GetDC(hwndZoom);
	HPALETTE hpalScreenOld, hpalWindowOld;
	if(hpalMyPal)
	{
		hpalScreenOld = SelectPalette(hdcScreen, hpalMyPal, FALSE);
		hpalWindowOld = SelectPalette(hdcWindow, hpalMyPal, FALSE);
		RealizePalette(hdcScreen);
	}
	StretchBlt(hdcWindow, 0, 0, ZOOMWIDTH, ZOOMHEIGHT, hdcScreen, sourcex, sourcey, MyWidth, MyHeight, SRCCOPY);
	int xoffset = (pt.x - sourcex) * MyZoom;
	int yoffset = (pt.y - sourcey) * MyZoom;
	HGDIOBJ hpenOld;
	if(flash)
		hpenOld = SelectObject(hdcWindow, GetStockObject(BLACK_PEN));
	else
		hpenOld = SelectObject(hdcWindow, GetStockObject(WHITE_PEN));
	flash = !flash;
	MoveToEx(hdcWindow, xoffset - 1, yoffset - 1, NULL);
	LineTo(hdcWindow, xoffset + MyZoom, yoffset - 1);
	LineTo(hdcWindow, xoffset + MyZoom, yoffset + MyZoom);
	LineTo(hdcWindow, xoffset - 1, yoffset + MyZoom);
	LineTo(hdcWindow, xoffset - 1, yoffset - 1);
	SelectObject(hdcWindow, hpenOld);
	if(hpalMyPal)
	{
		SelectPalette(hdcScreen, hpalScreenOld, FALSE);
		SelectPalette(hdcWindow, hpalWindowOld, FALSE);
	}
	ReleaseDC(hwndZoom, hdcWindow);
	DeleteDC(hdcScreen);
}

void RestoreMouse()
{
	if(bMouseIsSlow)
	{
		SystemParametersInfo
		(
			SPI_SETMOUSE,  // system parameter to set
			0,
			aiOldMouseParams, // the two mouse threshold values and the mouse speed
			0
		);
		bMouseIsSlow = FALSE;
	}
}

void SlowMouse()
{
	if(bSlowMouse && ! bMouseIsSlow)
	{
		SystemParametersInfo
		(
			SPI_GETMOUSE,     // system parameter to query
			0,
			aiOldMouseParams, // the two mouse threshold values and the mouse speed
			0
		);
		int aiNewMouseParams[3] = { 0, 0, 0 };
		SystemParametersInfo
		(
			SPI_SETMOUSE,  // system parameter to set
			0,
			aiNewMouseParams, // the two mouse threshold values and the mouse speed
			0
		);
		bMouseIsSlow = TRUE;
	}
}

BOOL WINAPI DllMain(HANDLE hModule, ULONG dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
		MyInst = (HINSTANCE)hModule;
	return TRUE;
}
