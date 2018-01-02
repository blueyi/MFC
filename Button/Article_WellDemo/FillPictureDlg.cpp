// FillPictureDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "svizres.h"
#include "FillPictureDlg.h"
#include "EffectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFillPictureDlg dialog
IMPLEMENT_DYNAMIC (CFillPictureDlg, CPropertyPage);

CFillPictureDlg::CFillPictureDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CFillPictureDlg::IDD)
{
	//{{AFX_DATA_INIT(CFillPictureDlg)
	m_type = -1;
	//}}AFX_DATA_INIT
}


void CFillPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFillPictureDlg)
	DDX_Control(pDX, IDC_SVIZ_WRAPMODE, m_typeCtrl);
	DDX_Control(pDX, IDC_SVIZ_SAMPLE, m_sample);
	DDX_CBIndex(pDX, IDC_SVIZ_WRAPMODE, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFillPictureDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CFillPictureDlg)
	ON_CBN_SELCHANGE(IDC_SVIZ_WRAPMODE, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_SVIZ_PICTURE, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFillPictureDlg message handlers

void CFillPictureDlg::DrawSample()
{

	//send message to m_sample to let it redraw;
	m_sample.Invalidate();
	m_sample.UpdateWindow();

}


void CFillPictureDlg::OnSelchangeCombo1() 
{
	SetValue();
	DrawSample();
}

void CFillPictureDlg::OnButton1() 
{
    USES_CONVERSION;

    CString szFilter = _T("JPEG (*.jpg;*.jpeg)|*.jpg;*.jpeg|Windows Bitmap (*.bmp)|*.bmp|Graphics Interchange Format (*.gif)|*.gif|Exchangeable Image File(*.Exif)|*.Exif|Tag Image File Format(*.tiff)|*.tiff|Windows Metafile (*.WMF)|*.wmf|Portable Graphics (*.PNG)|*.png|All Files (*.*)|*.*|");
	CFileDialog fileDlg( TRUE, _T(".gif"), _T(""), OFN_HIDEREADONLY, szFilter, this);
	if (fileDlg.DoModal() != IDOK)
		return;
	m_fileName=fileDlg.GetPathName();


#ifdef _UNICODE
	Image *image = Image::FromFile(m_fileName);
#else if
    LPWSTR lpwstr = A2W(m_fileName);
	Image *image = Image::FromFile(lpwstr);
#endif


	if (image->GetLastStatus()!=Ok){
		AfxMessageBox(_T("Not valid image file!"));
		m_fileName = "";
	}
	else{
		CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());
		pDlg->m_fileName = m_fileName;
		GetDlgItem(IDC_STATICNAME)->SetWindowText(m_fileName);
		SetValue();
		DrawSample();
	}
}


void CFillPictureDlg::SetValue()
{
	CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());

	pDlg->m_BrushType = BrushTypeTextureFill;

	//file name is already set by the OnButton1

	if (m_typeCtrl.GetCurSel() <=4){
		 	pDlg->m_wrapMode = (WrapMode)m_typeCtrl.GetCurSel();
			pDlg->m_nStretch = 0;
	}
	 else
			pDlg->m_nStretch = 1;
}

BOOL CFillPictureDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());
	if (pDlg->m_fileName!="")
		GetDlgItem(IDC_STATICNAME)->SetWindowText(pDlg->m_fileName);

	m_typeCtrl.SetCurSel(pDlg->m_wrapMode +pDlg->m_nStretch); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
