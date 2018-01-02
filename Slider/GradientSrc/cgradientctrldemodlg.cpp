// CGradientCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGradientCtrlDemo.h"
#include "CGradientCtrlDemoDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradientCtrlDemoDlg dialog

CGradientCtrlDemoDlg::CGradientCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGradientCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGradientCtrlDemoDlg)
	m_UseBackground = FALSE;
	m_SelPegPosition = 0.0f;
	m_EnableQuantization = FALSE;
	m_QuantizationEntries = 0;
	m_NewPegPosition = 0.0f;
	m_bShowToolTips = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGradientCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGradientCtrlDemoDlg)
	DDX_Control(pDX, IDC_METHOD_COMBO, m_wndMethodCombo);
		DDX_Control(pDX, IDC_GRADIENT, m_wndGradientCtrl);
		DDX_Control(pDX, IDC_NEWPEG_COLOUR, m_NewPegColour);
		DDX_Control(pDX, IDC_SELPEG_COLOUR, m_SelPegColour);
		DDX_Control(pDX, IDC_BACKGROUND_COLOUR, m_BackgroundColour);
	DDX_Check(pDX, IDC_USE_BACKGROUND, m_UseBackground);
	DDX_Text(pDX, IDC_SELPEG_POSITION, m_SelPegPosition);
	DDV_MinMaxFloat(pDX, m_SelPegPosition, 0.f, 1.f);
	DDX_Check(pDX, IDC_ENABLE_QUANTIZATION, m_EnableQuantization);
	DDX_Text(pDX, IDC_QUANTIZATION_ENTRIES, m_QuantizationEntries);
	DDV_MinMaxInt(pDX, m_QuantizationEntries, 1, 1000);
	DDX_Text(pDX, IDC_NEWPEG_POSITION, m_NewPegPosition);
	DDV_MinMaxFloat(pDX, m_NewPegPosition, 0.f, 1.f);
	DDX_Check(pDX, IDC_SHOWTOOLTIPS, m_bShowToolTips);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FIRE, m_FireWnd);
}

BEGIN_MESSAGE_MAP(CGradientCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGradientCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(CPN_SELENDOK, OnSelEndOK)
	ON_BN_CLICKED(IDC_ADD_PEG, OnAddPeg)
	ON_BN_CLICKED(IDC_DEL_PEG, OnDelPeg)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_SAVEAS, OnSaveas)
	ON_EN_CHANGE(IDC_SELPEG_POSITION, OnChangeSelpegPosition)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_USE_BACKGROUND, OnUseBackground)
	ON_CBN_SELCHANGE(IDC_METHOD_COMBO, OnSelchangeMethodCombo)
	ON_BN_CLICKED(IDC_ENABLE_QUANTIZATION, OnEnableQuantization)
	ON_EN_CHANGE(IDC_QUANTIZATION_ENTRIES, OnChangeQuantizationEntries)
	ON_BN_CLICKED(IDC_SHOWTOOLTIPS, OnShowtooltips)
	ON_BN_CLICKED(IDC_HORIZONTAL, OnHorizontal)
	ON_BN_CLICKED(IDC_VERTICAL, OnVertical)
	ON_BN_CLICKED(IDC_RIGHT_TOP, OnRightTop)
	ON_BN_CLICKED(IDC_LEFT_BOTTOM, OnLeftBottom)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GC_SELCHANGE, IDC_GRADIENT, OnNotifyChangeSelPeg)
	ON_NOTIFY(GC_PEGMOVE, IDC_GRADIENT, OnNotifyPegMove)
	ON_NOTIFY(GC_PEGMOVED, IDC_GRADIENT, OnNotifyPegMove)
	ON_NOTIFY(GC_PEGREMOVED, IDC_GRADIENT, OnNotifyPegRemoved)
	ON_NOTIFY(GC_CREATEPEG, IDC_GRADIENT, OnNotifyDoubleClickCreate)
	ON_NOTIFY(GC_EDITPEG, IDC_GRADIENT, OnNotifyEditPeg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientCtrlDemoDlg message handlers

BOOL CGradientCtrlDemoDlg::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//----- Setup the Gradient -----//
	CGradient &gradient = m_wndGradientCtrl.GetGradient();
	gradient.SetEndPegColour(0x00FFFFFF);
	gradient.AddPeg(0x007FFFFF, 0.765f);
	gradient.AddPeg(0x0000FFFF, 0.585f);
	gradient.AddPeg(0x00007FFF, 0.450f);
	gradient.AddPeg(0x000000FF, 0.315f);
	gradient.AddPeg(0x0000007F, 0.113f);
	gradient.SetStartPegColour(0x00000000);
	gradient.SetUseBackground(true);

	m_NewPegPosition = 0.5f;
	m_BackgroundColour.SetColor(gradient.GetBackgroundColour());
	m_NewPegColour.SetColor(0x000000FF);
	m_UseBackground = true;
	m_QuantizationEntries = 8;

	CDialog::OnInitDialog();

	//----- Setup the Fire -----//
	m_FireWnd.InitFire();
	UpdateFirePalette();

	//----- Update the controls -----//
	SetControls();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGradientCtrlDemoDlg::OnPaint() 
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
HCURSOR CGradientCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

long CGradientCtrlDemoDlg::OnSelEndOK(UINT /*lParam*/, LONG /*wParam*/)
{
	CGradient &gradient = m_wndGradientCtrl.GetGradient();
	int selindex = m_wndGradientCtrl.GetSelIndex();
	
	if(selindex != -1 && selindex > -4)
	{
		const CPeg &peg = gradient.GetPeg(selindex);
		gradient.SetPeg(selindex, m_SelPegColour.GetColor(), peg.position);
	}
	
	gradient.SetBackgroundColour(m_BackgroundColour.GetColor());

	m_wndGradientCtrl.Invalidate();

	UpdateFirePalette();

	return 0;
}

void CGradientCtrlDemoDlg::OnNotifyChangeSelPeg(NMHDR * pNotifyStruct, LRESULT *result)
{
	PegNMHDR* pPegNotifyStruct = (PegNMHDR*)pNotifyStruct;
	
	CString str;

	if(pPegNotifyStruct->index == -1)
	{
		m_SelPegColour.EnableWindow(FALSE);
		GetDlgItem(IDC_SELPEG_POSITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEL_PEG)->EnableWindow(FALSE);
		GetDlgItem(IDC_SELPEG)->SetWindowText(_T("Selected Peg - ID -1 [None]"));
	}
	else
	{	
		m_SelPegColour.EnableWindow(TRUE);
		GetDlgItem(IDC_DEL_PEG)->EnableWindow(TRUE);

		m_SelPegColour.SetColor(pPegNotifyStruct->peg.colour);
		m_SelPegPosition = max(0, pPegNotifyStruct->peg.position);
		UpdateData(FALSE);

		GetDlgItem(IDC_SELPEG_POSITION)->EnableWindow(pPegNotifyStruct->peg.position != -1);
		GetDlgItem(IDC_DEL_PEG)->EnableWindow(pPegNotifyStruct->peg.position != -1);

		CString append;
		
		switch(pPegNotifyStruct->index)
		{
		case STARTPEG: append = _T(" [Start Peg]"); break;
		case ENDPEG: append = _T(" [End Peg]"); break;
		default: append = _T(""); break;
		}
		str.Format(_T("Selected Peg - ID %d%s"), pPegNotifyStruct->index, append);
		GetDlgItem(IDC_SELPEG)->SetWindowText(str);
	}

	*result = 0;
}

void CGradientCtrlDemoDlg::OnNotifyPegMove(NMHDR * pNotifyStruct, LRESULT *result)
{
	PegNMHDR* pPegNotifyStruct = (PegNMHDR*)pNotifyStruct;
	
	m_SelPegPosition = pPegNotifyStruct->peg.position;
	UpdateData(FALSE);
	UpdateFirePalette();

	*result = 0;
}

void CGradientCtrlDemoDlg::OnNotifyPegMoved(NMHDR* , LRESULT *result)
{
	UpdateFirePalette();
	*result = 0;
}

void CGradientCtrlDemoDlg::OnNotifyPegRemoved(NMHDR* , LRESULT *result)
{
	UpdateFirePalette();
	*result = 0;
}

void CGradientCtrlDemoDlg::OnDelPeg() 
{
	m_wndGradientCtrl.DeleteSelected(TRUE);

	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::OnAddPeg() 
{
	UpdateData(TRUE);
	m_wndGradientCtrl.GetGradient().AddPeg(m_NewPegColour.GetColor(),
		m_NewPegPosition);
	m_wndGradientCtrl.Invalidate();

	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::UpdateFirePalette()
{
	RGBTRIPLE *rgbPalette = new RGBTRIPLE[256];
	m_wndGradientCtrl.GetGradient().Make8BitPalette(rgbPalette);
		
	m_FireWnd.SetPalette(rgbPalette);

	delete[] rgbPalette;
}

void CGradientCtrlDemoDlg::OnOpen() 
{
	CFileDialog dlg(TRUE, _T("cip"), _T("Untitled.cip"),
		OFN_HIDEREADONLY | OFN_EXPLORER,
			_T("Colour Scheme (*.cip)|*.cip||"));

	if(dlg.DoModal() == IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeRead | CFile::shareDenyWrite );
		CArchive ar(&file, CArchive::load);
		
		m_wndGradientCtrl.GetGradient().Serialize(ar);

		m_wndGradientCtrl.SetSelIndex(-1);
		m_wndGradientCtrl.Invalidate();
		
		SetControls();

		UpdateFirePalette();
	}
}

void CGradientCtrlDemoDlg::OnSaveas() 
{
	CFileDialog dlg(FALSE, _T("cip"), _T("Untitled.cip"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
			_T("Colour Scheme (*.cip)|*.cip||"));

	if(dlg.DoModal() == IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite );
		CArchive ar(&file, CArchive::store);
		m_wndGradientCtrl.GetGradient().Serialize(ar);
	}

}

void CGradientCtrlDemoDlg::OnChangeSelpegPosition() 
{
	UpdateData(TRUE);
	int newsel = m_wndGradientCtrl.MoveSelected(m_SelPegPosition, TRUE); 
		
	CString append,str;
		
	switch(newsel)
	{
	case STARTPEG: append = _T(" [Start Peg]"); break;
	case ENDPEG: append = _T(" [End Peg]"); break;
	default: append = _T(""); break;
	}
	str.Format(_T("Selected Peg - ID %d%s"), newsel, append);
	GetDlgItem(IDC_SELPEG)->SetWindowText(str);
	
	UpdateFirePalette();		
}

void CGradientCtrlDemoDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CGradientCtrlDemoDlg::OnNotifyDoubleClickCreate(NMHDR * pNotifyStruct, LRESULT *result)
{
	PegCreateNMHDR* pPegCreateNotifyStruct = (PegCreateNMHDR*)pNotifyStruct;
	
	UpdateData(TRUE);
	m_wndGradientCtrl.GetGradient().AddPeg(pPegCreateNotifyStruct->colour,
		pPegCreateNotifyStruct->position);
	m_wndGradientCtrl.Invalidate();

	UpdateFirePalette();

	*result = 0;
}

void CGradientCtrlDemoDlg::OnNotifyEditPeg(NMHDR * pNotifyStruct, LRESULT *result)
{
	PegNMHDR* pPegNotifyStruct = (PegNMHDR*)pNotifyStruct;
	
	CString message;
	message.Format(_T("Position: %.2f\nColour: RGB(%u, %u, %u)"), pPegNotifyStruct->peg.position,
		GetRValue(pPegNotifyStruct->peg.colour),
		GetGValue(pPegNotifyStruct->peg.colour),
		GetBValue(pPegNotifyStruct->peg.colour));
	MessageBox(message, _T("You just double clicked on a peg!"));

	*result = 0;
}

void CGradientCtrlDemoDlg::OnUseBackground() 
{
	UpdateData();
	m_wndGradientCtrl.GetGradient().SetUseBackground(m_UseBackground);
	m_wndGradientCtrl.Invalidate();
	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::OnSelchangeMethodCombo() 
{
	int sel = m_wndMethodCombo.GetCurSel();
	if(sel == -1)
		return;
	m_wndGradientCtrl.GetGradient().
	SetInterpolationMethod((CGradient::InterpolationMethod)sel);
	m_wndGradientCtrl.Invalidate();
	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::OnEnableQuantization() 
{
	UpdateData();
	GetDlgItem(IDC_QUANTIZATION_ENTRIES)->
		EnableWindow(m_EnableQuantization);

	m_wndGradientCtrl.GetGradient().
		SetQuantization(m_EnableQuantization
		? m_QuantizationEntries : -1);

	m_wndGradientCtrl.Invalidate();
	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::OnChangeQuantizationEntries() 
{
	UpdateData();
	m_wndGradientCtrl.GetGradient().
		SetQuantization(m_EnableQuantization
		? m_QuantizationEntries : -1);
	m_wndGradientCtrl.Invalidate();
	UpdateFirePalette();
}

void CGradientCtrlDemoDlg::OnShowtooltips() 
{
	UpdateData();
	m_wndGradientCtrl.ShowTooltips(m_bShowToolTips);
}

void CGradientCtrlDemoDlg::SetControls()
{
	//----- Set the interpolation method -----//
	m_wndMethodCombo.SetCurSel((int)m_wndGradientCtrl.GetGradient().
		GetInterpolationMethod());
	GetDlgItem(IDC_QUANTIZATION_ENTRIES)->
		EnableWindow(false);
	
	//----- Set the dialog's selection -----//
	LRESULT result;
	PegNMHDR nmhdr;
	nmhdr.nmhdr.code = 0;
	nmhdr.nmhdr.idFrom = 0;
	nmhdr.nmhdr.hwndFrom = 0;
	nmhdr.index = -1;
	OnNotifyChangeSelPeg((NMHDR*) &nmhdr, &result);

	//----- Select the right radio button -----//
	m_wndGradientCtrl.SetPegSide(true, true);
	((CButton*)GetDlgItem(IDC_RIGHT_TOP))->SetCheck(1);
	m_wndGradientCtrl.SetPegSide(false, false);
	((CButton*)GetDlgItem(IDC_LEFT_BOTTOM))->SetCheck(0);
	
	GetDlgItem(IDC_GRADIENT)->SetWindowPos(GetDlgItem(IDC_GRADIENT), 11,11, 107, 330, SWP_NOZORDER);
	((CButton*)GetDlgItem(IDC_VERTICAL))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_HORIZONTAL))->SetCheck(0);
}

void CGradientCtrlDemoDlg::OnHorizontal() 
{
	GetDlgItem(IDC_GRADIENT)->SetWindowPos(GetDlgItem(IDC_GRADIENT), 10,225, 830, 120, SWP_NOZORDER);
}

void CGradientCtrlDemoDlg::OnVertical() 
{
	GetDlgItem(IDC_GRADIENT)->SetWindowPos(GetDlgItem(IDC_GRADIENT), 11,11, 107, 330, SWP_NOZORDER);
}

void CGradientCtrlDemoDlg::OnRightTop() 
{
	m_wndGradientCtrl.SetPegSide(true, ((CButton*)GetDlgItem(IDC_RIGHT_TOP))->GetCheck());
	m_wndGradientCtrl.Invalidate();
}

void CGradientCtrlDemoDlg::OnLeftBottom() 
{
	m_wndGradientCtrl.SetPegSide(false, ((CButton*)GetDlgItem(IDC_LEFT_BOTTOM))->GetCheck());
	m_wndGradientCtrl.Invalidate();
}
