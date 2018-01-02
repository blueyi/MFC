#include "stdafx.h"
#include "Work.h"
#include "Input.h"


/////////////////////////////////////////////////////////////////////////////
// CInput dialog


CInput::CInput(CWnd* pParent /*=NULL*/)
	: CDialog(CInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInput)
	m_x1 = FALSE;
	m_x2 = FALSE;
	m_x3 = FALSE;
	m_c1 = FALSE;
	m_c2 = FALSE;
	m_c3 = FALSE;
	m_m = 1;
	m_add = _T("");
	m_attrib = _T("");
	m_contact = _T("");
	m_industry = _T("");
	m_introdu = _T("");
	m_name = _T("");
	m_npost = _T("");
	m_salary = _T("");
	m_scale = _T("");
	m_source = _T("");
	m_level = _T("");
	//}}AFX_DATA_INIT
}


void CInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInput)
	DDX_Check(pDX, IDC_CHECK1, m_x1);
	DDX_Check(pDX, IDC_CHECK2, m_x2);
	DDX_Check(pDX, IDC_CHECK3, m_x3);
	DDX_Check(pDX, IDC_CHECK4, m_c1);
	DDX_Check(pDX, IDC_CHECK5, m_c2);
	DDX_Check(pDX, IDC_CHECK6, m_c3);
	DDX_Radio(pDX, IDC_RADIO1, m_m);
	DDX_Text(pDX, IDC_EDIT_ADD, m_add);
	DDV_MaxChars(pDX, m_add, 60);
	DDX_Text(pDX, IDC_EDIT_ATTRIB, m_attrib);
	DDV_MaxChars(pDX, m_attrib, 40);
	DDX_Text(pDX, IDC_EDIT_CONTACT, m_contact);
	DDV_MaxChars(pDX, m_contact, 60);
	DDX_Text(pDX, IDC_EDIT_INDUSTRY, m_industry);
	DDV_MaxChars(pDX, m_industry, 60);
	DDX_Text(pDX, IDC_EDIT_INTRODU, m_introdu);
	DDV_MaxChars(pDX, m_introdu, 750);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 80);
	DDX_Text(pDX, IDC_EDIT_NPOST, m_npost);
	DDV_MaxChars(pDX, m_npost, 40);
	DDX_Text(pDX, IDC_EDIT_SALARY, m_salary);
	DDV_MaxChars(pDX, m_salary, 40);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_scale);
	DDV_MaxChars(pDX, m_scale, 60);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_source);
	DDV_MaxChars(pDX, m_source, 60);
	DDX_Text(pDX, IDC_EDIT10, m_level);
	DDV_MaxChars(pDX, m_level, 750);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInput, CDialog)
	//{{AFX_MSG_MAP(CInput)
	ON_BN_CLICKED(IDC_BYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CInput::OnOK() 
{

}

void CInput::OnYes() 
{
	UpdateData();
	memset(&xData,0,sizeof(MYDATA));

	memcpy(xData.name,m_name,m_name.GetLength());
	memcpy(xData.add,m_add,m_add.GetLength());
	memcpy(xData.industry,m_industry,m_industry.GetLength());
	memcpy(xData.scale,m_scale,m_scale.GetLength());
	memcpy(xData.contact,m_contact,m_contact.GetLength());
	memcpy(xData.attrib,m_attrib,m_attrib.GetLength());
	memcpy(xData.source,m_source,m_source.GetLength());
	memcpy(xData.introduction,m_introdu,m_introdu.GetLength());
	memcpy(xData.npost,m_npost,m_npost.GetLength());
	memcpy(xData.salary,m_salary,m_salary.GetLength());
	memcpy(xData.level,m_level,m_level.GetLength());
    xData.stype=m_m;
    xData.x1=m_x1;
    xData.x2=m_x2;
    xData.x3=m_x3;
    xData.c1=m_c1;
    xData.c2=m_c2;
    xData.c3=m_c3;
	xData.ls=5;
	CDialog::OnOK();	
}
