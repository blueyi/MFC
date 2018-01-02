// USBDisk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include <stdio.h>

#include <dbt.h>						// For DeviceChange.
#include <winioctl.h>					// For DeviceIOCtl.

#define MAX_LOADSTRING 100

// Add fro USB Task.

// USB letters' container
TCHAR   szMoveDiskName[33];
TCHAR	szDrvName[33];
BOOL	bInitUSBs;
// Drive type names
#define DRVUNKNOWN		0
#define DRVFIXED		1
#define DRVREMOTE		2
#define DRVRAM			3
#define DRVCD			4
#define DRVREMOVE		5

// IOCTL control code
#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

//// The following structures all can find at MSDN.
// enumeration type specifies the various types of storage buses
typedef enum _STORAGE_BUS_TYPE {
    BusTypeUnknown = 0x00,
    BusTypeScsi,
    BusTypeAtapi,
    BusTypeAta,
    BusType1394,
    BusTypeSsa,
    BusTypeFibre,
    BusTypeUsb,
    BusTypeRAID,
    BusTypeMaxReserved = 0x7F
} STORAGE_BUS_TYPE, *PSTORAGE_BUS_TYPE;

// retrieve the storage device descriptor data for a device. 
typedef struct _STORAGE_DEVICE_DESCRIPTOR {
  ULONG  Version;
  ULONG  Size;
  UCHAR  DeviceType;
  UCHAR  DeviceTypeModifier;
  BOOLEAN  RemovableMedia;
  BOOLEAN  CommandQueueing;
  ULONG  VendorIdOffset;
  ULONG  ProductIdOffset;
  ULONG  ProductRevisionOffset;
  ULONG  SerialNumberOffset;
  STORAGE_BUS_TYPE  BusType;
  ULONG  RawPropertiesLength;
  UCHAR  RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_QUERY_TYPE {
  PropertyStandardQuery = 0,
  PropertyExistsQuery,
  PropertyMaskQuery,
  PropertyQueryMaxDefined

} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_PROPERTY_ID {
  StorageDeviceProperty = 0,
  StorageAdapterProperty,
  StorageDeviceIdProperty

} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

// retrieve the properties of a storage device or adapter. 
typedef struct _STORAGE_PROPERTY_QUERY {
  STORAGE_PROPERTY_ID  PropertyId;
  STORAGE_QUERY_TYPE  QueryType;
  UCHAR  AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;

/****************************************************************************
*
*    FUNCTION: GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
*
*    PURPOSE:  get the info of specified device
*
****************************************************************************/
BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
{
	STORAGE_PROPERTY_QUERY	Query;	// input param for query
	DWORD dwOutBytes;				// IOCTL output length
	BOOL bResult;					// IOCTL return val

	// specify the query type
	Query.PropertyId = StorageDeviceProperty;
	Query.QueryType = PropertyStandardQuery;

	// Query using IOCTL_STORAGE_QUERY_PROPERTY 
	bResult = ::DeviceIoControl(hDevice,			// device handle
			IOCTL_STORAGE_QUERY_PROPERTY,			// info of device property
			&Query, sizeof(STORAGE_PROPERTY_QUERY),	// input data buffer
			pDevDesc, pDevDesc->Size,				// output data buffer
			&dwOutBytes,							// out's length
			(LPOVERLAPPED)NULL);					

	return bResult;
}

/****************************************************************************
*
*    FUNCTION: chFirstDriverFrameMask(ULONG unitmask)
*
*    PURPOSE:  get the logic name of driver
*
****************************************************************************/
char chFirstDriveFromMask (ULONG unitmask)
{

      char i;
      for (i = 0; i < 26; ++i)  
      {
           if (unitmask & 0x1) 
				break;
            unitmask = unitmask >> 1;
      }
    return (i + 'A');
}

/****************************************************************************
*
*    FUNCTION: ReInitUSB_Disk_Letter()
*
*    PURPOSE:  get the usb disks, and filling the 'szMoveDiskName' with them
*
****************************************************************************/
void ReInitUSB_Disk_Letter()
{
	int k = 0;
	DWORD			MaxDriveSet, CurDriveSet;
	DWORD			drive, drivetype;
	TCHAR			szBuf[300];
	HANDLE			hDevice;
	PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;

	for(k=0; k<26; k++)
		szMoveDiskName[k] = '\0';	
	k = 1;		
	// Get available drives we can monitor
	MaxDriveSet = CurDriveSet = 0;

	MaxDriveSet = GetLogicalDrives();
	CurDriveSet = MaxDriveSet;
	for ( drive = 0; drive < 32; ++drive )  
	{
		if ( MaxDriveSet & (1 << drive) )  
		{
			DWORD temp = 1<<drive;
			_stprintf( szDrvName, _T("%c:\\"), 'A'+drive );
			switch ( GetDriveType( szDrvName ) )  
			{
				case 0:					// The drive type cannot be determined.
				case 1:					// The root directory does not exist.
					drivetype = DRVUNKNOWN;
					break;
				case DRIVE_REMOVABLE:	// The drive can be removed from the drive.
					drivetype = DRVREMOVE;
					szMoveDiskName[k] = chFirstDriveFromMask(temp);
					szMoveDiskName[0]=k;
					k++;
					break;
				case DRIVE_CDROM:		// The drive is a CD-ROM drive.
					break;
				case DRIVE_FIXED:		// The disk cannot be removed from the drive.
					drivetype = DRVFIXED;
					sprintf(szBuf, "\\\\?\\%c:", 'A'+drive);
					hDevice = CreateFile(szBuf, GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

					if (hDevice != INVALID_HANDLE_VALUE)
					{

						pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];

						pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

						if(GetDisksProperty(hDevice, pDevDesc))
						{
							if(pDevDesc->BusType == BusTypeUsb)
							{
								szMoveDiskName[k] = chFirstDriveFromMask(temp);
								szMoveDiskName[0]=k;
								k++;
							}
						}

						delete pDevDesc;
						CloseHandle(hDevice);
					}
					
					break;
				case DRIVE_REMOTE:		// The drive is a remote (network) drive.
					drivetype = DRVREMOTE;
					szMoveDiskName[k] = chFirstDriveFromMask(temp);
					szMoveDiskName[0]=k;
					k++;
					break;
				case DRIVE_RAMDISK:		// The drive is a RAM disk.
					drivetype = DRVRAM;
					break;
			}
		}
	}

}
///////////////////////////////////////////////////////////////////////////////////
// Global Variables:
HINSTANCE hInst;											// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];						// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_USBDISK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_USBDISK);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_USBDISK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_USBDISK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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
	int				wmId, wmEvent;
	PAINTSTRUCT		ps;
	HDC				hdc;
	TCHAR			szHello[256];
	//LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

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
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);

			if(bInitUSBs)
				strcpy(szHello, "\n\nNow analysing the usb disks of this machine.");
			else
				sprintf(szHello, "\n\nUSB disk(s) are: \n%s", &szMoveDiskName[1]);

			if(szMoveDiskName[0] == 0)
				strcpy(szHello, "\n\nThere is no any USB disks detected!");

			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			bInitUSBs = TRUE;

			ReInitUSB_Disk_Letter();

			bInitUSBs = FALSE;

			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, TRUE);
			break;
		case WM_DEVICECHANGE:	
			switch (wParam){
				case DBT_DEVICEARRIVAL:				// 
				case DBT_DEVICEREMOVECOMPLETE:		// We only concern about these two cases.
					{
						bInitUSBs = TRUE;

						ReInitUSB_Disk_Letter();

						bInitUSBs = FALSE;

						RECT rt;
						GetClientRect(hWnd, &rt);
						InvalidateRect(hWnd, &rt, TRUE);
					}
			}
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
