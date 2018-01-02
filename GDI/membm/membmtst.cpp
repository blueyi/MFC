// membmtst.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

//explicit bitmap bits
const int iXSize = 256;
const int iXLineSize = iXSize * sizeof( RGBQUAD );
const int iYSize = 256;
BYTE abBits[iYSize][iXLineSize];

//bitmap canvas
MChMemBm bmCanvas;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
									 HINSTANCE hPrevInstance,
									 LPTSTR    lpCmdLine,
									 int       nCmdShow)
{
	//initialize bitmap bits
	for( int j = 0; j < iYSize; ++j )
	{
		for(int i = 0; i < iXLineSize; ++i )
		{
			abBits[j][i] = j;
		}
	}

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MEMBMTST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	try
	{

		// Perform application initialization:
		if (!InitInstance (hInstance, nCmdShow)) 
		{
			return FALSE;
		}

		hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MEMBMTST);

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	catch( MException& ex )
	{
		MessageBox(NULL, ex.GetMsg(), M_L("Error"), MB_OK);
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
#ifndef UNDER_CE		
	WNDCLASSEX
#else
	WNDCLASS
#endif 
		wcls;

	wcls.style			= CS_HREDRAW | CS_VREDRAW;
	wcls.lpfnWndProc	= (WNDPROC)WndProc;
	wcls.cbClsExtra		= 0;
	wcls.cbWndExtra		= 0;
	wcls.hInstance		= hInstance;
#ifndef UNDER_CE
	wcls.cbSize			= sizeof(wcls);
	wcls.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MEMBMTST);
	wcls.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcls.lpszMenuName	= (LPCTSTR)IDC_MEMBMTST;
#else
	wcls.hIcon			= NULL;
	wcls.hCursor		= NULL;
	wcls.lpszMenuName	= NULL;
#endif
	wcls.hbrBackground	= NULL;
	wcls.lpszClassName	= szWindowClass;

#ifndef UNDER_CE
	wcls.hIconSm		= LoadIcon(wcls.hInstance, (LPCTSTR)IDI_SMALL);
#endif //UNDER_CE

	return 
#ifndef UNDER_CE
		RegisterClassEx
#else
		RegisterClass
#endif
		(&wcls);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	UINT nStyle =
#ifndef UNDER_CE
		WS_OVERLAPPEDWINDOW
#else
		WS_POPUP
#endif
		;

	MChRect rInitialExt;

#ifdef UNDER_CE
	rInitialExt.right = GetSystemMetrics(SM_CXSCREEN);
	rInitialExt.bottom = GetSystemMetrics(SM_CYSCREEN);
#else
	rInitialExt.right = GetSystemMetrics(SM_CXSCREEN) / 2;
	rInitialExt.bottom = GetSystemMetrics(SM_CYSCREEN) / 2;
#endif

	hWnd = CreateWindow(szWindowClass, szTitle, nStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, rInitialExt.GetWidth(), rInitialExt.GetHeight(), 
		NULL, NULL, hInst, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Paint( HWND hWnd )
{
	MChMemBm bmMem8( hInst, IDB_BMP8 );	//8 bpp bitmap(256 colors)
	MChMemBm bmMem4( hInst, IDB_BMP4 ); //4 bpp bitmap(16 colors)
	MChMemBm bmMem24( hInst, IDB_BMP24 ); //24 bpp bitmap(16M colors)
#ifndef UNDER_CE
	MChMemBm bmFile(NULL, _T("avatar.bmp")); //load from image file
#endif //UNDER_CE
	MChMemBm bmExplicit( bmCanvas, iXSize, iYSize, 1, 32, abBits, NULL ); //explicit creation of 32 bit bitmap

	bmMem8.Draw( bmCanvas, 20, 20 );
	bmMem4.Draw( bmCanvas, 20, 70 );
	bmMem24.Draw( bmCanvas, 20, 120 );

#ifndef UNDER_CE	
	bmFile.Draw( bmCanvas, 500, 20 );
#endif //UNDER_CE

	bmMem8.Draw( bmCanvas, 70, 20, 60, 30 );
	bmMem4.Draw( bmCanvas, 70, 70, 60, 30 );
	bmMem24.Draw( bmCanvas, 70, 120, 60, 30 );

	bmMem8.DrawTrans( bmCanvas, 140, 20, 60, 30, RGB(0,0,255) );
	bmMem4.DrawTrans( bmCanvas, 140, 70, 60, 30, RGB(0,0,255) );
	bmMem24.DrawTrans( bmCanvas, 140, 120, 60, 30, RGB(0,0,255) );

	//get snapshot inside this dc
	MChMemBm bmSnap( bmCanvas, NULL, 40, 40, 80, 80 );
	bmSnap.Draw( bmCanvas, 20, 200 );

	//get screen snapshot, draw red line on it, and draw it in view
	bmSnap.Cleanup();
	bmSnap.Create(NULL, NULL, 40, 40, 80, 80 );
	HPEN hPen = CreatePen( PS_SOLID, 1, RGB(255,0,0) );
	HANDLE hOldPen = SelectObject(bmSnap, hPen);
	MoveToEx( bmSnap, 0, 0, NULL );
	LineTo( bmSnap, 80, 80 );
	SelectObject(bmSnap, hOldPen);
	DeleteObject(hPen);
	bmSnap.Draw( bmCanvas, 20, 300 );

	//pattern filling
	bmSnap.Fill( bmCanvas, 200, 20, 200, 200, true );

#ifndef UNDER_CE
	//test alpha blending: AC_SRC_OVER and 0 are mandatory so far,
	//128 = 50% opacity( 0 - 255), 0 - do not use bitmap's alpha channel
	BLENDFUNCTION blendFunc = {AC_SRC_OVER, 0, 128, 0};
	bmSnap.DrawAlpha( bmCanvas, 200, 250, 80, 80, blendFunc );
#endif //UNDER_CE

	//explicit bitmap drawing
	bmExplicit.Draw(bmCanvas, 300, 250);

	//get entire window snapshot
	bmSnap.Cleanup();
	bmSnap.Create( bmCanvas, NULL, 100, 100, 200, 200 );

	HGDIOBJ hOldBrush = SelectObject(bmCanvas, GetStockObject(NULL_BRUSH) );
	Rectangle( bmCanvas, 100, 100, 300, 300 );

#ifndef MCH_USE_DDB
	//apply smoothing filter
	const MChMemBm::MChFilter aFilter = {
		1,  1, 1,
		1,  4, 1,
		1,  1, 1
	};
	bmSnap.ApplyFilter(aFilter);
#endif //MCH_USE_DDB

	Rectangle(bmCanvas, 499, 119, bmSnap.GetWidth() + 501, bmSnap.GetHeight() + 121);
	bmSnap.Draw(bmCanvas, 500, 120 );

	SelectObject(bmCanvas, hOldBrush);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD , LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	MChRect rt;
	PAINTSTRUCT ps;
	std::ofstream ofs;
	MByteString imgBuff;
	HANDLE hBmpFile;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_SAVE:
			//save canvas to the file
			bmCanvas.GetAsDIB( imgBuff );
			hBmpFile = CreateFile(_T("snapshot.bmp"), 
				GENERIC_WRITE, 
				0, 
				NULL, 
				CREATE_ALWAYS, 
				FILE_ATTRIBUTE_NORMAL, 
				NULL); 

			if (hBmpFile != INVALID_HANDLE_VALUE) 
			{ 
				DWORD dwBytesWrite = 0;    
				WriteFile(hBmpFile, imgBuff.data(), imgBuff.size(), &dwBytesWrite, NULL); 
				CloseHandle(hBmpFile); 
			} 
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		// TODO: Add any drawing code here...
		GetClientRect(hWnd, &rt);

		if( bmCanvas && ((bmCanvas.GetWidth() != rt.right) || (bmCanvas.GetHeight() != rt.bottom)) )
			bmCanvas.Cleanup();

		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);

		if( rt.GetWidth() && rt.GetHeight() && !bmCanvas )
		{
			bmCanvas.Create(hdc, NULL, 0, 0, rt.right, rt.bottom);
			FillRect( bmCanvas, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH) );
			Paint( hWnd );
		}

		bmCanvas.Draw(hdc, 0, 0);

		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		if( bmCanvas )
		{
			//draw rect in non-client area filling it with current pixel color
			COLORREF clColor = bmCanvas.GetPixel(LOWORD(lParam), HIWORD(lParam));

			MChDC hWndDC;
			hWndDC.GetWindowDC( hWnd ); 
			RECT rColor;
			rColor.left = 200;
			rColor.top = 2;
			rColor.right = 221;
			rColor.bottom = 23;
			MChGDIObj hBr(CreateSolidBrush(clColor));
			FillRect( hWndDC, &rColor, (HBRUSH)(HGDIOBJ)hBr );
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
