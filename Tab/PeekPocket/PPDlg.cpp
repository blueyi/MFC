// PPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PeekPocket.h"
#include "PPDlg.h"

// CPPDlg dialog

/////////////////////////////////////////////////////////////////////////
CPPDlg::CPPDlg(CWnd* pParent /*=NULL*/)
	: CColoredDlg(CPPDlg::IDD, pParent)
{
	m_iRefreshRate=REFRESH_RATE_DEFAULT;
	m_bRunning=true;
	m_dwTickCounter=0;
	InitializeCriticalSection(&m_DataLock);

	m_bSoundOff=true;	//sub ping off by default :-)
	m_bHidePeer=true;
	m_bHideSecure=true;
}

//////////////////////////////////////////////////////////////////////////
CPPDlg::~CPPDlg()
{
	DeleteCriticalSection(&m_DataLock);
}

/////////////////////////////////////////////////////////////////////////
void CPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CColoredDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCTRL, m_tab);
	DDX_Control(pDX, IDC_SUSRES, m_btnSusRes);
	DDX_Control(pDX, IDC_APICON, m_apicon);
	DDX_Control(pDX, IDC_EXITBTN, m_btnExit);
}

BEGIN_MESSAGE_MAP(CPPDlg, CColoredDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXITBTN, &CPPDlg::OnBnClickedExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SUSRES, &CPPDlg::OnBnClickedSuspendResume)
	ON_CBN_SELCHANGE(IDC_ADAPTERS_COMBO, &CPPDlg::OnCbnSelchangeAdaptersCombo)
END_MESSAGE_MAP()


// CPPDlg message handlers

//////////////////////////////////////////////////////////////////////////
BOOL CPPDlg::OnInitDialog()
{
WCHAR buf[1024];
DWORD dwSize;
RECT rcWA;
CRect rcOld, rcNew;

	CColoredDlg::OnInitDialog();

	//set dialog colors
	SetBkgColor(GetSysColor(COLOR_ACTIVECAPTION));
	SetFrgColor(GetSysColor(COLOR_CAPTIONTEXT));

	//init tab control styles
	m_tab.ModifyStyle(0, WS_VISIBLE | CTCS_TOP | CTCS_AUTOHIDEBUTTONS | CTCS_CONTAINER);	

	//setup tab control colors
	TabItemColors ticColors;

	//get colors..
	m_tab.GetColors(&ticColors);
	
	//modify them..
	ticColors.crBkgActive=RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255));
	ticColors.crTxtActive=RGB(0, 0, 0);
	ticColors.crBkgInactive=GetSysColor(COLOR_ACTIVECAPTION);
	ticColors.crTxtInactive=RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), GetSysColor(COLOR_CAPTIONTEXT));
	ticColors.crWndBkg=GetSysColor(COLOR_ACTIVECAPTION);
	
	//..and write back
	m_tab.SetColors(&ticColors);

	//create tabs and setup page colors

	//create the scanner dlg
	m_pScannerDlg=new CScannerDlg();
	m_pScannerDlg->Create(CScannerDlg::IDD, this);
	//..setup colors
	m_pScannerDlg->SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_pScannerDlg->SetFrgColor(RGB(0, 0, 0));
	//..add tab to tab control & dialog to container with the same call
	m_tab.AddDialog(0, _T("Scanner"), m_pScannerDlg);

	//create the options dlg
	m_pOptionsDlg=new COptionsDlg();
	m_pOptionsDlg->Create(COptionsDlg::IDD, this);
	//..setup colors
	m_pOptionsDlg->SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_pOptionsDlg->SetFrgColor(RGB(0, 0, 0));
	//..add tab to tab control & dialog to container with the same call
	m_tab.AddDialog(1, _T("Options"), m_pOptionsDlg);

	//init buttons

	//init exit btn
	m_btnExit.SetBkgIdleColor(GetSysColor(COLOR_ACTIVECAPTION));
	m_btnExit.SetBkgActiveColor(GetSysColor(COLOR_ACTIVECAPTION));
	m_btnExit.SetGradientColors(GetSysColor(COLOR_ACTIVECAPTION), RGB(200, 200, 200));
	m_btnExit.SetFlags(bfHGradient);

	//init suspend/resume btn
	m_btnSusRes.SetBkgIdleColor(GetSysColor(COLOR_ACTIVECAPTION));
	m_btnSusRes.SetBkgActiveColor(GetSysColor(COLOR_ACTIVECAPTION));
	m_btnSusRes.SetCaption(_T("Suspend"), _T("Resume"));
	m_btnSusRes.SetGradientColors(GetSysColor(COLOR_ACTIVECAPTION), RGB(200, 200, 200));
	m_btnSusRes.SetFlags(bfHGradient);
	m_btnSusRes.ModifyStyle(0, BS_PUSHLIKE);

	//init adapter list

	dwSize=sizeof(buf);
	if(false == m_wp.GetAdapters(buf, dwSize) || dwSize == 0)
	{
//		AfxMessageBox(_T("No adapters found!"));
	}
	else
	{
		//split adapter names, and add to combo

		CString strList, strName;
		int pos;

		strList=buf;
		pos=0;

		//just one adapter?
		if(strList.Find(_T(',')) == -1)
		{
			m_pOptionsDlg->m_adapters.AddString(strList);	
		}
		else
		//no, a list of adapters
		{
			do
			{
				strName=SplitString(strList, _T(','), pos);
				m_pOptionsDlg->m_adapters.AddString(strName);
			}while(strName != _T("") && pos != -1);
		}
		m_pOptionsDlg->m_adapters.SetCurSel(0);
		m_pOptionsDlg->UpdateData(FALSE);
		OnCbnSelchangeAdaptersCombo();
	}

	//position controls according to current screen orientation
	if(SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWA, 0))
	{
		if(rcWA.right - rcWA.left > rcWA.bottom - rcWA.top)
		{
			//landscape: reposition buttons
			m_btnExit.GetWindowRect(&rcOld);
			rcNew.SetRect(rcOld.top, rcOld.left+55, rcOld.top+rcOld.Width(), rcOld.left+55+rcOld.Height());
			m_btnExit.MoveWindow(&rcNew);

			m_btnSusRes.GetWindowRect(&rcOld);
			rcNew.SetRect(rcOld.top, rcOld.left, rcOld.top+rcOld.Width(), rcOld.left+rcOld.Height());
			m_btnSusRes.MoveWindow(&rcNew);

			m_apicon.GetWindowRect(&rcOld);
			rcNew.SetRect(rcOld.top+25, rcOld.left, rcOld.top+25+rcOld.Width(), rcOld.left+rcOld.Height());
			m_apicon.MoveWindow(&rcNew);

			//resize dialog
			MoveWindow(&rcWA);
		}
	}

	m_data.RemoveAll();

	//launch timers
	SetTimer(REFRESH_TIMER_ID, m_iRefreshRate, 0);
	SetTimer(ANIM_TIMER_ID, m_iRefreshRate/2, 0);
	m_dwTickCounter=0;
	m_apicon.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
}

//////////////////////////////////////////////////////////////////////////
void CPPDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
		case ANIM_TIMER_ID:
		{
			//kill timer so that change to speed will be applied immediately
			KillTimer(ANIM_TIMER_ID);
			
			m_dwTickCounter++;

			//if there is an adapter we can use
			if(m_strCurrentAdapter != _T(""))
			{
				//flash icon
				if(m_dwTickCounter % 2)
				{
					m_apicon.ShowWindow(SW_SHOW);
				}
				else
				{
					m_apicon.ShowWindow(SW_HIDE);
				}
				//restart this timer, with current refresh rate
				SetTimer(ANIM_TIMER_ID, m_iRefreshRate/2, NULL);
			}
			else
			{
				//no adapter, hide icon
				m_apicon.ShowWindow(SW_HIDE);
			}
			break;
		}
		case REFRESH_TIMER_ID:
		{
			DWORD dwTmp, dwCount;
			BSSIDInfo nfo[128];
			POSITION pos;
			DisplayInfo di;
			BYTE *key;

			//temporarily disable timer
			KillTimer(REFRESH_TIMER_ID);

			//reset active flag
			EnterCriticalSection(&m_DataLock);
			pos=m_data.GetStartPosition();
			while(pos != NULL)
			{
				m_data.GetNextAssoc(pos, key, di);
				di.bActive=false;
				m_data.SetAt(di.BSSID, di);
			}
			LeaveCriticalSection(&m_DataLock);

			dwTmp=sizeof(nfo);
			dwCount=0;
			//refresh BSSID list and get list
			if(m_wp.RefreshBSSIDs(m_strCurrentAdapter.GetBuffer()) && m_wp.GetBBSIDs(m_strCurrentAdapter.GetBuffer(), nfo, dwTmp, dwCount) && dwCount > 0)
			{
				ProcessInfo(nfo, dwCount);
			}//get BSSID ok

			//update list even if nothing found
			m_pScannerDlg->UpdateList();

			//restart timer
			SetTimer(REFRESH_TIMER_ID, m_iRefreshRate, 0);

			break;
		}//case REFRESH_TIMER_ID
	}//switch timer id
}

//////////////////////////////////////////////////////////////////////////
void CPPDlg::OnBnClickedExit()
{
	//shotdown timers
	KillTimer(REFRESH_TIMER_ID);
	KillTimer(ANIM_TIMER_ID);
	EndDialog(IDOK);
}

//////////////////////////////////////////////////////////////////////////
//this is a CString::Tokenize replacement, it is not better, just it can
//be used on old MFC versions where the above call is missing.
CString CPPDlg::SplitString(CString strIn, TCHAR cSplitAt, int &iPos)
{
int i1, i2;

	if(iPos >= strIn.GetLength())
	{
		iPos=-1;
		return CString(_T(""));
	}

	i1=strIn.Find(cSplitAt, iPos);
	//not found?
	if(i1 == -1)
	{
		//return input string from iPos.
		i1=iPos;
		iPos=-1;
		return strIn.Mid(i1);
	}
	else
	{
		//found, return substring between (startpos, foundpos)
		i2=iPos;
		iPos=i1+1;

		if(i1 > i2)
		{
			return strIn.Mid(i2, i1-i2);
		}
		else
		{
			return strIn.Mid(i2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//handle suspend/resume
void CPPDlg::OnBnClickedSuspendResume()
{
	if(m_bRunning)
	{
		m_bRunning=false;
		KillTimer(REFRESH_TIMER_ID);
		KillTimer(ANIM_TIMER_ID);
		m_apicon.ShowWindow(SW_HIDE);
	}
	else
	{
		m_bRunning=true;
		//restart timer
		SetTimer(REFRESH_TIMER_ID, m_iRefreshRate, 0);
		SetTimer(ANIM_TIMER_ID, m_iRefreshRate/2, 0);
		m_dwTickCounter=0;
		m_apicon.ShowWindow(SW_SHOW);
	}
}

//////////////////////////////////////////////////////////////////////////
void CPPDlg::OnCbnSelchangeAdaptersCombo()
{
	//store current adapter name
	m_pOptionsDlg->m_adapters.GetWindowText(m_strCurrentAdapter);
}

//////////////////////////////////////////////////////////////////////////
//this function adds APs to the list or updates existing ones.
void CPPDlg::ProcessInfo(struct BSSIDInfo *pInfo, DWORD dwNum)
{
int i;
DisplayInfo di;
SYSTEMTIME time;

	EnterCriticalSection(&m_DataLock);
	for(i=0; i<dwNum; i++)
	{
		//already known BSSID?
		if(m_data.Lookup(pInfo[i].BSSID, di) == TRUE)
		{
			//update data
			di.bActive=true;
			di.Channel=pInfo[i].Channel;
			di.Infastructure=pInfo[i].Infastructure;
			di.Auth=pInfo[i].Auth;
			di.RSSI=pInfo[i].RSSI;
			wcscpy(di.SSID, pInfo[i].SSID);
		
			//current is the strongest so far?
			if(di.iBestSig < di.RSSI)
			{
				di.iBestSig=di.RSSI;
			}
			
			if(di.iWorstSig > di.RSSI)
			{
				di.iWorstSig=di.RSSI;
			}
	
			//store signal history
			di.ilSigHistory.AddTail(di.RSSI);
			if(di.ilSigHistory.GetCount() > MAX_SIGNAL_HISTORY)
			{
				di.ilSigHistory.RemoveHead();
			}

			//update last seen
			GetLocalTime(&time);
			COleDateTime dt(time);

			di.dLastSeen=dt;

			//plug back to map
			m_data.SetAt(di.BSSID, di);
		}
		else
		{
			//add to list if not filtered out
			if(pInfo[i].Auth != Ndis802_11AuthModeOpen && m_bHideSecure == true)
			{
				continue;
			}

			if(pInfo[i].Infastructure == Ndis802_11IBSS && m_bHidePeer == true)
			{
				continue;
			}

			//a new one, play sound
			if(m_bSoundOff == false)
			{
				PlaySound(MAKEINTRESOURCE(IDR_SONAR), AfxGetResourceHandle(), SND_RESOURCE | SND_ASYNC);
			}

			di.bActive=true;
			di.Channel=pInfo[i].Channel;
			di.Infastructure=pInfo[i].Infastructure;
			di.Auth=pInfo[i].Auth;
			di.RSSI=pInfo[i].RSSI;
			di.iBestSig=di.iWorstSig=di.RSSI;

			//create first seen, last seen
			GetLocalTime(&time);
			COleDateTime dt(time);

			di.dFirstSeen=dt;
			di.dLastSeen=dt;

			memcpy(di.BSSID, pInfo[i].BSSID, 6);
			wcscpy(di.SSID, pInfo[i].SSID);
			
			di.ID=m_data.GetCount();
			m_data.SetAt(di.BSSID, di);
		}
	}
	LeaveCriticalSection(&m_DataLock);
}