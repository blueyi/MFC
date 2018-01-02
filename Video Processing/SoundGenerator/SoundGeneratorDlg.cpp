// SoundGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Player.h"
#include "SoundGenerator.h"
#include "SoundGeneratorDlg.h"
#include "MatException.h"
#include "ScopeGuardMutex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CSoundGeneratorDlg dialog

CSoundGeneratorDlg::CSoundGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundGeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundGeneratorDlg)
	m_shape1 = _T("");
	m_shape3 = _T("");
	m_shape2 = _T("");
	m_varx = _T("");
	m_vary = _T("");
	m_varz = _T("");
	m_msg = _T("");
	m_shape1Active = FALSE;
	m_shape2Active = FALSE;
	m_shape3Active = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pVarExpr = NULL;
	m_pShapeExpr = NULL;
	m_pUserVar = NULL;
	m_pShapeVolume = NULL;
	m_pShapeActive = NULL;
	m_pSamples = NULL;
	m_pSoundPlayer = NULL;

}

CSoundGeneratorDlg::~CSoundGeneratorDlg()
{
	if( m_pSoundPlayer != NULL )
	{
		delete m_pSoundPlayer;
	}
	
	if( m_pVarExpr != NULL )
	{
		delete []m_pVarExpr;
	}
	if( m_pShapeExpr != NULL )
	{
		delete []m_pShapeExpr;
	}
	
	if( m_pUserVar != NULL )
	{
		delete []m_pUserVar;
	}

	if( m_pShapeVolume != NULL )
	{
		delete []m_pShapeVolume;
	}

	if( m_pShapeActive != NULL )
	{	
		delete []m_pShapeActive;
	}	

	if( m_pSamples != NULL )
	{
		delete []m_pSamples;
	}

}

void CSoundGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundGeneratorDlg)
	DDX_Control(pDX, IDC_VOLUME_SHAPE3, m_volumeShape3);
	DDX_Control(pDX, IDC_VOLUME_SHAPE2, m_volumeShape2);
	DDX_Control(pDX, IDC_VOLUME_SHAPE1, m_volumeShape1);
	DDX_Text(pDX, IDC_SHAPE1, m_shape1);
	DDX_Text(pDX, IDC_SHAPE3, m_shape3);
	DDX_Text(pDX, IDC_SHAPE2, m_shape2);
	DDX_Text(pDX, IDC_VARX, m_varx);
	DDX_Text(pDX, IDC_VARY, m_vary);
	DDX_Text(pDX, IDC_VARZ, m_varz);
	DDX_Text(pDX, IDC_MSG, m_msg);
	DDX_Check(pDX, IDC_ACTIVE_SHAPE1, m_shape1Active);
	DDX_Check(pDX, IDC_ACTIVE_SHAPE2, m_shape2Active);
	DDX_Check(pDX, IDC_ACTIVE_SHAPE3, m_shape3Active);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoundGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CSoundGeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ACTIVE_SHAPE1, OnActiveShape1)
	ON_BN_CLICKED(IDC_ACTIVE_SHAPE2, OnActiveShape2)
	ON_BN_CLICKED(IDC_ACTIVE_SHAPE3, OnActiveShape3)
	ON_BN_CLICKED(IDC_APPLY_SHAPE1, OnApplyShape1)
	ON_BN_CLICKED(IDC_APPLY_SHAPE2, OnApplyShape2)
	ON_BN_CLICKED(IDC_APPLY_SHAPE3, OnApplyShape3)
	ON_EN_CHANGE(IDC_SHAPE1, OnChangeShape1)
	ON_EN_CHANGE(IDC_SHAPE2, OnChangeShape2)
	ON_EN_CHANGE(IDC_SHAPE3, OnChangeShape3)
	ON_BN_CLICKED(IDC_APPLY_VARX, OnApplyVarx)
	ON_BN_CLICKED(IDC_APPLY_VARY, OnApplyVary)
	ON_BN_CLICKED(IDC_APPLY_VARZ, OnApplyVarz)
	ON_EN_CHANGE(IDC_VARX, OnChangeVarx)
	ON_EN_CHANGE(IDC_VARY, OnChangeVary)
	ON_EN_CHANGE(IDC_VARZ, OnChangeVarz)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundGeneratorDlg message handlers

BOOL CSoundGeneratorDlg::OnInitDialog()
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

	m_volumeShape1.SetRange(0, 100);
	m_volumeShape2.SetRange(0, 100);
	m_volumeShape3.SetRange(0, 100);
	
	
	//*** math expression initializations
	m_nbVars = 3;
	m_nbShapes = 3;	
	m_t = 0;

	m_pVarExpr = new MathExpression[m_nbVars];
	m_pUserVar = new EXPR_VALTYPE[m_nbVars];
	m_pShapeExpr = new MathExpression[m_nbShapes];	
	m_pShapeVolume = new double[m_nbShapes];
	m_pShapeActive = new bool[m_nbShapes];

	for( int t=0; t<m_nbVars; t++ )
	{
		m_pVarExpr[t].defineVar(_T("t"), &m_t);	
	}

	for( t=0; t<m_nbShapes; t++ )
	{
		m_pShapeActive[t] = true;
		m_pShapeExpr[t].defineVar(_T("t"), &m_t);		

		for( int var=0; var<m_nbVars; var++ )
		{			
			wchar_t varName[2] = {0};
			varName[0] = 'x' + var;
			m_pShapeExpr[t].defineVar(varName, &m_pUserVar[var]);
		}
	}

	m_soundPlayerEventNbSamples = 10000;	
	m_nbSoudPlayerEvents = 3;
	
	
	GetDlgItem(IDC_WAVE)->GetClientRect(&m_graphRect);
	m_graphMaxLines = m_graphRect.right - m_graphRect.left - 10;		
	m_graphStep = m_soundPlayerEventNbSamples / m_graphMaxLines+1;
	if( m_graphStep < 1 )
	{	
		m_graphStep = 1;
	}	

	m_graphCursor = 0;
	m_graphLastVal = 0;
	m_hdc = ::GetDC(GetDlgItem(IDC_WAVE)->m_hWnd);
	m_hRedPen = CreatePen(PS_SOLID, 1, RGB(250,50,30));
	m_hBgPen = CreatePen(PS_SOLID, 1, RGB(80,90,110));
	m_hBgBrush = CreateSolidBrush(RGB(80,90,110));

	// **** some settings... should be put in a config file
	m_varx = _T("min(sin(t), cos(t))");
	m_vary = _T("max(300+200*cos(t), 300+200*sin(t))");
	m_varz = _T("max(300+200*cos(t*1.5), 300+200*sin(t*1.7))");
	m_shape1 = _T("tan(t*2)*sin(x*y*600)*abs(sin(t/10))*abs(cos(t/5))");
	m_shape2 = _T("abs(sin(t*10))*sin(x*y)");
	m_shape3 = _T("sin(sin(z*t*0.1))");

	m_pShapeVolume[0] = 0.2;
	m_pShapeVolume[1] = 0.45;
	m_pShapeVolume[2] = 0.15;

	m_volumeShape1.SetPos(m_pShapeVolume[0]*100);
	m_volumeShape2.SetPos(m_pShapeVolume[1]*100);
	m_volumeShape3.SetPos(m_pShapeVolume[2]*100);

	m_shape1Active = TRUE;
	m_shape2Active = TRUE;
	m_shape3Active = TRUE;
	


	// ****  sound player initialization	
	try
	{
		Player *pPlayer = new Player();
		pPlayer->SetHWnd(m_hWnd);
		m_pSoundPlayer = pPlayer;
		m_pSoundPlayer->Init();
		
		SOUNDFORMAT format;
		format.NbBitsPerSample = 16;
		format.NbChannels = 1;
		format.SamplingRate = 44100;	
		
		m_sampleScaleVal = pow(2, format.NbBitsPerSample - 1);
		m_maxEventComputeTime = m_soundPlayerEventNbSamples / (double)format.SamplingRate * 1000;
		
		m_pSamples = new short[m_soundPlayerEventNbSamples];	// 16 bits samples -> short		
		m_tStep = (m_soundPlayerEventNbSamples/(double)format.SamplingRate) * 2.0*3.14159 / (double)m_soundPlayerEventNbSamples;	// 1 sec = 2*pi

		
		m_soundPlayerEventSize = m_soundPlayerEventNbSamples * format.NbBitsPerSample/8;	
		int bufferSize = m_soundPlayerEventSize * m_nbSoudPlayerEvents;
		
		m_pSoundPlayer->CreateSoundBuffer(format, bufferSize, 0);

		m_pSoundPlayer->SetSoundEventListener(this);
		std::vector<DWORD> events;

		for( int t=0; t<m_nbSoudPlayerEvents; t++ )
		{	
			events.push_back((t+1)*m_soundPlayerEventSize - m_soundPlayerEventSize*0.95);
		}

		m_pSoundPlayer->CreateEventReadNotification(events);
		m_pSoundPlayer->Play(1); // loop playing
	}
	catch(MATExceptions &e)
	{
		MessageBox(e.getAllExceptionStr().c_str(), _T("Error initializing the sound player"));
		EndDialog(IDCANCEL);
		return FALSE;
	}

	UpdateData(0);

	SetTimer(0, 1000, NULL);
	
	OnApplyVarx();
	OnApplyVary();
	OnApplyVarz();
	OnApplyShape1();
	OnApplyShape2();
	OnApplyShape3();

	

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoundGeneratorDlg::OnPaint() 
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
HCURSOR CSoundGeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSoundGeneratorDlg::OnActiveShape1() 
{
	UpdateData(1);

	if( m_shape1Active )
	{
		m_pShapeActive[0] = true;
	}
	else
	{
		m_pShapeActive[0] = false;

	}	
}

void CSoundGeneratorDlg::OnActiveShape2() 
{
	UpdateData(1);

	if( m_shape2Active )
	{
		m_pShapeActive[1] = true;
	}
	else
	{
		m_pShapeActive[1] = false;

	}	
}

void CSoundGeneratorDlg::OnActiveShape3() 
{
	UpdateData(1);

	if( m_shape3Active )
	{
		m_pShapeActive[2] = true;
	}
	else
	{
		m_pShapeActive[2] = false;

	}	
}

void CSoundGeneratorDlg::OnApplyShape1() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	
	try
	{
		m_pShapeExpr[0].setExpression(m_shape1.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("Shape1 apply error: ") + e.getAllExceptionStr()).c_str();
		
	}	
	UpdateData(0);
	
	GetDlgItem(IDC_APPLY_SHAPE1)->EnableWindow(FALSE);
}

void CSoundGeneratorDlg::OnApplyShape2() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	
	try
	{
		m_pShapeExpr[1].setExpression(m_shape2.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("Shape2 apply error: ") + e.getAllExceptionStr()).c_str();		
	}	

	UpdateData(0);
	
	GetDlgItem(IDC_APPLY_SHAPE2)->EnableWindow(FALSE);
	
}

void CSoundGeneratorDlg::OnApplyShape3() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	
	try
	{
		m_pShapeExpr[2].setExpression(m_shape3.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("Shape3 apply error: ") + e.getAllExceptionStr()).c_str();
		
	}	
	
	UpdateData(0);
	GetDlgItem(IDC_APPLY_SHAPE3)->EnableWindow(FALSE);
	
}

void CSoundGeneratorDlg::OnChangeShape1() 
{
	GetDlgItem(IDC_APPLY_SHAPE1)->EnableWindow(TRUE);
}

void CSoundGeneratorDlg::OnChangeShape2() 
{
	GetDlgItem(IDC_APPLY_SHAPE2)->EnableWindow(TRUE);
	
}

void CSoundGeneratorDlg::OnChangeShape3() 
{
	GetDlgItem(IDC_APPLY_SHAPE3)->EnableWindow(TRUE);	
}

void CSoundGeneratorDlg::OnApplyVarx() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	try
	{
		m_pVarExpr[0].setExpression(m_varx.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("VarX apply error: ") + e.getAllExceptionStr()).c_str();
		
	}

	UpdateData(0);
	GetDlgItem(IDC_APPLY_VARX)->EnableWindow(FALSE);
	
}

void CSoundGeneratorDlg::OnApplyVary() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	try
	{
		m_pVarExpr[1].setExpression(m_vary.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("VarY apply error: ") + e.getAllExceptionStr()).c_str();		
	}
	
	UpdateData(0);
	GetDlgItem(IDC_APPLY_VARY)->EnableWindow(FALSE);
	
}

void CSoundGeneratorDlg::OnApplyVarz() 
{
	UpdateData(1);
	ScopeGuardMutex guard(&m_exprMutex);
	try
	{
		m_pVarExpr[2].setExpression(m_varz.GetBuffer(0));
		m_msg = _T("");
	}
	catch( MATExceptions &e )
	{
		m_msg = (_T("VarZ apply error: ") + e.getAllExceptionStr()).c_str();		
	}

	UpdateData(0);
	GetDlgItem(IDC_APPLY_VARZ)->EnableWindow(FALSE);
	
}

void CSoundGeneratorDlg::OnChangeVarx() 
{
	GetDlgItem(IDC_APPLY_VARX)->EnableWindow(TRUE);
	
}

void CSoundGeneratorDlg::OnChangeVary() 
{
	GetDlgItem(IDC_APPLY_VARY)->EnableWindow(TRUE);
	
}

void CSoundGeneratorDlg::OnChangeVarz() 
{
	GetDlgItem(IDC_APPLY_VARZ)->EnableWindow(TRUE);
}

void CSoundGeneratorDlg::OnSoundPlayerNotify(int eventNumber)
{
	ScopeGuardMutex guard(&m_exprMutex);

	// compute the next sound samples...

	double sample;

	DWORD begin = GetTickCount();
	try
	{
		for( int s=0; s<m_soundPlayerEventNbSamples; s++ )
		{
			sample = 0;

			for( int t=0; t<m_nbVars; t++ )
			{
				m_pUserVar[t] = m_pVarExpr[t].evaluate();		
			}

			for( t=0; t<m_nbShapes; t++ )
			{
				if( m_pShapeActive[t] )
				{
					sample += m_pShapeExpr[t].evaluate() * m_pShapeVolume[t];		
				}
			}

			m_pSamples[s] = sample*m_sampleScaleVal;	

			m_t+=m_tStep;	// increment the time			
		}
	}
	catch( MATExceptions &e )
	{
		OutputDebugString(e.getAllExceptionStr().c_str());		// math expression evaluation error...
	}
	
	try
	{
		m_pSoundPlayer->Write(((eventNumber+1)%m_nbSoudPlayerEvents)*m_soundPlayerEventSize, (unsigned char*)m_pSamples, m_soundPlayerEventSize);
	}
	catch( MATExceptions &e )
	{
		OutputDebugString(e.getAllExceptionStr().c_str());		// it would be better to stop the program...
	}			
	
	drawWave();

	DWORD end = GetTickCount();
	DWORD elapsed = end-begin;	

	
	if( elapsed > m_maxEventComputeTime )
	{
		m_warningMsg.Format(_T("Warning! compute time: %dms"), elapsed);
	}
	else
	{
		m_warningMsg.Format(_T("compute time: %dms"), elapsed);
	}

	
}

void CSoundGeneratorDlg::drawWave()
{
	int nbSteps = m_soundPlayerEventNbSamples / m_graphStep;
	::SelectObject(m_hdc, m_hBgPen);
	::SelectObject(m_hdc, m_hBgBrush);
	
	int end = m_graphRect.left + m_graphCursor + nbSteps;
	int remaining = 0;
	if( end > m_graphRect.right )
	{
		remaining = end - m_graphRect.right;
		end = m_graphRect.right;
	}
	Rectangle(m_hdc,	m_graphRect.left + m_graphCursor,
						m_graphRect.top,
						end,
						m_graphRect.bottom );

	if( remaining > 0 )
	{
		Rectangle(m_hdc,	m_graphRect.left,
							m_graphRect.top,
							m_graphRect.left+remaining,
							m_graphRect.bottom );

	}

	int pos = m_graphCursor;
	
	int middle = (m_graphRect.bottom - m_graphRect.top)/2;
	double scaleY = middle / (double)m_sampleScaleVal;

	::SelectObject(m_hdc, m_hRedPen);
	MoveToEx(m_hdc, pos, m_graphLastVal, NULL);
	unsigned int val;

	for( int s=0; s<m_soundPlayerEventNbSamples; s+=m_graphStep )
	{
		val = -m_pSamples[s] * scaleY+middle;
		pos++;
		if( pos >= m_graphRect.right )
		{
			pos = m_graphRect.left;			
			MoveToEx(m_hdc, pos, val, NULL);				
		}
		
		LineTo(m_hdc, pos, val);		
	}

	m_graphCursor = pos;
	m_graphLastVal = val;
}

void CSoundGeneratorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pSoundPlayer->Stop();	
}

void CSoundGeneratorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// volume scroll bars...

	CSliderCtrl *pCtrl = (CSliderCtrl*)pScrollBar;

	if( pCtrl == &m_volumeShape1 )
	{
		m_pShapeVolume[0] = m_volumeShape1.GetPos() / 100.0;

	}
	else if( pCtrl == &m_volumeShape2 )
	{
		m_pShapeVolume[1] = m_volumeShape2.GetPos() / 100.0;

	}
	else if( pCtrl == &m_volumeShape3 )
	{
		m_pShapeVolume[2] = m_volumeShape3.GetPos() / 100.0;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSoundGeneratorDlg::OnTimer(UINT nIDEvent) 
{

	GetDlgItem(IDC_MSGWARNING)->SetWindowText(m_warningMsg);
	m_warningMsg = _T("");
	
	CDialog::OnTimer(nIDEvent);
}
