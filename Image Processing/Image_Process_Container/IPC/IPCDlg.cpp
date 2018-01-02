// IPCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPC.h"
#include "IPCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DLG_TOOLS_WIDTH 300

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCDlg dialog

CIPCDlg::CIPCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CIPCDlg::~CIPCDlg()
{
}

void CIPCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPCDlg, CDialog)
	//{{AFX_MSG_MAP(CIPCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_FILE_OPEN, OnFileOpen)
	ON_COMMAND(IDM_SELECT_ROI, OnSelectRoi)
	ON_COMMAND(IDM_SHOW_ROI, OnShowRoi)
	ON_COMMAND(IDM_DETECT_EDGE, OnDetectEdge)
	ON_COMMAND(IDM_OPERATION_NULL, OnOperationNull)
	ON_COMMAND(IDM_OPERATION_BRUSH, OnOperationBrush)
	ON_COMMAND(IDM_OPERATION_ERASE, OnOperationErase)
	ON_COMMAND(IDM_OPERATION_DRAW, OnOperationDraw)
	ON_COMMAND(IDM_OPERATION_CUT, OnOperationCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCDlg message handlers

BOOL CIPCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int iTopBlank = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
	int iBottomBlank = GetSystemMetrics(SM_CYBORDER);
	int iLeftBlank = GetSystemMetrics(SM_CXBORDER);
	int iRightBlank = iLeftBlank;

	//creat and show tools dialog
	CRect rtDlgTools;
	rtDlgTools.left = GetSystemMetrics(SM_CXSCREEN) - DLG_TOOLS_WIDTH;
	rtDlgTools.right = GetSystemMetrics(SM_CXSCREEN);// - iRightBlank;
	rtDlgTools.top = 0;
	rtDlgTools.bottom = GetSystemMetrics(SM_CYSCREEN) - iTopBlank;// - iBottomBlank;
	if(m_dlgTools.GetSafeHwnd() == NULL)
	{
		m_dlgTools.Create(IDD_DLG_TOOLS,this);
		m_dlgTools.SetParent(this);
	}
	m_dlgTools.MoveWindow(&rtDlgTools);
	m_dlgTools.ShowWindow(SW_SHOW);

	//creat and show image container dialog
	CRect rtDlgImageContainer;
	rtDlgImageContainer.left = 0;//iLeftBlank;
	rtDlgImageContainer.right = GetSystemMetrics(SM_CXSCREEN) - DLG_TOOLS_WIDTH - 1;
	rtDlgImageContainer.top = 0;
	rtDlgImageContainer.bottom = GetSystemMetrics(SM_CYSCREEN) - iTopBlank;// - iBottomBlank;
	if(m_dlgImageContainer.GetSafeHwnd() == NULL)
	{
		m_dlgImageContainer.Create(IDD_DLG_IMAGECONTAINER,this);
		m_dlgImageContainer.SetParent(this);
	}
	m_dlgImageContainer.MoveWindow(&rtDlgImageContainer);
	m_dlgImageContainer.ShowWindow(SW_SHOW);

	ShowWindow(SW_SHOWMAXIMIZED);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIPCDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"BMP/JPG/PNG files|*.bmp;*.jpg;*.png|All files|*.*||"); 
	if (dlg.DoModal() == IDOK) 
	{
		CString filename = dlg.GetPathName();

		CxImage * pCxImage = m_dlgImageContainer.GetCxImage();

		if (NULL != pCxImage) 
		{
			delete pCxImage;
			pCxImage = NULL;
		}
		pCxImage = new CxImage();

		CString ext(FindExtension(filename));
		ext.MakeLower();
		if (ext == _T("")) return;
		
		int type = FindType(ext);
		switch(type) {
		case CXIMAGE_FORMAT_BMP:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_BMP)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_GIF:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_GIF)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_JPG:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_JPG)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_PNG:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_PNG)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_ICO:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_ICO)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_TIF:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_TIF)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_TGA:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_TGA)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_PCX:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_PCX)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_WBMP:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_WBMP)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_WMF:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_WMF)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_JP2:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_JP2)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_JPC:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_JPC)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_PGX:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_PGX)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_PNM:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_PNM)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_RAS:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_RAS)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case 16:	//CXIMAGE_FORMAT_JBG
			if (pCxImage->Load(filename, type)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_MNG:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_MNG)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_SKA:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_SKA)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		case CXIMAGE_FORMAT_RAW:
			if (pCxImage->Load(filename, CXIMAGE_FORMAT_RAW)) 
			{
				m_dlgImageContainer.Invalidate(FALSE);
			}
			break;
		default:
			break;
		}

		if (pCxImage) 
		{
			m_dlgImageContainer.GetRectangleROI()->InitializePara(pCxImage->GetWidth(), pCxImage->GetHeight());
		}
		else
		{
			m_dlgImageContainer.GetRectangleROI()->InitializePara(0, 0);
		}

		m_dlgImageContainer.SetCxImage(pCxImage);
	}
	else
	{
		AfxMessageBox("Open file failing!");
	}
}

CString CIPCDlg::FindExtension(const CString &name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

int CIPCDlg::FindType(const CString &ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CIPCDlg::OnSelectRoi() 
{
	// TODO: Add your command handler code here
	if (m_dlgImageContainer.GetRectangleROI()->GetSelectROI()) 
	{
		m_dlgImageContainer.GetRectangleROI()->SetSelectROI(FALSE);
	}
	else
	{
		m_dlgImageContainer.GetRectangleROI()->SetSelectROI(TRUE);
	}
	m_dlgImageContainer.Invalidate(FALSE);
}

void CIPCDlg::OnShowRoi() 
{
	// TODO: Add your command handler code here
	if (m_dlgImageContainer.GetRectangleROI()->GetShowROI()) 
	{
 		m_dlgImageContainer.GetRectangleROI()->SetShowROI(FALSE);
 	}
 	else
 	{
 		m_dlgImageContainer.GetRectangleROI()->SetShowROI(TRUE);
 	}
 	m_dlgImageContainer.Invalidate(FALSE);
}

void CIPCDlg::OnDetectEdge() 
{
	// TODO: Add your command handler code here
	int i, j;
	
	if (m_dlgImageContainer.GetCxImage()) 
	{
		BYTE* pImage = m_dlgImageContainer.GetCxImage()->GetBits();
		int iImageWidth = m_dlgImageContainer.GetCxImage()->GetWidth();
		int iImageWidthFormat = (iImageWidth + 3) / 4 * 4;
		int iImageHeight = m_dlgImageContainer.GetCxImage()->GetHeight();

		if (m_dlgImageContainer.GetRectangleROI()->GetShowROI()) 
		{
			CPoint	ptTopLeft = m_dlgImageContainer.GetRectangleROI()->GetTopLeftPt();
			CPoint	ptBottomRight = m_dlgImageContainer.GetRectangleROI()->GetBottomRightPt();
			CPoint	ptROIStart(ptTopLeft.x, ptBottomRight.y);	//BottomLeft (x, y)
			int		iROIWidth = ptBottomRight.x - ptTopLeft.x;
			int		iROIHeight = ptBottomRight.y - ptTopLeft.y;
			BYTE*	pROIImage = new BYTE[iROIWidth*iROIHeight];
			for (j=0; j<iROIHeight; j++)
			{
				for (i=0; i<iROIWidth; i++)
				{
					*(pROIImage + j*iROIWidth + i) = *(pImage + 
						(iImageHeight - ptROIStart.y +j)*iImageWidthFormat + ptROIStart.x+i);
				}
			}

			//use for test
//			IplImage* pROICvImage = NULL;
//			pROICvImage = cvCreateImageHeader(cvSize(iROIWidth,iROIHeight), IPL_DEPTH_8U, 1);
//			cvSetData(pROICvImage, (void*)pROIImage, sizeof(BYTE)*iROIWidth);
//			cvSaveImage("D:\\ROItest.jpg", pROICvImage);
//			cvReleaseImageHeader(&pROICvImage);

			m_dlgImageContainer.GetEdgeDetect()->DetectEdge(/*in*/pROIImage, iROIWidth, iROIHeight, 
				/*out*/m_dlgImageContainer.GetEdge());

			m_dlgImageContainer.GetRectangleROI()->SetSelectROI(FALSE);

			delete [] pROIImage;
			pROIImage = NULL;
		}
	}

	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_BRUSH);

	m_dlgImageContainer.Invalidate(FALSE);
}

void CIPCDlg::OnOperationNull() 
{
	// TODO: Add your command handler code here
	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_NULL);
}

void CIPCDlg::OnOperationBrush() 
{
	// TODO: Add your command handler code here
	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_BRUSH);
}

void CIPCDlg::OnOperationErase() 
{
	// TODO: Add your command handler code here
	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_ERASE);
}

void CIPCDlg::OnOperationDraw() 
{
	// TODO: Add your command handler code here
	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_DRAW);
}

void CIPCDlg::OnOperationCut() 
{
	// TODO: Add your command handler code here
	m_dlgImageContainer.GetEdgeInteraction()->SetEdgeOperationPara(EDGE_OPERATION_CUT);
}
