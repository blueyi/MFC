// BaseList.cpp : implementation file
//

#include "stdafx.h"
#include "MyCanEditListCtrl.h"
// #include "FindChildPart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMyCanEditListCtrl

CMyCanEditListCtrl::CMyCanEditListCtrl()
{
	m_iStopDestroy=0;
	m_bSetValue=false;
	m_iEditedIndex=-2;

	m_Next=false;
	m_bWaitPopList=false;
	m_iEditedIndex=0;
	this->m_nItem=0;
	this->m_nSubItem=0;

	m_bValueChanged=FALSE;
	m_bIsEdit=FALSE;
	m_bIsComboBox=FALSE;

	m_pDocument=NULL;
}

CMyCanEditListCtrl::~CMyCanEditListCtrl()
{	

	
}


BEGIN_MESSAGE_MAP(CMyCanEditListCtrl, CMyListCtrl)
	//{{AFX_MSG_MAP(CMyCanEditListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	//}}AFX_MSG_MAP
	ON_MESSAGE(QUERY_SETNEXTITEMPHFOCUS,SetNextItemFocus)
	ON_MESSAGE(QUERY_MESSAGE_EDIT_MOVED,OnParentMoved)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCanEditListCtrl message handlers
/////////////////////////////////////////////////////////////////////////////
// CMyChildEdit

CMyChildEdit::CMyChildEdit()
{
	m_bInputValid = FALSE;
	this->m_breturn=false;
	this->m_besc=false;
	this->kc_number=0;
	this->m_dSetFocusValue=0;
}

CMyChildEdit::~CMyChildEdit()
{
}


BEGIN_MESSAGE_MAP(CMyChildEdit, CEdit)
	//{{AFX_MSG_MAP(CMyChildEdit)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyChildEdit message handlers

/////////////////////////////////////////////////////////////////////////////
// CCMyChildComboBox

CMyChildComboBox::CMyChildComboBox()
{
	m_bSelectValid=TRUE;
}

CMyChildComboBox::~CMyChildComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyChildComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyChildComboBox)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetfocus)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyChildComboBox message handlers

void CMyCanEditListCtrl::PreSubclassWindow() 
{
	ModifyStyle(LVS_EDITLABELS, 0L);		//禁止标题编辑
	ModifyStyle(0L, LVS_REPORT);			//设为Report类型
	ModifyStyle(0L, LVS_SHOWSELALWAYS);		//始终高亮度被选中的表项
	ModifyStyle(LVS_OWNERDRAWFIXED ,0L);
	SetExtendedStyle( LVS_EX_FULLROWSELECT 		//允许整行选中
		| LVS_EX_HEADERDRAGDROP 	//允许整列拖动
		| LVS_EX_GRIDLINES 	//画出网格线
		//| LVS_EX_FLATSB				//扁平风格的滚动条	
		);	
	CMyListCtrl::PreSubclassWindow();
}

void CMyCanEditListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	POSITION pos;
	bool		flag=false;
	int i;
	int nItem,nSubItem;
	BOOL bSelected = FALSE;

	//this->GetFocus();

	int mark=this->GetSelectionMark();
//	if(mark<0)	goto defalt_session;
	// 检查是否有Item被选中，没有时不进入编辑
	pos = GetFirstSelectedItemPosition();
	if( pos )
	{
		// 得到被点击的Item
		LVHITTESTINFO testinfo;
		testinfo.pt.x = point.x;
		testinfo.pt.y = point.y;			//点击时的鼠标位置
		testinfo.flags = LVHT_ONITEMLABEL;	//点击的必须是标题
		if( SubItemHitTest(&testinfo)<0 )
			goto defalt_session;			//没有点在有效区域，不进入编辑
		nItem = testinfo.iItem;			//被点击表项的行号
		nSubItem = testinfo.iSubItem;	//被点击表项的列号
		if(nItem!=mark)goto defalt_session;

		BOOL bIsEdit_old;
		bIsEdit_old=m_bIsEdit;
		// 判断得到的单元格是否允许被编辑，同时，记录被编辑的编号
		for(i=0;i<this->m_iColumnEdited.GetCount();i++)
		{
			if(nSubItem==m_iColumnEdited.GetAt(m_iColumnEdited.FindIndex(i)))
			{
				flag=true;
				m_bIsEdit=TRUE;
				m_bIsComboBox=FALSE;
				this->m_iEditedIndex=i;
			}
		}
		for(i=0;i<this->m_iColumnComboBox.GetCount();i++)
		{
			if(nSubItem==m_iColumnComboBox.GetAt(m_iColumnComboBox.FindIndex(i)))
			{
				flag=true;
				m_bIsEdit=FALSE;
				m_bIsComboBox=TRUE;
				this->m_iEditedIndex=i;
			}
		}

		if(!flag)
			goto defalt_session;

			// 开始编辑
		
		if(m_bIsEdit)
		{
			
			if(bIsEdit_old)
			{
			    OnEditKillFocus(m_nItem,m_nSubItem);
			    if(this->m_edit.m_bInputValid)
				{
				    EndEdit(TRUE,m_nSubItem);
				    //AfxMessageBox("this->m_bInputValid  and after parent->OnEditReturn()"); 
				}
			    else
				{
			       EndEdit(FALSE,m_nSubItem);
				}
            }
		    BeginEdit(nItem,nSubItem);
		}
		else if(m_bIsComboBox)
		{
			BeginSelect(nItem,nSubItem);
		}
		return;
	}
defalt_session:
	CMyListCtrl::OnLButtonDown(nFlags, point);
}


BOOL CMyCanEditListCtrl::BeginEdit(int nItem,int nSubItem)
{

	TRACE("BOOL CMyCanEditListCtrl::MyBeginEdit()\n");
	// 得到被编辑表项的区域
	CRect rect;
	if( GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect)==FALSE )
	{
		return FALSE;
	}
	rect.left+=1;
	rect.bottom-=1;

	CString txtItem;
	
	m_ComboBox.ShowWindow(SW_HIDE);
			

		//////////
	DWORD oldflag,flag;
	
	if(nSubItem<m_strArrColumnFmt.GetSize())
	{
	    CString fmt;
		fmt=m_strArrColumnFmt.GetAt(nSubItem);
		
		if(fmt=="LVCFMT_CENTER")
		{
			flag=ES_CENTER;
			oldflag=ES_LEFT|ES_RIGHT;
		}
		else if(fmt=="LVCFMT_LEFT")
		{
			flag=ES_LEFT;
			oldflag=ES_CENTER|ES_RIGHT;
		}
		else if(fmt=="LVCFMT_RIGHT")
		{
			flag=ES_RIGHT;
			oldflag=ES_LEFT|ES_CENTER;
		}
		else
		{
			flag=ES_LEFT;
			oldflag=ES_CENTER|ES_RIGHT;
		}
	}
	else
	{
		flag=ES_LEFT;
		oldflag=ES_CENTER|ES_RIGHT;
	}

	m_edit.ModifyStyle(oldflag,flag,1);

	////////////////////////
	    m_edit.ShowWindow(SW_SHOW);
	    SetValueUnChange("",nSubItem);
	    m_edit.MoveWindow(&rect);

	    txtItem=this->GetItemText(nItem,nSubItem);
	    // 取出的文字填写到编辑控件
		CString str;
	//	str.Format("BeginEdit:  m_nItem=%d,m_nSubItem=%d,txtItem=%s",m_nItem,m_nSubItem,txtItem);
		//AfxMessageBox(str);
	    SetValueUnChange(txtItem,nSubItem);
	    this->OnEditSetFocus(nItem,nSubItem);
		
	    m_edit.SetFocus();
	    m_edit.SetSel( 0, -1 );
	    m_edit.Invalidate();
		m_edit.MoveWindow(&rect);
	    m_edit.ShowWindow(SW_SHOW);
	
	this->m_nItem=nItem;
	this->m_nSubItem=nSubItem;
	
	return TRUE;
}

void CMyCanEditListCtrl::EndEdit( BOOL bValidate,int nSubItem )
{
	if(nSubItem<0 || nSubItem>=this->GetHeaderCtrl()->GetItemCount())
	{
		return;
	}
	    CString txtEdit;
	    m_edit.GetWindowText(txtEdit);
	    if(bValidate==TRUE)
		{
			CString str;
		    str.Format("EndEdit: bValidate=%d,  nSubItem=%d,txtEdit=%s,GetItemText=%s",bValidate,nSubItem,txtEdit,GetItemText(m_nItem, nSubItem));
		    //AfxMessageBox(str);
		    if(txtEdit!=GetItemText(m_nItem, nSubItem))
			{
		        m_bValueChanged=TRUE;////置修改标志为TRUE
				if(this->m_pDocument)
				{
			        this->m_pDocument->SetModifiedFlag(TRUE);
				}
			}
	        SetItemText(m_nItem, nSubItem, txtEdit);
		}
		
	    m_edit.ShowWindow(SW_HIDE);
		
		
	//SetValueUnChange("");


}

int CMyChildEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 改变字体
	LOGFONT logfont;
	logfont.lfHeight = -14;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = 400;
	logfont.lfItalic = 0;
	logfont.lfUnderline = 0;
	logfont.lfStrikeOut = 0;
	logfont.lfCharSet = 134;
	logfont.lfOutPrecision = 0;
	logfont.lfClipPrecision = 0;
	logfont.lfQuality = 0;
	logfont.lfPitchAndFamily = 2;
	strcpy( logfont.lfFaceName, "宋体" );
	m_font.DeleteObject();
	if( m_font.CreateFontIndirect(&logfont) )
		SetFont( &m_font );
	
	return 0;
}
void CMyChildEdit::OnSetFocus(CWnd* pOldWnd)
{	
	m_bInputValid=true;
	CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
	parent->OnEditSetFocus(parent->m_nItem,parent->m_nSubItem);

	CEdit::OnSetFocus(pOldWnd);
}
void CMyChildEdit::OnChange()
{
	CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
	if(parent->m_bSetValue)return;
	parent->OnNewEditChange(parent->m_nItem,parent->m_nSubItem);

}
void CMyChildEdit::OnKillFocus(CWnd* pNewWnd) 
{
	
	// 得到父窗口，并通知父窗口结束编辑过程
	CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
	
	HWND hwnd=pNewWnd->GetSafeHwnd();
	if(pNewWnd!=NULL)
	{
	
			
			parent->OnEditKillFocus(parent->m_nItem,parent->m_nSubItem);
			////CMyChildEdit::OnSetFocus(CWnd* pOldWnd)中赋TRUE值
			//CMyCanEditListCtrl::OnESC()中赋FALSE值
			if(this->m_bInputValid)
			{
				
			    //parent->OnEditReturn(parent->m_nItem,parent->m_nSubItem);
				parent->EndEdit(TRUE,parent->m_nSubItem);
				//AfxMessageBox("this->m_bInputValid  and after parent->OnEditReturn()"); 
			}
			else
			{
			    parent->EndEdit(FALSE,parent->m_nSubItem);
			}
		
	}
	CEdit::OnKillFocus(pNewWnd);
}

BOOL CMyChildEdit::PreTranslateMessage(MSG* pMsg) 
{
	
	//拦截ESC键解释为WM_KILLFOCUS消息
	if( pMsg->message==WM_KEYDOWN )
	{
		if(pMsg->wParam==27)	//ESC键
		{
			pMsg->message=QUERY_MESSAGE_EDIT_ESC;
		}
	}
	else if(pMsg->message==WM_CHAR)
	{
			CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
			parent->PreOnEditChar(parent->m_nItem,parent->m_nSubItem,pMsg->wParam);
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyCanEditListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->EndEdit(FALSE,m_nSubItem);

	this->EndSelect(FALSE,m_nSubItem);
	
	UpdateWindow();
	CMyListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyCanEditListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->EndEdit(FALSE,m_nSubItem);	

	m_edit.ShowWindow(SW_HIDE);

	this->EndSelect(FALSE,m_nSubItem);
	
	UpdateWindow();
	CMyListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

LRESULT CMyCanEditListCtrl::SetNextItemFocus(WPARAM wParam,LPARAM lParam)
{
	
	///////////////////
	TRACE("BOOL CMyCanEditListCtrl::SetNextItemFocus()\n");
	if(m_iEditedIndex==-2)return false;
	m_Next=true;
	int r;
	r=GetItemCount();
	m_iEditedIndex++;

	int nItem,nSubItem;
	nItem=this->m_nItem;
	nSubItem=this->m_nSubItem;


	if(m_iEditedIndex>this->m_iColumnEdited.GetCount()-1)
	{
		nItem++;
		if(nItem>(r-1))
		{
            //如果设置m_nItem=0的话,将回到第一可编辑的行
			CString strNew;
			//strNew.Format("%d",this->GetItemCount()+1);
			strNew="";
			InsertItem(nItem, strNew );//加入一新行
			this->m_bValueChanged=TRUE;
			if(this->m_pDocument)
			{
			    this->m_pDocument->SetModifiedFlag(TRUE);
			}
		}
		m_iEditedIndex=0;
		
	}

	nSubItem=m_iColumnEdited.GetAt(m_iColumnEdited.FindIndex(m_iEditedIndex));
	m_bIsEdit=TRUE;
	m_bIsComboBox=FALSE;

	int i;
	BOOL flag;
	flag=FALSE;
	// 判断得到的单元格是否允许被编辑，同时，记录被编辑的编号
		for(i=0;i<this->m_iColumnEdited.GetCount();i++)
		{
			if(nSubItem==m_iColumnEdited.GetAt(m_iColumnEdited.FindIndex(i)))
			{
				flag=TRUE;
				m_bIsEdit=TRUE;
				m_bIsComboBox=FALSE;
				this->m_iEditedIndex=i;
			}
		}

	
	for(i=0;i<this->m_iColumnComboBox.GetCount();i++)
	{
			if(nSubItem==m_iColumnComboBox.GetAt(m_iColumnComboBox.FindIndex(i)))
			{
				flag=TRUE;
				m_bIsEdit=FALSE;
				m_bIsComboBox=TRUE;
				//this->m_iEditedIndex=i;
				
			}
	}

	
	if(flag!=TRUE)
		return true;
	if(m_bIsEdit)
	{
		BeginEdit(nItem,nSubItem);
	}
	else if(m_bIsComboBox)
	{
		BeginSelect(nItem,nSubItem);
	}

	return true;
}

void CMyCanEditListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CMyListCtrl::OnKillFocus(pNewWnd);

}

void CMyCanEditListCtrl::OnNewEditChange(const int& item,const int& sub_item)
{

}

bool CMyCanEditListCtrl::SetSubItemCanEdited(const int& subitem)
{
	int n=m_iColumnEdited.GetCount();
	if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	bool flag=false;
	int column;
	for(int i=0;i<this->m_iColumnEdited.GetCount();i++)
	{
		column=this->m_iColumnEdited.GetAt(m_iColumnEdited.FindIndex(i));
		if(subitem<column)
		{
			this->m_iColumnEdited.InsertBefore(m_iColumnEdited.FindIndex(i),subitem);
			flag=true;
		}
		else if(subitem==column)//如果已经存在
		{
			//AfxMessageBox("subitem==column");
			return true;
		}

	}
	if(!flag)
	{
		m_iColumnEdited.AddTail(subitem);
	}
	return true;
}

int CMyCanEditListCtrl::GetSubItemNumber()
{
	CHeaderCtrl *ct=GetHeaderCtrl();
    return ct->GetItemCount();
	
}

int CMyCanEditListCtrl::GetCountCanEdited()
{
	return this->m_iColumnEdited.GetCount();
}

bool CMyCanEditListCtrl::SetSubItemUnEdited(const int& subitem)
{
	if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	bool flag=false;
	for(int i=0;i<this->m_iColumnEdited.GetCount();i++)
	{
		if(subitem==this->m_iColumnEdited.GetAt(m_iColumnEdited.FindIndex(i)))
		{
			this->m_iColumnEdited.RemoveAt(m_iColumnEdited.FindIndex(i));
			flag=true;
		}
	}
	return flag;
}
void CMyCanEditListCtrl::OnEditKillFocus(const int& item, const int& subitem)
{
}

void CMyCanEditListCtrl::OnEditSetFocus(const int& item, const int& subitem)
{
	if(m_bIsEdit)
	{
		m_edit.m_bInputValid=true;
	}
	else if(m_bIsComboBox)
	{

	}
}
void CMyCanEditListCtrl::OnComboBoxSetFocus(const int& item, const int& subitem)
{
	if(m_bIsComboBox)
	{

	}
}

BOOL CMyCanEditListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	HWND hwnd;
	if(pMsg->hwnd!=NULL)
	{
		hwnd=pMsg->hwnd;
	}

	if(hwnd==this->m_edit.GetSafeHwnd() && pMsg->message==WM_KEYDOWN)
	{
			if(pMsg->wParam==13)//回车VK_ENTER
			{
				if(this->m_bIsEdit)
				{
				    OnEditReturn(this->m_nItem,this->m_nSubItem);
					
				}
				pMsg->hwnd=GetSafeHwnd();
				pMsg->message=QUERY_SETNEXTITEMPHFOCUS;
			}
			else if(pMsg->wParam==VK_UP||pMsg->wParam==VK_DOWN||
				pMsg->wParam==VK_NEXT||pMsg->wParam==VK_PRIOR)
			{
				this->OnEditUDNPMessage(this->m_nItem,this->m_nSubItem,pMsg->wParam);
			}
	}
	else if(hwnd==this->GetSafeHwnd() && pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam== VK_DELETE)
		{
			this->DeleteSelectedByVK_DELETE();
		}
		else if(pMsg->wParam==13) 
		{
			this->m_iEditedIndex=-1;
			this->m_nItem=this->GetSelectionMark();

			if(m_nItem<0||m_nItem>=this->GetItemCount())m_nItem=0;
			{
				pMsg->hwnd=GetSafeHwnd();
			}
				pMsg->message=QUERY_SETNEXTITEMPHFOCUS;
		}
	}
	else  if(hwnd==this->m_ComboBox.GetSafeHwnd() && pMsg->message==WM_KEYDOWN)
	{
			if(pMsg->wParam==13)//回车VK_ENTER
			{
				if(this->m_bIsComboBox)
				{
					EndSelect(TRUE,this->m_nSubItem);
				}

				pMsg->hwnd=GetSafeHwnd();
				pMsg->message=QUERY_SETNEXTITEMPHFOCUS;
			}
			else if(pMsg->wParam==VK_UP||pMsg->wParam==VK_DOWN||
				pMsg->wParam==VK_NEXT||pMsg->wParam==VK_PRIOR)
			{
				this->OnEditUDNPMessage(this->m_nItem,this->m_nSubItem,pMsg->wParam);
			}
	}
	

	return 	CMyListCtrl::PreTranslateMessage(pMsg);
}

bool CMyCanEditListCtrl::OnEditReturn(const int& item, const int& subitem)
{
	if(!IsTheSubItemCanEdited(subitem)  )
	{
		return false;
	}

	this->EndEdit(TRUE,subitem);
	return true;
}

bool CMyCanEditListCtrl::IsTheSubItemCanEdited(const int& subitem)
{
	if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	if(m_iColumnEdited.Find(subitem)==NULL)
		return false;
	return true;

}

bool CMyCanEditListCtrl::SetTheEditFocus(const int& item, const int& subitem)
{
	
	return true;
}

bool CMyCanEditListCtrl::DeleteSelected()
{
	LVITEM* item=new LVITEM;
	int number=this->GetSelectedCount();
	for(int i=this->GetItemCount()-1;i>=0;i--)
	{
			this->m_nItem=i;
			item->iItem=i;
			item->mask=LVIF_STATE ;
			item->stateMask=LVIS_SELECTED ;
			GetItem(item);
		if(item->state==LVIS_SELECTED)
		{
			DeleteItem(i);
		}
	}
		if(GetItemCount()==0)
		{
			//InsertItem(0,"");
			EndEdit(FALSE,m_nSubItem);
			m_edit.ShowWindow(SW_HIDE);
			this->EndSelect(FALSE,m_nSubItem);
			
			 m_ComboBox.ShowWindow(SW_HIDE);
				
		}
		this->m_nItem=0;
		Invalidate();

		//////////////
		this->m_bValueChanged=TRUE;//////////////
		if(this->m_pDocument)
		{
			this->m_pDocument->SetModifiedFlag(TRUE);
		}
    
		
	return true;
}

void CMyCanEditListCtrl::SetValueUnChange(CString str,int nSubItem)
{
			TRACE("void CMyCanEditListCtrl::SetValueUnChange(CString sql)\n");
	
        m_bSetValue=true;
		if(m_bIsEdit)
		{
            this->m_edit.SetWindowText(str);
		}
		else if(m_bIsComboBox)
		{
			m_ComboBox.SelectString(0,str);
			
		}
        m_bSetValue=false;
	
}
LRESULT CMyCanEditListCtrl::OnParentMoved(WPARAM wParam,LPARAM lParam)
{
	//TRACE("void CListXSDJ::OnParentMoved()\n");

	if(m_edit.m_hWnd==NULL)return -1;
	m_edit.GetWindowRect(&this->m_rectWindow);
	
	if(m_ComboBox.m_hWnd==NULL)return -1;
	
	return 0;
}

void CMyCanEditListCtrl::OnESC(const int& item, const int& subitem)
{
	if(m_bIsEdit)
	{
	    m_edit.m_bInputValid=false;
	}
	else if(m_bIsComboBox)
	{

	}
}

bool CMyCanEditListCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	BOOL b=CMyListCtrl::Create(dwStyle,rect,pParentWnd,nID);
	// 创建编辑控件
	if( m_edit.Create(WS_CHILD|ES_AUTOHSCROLL , CRect(0,0,0,0), this, ID_VALUE)==FALSE )
		return FALSE;
    //创建列表控件
	if( m_ComboBox.Create(WS_CHILD|ES_AUTOHSCROLL|CBS_DROPDOWNLIST|WS_VSCROLL|WS_HSCROLL, CRect(0,0,100,100), this, ID_COMBOBOX)==FALSE )
		return FALSE;
	///////
	return b;
}
void CMyCanEditListCtrl::OnEditUDNPMessage(const int& item, const int& subitem,UINT key)
{

}
void CMyCanEditListCtrl::PreOnEditChar(const int& item, const int& subitem,UINT& key)
{

}

LRESULT CMyChildEdit::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message==QUERY_MESSAGE_EDIT_ESC)
	{
			CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
			parent->OnESC(parent->m_nItem,parent->m_nSubItem);
			this->ShowWindow(SW_HIDE);
	}
	return	CEdit::WindowProc(message,wParam,lParam);
}


void CMyCanEditListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//AfxMessageBox("CMyCanEditListCtrl::OnColumnclick");
	EndEdit(FALSE,m_nSubItem);
	this->EndSelect(FALSE,m_nSubItem);
	CMyListCtrl::OnColumnclick( pNMHDR,  pResult);
	
	/////////
	*pResult = 0;
}
/*
void CMyCanEditListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//AfxMessageBox("OnItemchanged");
	//EndEdit(TRUE);
	//this->m_edit.ShowWindow(SW_HIDE);

	*pResult = 0;
}
*/
void CMyCanEditListCtrl::DeleteSelectedByVK_DELETE()
{
	this->DeleteSelected();
	int count;
	count=this->GetItemCount();
	if(count<1)
		return;
//	int item_cur;
	/*
	POSITION pos;
	pos=this->GetFirstSelectedItemPosition();
	if(!pos)
	{
		AfxMessageBox("!pos");
		return;
	}
	item_cur=this->GetNextSelectedItem(pos);
	*/

	//item_cur=
	//SetItemState(-1, 0, LVNI_SELECTED);//取消所有的item选中状态,执行后,item_cur可能会改变
    //SetFocus();
    //SetItemState(item_cur,LVNI_SELECTED,LVNI_SELECTED);

}

BOOL CMyCanEditListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	this->EndEdit(FALSE,m_nSubItem);
	m_edit.ShowWindow(SW_HIDE);
	this->EndSelect(FALSE,m_nSubItem);
	
	UpdateWindow();

	return CMyListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}
///////

bool CMyCanEditListCtrl::IsTheSubItemCanListBox(const int &subitem)
{
    if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	if(m_iColumnComboBox.Find(subitem)==NULL)
		return false;
	return true;
}

bool CMyCanEditListCtrl::SetSubItemCanListBox(const int &subitem)
{
    int n=m_iColumnComboBox.GetCount();
	if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	bool flag=false;
	int column;
	for(int i=0;i<this->m_iColumnComboBox.GetCount();i++)
	{
		column=this->m_iColumnComboBox.GetAt(m_iColumnComboBox.FindIndex(i));
		if(subitem<column)
		{
			this->m_iColumnComboBox.InsertBefore(m_iColumnComboBox.FindIndex(i),subitem);
			flag=true;
		}
		else if(subitem==column)//如果已经存在
		{
			//AfxMessageBox("subitem==column");
			return true;
		}

	}
	if(!flag)
	{
		m_iColumnComboBox.AddTail(subitem);
	}
	return true;
}

bool CMyCanEditListCtrl::SetSubItemUnListBox(const int &subitem)
{
    if(subitem>=this->GetSubItemNumber()||subitem<0)return false;
	bool flag=false;
	for(int i=0;i<this->m_iColumnComboBox.GetCount();i++)
	{
		if(subitem==this->m_iColumnComboBox.GetAt(m_iColumnComboBox.FindIndex(i)))
		{
			this->m_iColumnComboBox.RemoveAt(m_iColumnComboBox.FindIndex(i));
			flag=true;
		}
	}
	return flag;
}


int CMyCanEditListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMyListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// 改变字体
	LOGFONT logfont;
	logfont.lfHeight = -16;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = 400;
	logfont.lfItalic = 0;
	logfont.lfUnderline = 0;
	logfont.lfStrikeOut = 0;
	logfont.lfCharSet = 134;
	logfont.lfOutPrecision = 0;
	logfont.lfClipPrecision = 0;
	logfont.lfQuality = 0;
	logfont.lfPitchAndFamily = 2;
	strcpy( logfont.lfFaceName, "宋体" );
	m_Listfont.DeleteObject();
	if( m_Listfont.CreateFontIndirect(&logfont) )
		SetFont( &m_Listfont );
	
	return 0;
}

BOOL CMyChildComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//拦截ESC键解释为WM_KILLFOCUS消息
	if( pMsg->message==WM_KEYDOWN )
	{
		if(pMsg->wParam==27)	//ESC键
		{
			pMsg->message=QUERY_MESSAGE_EDIT_ESC;
		}
	}
	else if(pMsg->message==WM_CHAR)
	{
			CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
			parent->PreOnEditChar(parent->m_nItem,parent->m_nSubItem,pMsg->wParam);
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void CMyChildComboBox::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox("CMyChildComboBox::OnKillfocus()");
	// 得到父窗口，并通知父窗口结束编辑过程
	CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
	
	parent->OnEditKillFocus(parent->m_nItem,parent->m_nSubItem);
			
			if(this->m_bSelectValid)//改变了选择的项目
			{
				
				parent->EndSelect(TRUE,parent->m_nSubItem);
				
			}
			else
			{
			    parent->EndSelect(FALSE,parent->m_nSubItem);
			}
		
	
	//////////////
}

int CMyChildComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	// 改变字体
	LOGFONT logfont;
	logfont.lfHeight = -12;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = 400;
	logfont.lfItalic = 0;
	logfont.lfUnderline = 0;
	logfont.lfStrikeOut = 0;
	logfont.lfCharSet = 134;
	logfont.lfOutPrecision = 0;
	logfont.lfClipPrecision = 0;
	logfont.lfQuality = 0;
	logfont.lfPitchAndFamily = 2;
	strcpy( logfont.lfFaceName, "宋体" );
	m_ComboBoxfont.DeleteObject();
	if( m_ComboBoxfont.CreateFontIndirect(&logfont) )
		SetFont( &m_ComboBoxfont );
	
	return 0;
}

LRESULT CMyChildComboBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message==QUERY_MESSAGE_EDIT_ESC)
	{
			CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();
			parent->OnESC(parent->m_nItem,parent->m_nSubItem);
			this->ShowWindow(SW_HIDE);
	}

	return CComboBox::WindowProc(message, wParam, lParam);
}

void CMyChildComboBox::OnSetfocus() 
{
	// TODO: Add your control notification handler code here
	
	CMyCanEditListCtrl *parent = (CMyCanEditListCtrl *)GetParent();

//	parent->m_bSelectValid=true;
//	parent->OnEditSetFocus(parent->m_nItem,parent->m_nSubItem);
}

void CMyChildComboBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here
	m_bSelectValid=TRUE;
	
}

void CMyCanEditListCtrl::InitItem()
{
	///在这里添加各ComboBox列表中的值
	
    
}

void CMyCanEditListCtrl::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	EndEdit(FALSE,m_nSubItem);
	m_edit.ShowWindow(SW_HIDE);
	this->EndSelect(FALSE,m_nSubItem);
	
			//////////////
	*pResult = 0;
}

void CMyCanEditListCtrl::EndSelect(BOOL bValidate, int nSubItem)
{
	//CString str;
	//str.Format("EndSelect:  m_nItem=%d,nSubItem=%d",m_nItem,nSubItem);
	//AfxMessageBox(str);
	
	/////////////
	CString txtSelect;
		int k;
	    k=m_ComboBox.GetCurSel();
		if(k!=CB_ERR)
		{
		    m_ComboBox.GetLBText(k,txtSelect);
		}
		//CString str;
		//str.Format("EndSelect:  m_nItem=%d,nSubItem=%d,k=%d,txtSelect=%s,GetItemText=%s",m_nItem,nSubItem,k,txtSelect,GetItemText(m_nItem, nSubItem));
		//AfxMessageBox(str);
	    if(bValidate==TRUE)
		{
		    if(txtSelect!=GetItemText(m_nItem, nSubItem))
			{
		        m_bValueChanged=TRUE;////置修改标志为TRUE
				if(this->m_pDocument)
				{
			         this->m_pDocument->SetModifiedFlag(TRUE);
				}
			}
	        SetItemText(m_nItem, nSubItem, txtSelect);
		}
		
		m_ComboBox.m_bSelectValid=FALSE;
	    m_ComboBox.ShowWindow(SW_HIDE);

		//AfxMessageBox("EndSelect OK!");
}

BOOL CMyCanEditListCtrl::BeginSelect(int nItem,int nSubItem)
{
	//CString str;
	//str.Format("BeginSelect: nItem=%d,nSubItem=%d",nItem,nSubItem);
	//AfxMessageBox(str);
	
	// 得到被编辑表项的区域
	CRect rect;
	if( GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect)==FALSE )
	{
		return FALSE;
	}
	//rect.right-=1;
	rect.left+=1;
	rect.top-=1;
	rect.bottom-=3;

	CString txtItem;
	
		m_edit.ShowWindow(SW_HIDE);

		m_ComboBox.ShowWindow(SW_HIDE);
		
		m_ComboBox.SetCurSel(-1);
	    m_ComboBox.MoveWindow(&rect);

	    txtItem=this->GetItemText(nItem,nSubItem);
		//AfxMessageBox(txtItem);
	    // 取出的文字填写到下拉列表控件
		this->OnComboBoxSetFocus(nItem,nSubItem);
	    SetValueUnChange(txtItem,nSubItem);
	    
		//AfxMessageBox("Before m_pComboBox[nSubItem]->SetFocus()");
	    m_ComboBox.SetFocus();
		//AfxMessageBox("After m_pComboBox[nSubItem]->SetFocus()");

	    m_ComboBox.ShowWindow(SW_SHOW);

	this->m_nItem=nItem;
	this->m_nSubItem=nSubItem;

	return TRUE;

}

//判断是否为数字,包括整数,实数
BOOL CMyCanEditListCtrl::IsNumber(CString szNum)
{
    CString szTemp;
	CString str;
	str=szNum;
	str.TrimRight("0");

    szTemp.Format("%d",atoi(szNum));
    if(szTemp.CompareNoCase(szNum) == 0)
        return TRUE;

    szTemp.Format("%f",atof(szNum));
    szTemp.TrimRight("0");
    szTemp.TrimRight(".");
    if(szTemp.CompareNoCase(str) == 0)
        return TRUE;

    return FALSE;

}


//判断是否为整数
BOOL CMyCanEditListCtrl::IsInt(CString szInt)
{
    CString szTemp;
    szTemp.Format("%d",atoi(szInt));

    if(szTemp.CompareNoCase(szInt) == 0)
        return TRUE;

    return FALSE;
}

BOOL CMyCanEditListCtrl::CreateChild()
{
	
	return TRUE;

}

void CMyCanEditListCtrl::InitColumn()
{

}

BOOL CMyCanEditListCtrl::InitListCtrl()
{
    this->InitColumn();
	if(this->CreateChild()==FALSE)
	{
		return FALSE;
	}
	this->InitItem();

	return TRUE;
}

void CMyCanEditListCtrl::SetModifiedFlag(BOOL bModified)
{
    if(this->m_pDocument!=NULL)
	{
		this->m_pDocument->SetModifiedFlag(bModified);
	}
}

BOOL CMyCanEditListCtrl::IsModified()
{
    if(this->m_pDocument!=NULL)
	{
		return this->m_pDocument->IsModified();
	}
	else
	{
		return FALSE;
	}
}

void CMyCanEditListCtrl::SetDocument(CDocument *pDocument)
{
    this->m_pDocument=pDocument;
}

CDocument* CMyCanEditListCtrl::GetDocument()
{
    return this->m_pDocument;
}

void CMyCanEditListCtrl::SetListCtrlFont(LOGFONT logfont)
{
    // 改变字体
	
	m_Listfont.DeleteObject();
	if( m_Listfont.CreateFontIndirect(&logfont) )
	{
		SetFont( &m_Listfont );
		this->Invalidate(TRUE);
	}
}

void CMyCanEditListCtrl::SetChildEditFont(LOGFONT logfont)
{
    this->m_edit.m_font.DeleteObject();
	if( this->m_edit.m_font.CreateFontIndirect(&logfont) )
	{
		this->m_edit.SetFont( &(this->m_edit.m_font ));
		this->m_edit.Invalidate(TRUE);
	}
}

void CMyCanEditListCtrl::SetChildComboBoxFont(LOGFONT logfont)
{
	
			m_ComboBox.m_ComboBoxfont.DeleteObject();
	        if( m_ComboBox.m_ComboBoxfont.CreateFontIndirect(&logfont) )
			{
	        	m_ComboBox.SetFont( &(m_ComboBox.m_ComboBoxfont ));
		        //m_ComboBox.SetItemHeight(0,12)
				m_ComboBox.Invalidate(TRUE);
			}
	

}

CFont* CMyCanEditListCtrl::GetListCtrlFont()
{
	return this->GetFont();

}

CFont* CMyCanEditListCtrl::GetChildEditFont()
{
	return this->m_edit.GetFont();

}

CFont* CMyCanEditListCtrl::GetChildComboBoxFont()
{
    
	return m_ComboBox.GetFont();
	

	return NULL;
}

void CMyCanEditListCtrl::SetListCtrlFontSize(int fontsize)
{
	CFont *pFont;
	pFont=this->GetFont();
    LOGFONT LogFont;
	pFont->GetLogFont(&LogFont);
	if(fontsize>0)
	{
	    LogFont.lfHeight = -fontsize;
	}
	else
	{
		LogFont.lfHeight = fontsize;
	}
	this->SetListCtrlFont(LogFont);
}

void CMyCanEditListCtrl::SetChildEditFontSize(int fontsize)
{
    CFont *pFont;
	pFont=this->m_edit.GetFont();
    LOGFONT LogFont;
	pFont->GetLogFont(&LogFont);
	if(fontsize>0)
	{
	    LogFont.lfHeight = -fontsize;
	}
	else
	{
		LogFont.lfHeight = fontsize;
	}
	this->SetChildEditFont(LogFont);
}

void CMyCanEditListCtrl::SetChildComboBoxFontSize(int fontsize)
{
	
			CFont *pFont;
	        pFont=m_ComboBox.GetFont();
            LOGFONT LogFont;
	        pFont->GetLogFont(&LogFont);
	        if(fontsize>0)
			{
	           LogFont.lfHeight = -fontsize;
			}
	        else
			{
		       LogFont.lfHeight = fontsize;
			}
	        this->SetChildComboBoxFont(LogFont);
	
	return ;

    
}
