// WifiDevicesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PeekPocket.h"
#include "ScannerDlg.h"
#include "PPDlg.h"

// CWifiDevicesDlg dialog

IMPLEMENT_DYNAMIC(CScannerDlg, CColoredDlg)

CScannerDlg::CScannerDlg(CWnd* pParent /*=NULL*/)
	: CColoredDlg(CScannerDlg::IDD, pParent)
{
	m_bListFontApplied=false;
	m_bLarge=false;
	m_numactive=_T("");
	m_rb_static=_T("");
}

CScannerDlg::~CScannerDlg()
{
}

void CScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CColoredDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE_LIST, m_list);
	DDX_Text(pDX, IDC_NUM_ACTIVE, m_numactive);
	DDX_Text(pDX, IDC_RB_STATIC, m_rb_static);
}


BEGIN_MESSAGE_MAP(CScannerDlg, CColoredDlg)
	ON_WM_PAINT()
	ON_COMMAND(ID_POPUP_GOLARGE, &CScannerDlg::OnPopupGolarge)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CWifiDevicesDlg message handlers
//////////////////////////////////////////////////////////////////////////
BOOL CScannerDlg::OnInitDialog()
{
CRect rcDlg, rcList;
CPPDlg *pParent;

	CColoredDlg::OnInitDialog();

	//set up list columns
	m_list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T("Sig"), LVCFMT_LEFT, 30);
	m_list.InsertColumn(2, _T("Ch"), LVCFMT_LEFT, 30);
	m_list.InsertColumn(3, _T("Type"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(4, _T("Sec"), LVCFMT_LEFT, 30);
	m_list.InsertColumn(5, _T("MAC"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(6, _T("BSig"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(7, _T("WSig"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(8, _T("First Seen"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(9, _T("Last Seen"), LVCFMT_LEFT, 100);

	//resize list
	pParent=(CPPDlg *)GetParent();
	if(pParent != NULL)
	{
		//size to fit to tab control
		pParent->m_tab.GetWindowRect(&rcDlg);
		m_list.GetWindowRect(&rcList);
		rcList.SetRect(0, 0, rcDlg.Width(), rcList.Height());
		m_list.MoveWindow(&rcList);
	}

	SetListFont(12);

	m_rb_static=_T("Tap an AP name");

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CScannerDlg::OnPaint()
{
	CColoredDlg::OnPaint();
	m_list.ShowWindow(SW_HIDE);
	ApplyListFont();

	//show list only if not in large mode
	if(m_bLarge == false)
	{
		m_list.ShowWindow(SW_SHOW);
	}
	else
	{
		//display AP data with huge font
		CFont font;
		HGDIOBJ hOldObj;
		CRect rc;
		CString str;
		DisplayInfo di;

		CDC *pDC=GetDC();
		if(pDC != NULL)
		{
			font.CreateFont(100, 0, 0, 0, FW_BOLD, FALSE /*italic*/, FALSE /*underline*/, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Tahoma")) ;
			hOldObj=pDC->SelectObject(font);

			str=_T("--");
			
			//get row
			GetRow(m_iLargeID, di);				

			//only if active
			if(di.bActive == true)
			{
				str.Format(_T("%d"), abs(di.RSSI));
			}

			//let the dialog setup colors in DC
			SendMessage(WM_CTLCOLORSTATIC, (WPARAM)pDC->GetSafeHdc(), -1);

			//display signal
			GetClientRect(&rc);
			rc.top+=20;
			rc.bottom-=20;

			pDC->DrawText(str, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			pDC->SelectObject(hOldObj);

			//display AP name
			font.DeleteObject();
			font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE /*italic*/, FALSE /*underline*/, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Tahoma")) ;
			hOldObj=pDC->SelectObject(font);

			GetClientRect(&rc);
			rc.bottom=rc.top+20;

			str=di.SSID;

			pDC->DrawText(str, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			pDC->SelectObject(hOldObj);

			ReleaseDC(pDC);
		}//if DC ok
	}//if large
}

//////////////////////////////////////////////////////////////////////////
//internal function to apply changed list font and resize columns if required
void CScannerDlg::ApplyListFont()
{
LVCOLUMN col;

	if(m_bListFontApplied == false)
	{
		col.mask = LVCF_WIDTH;

		//resize columns
		col.cx=(int) (50 * (m_iListFontSize/10.0));
		m_list.SetColumn(0, &col);

		col.cx=(int) (30 * (m_iListFontSize/10.0));
		m_list.SetColumn(1, &col);

		col.cx=(int) (30 * (m_iListFontSize/10.0));
		m_list.SetColumn(2, &col);

		col.cx=(int) (40 * (m_iListFontSize/10.0));
		m_list.SetColumn(3, &col);

		col.cx=(int) (35 * (m_iListFontSize/10.0));
		m_list.SetColumn(4, &col);

		col.cx=(int) (90 * (m_iListFontSize/10.0));
		m_list.SetColumn(5, &col);

		col.cx=(int) (40 * (m_iListFontSize/10.0));
		m_list.SetColumn(6, &col);

		col.cx=(int) (40 * (m_iListFontSize/10.0));
		m_list.SetColumn(7, &col);

		col.cx=(int) (100 * (m_iListFontSize/10.0));
		m_list.SetColumn(8, &col);

		col.cx=(int) (100 * (m_iListFontSize/10.0));
		m_list.SetColumn(9, &col);

		//set list font
		CWnd* pWnd=GetDlgItem(IDC_DEVICE_LIST);
		if(pWnd != NULL)
		{
			//no repaint
			pWnd->SetFont(NULL, FALSE);
			m_listfont.DeleteObject();
			m_listfont.CreateFont(m_iListFontSize, 0, 0, 0, FW_BOLD, FALSE /*italic*/, FALSE /*underline*/, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Tahoma")) ;
			//do repaint
			pWnd->SetFont(&m_listfont);
		}
		m_bListFontApplied=true;
	}	
	//font will be deleted by dialog dtor
}

//////////////////////////////////////////////////////////////////////////
//this function will make sure the list font gets updated
void CScannerDlg::SetListFont(int iFontSize)
{
	//if size differs from current
	if(m_iListFontSize != iFontSize)
	{
		m_iListFontSize=iFontSize;
		//need to set on next activate
		m_bListFontApplied=false;
	}
}

//////////////////////////////////////////////////////////////////////////
//this function updates the list control with current data
void CScannerDlg::UpdateList()
{
POSITION pos;
DisplayInfo di;
BYTE *key;
DWORD dwTotal, dwActive;

	CPPDlg *pParent=(CPPDlg *)GetParent();
	if(pParent != NULL)
	{
		EnterCriticalSection(&pParent->m_DataLock);
		//for every SSID
		pos=pParent->m_data.GetStartPosition();
		dwTotal=dwActive=0;
		while(pos != NULL)
		{
			pParent->m_data.GetNextAssoc(pos, key, di);
			//if not filtered out, add/update in list
			if( (pParent->m_bHideSecure == true && di.Auth != Ndis802_11AuthModeOpen) || (pParent->m_bHidePeer == true && di.Infastructure != Ndis802_11Infrastructure) )
			{
				continue;
			}
			else
			{
				dwTotal++;
				if(di.bActive == true)
				{
					dwActive++;
				}
				UpdateItem(di);
			}
		}
		LeaveCriticalSection(&pParent->m_DataLock);
	}
	m_numactive.Format(_T("%d/%d active"), dwActive, dwTotal);
	UpdateData(FALSE);
	//force repaint if large
	if(m_bLarge == true)
	{
		Invalidate();
	}
}

//////////////////////////////////////////////////////////////////////////
void CScannerDlg::UpdateItem(DisplayInfo nfo)
{
LVITEM lvi;
CString strItem;
int nItemNo;
LVFINDINFO info;
bool bInsert;

	//insert or update? find item in list
	info.flags=LVFI_PARAM;
	info.lParam=nfo.ID;
	nItemNo=m_list.FindItem(&info);

	if(nItemNo == -1)
	{
		//not found
		bInsert=true;
		nItemNo=m_list.GetItemCount();
	}
	else
	{
		bInsert=false;
	}

	lvi.mask=LVIF_TEXT;
	lvi.iItem=nItemNo;
	//ssid
	strItem=nfo.SSID;
	lvi.iSubItem=0;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);

	//insert or update?
	if(bInsert == true)
	{
		m_list.InsertItem(&lvi);
	}
	else
	{
		m_list.SetItem(&lvi);
	}

	//store ID as "lParam", so can lookup later
	lvi.mask=LVIF_PARAM;
	lvi.lParam=nfo.ID;
	m_list.SetItem(&lvi);

	lvi.mask=LVIF_TEXT;
	//signal
	strItem.Format(_T("%d"), nfo.RSSI);
	lvi.iSubItem=1;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//channel
	strItem.Format(_T("%d"), nfo.Channel);
	lvi.iSubItem=2;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//type
	switch(nfo.Infastructure)
	{
		case Ndis802_11IBSS:
		{
			strItem=_T("Peer");
			break;
		}
		case Ndis802_11Infrastructure:
		{
			strItem=_T("AP");
			break;
		}
		default:
		strItem=_T("?");
	}
	lvi.iSubItem=3;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//auth
	if(nfo.Auth == Ndis802_11AuthModeOpen)
	{
		strItem=_T("Open");
	}
	else
	{
		strItem=_T("WEP");
	}
	lvi.iSubItem=4;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//mac
	strItem.Format(_T("%02x-%02x-%02x-%02x-%02x-%02x"), nfo.BSSID[0], nfo.BSSID[1], nfo.BSSID[2], nfo.BSSID[3], nfo.BSSID[4], nfo.BSSID[5]);
	lvi.iSubItem=5;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//best signal
	strItem.Format(_T("%d"), nfo.iBestSig);
	lvi.iSubItem=6;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//worst signal
	strItem.Format(_T("%d"), nfo.iWorstSig);
	lvi.iSubItem=7;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);

	//first seen
	COleDateTime dFirst(nfo.dFirstSeen);

	//could use COleDateTime::Format
	strItem.Format(_T("%02d/%02d/%02d %02d:%02d:%02d"), dFirst.GetYear() % 1000, dFirst.GetMonth(), dFirst.GetDay(), dFirst.GetHour(), dFirst.GetMinute(), dFirst.GetSecond());
	lvi.iSubItem=8;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);	

	//last seen
	COleDateTime dLast(nfo.dLastSeen);

	strItem.Format(_T("%02d/%02d/%02d %02d:%02d:%02d"), dLast.GetYear() % 1000, dLast.GetMonth(), dLast.GetDay(), dLast.GetHour(), dLast.GetMinute(), dLast.GetSecond());
	lvi.iSubItem=9;
	lvi.pszText=(LPTSTR)(LPCTSTR)(strItem);
	m_list.SetItem(&lvi);	
}

//////////////////////////////////////////////////////////////////////////
//this handler pops up "go large" menu and also takes
//care of list items coloring.
//more on the subject can be found in M. Dunn's article:
//http://www.codeproject.com/listctrl/lvcustomdraw.asp
//
BOOL CScannerDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

	//if not coming from the list control, 
	if(wParam != IDC_DEVICE_LIST)
	{
		*pResult=0;
		return CWnd::OnNotify(wParam, lParam, pResult);
	}
	
	LPNMHDR pNMHDR=(LPNMHDR) lParam;

#ifdef _DEBUG
	CString str;
	str.Format(_T("Notification from %d: %d\n"), wParam, pNMHDR->code);
	OutputDebugString(str);
#endif

	*pResult=0;

	switch(pNMHDR->code)
	{
		case NM_CLICK:
		{
			LPNMLISTVIEW lplv = (LPNMLISTVIEW) lParam;
			if(lplv->iItem != -1)
			{
				CMenu popup, *subitem;
				CPoint pt;

				popup.LoadMenu(IDR_MENU_GOLARGE);

				subitem = popup.GetSubMenu(0);    
				pt=lplv->ptAction;
				m_list.ClientToScreen(&pt);

				//store clicked item ID
				
				//this was always zero.
				//m_iLargeID=lplv->lParam;

				//so query back from list item
				LVITEM lvi;
				lvi.mask=LVIF_PARAM;
				lvi.iItem=lplv->iItem;
				lvi.iSubItem=0;
				if(FALSE == m_list.GetItem(&lvi))
				{
					m_iLargeID=0;
					#ifdef _DEBUG
						OutputDebugString(_T("Failed to query LPARAM for clicked list item."));
					#endif
				}
				else
				{
					m_iLargeID=lvi.lParam;
				}
				subitem->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
			}

			break;
		}
		case NM_RECOGNIZEGESTURE:
		{
			//no dots
			*pResult=TRUE;		
			break;
		}
		case NM_CUSTOMDRAW:
		{
			NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

			//do default processing after this
			*pResult = CDRF_DODEFAULT;

			// First thing - check the draw stage. If it's the control's prepaint
			// stage, then tell Windows we want messages for every item.
			switch(pLVCD->nmcd.dwDrawStage)
			{
				case CDDS_PREPAINT:
				{
					*pResult = CDRF_NOTIFYITEMDRAW;
					break;
				}
				case CDDS_ITEMPREPAINT:
				{
					// This is the notification message for an item.  We'll request
					// notifications before each subitem's prepaint stage.

					*pResult = CDRF_NOTIFYSUBITEMDRAW;

					//lookup info struct for coloring
					GetRow(pLVCD->nmcd.lItemlParam, m_diTmp);

					break;
				}
				case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
				{
					COLORREF crTxt, crBkg;

					crBkg=GetSysColor(COLOR_WINDOW);
					crTxt=GetSysColor(COLOR_WINDOWTEXT);

					//if BSSID requires Auth, name and "Sec" will be printed in red
					if(pLVCD->iSubItem == 0 || pLVCD->iSubItem == 4)
					{
						if(m_diTmp.Auth != Ndis802_11AuthModeOpen)
						{
							crTxt=RGB(255, 0, 0);
						}
					}
					if(m_diTmp.bActive == false)
					{
						crTxt=GetSysColor(COLOR_GRAYTEXT);
					}

					pLVCD->clrText=crTxt;
					pLVCD->clrTextBk=crBkg;

					// Tell Windows to paint the control itself.
					*pResult = CDRF_DODEFAULT;
					break;
				}//case subitem prepaint
			}//switch drawstage
			break;
		}//NM_CUSTOMDRAW
	}//switch notification code
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//get all data of a certain AP
bool CScannerDlg::GetRow(DWORD ID, DisplayInfo &di)
{
bool retval;
POSITION pos;
BYTE *key;

	retval=false;
	CPPDlg *pParent=(CPPDlg *)GetParent();
	if(pParent != NULL)
	{
		EnterCriticalSection(&pParent->m_DataLock);
		//for every SSID
		pos=pParent->m_data.GetStartPosition();
		while(pos != NULL)
		{
			pParent->m_data.GetNextAssoc(pos, key, di);
			if(di.ID == ID)
			{
				//looked up OK.
				retval=true;
				//end while
				break;
			}
		}
		LeaveCriticalSection(&pParent->m_DataLock);
	}
	return retval;
}

//////////////////////////////////////////////////////////////////////////
//handle go large menu click
void CScannerDlg::OnPopupGolarge()
{
	m_bLarge=true;
	m_rb_static=_T("Tap to restore");
	m_list.ShowWindow(SW_HIDE);
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
//tap handler - used to come back from large mode
void CScannerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if in large mode, return to normal
	if(m_bLarge == true)
	{
		m_bLarge=false;
		m_rb_static=_T("Tap an AP name");
		m_list.ShowWindow(SW_SHOW);
		UpdateData(FALSE);
	}
	Default();
}

