// ChildDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ThumbNail.h"
#include "ChildDialog.h"


// CChildDialog dialog

IMPLEMENT_DYNAMIC(CChildDialog, CDialog)

CChildDialog::CChildDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CChildDialog::IDD, pParent)
{

}

CChildDialog::~CChildDialog()
{
}

void CChildDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CUSTOM_CHILD, m_ChildThumbNailControl);
}


BEGIN_MESSAGE_MAP(CChildDialog, CDialog)
END_MESSAGE_MAP()


// CChildDialog message handlers

BOOL CChildDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    m_ChildThumbNailControl.InitializeVariables( 50, 50 );

    m_ChildThumbNailControl.Add( "fish.bmp" );
    m_ChildThumbNailControl.Add( "pinboard.bmp" );
    m_ChildThumbNailControl.Add( "chess.bmp" );
    m_ChildThumbNailControl.Add( "box.bmp" );
    m_ChildThumbNailControl.Add( "fish.bmp" );
    m_ChildThumbNailControl.Add( "pinboard.bmp" );
    m_ChildThumbNailControl.Add( "chess.bmp" );
    m_ChildThumbNailControl.Add( "box.bmp" );

    m_ChildThumbNailControl.RecalButtonPos();
    m_ChildThumbNailControl.RecalScrollBars();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
