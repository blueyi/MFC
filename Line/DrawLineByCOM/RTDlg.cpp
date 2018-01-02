// RTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RTDemo.h"
#include "RTDlg.h"
#include "ChildFrm.h"
#include "RTDemoDoc.h"
#include "RTDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTDlg dialog


CRTDlg::CRTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRTDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParent = pParent;
}


void CRTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRTDlg)
	DDX_Control(pDX, IDC_LDELETENAME, m_LDeleteName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRTDlg, CDialog)
	//{{AFX_MSG_MAP(CRTDlg)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_LBN_DBLCLK(IDC_LDELETENAME, OnDblclkLdeletename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRTDlg::ResetColorList()
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	int n = pView->m_Graph.m_LineArray.GetSize();
	for(int i = 0; i < n; i ++)
		m_LDeleteName.AddString((LPCTSTR)i);
}

/////////////////////////////////////////////////////////////////////////////
// RTDlg message handlers

void CRTDlg::OnBdelete() 
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	int n = pView->m_Graph.m_LineArray.GetSize();

	int m = m_LDeleteName.GetCurSel();
	if (m < 0 || m >= n)
		return;

	CString str;
	str.Format("Are you sure to delete <%s>", pView->m_Graph.m_LineArray[m].m_sName.GetChar());
	n = MessageBox(str, "Warning ...", MB_YESNO);
	if (n == IDNO)
		return;

	pView->RemoveALine(m);
	m_LDeleteName.ResetContent();
	ResetColorList();

	pView->RefreshGraph();
}

BOOL CRTDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ResetColorList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRTDlg::OnDblclkLdeletename() 
{
	OnBdelete();
}
/////////////////////////////////////////////////////////////////////////////
// CModify dialog


CModify::CModify(CWnd* pParent /*=NULL*/)
	: CDialog(CModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModify)
	m_EMDesc = _T("");
	m_EMMax = 0.0;
	m_EMMin = 0.0;
	m_EMScaleMin = 0.0;
	m_EMUnit = _T("");
	m_EMWidth = 0;
	m_EMScaleMax = 0.0;
	m_EMName = _T("");
	//}}AFX_DATA_INIT
	m_pParent = pParent;
}


void CModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModify)
	DDX_Control(pDX, IDC_BAPPLY, m_BApply);
	DDX_Control(pDX, IDC_SMWIDTH, m_SMWidth);
	DDX_Control(pDX, IDC_CMSTYLE, m_CMStyle);
	DDX_Control(pDX, IDC_CMNAME, m_CMName);
	DDX_Control(pDX, IDC_BMCOLOR, m_BMColor);
	DDX_Text(pDX, IDC_EMDESC, m_EMDesc);
	DDV_MaxChars(pDX, m_EMDesc, 32);
	DDX_Text(pDX, IDC_EMMAX, m_EMMax);
	DDX_Text(pDX, IDC_EMMIN, m_EMMin);
	DDX_Text(pDX, IDC_EMSCALEMIN, m_EMScaleMin);
	DDV_MinMaxDouble(pDX, m_EMScaleMin, 0., 100.);
	DDX_Text(pDX, IDC_EMUNIT, m_EMUnit);
	DDV_MaxChars(pDX, m_EMUnit, 12);
	DDX_Text(pDX, IDC_EMWIDTH, m_EMWidth);
	DDV_MinMaxInt(pDX, m_EMWidth, 0, 5);
	DDX_Text(pDX, IDC_EMSCALEMAX, m_EMScaleMax);
	DDV_MinMaxDouble(pDX, m_EMScaleMax, 0., 100.);
	DDX_Text(pDX, IDC_EMNAME, m_EMName);
	DDV_MaxChars(pDX, m_EMName, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModify, CDialog)
	//{{AFX_MSG_MAP(CModify)
	ON_BN_CLICKED(IDC_BMCOLOR, OnBmcolor)
	ON_CBN_SELCHANGE(IDC_CMNAME, OnSelchangeCmname)
	ON_CBN_SELCHANGE(IDC_CMSTYLE, OnSelchangeCmstyle)
	ON_BN_CLICKED(IDC_BAPPLY, OnBapply)
	ON_EN_CHANGE(IDC_EMNAME, OnChangeEmname)
	ON_EN_CHANGE(IDC_EMDESC, OnChangeEmdesc)
	ON_EN_CHANGE(IDC_EMUNIT, OnChangeEmunit)
	ON_EN_CHANGE(IDC_EMWIDTH, OnChangeEmwidth)
	ON_EN_CHANGE(IDC_EMMIN, OnChangeEmmin)
	ON_EN_CHANGE(IDC_EMMAX, OnChangeEmmax)
	ON_EN_CHANGE(IDC_EMSCALEMIN, OnChangeEmscalemin)
	ON_EN_CHANGE(IDC_EMSCALEMAX, OnChangeEmscalemax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModify message handlers

void CModify::OnBmcolor() 
{
	CColorDialog crDlg;
	
	if (crDlg.DoModal() == IDOK)
	{
		m_nColor = crDlg.GetColor();
		m_BMColor.SetColor(m_nColor);
		m_BApply.EnableWindow();
	}
}

void CModify::SaveLine(int i)
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);

	UpdateData();
	pView->m_Graph.m_LineArray[i].m_dMin	 	 = m_EMMin;
	pView->m_Graph.m_LineArray[i].m_dMax		 = m_EMMax;
	pView->m_Graph.m_LineArray[i].m_dScaleLow    = m_EMScaleMin;
	pView->m_Graph.m_LineArray[i].m_dScaleHigh   = m_EMScaleMax;
	pView->m_Graph.m_LineArray[i].m_sDescription = (const char*)m_EMDesc;
	pView->m_Graph.m_LineArray[i].m_sUnit		 = (const char*)m_EMUnit;
	pView->m_Graph.m_LineArray[i].m_sName		 = (const char*)m_EMName;
	pView->m_Graph.m_LineArray[i].m_nColor		 = m_nColor;
	pView->m_Graph.m_LineArray[i].m_nLineWidth   = m_SMWidth.GetPos();
	pView->m_Graph.m_LineArray[i].m_nLineStyle   = m_CMStyle.GetCurSel();
	UpdateData(FALSE);

	pView->SaveAModifiedLine();
}

void CModify::OnSelchangeCmname() 
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	int n = pView->m_Graph.m_LineArray.GetSize();

	int m = m_CMName.GetCurSel();
	if (m < 0 || m >= n)
		return;

	if (m_BApply.IsWindowEnabled())
	{
		n = MessageBox("Save changes for <" + (CString)pView->m_Graph.m_LineArray[m_nIndex].m_sName.GetChar() + "> ?", 
						AfxGetAppName(), MB_YESNO);
		if (n == IDYES)
		{
			SaveLine(m_nIndex);
		}
	}

	Reset(m);	
}

void CModify::OnSelchangeCmstyle() 
{
	int m = m_CMStyle.GetCurSel();
	if (m < 0 || m > 2)
		return;

	if (m > 0)
		m_SMWidth.SetPos(0);
	UpdateData();
	UpdateData(FALSE);
	m_BApply.EnableWindow();
}

void CModify::Reset(int i)
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);

	m_nIndex	 = i;
	m_EMMin		 = pView->m_Graph.m_LineArray[i].m_dMin;
	m_EMMax		 = pView->m_Graph.m_LineArray[i].m_dMax;
	m_EMScaleMin = pView->m_Graph.m_LineArray[i].m_dScaleLow;
	m_EMScaleMax = pView->m_Graph.m_LineArray[i].m_dScaleHigh;
	m_EMName	 = pView->m_Graph.m_LineArray[i].m_sName.GetChar();
	m_EMDesc	 = pView->m_Graph.m_LineArray[i].m_sDescription.GetChar();
	m_EMUnit	 = pView->m_Graph.m_LineArray[i].m_sUnit.GetChar();
	m_CMName.SetCurSel(i);
	m_CMStyle.SetCurSel(pView->m_Graph.m_LineArray[i].m_nLineStyle);
	UpdateData(FALSE);
	m_SMWidth.SetPos(pView->m_Graph.m_LineArray[i].m_nLineWidth);
	m_nColor = pView->m_Graph.m_LineArray[i].m_nColor;
	m_BMColor.SetColor(m_nColor);
	m_BApply.EnableWindow(FALSE);
}

BOOL CModify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	int n = pView->m_Graph.m_LineArray.GetSize();
	if (n == 0)
		return FALSE;

	for(int i = 0; i < n; i ++)
		m_CMName.AddString(pView->m_Graph.m_LineArray[i].m_sName.GetChar());

	m_SMWidth.SetRange(0, 5);
	Reset(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModify::OnBapply() 
{
	SaveLine(m_nIndex);
	m_BApply.EnableWindow(FALSE);
}

void CModify::OnChangeEmname() 
{
	UpdateData();
	m_CMName.InsertString(m_nIndex, (LPCTSTR)m_EMName);
	m_CMName.DeleteString(m_nIndex + 1);
	m_CMName.SetCurSel(m_nIndex);
	UpdateData(FALSE);
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmdesc() 
{
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmunit() 
{
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmwidth() 
{
	if (::IsWindow(m_BApply.m_hWnd))
	{
		m_BApply.EnableWindow();

		UpdateData();
		if (m_SMWidth.GetPos() > 1)
			m_CMStyle.SetCurSel(0);
		UpdateData(FALSE);
	}
}

void CModify::OnChangeEmmin() 
{
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmmax() 
{
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmscalemin() 
{
	m_BApply.EnableWindow();
}

void CModify::OnChangeEmscalemax() 
{
	m_BApply.EnableWindow();
}

void CModify::OnCancel() 
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	if (m_BApply.IsWindowEnabled())
	{
		int n = MessageBox("Save changes for <" + (CString)pView->m_Graph.m_LineArray[m_nIndex].m_sName.GetChar() + "> ?", 
						AfxGetAppName(), MB_YESNO);
		if (n == IDYES)
		{
			SaveLine(m_nIndex);
		}
	}
	
	CDialog::OnCancel();
}
/////////////////////////////////////////////////////////////////////////////
// CInsert dialog


CInsert::CInsert(CWnd* pParent /*=NULL*/)
	: CDialog(CInsert::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsert)
	m_EIDesc = _T("");
	m_EIIndex = 0;
	m_EIMax = 0.0;
	m_EIMin = 0.0;
	m_EIName = _T("");
	m_EIScaledMax = 0.0;
	m_EIScaledMin = 0.0;
	m_EIUnit = _T("");
	m_EIWidth = 0;
	//}}AFX_DATA_INIT
	m_pParent = pParent;
}


void CInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsert)
	DDX_Control(pDX, IDC_BIAPPLY, m_BIApply);
	DDX_Control(pDX, IDC_SIWIDTH, m_SIWidth);
	DDX_Control(pDX, IDC_SIINDEX, m_SIIndex);
	DDX_Control(pDX, IDC_CISTYLE, m_CIStyle);
	DDX_Control(pDX, IDC_BICOLOR, m_BIColor);
	DDX_Text(pDX, IDC_EIDESCRIPTION, m_EIDesc);
	DDV_MaxChars(pDX, m_EIDesc, 32);
	DDX_Text(pDX, IDC_EIINDEX, m_EIIndex);
	DDV_MinMaxInt(pDX, m_EIIndex, 0, 20);
	DDX_Text(pDX, IDC_EIMAX, m_EIMax);
	DDX_Text(pDX, IDC_EIMIN, m_EIMin);
	DDX_Text(pDX, IDC_EIName, m_EIName);
	DDV_MaxChars(pDX, m_EIName, 16);
	DDX_Text(pDX, IDC_EISCALEDMAX, m_EIScaledMax);
	DDV_MinMaxDouble(pDX, m_EIScaledMax, 0., 100.);
	DDX_Text(pDX, IDC_EISCALEDMIN, m_EIScaledMin);
	DDV_MinMaxDouble(pDX, m_EIScaledMin, 0., 100.);
	DDX_Text(pDX, IDC_EIUNIT, m_EIUnit);
	DDV_MaxChars(pDX, m_EIUnit, 8);
	DDX_Text(pDX, IDC_EIWIDTH, m_EIWidth);
	DDV_MinMaxInt(pDX, m_EIWidth, 0, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsert, CDialog)
	//{{AFX_MSG_MAP(CInsert)
	ON_BN_CLICKED(IDC_BICOLOR, OnBicolor)
	ON_CBN_SELCHANGE(IDC_CISTYLE, OnSelchangeCistyle)
	ON_BN_CLICKED(IDC_BIAPPLY, OnBiapply)
	ON_EN_CHANGE(IDC_EIWIDTH, OnChangeEiwidth)
	ON_EN_CHANGE(IDC_EIUNIT, OnChangeEiunit)
	ON_EN_CHANGE(IDC_EISCALEDMIN, OnChangeEiscaledmin)
	ON_EN_CHANGE(IDC_EISCALEDMAX, OnChangeEiscaledmax)
	ON_EN_CHANGE(IDC_EIName, OnChangeEIName)
	ON_EN_CHANGE(IDC_EIMIN, OnChangeEimin)
	ON_EN_CHANGE(IDC_EIMAX, OnChangeEimax)
	ON_EN_CHANGE(IDC_EIINDEX, OnChangeEiindex)
	ON_EN_CHANGE(IDC_EIDESCRIPTION, OnChangeEidescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsert message handlers

void CInsert::OnBicolor() 
{
	CColorDialog crDlg;
	
	if (crDlg.DoModal() == IDOK)
	{
		m_nColor = crDlg.GetColor();
		m_BIColor.SetColor(m_nColor);
	}
}

void CInsert::OnSelchangeCistyle() 
{
	int m = m_CIStyle.GetCurSel();
	if (m < 0 || m > 2)
		return;

	if (m > 0)
		m_SIWidth.SetPos(0);
	UpdateData();
	UpdateData(FALSE);
	m_BIApply.EnableWindow();
}

BOOL CInsert::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	int n = pView->m_Graph.m_LineArray.GetSize();

	m_CIStyle.SetCurSel(0);
	m_SIIndex.SetRange(1, n + 1);
	m_SIWidth.SetRange(0, 5);
	m_SIIndex.SetPos(n + 1);
	m_SIWidth.SetPos(0);
	m_BIApply.EnableWindow(FALSE);

	m_EIName	  = "Type name here";
	m_EIDesc	  = "Type description here";
	m_EIUnit	  = "N/A";
	m_EIMin		  = 0;
	m_EIMax		  = 100;
	m_EIScaledMin = 0;
	m_EIScaledMax = 100;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsert::OnBiapply() 
{
	InsertALine();
}

void CInsert::InsertALine()
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);

	UpdateData();
	int i = m_SIIndex.GetPos() - 1;

	if (pView->InsertALine(i, m_BIColor.GetColor(), m_EIScaledMin, m_EIScaledMax, 
						  (const char*)m_EIName, (const char*)m_EIDesc, (const char*)m_EIUnit, 
					       m_EIMin, m_EIMax, m_CIStyle.GetCurSel(), m_SIWidth.GetPos()))
	{
		int lower, upper;
		m_SIIndex.GetRange(lower, upper);
		m_SIIndex.SetRange(lower, upper + 1); 
		UpdateData(FALSE);
		m_BIApply.EnableWindow(FALSE);
		pView->RefreshGraph();
	}
	else
		MessageBox("Insert a line failed !!!");
}

void CInsert::OnCancel() 
{
	CChildFrame* pWnd  = (CChildFrame*)m_pParent;
	CRTDemoView*  pView = (CRTDemoView*)pWnd->m_wndSplitter.GetPane(0, 0);
	if (m_BIApply.IsWindowEnabled())
	{
		UpdateData();
		int n = MessageBox("Save changes for <" + m_EIName + "> ?", 
						AfxGetAppName(), MB_YESNO);
		if (n == IDYES)
		{
			InsertALine();
		}
	}
	
	CDialog::OnCancel();
}

void CInsert::OnChangeEiwidth() 
{
	if (::IsWindow(m_BIApply.m_hWnd))
	{
		m_BIApply.EnableWindow();

		UpdateData();
		if (m_SIWidth.GetPos() > 1)
			m_CIStyle.SetCurSel(0);
		UpdateData(FALSE);
	}
}

void CInsert::OnChangeEiunit() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEiscaledmin() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEiscaledmax() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEIName() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEimin() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEimax() 
{
	m_BIApply.EnableWindow();
}

void CInsert::OnChangeEiindex() 
{
	if (::IsWindow(m_BIApply.m_hWnd))
		m_BIApply.EnableWindow();
}

void CInsert::OnChangeEidescription() 
{
	m_BIApply.EnableWindow();
}
