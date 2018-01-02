#ifndef KEYHOOK_HEADER
#define KEYHOOK_HEADER

#ifdef KEYHOOK_DLL
	#define KEYHOOK_EXPORT __declspec( dllexport )
#else
	#define KEYHOOK_EXPORT __declspec( dllimport )
#endif

#define DEFAULT_ZOOM_RATE	100

KEYHOOK_EXPORT void KHAttachHookDLL(HWND hwndParentWindow);
KEYHOOK_EXPORT void KHShowZoomWindow(BOOL bShow);
KEYHOOK_EXPORT BOOL KHIsWindowVisible();
KEYHOOK_EXPORT void KHEnableZoomWindow(BOOL);
KEYHOOK_EXPORT void KHSetZoomParams(int Width, int Height, WORD HotKey,
	WORD ModKey, int Rate, int Zoom, BOOL bPersist);

LRESULT CALLBACK MyKeyboardProc(int, WPARAM, LPARAM);
void CreateZoomWindow(HWND hwndParentWindow);
void CloseZoomWindow();
void UpdateZoomWindow();
void SlowMouse();
void RestoreMouse();

#define ZOOMWIDTH  (MyWidth  * MyZoom)
#define ZOOMHEIGHT (MyHeight * MyZoom)
#define WINDOWWIDTH  (ZOOMWIDTH  + 2)
#define WINDOWHEIGHT (ZOOMHEIGHT + 2)
#define CURSORXOFFSET (-MyWidth  / 2)
#define CURSORYOFFSET (-MyHeight / 2)

#define ID_TIMER 132

#define ZOOMWINDOWNAME "ZoomWindow"
#define ZOOMCLASSNAME  "ZoomWindowClass"

#endif