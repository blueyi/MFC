/********************************************************************
    File:	        TipOfTheDayDlg	
    Creation Date:	2009/11/01
	
	Author: 	    Ahmed Charfeddine
					info@potatosoftware.com

	License:        Copyright [2009] [Potato software]

					Licensed under the Apache License, Version 2.0 (the "License");
					you may not use this file except in compliance with the License.
					You may obtain a copy of the License at

							http://www.apache.org/licenses/LICENSE-2.0

					Unless required by applicable law or agreed to in writing, software
					distributed under the License is distributed on an "AS IS" BASIS,
					WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
					See the License for the specific language governing permissions and
					limitations under the License.
    
	Note :	  		
*********************************************************************/
// TipOfTheDayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TipOfTheDayDlg.h"

#include "./TipOfTheDay/webbro.h"
#include <mshtml.h>

#include "Observer.h"

#define nMaxTips 3
// CTipOfTheDayDlg dialog

IMPLEMENT_DYNAMIC(CTipOfTheDayDlg, CDialog)

CTipOfTheDayDlg::CTipOfTheDayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTipOfTheDayDlg::IDD, pParent)
	, m_bActive(FALSE)
{
	lastShown=1;
}

CTipOfTheDayDlg::~CTipOfTheDayDlg()
{
	//
}

void CTipOfTheDayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, ID_CHECK1, m_bActive);
}


BEGIN_MESSAGE_MAP(CTipOfTheDayDlg, CDialog)
	ON_BN_CLICKED(IDNEXT, &CTipOfTheDayDlg::OnBnClickedNext)
END_MESSAGE_MAP()


// CTipOfTheDayDlg message handlers

BOOL CTipOfTheDayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CObserverApp* pMyApp=(CObserverApp*) AfxGetApp();
	lastShown=pMyApp->GetInt(_T("lastTip"),1);


	TCHAR Buffer[MAX_PATH];
	DWORD dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	if(dwRet > 0 && dwRet <=MAX_PATH)
	{
		CString str(Buffer);
		progDir=str;
	}


	m_bActive=true;
	UpdateData(FALSE);
	OnBnClickedNext();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTipOfTheDayDlg::OnBnClickedNext()
{
	if(lastShown==nMaxTips)
		lastShown=0;
	lastShown++;
	// TODO: Add your control notification handler code here
	CString strURL;
	strURL.Format(_T("%s/TipOfTheDay/tip%d.html"),progDir,lastShown);

	CWebBrowser2* pBrowser = (CWebBrowser2*)GetDlgItem( IDC_EXPLORER1 );

	COleVariant* pvarURL = new COleVariant( strURL );
	COleVariant* pvarEmpty = new COleVariant;
	pBrowser->Navigate2( pvarURL, pvarEmpty, pvarEmpty, pvarEmpty, pvarEmpty );
	delete pvarURL;
	delete pvarEmpty;
}

void CTipOfTheDayDlg::OnOK()
{
	UpdateData(TRUE);

	CObserverApp* pMyApp=(CObserverApp*)AfxGetApp();
	pMyApp->WriteInt(_T("showTips"),m_bActive ? 1 : 0);
	pMyApp->WriteInt(_T("lastTip"),lastShown);
	//theApp.m_persistance.UpdateTipOfTheDay(m_bActive,lastShown);
	CDialog::OnOK();
}