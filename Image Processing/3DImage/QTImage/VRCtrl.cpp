// DlgVolumeSetting.cpp : implementation file
//

#include "stdafx.h"
#include "VRCtrl.h"
#include "Commands.h"
#include "GlobalHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVRCtrl dialog


CDlgVRCtrl::CDlgVRCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVRCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVRCtrl)
	m_iMode = -1;
	m_iEngine = 0;
	m_bUseGrad = FALSE;
	m_bUseShade = FALSE;
	//}}AFX_DATA_INIT

	
	m_bRealUpdate=TRUE; 
	m_pVRView=NULL;
}


void CDlgVRCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVRCtrl)
	DDX_Control(pDX, IDC_SLIDER_LOD, m_lodSlider);
	DDX_Control(pDX, IDC_STATIC_GRAD_OPACITY, m_ctrlGrad);
	DDX_Control(pDX, IDC_STATIC_OPACITY, m_ctrlOpacity);
	DDX_Radio(pDX, IDC_RADIO_MIP, m_iMode);
	DDX_Radio(pDX, IDC_RADIO_HARDWARE, m_iEngine);
	DDX_Check(pDX, IDC_CHECK_GRADON, m_bUseGrad);
	DDX_Check(pDX, IDC_CHECK_SHADE, m_bUseShade);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVRCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgVRCtrl)
	ON_BN_CLICKED(IDC_BTN_OPACITY, OnBtnOpacity)
	ON_BN_CLICKED(IDC_RADIO_MIP, OnRadioMip)
	ON_BN_CLICKED(IDC_RADIO_COMPOSITE, OnRadioComposite)
	ON_BN_CLICKED(IDC_RADIO_SOFTWARE, OnRadioSoftware)
	ON_BN_CLICKED(IDC_RADIO_HARDWARE, OnRadioHardware)
	ON_BN_CLICKED(IDC_BUTTON_GRAD, OnButtonGrad)
	ON_BN_CLICKED(IDC_CHECK_GRADON, OnCheckGradon)
	ON_BN_CLICKED(IDC_CHECK_SHADE, OnCheckShade)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_MESSAGE(WM_CALL_COMMAND,OnCallCommand)
	ON_CBN_SETFOCUS(IDC_COMBO_GRAD, OnSetfocusComboGrad)
	ON_CBN_SETFOCUS(IDC_COMBO_OPACITY, OnSetfocusComboOpacity)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_LOD, OnReleasedcaptureSliderLod)
	ON_BN_CLICKED(IDC_RADIO_FIXPOINT, OnRadioFixpoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVRCtrl message handlers

BOOL CDlgVRCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlGrad.m_iMode=2;

	m_lodSlider.SetRange(0,100);
	m_lodSlider.SetPageSize(1);
	m_lodSlider.SetPos(50);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDlgVRCtrl::OnCallCommand(WPARAM wParam, LPARAM lParam)
{
	CString sPara="";
	int nCmdID = (int)wParam;
	if(lParam)
	{
		sPara=*((CString *)lParam);
	}


	switch(nCmdID)
	{
	case CMD_ADDPIXEL:
		{
			
		}
		
	}
	return 0;
}

void CDlgVRCtrl::SetPixelRange()
{
		m_ctrlOpacity.SetPixelRange(0,VRCTRL_PIXELMAXRANGE);
	m_ctrlGrad.SetPixelRange(0,VRCTRL_GRADIENTRANGE);

	IA_PIXEL_ITEM item;
	
	POSITION pos;
	m_ctrlOpacity.m_itemList.RemoveAll();
	pos=m_pVolConfig->pixelOpacityColorList.GetHeadPosition();
	while(pos)
	{
		item=m_pVolConfig->pixelOpacityColorList.GetNext(pos);
		m_ctrlOpacity.m_itemList.AddTail(item);
	}

	m_ctrlGrad.m_itemList.RemoveAll();
	pos=m_pVolConfig->gradOpacityList.GetHeadPosition();
	while(pos)
	{
		item=m_pVolConfig->gradOpacityList.GetNext(pos);
		m_ctrlGrad.m_itemList.AddTail(item);
	}
	
}

BOOL CDlgVRCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam==IDC_SLIDER_LOD)
	{
		return CDialog::OnNotify(wParam, lParam, pResult);
		
	}

	int iResult=*((int *)wParam);
	IA_PIXEL_ITEM item;

	if(iResult==10 || iResult==20 || iResult==30)
	{
		item = *((IA_PIXEL_ITEM *)lParam);
	}
	CString sTmp;

	if(iResult==10) //opacity map
	{
		sTmp.Format("%i",item.pixel);
		GetDlgItem(IDC_EDIT_OPACITY_PIXEL)->SetWindowText(sTmp);
		sTmp.Format("%.2f",item.opacity);
		GetDlgItem(IDC_EDIT_OPACITY)->SetWindowText(sTmp);
				
	}

	if(iResult==11) //Update opacity map
	{
		if(m_pVolConfig->method==VOLRENDER_HARDWARE 
			&& m_pVolConfig->renderMode==VOLRENDER_VOLUME)
		{
			OnBtnOpacity();
		}
	}

	

	if(iResult==30) //grad map
	{
		sTmp.Format("%i",item.pixel);
		GetDlgItem(IDC_EDIT_GRAD_OPACITY_PIXEL)->SetWindowText(sTmp);
		sTmp.Format("%.2f",item.opacity);
		GetDlgItem(IDC_EDIT_GRAD_OPACITY)->SetWindowText(sTmp);
		
		
	}

	if(iResult==31) //Update color map
	{
		if(m_pVolConfig->method==VOLRENDER_HARDWARE 
			&& m_pVolConfig->renderMode==VOLRENDER_VOLUME)
		{
			OnButtonGrad();
		}
	}

	
	return TRUE; //CDialog::OnNotify(wParam, lParam, pResult);
}


void CDlgVRCtrl::OnBtnOpacity() 
{
	// TODO: Add your control notification handler code here
	IA_PIXEL_ITEM item;
	m_pVolConfig->pixelOpacityColorList.RemoveAll();
	POSITION pos=m_ctrlOpacity.m_itemList.GetHeadPosition();
	while(pos)
	{
		item=m_ctrlOpacity.m_itemList.GetNext(pos);
		m_pVolConfig->pixelOpacityColorList.AddTail(item);
	}
	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}

void CDlgVRCtrl::SendCommand(int nCmdID,CString sPara)
{
	m_pVRView->SendMessage(WM_CALL_COMMAND,WPARAM(nCmdID),LPARAM(&sPara));
}

void CDlgVRCtrl::OnRadioMip() 
{
	// TODO: Add your control notification handler code here
	m_pVolConfig->renderMode=VOLRENDER_MIP;
	
	//GetDlgItem(IDC_RADIO_HARDWARE)->EnableWindow(FALSE);
	//GetDlgItem(IDC_RADIO_SOFTWARE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_GRADON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SHADE)->EnableWindow(FALSE);

	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}

void CDlgVRCtrl::OnRadioComposite() 
{
	// TODO: Add your control notification handler code here
	m_pVolConfig->renderMode=VOLRENDER_VOLUME;

	
	//GetDlgItem(IDC_RADIO_HARDWARE)->EnableWindow(TRUE);
	//GetDlgItem(IDC_RADIO_SOFTWARE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_GRADON)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_SHADE)->EnableWindow(TRUE);

	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}



void CDlgVRCtrl::OnRadioSoftware() 
{
	// TODO: Add your control notification handler code here
		
	m_pVolConfig->method=VOLRENDER_SOFTWARE;
	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}

void CDlgVRCtrl::OnRadioHardware() 
{
	// TODO: Add your control notification handler code here
			
	m_pVolConfig->method=VOLRENDER_HARDWARE;
	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}


void CDlgVRCtrl::OnButtonGrad() 
{
	// TODO: Add your control notification handler code here
	IA_PIXEL_ITEM item;
	m_pVolConfig->gradOpacityList.RemoveAll();
	POSITION pos=m_ctrlGrad.m_itemList.GetHeadPosition();
	while(pos)
	{
		item=m_ctrlGrad.m_itemList.GetNext(pos);
		m_pVolConfig->gradOpacityList.AddTail(item);
	}
	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}

void CDlgVRCtrl::OnCheckGradon() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	m_pVolConfig->bGradient=m_bUseGrad;
	

	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
	
}

void CDlgVRCtrl::OnCheckShade() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_pVolConfig->bShade=m_bUseShade;

	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}

void CDlgVRCtrl::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Par Files (*.par)|*.par|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(FALSE,
		".par",NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
		return;

	char sTmp[256];
	IA_PIXEL_ITEM item;
	POSITION pos;
	FILE *file;

	if((file = fopen (sFolderName, "w+b")) == NULL)
	{
		MessageBox("Failed to save parameter file.");
		return ;
	}
	
	fseek(file,0,SEEK_SET);
	sprintf(sTmp,"QTImage volume para");
	fwrite((char*)sTmp,sizeof(char),256,file);

	
	sprintf(sTmp,"%i",m_ctrlOpacity.m_itemList.GetCount());
	fwrite((char*)sTmp,sizeof(char),256,file);

	pos=m_ctrlOpacity.m_itemList.GetHeadPosition();
	while(pos)
	{
		item=m_ctrlOpacity.m_itemList.GetNext(pos);
		fwrite((char*)&item,sizeof(IA_PIXEL_ITEM),1,file);
	}


	sprintf(sTmp,"%i",m_ctrlGrad.m_itemList.GetCount());
	fwrite((char*)sTmp,sizeof(char),256,file);

	pos=m_ctrlGrad.m_itemList.GetHeadPosition();
	while(pos)
	{
		item=m_ctrlGrad.m_itemList.GetNext(pos);
		fwrite((char*)&item,sizeof(IA_PIXEL_ITEM),1,file);
	}

	fclose(file);

	
}

void CDlgVRCtrl::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Par Files (*.par)|*.par|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
		return;

	char sTmp[256];
	IA_PIXEL_ITEM item;
	FILE *file;
	int iReadSize;
	int iCount;

	if((file = fopen (sFolderName, "rb")) == NULL)
	{
		MessageBox("Failed to open parameter file.");
		return ;
	}
	
	fseek(file,0,SEEK_SET);
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 && sTmp!="QTImage volume para")
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}
	

	//read opacity data
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	iCount=atoi(sTmp);
	m_pVolConfig->pixelOpacityColorList.RemoveAll();
	m_ctrlOpacity.m_itemList.RemoveAll();
	for(int i=0;i<iCount;i++)
	{
		iReadSize=fread((char*)&item,sizeof(char),sizeof(IA_PIXEL_ITEM),file);
		if(iReadSize!=sizeof(IA_PIXEL_ITEM) )
		{
			fclose(file);
			MessageBox("Failed to open parameter file.");
			return;
		}

		m_pVolConfig->pixelOpacityColorList.AddTail(item);
		m_ctrlOpacity.m_itemList.AddTail(item);
	}

	//read gracity data
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	iCount=atoi(sTmp);
	m_pVolConfig->gradOpacityList.RemoveAll();
	m_ctrlGrad.m_itemList.RemoveAll();
	for(i=0;i<iCount;i++)
	{
		iReadSize=fread((char*)&item,sizeof(char),sizeof(IA_PIXEL_ITEM),file);
		if(iReadSize!=sizeof(IA_PIXEL_ITEM) )
		{
			fclose(file);
			MessageBox("Failed to open parameter file.");
			return;
		}
		if(item.pixel>VRCTRL_GRADIENTRANGE)
		{
			item.pixel=VRCTRL_GRADIENTRANGE;
		}
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);
	}

	fclose(file);

	if(iCount==0)
	{
		item.pixel=0;
		item.opacity=0;
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);

		item.pixel=VRCTRL_GRADIENTRANGE;
		item.opacity=1;
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);
	}

	m_ctrlOpacity.DrawLine();
	m_ctrlGrad.DrawLine();

	
}

/*void CDlgVRCtrl::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Par Files (*.par)|*.par|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
		return;

	char sTmp[256];
	IA_PIXEL_ITEM item;
	FILE *file;
	int iReadSize;
	int iCount;

	if((file = fopen (sFolderName, "rb")) == NULL)
	{
		MessageBox("Failed to open parameter file.");
		return ;
	}
	
	fseek(file,0,SEEK_SET);
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 && sTmp!="QTImage volume para")
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	//window width
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}
	m_pVolConfig->WW=atoi(sTmp);

	//window level
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}
	m_pVolConfig->WL=atoi(sTmp);

	//read opacity data
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	iCount=atoi(sTmp);
	m_pVolConfig->pixelOpacityColorList.RemoveAll();
	m_ctrlOpacity.m_itemList.RemoveAll();
	for(int i=0;i<iCount;i++)
	{
		iReadSize=fread((char*)&item,sizeof(char),sizeof(IA_PIXEL_ITEM),file);
		if(iReadSize!=sizeof(IA_PIXEL_ITEM) )
		{
			fclose(file);
			MessageBox("Failed to open parameter file.");
			return;
		}

		m_pVolConfig->pixelOpacityColorList.AddTail(item);
		m_ctrlOpacity.m_itemList.AddTail(item);
	}

	//read color data
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	iCount=atoi(sTmp);
	//m_pVolConfig->pixelColorList.RemoveAll();
	for(i=0;i<iCount;i++)
	{
		iReadSize=fread((char*)&item,sizeof(char),sizeof(IA_PIXEL_ITEM),file);
		if(iReadSize!=sizeof(IA_PIXEL_ITEM) )
		{
			fclose(file);
			MessageBox("Failed to open parameter file.");
			return;
		}
		//m_pVolConfig->pixelColorList.AddTail(item);
	}

	//read gracity data
	iReadSize=fread((char*)sTmp,sizeof(char),256,file);
	if(iReadSize!=256 )
	{
		fclose(file);
		MessageBox("Failed to open parameter file.");
		return;
	}

	iCount=atoi(sTmp);
	m_pVolConfig->gradOpacityList.RemoveAll();
	m_ctrlGrad.m_itemList.RemoveAll();
	for(i=0;i<iCount;i++)
	{
		iReadSize=fread((char*)&item,sizeof(char),sizeof(IA_PIXEL_ITEM),file);
		if(iReadSize!=sizeof(IA_PIXEL_ITEM) )
		{
			fclose(file);
			MessageBox("Failed to open parameter file.");
			return;
		}
		if(item.pixel>VRCTRL_GRADIENTRANGE)
		{
			item.pixel=VRCTRL_GRADIENTRANGE;
		}
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);
	}

	if(iCount==0)
	{
		item.pixel=0;
		item.opacity=0;
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);

		item.pixel=VRCTRL_GRADIENTRANGE;
		item.opacity=1;
		m_ctrlGrad.m_itemList.AddTail(item);
		m_pVolConfig->gradOpacityList.AddTail(item);
	}
		
	
	m_ctrlOpacity.DrawLine();
	m_ctrlGrad.DrawLine();

	fclose(file);
}*/



void CDlgVRCtrl::Update()
{
	m_pVolConfig=&m_pVRView->m_volConfig;
	

	SetPixelRange();
	m_ctrlOpacity.m_bRedrawHistogram=FALSE;
	m_ctrlOpacity.DrawLine();
	m_ctrlGrad.m_bRedrawHistogram=FALSE;
	m_ctrlGrad.DrawLine();

	int pos=100 * (m_pVolConfig->LOD-m_pVolConfig->lodRange[0])/(m_pVolConfig->lodRange[1]-m_pVolConfig->lodRange[0]);
	m_lodSlider.SetPos(pos);

	
	if(m_pVolConfig->renderMode==VOLRENDER_MIP)
	{
		m_iMode=0;
		

		//GetDlgItem(IDC_RADIO_HARDWARE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_RADIO_SOFTWARE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_GRADON)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SHADE)->EnableWindow(FALSE);
	}else
	{
		m_iMode=1;
	

		//GetDlgItem(IDC_RADIO_HARDWARE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_RADIO_SOFTWARE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_GRADON)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SHADE)->EnableWindow(TRUE);
	}
	
	

	if(m_pVolConfig->bShade)
	{
		m_bUseShade=TRUE;
	}else
	{
		m_bUseShade=FALSE;
	}

	if(m_pVolConfig->bGradient)
	{
		m_bUseGrad=TRUE;
	}else
	{
		m_bUseGrad=FALSE;
	}

	if(m_pVolConfig->method==VOLRENDER_HARDWARE)
	{
		m_iEngine=0;
	}else if(m_pVolConfig->method==VOLRENDER_FIXPOINT)
	{
		m_iEngine=1;
	}else
	{
		m_iEngine=2;
	}

	
	UpdateData(FALSE);
}


void CDlgVRCtrl::OnSetfocusComboGrad() 
{
	// TODO: Add your control notification handler code here
		
	GetDlgItem(IDC_BTN_OPACITY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_OPACITY_PIXEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_OPACITY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_OPACITY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_GRAD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY_PIXEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_GRAD_OPACITY)->ShowWindow(SW_SHOW);

	
}

void CDlgVRCtrl::OnSetfocusComboOpacity() 
{
	// TODO: Add your control notification handler code here
		
	GetDlgItem(IDC_BTN_OPACITY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_OPACITY_PIXEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_OPACITY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_OPACITY)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_GRAD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY_PIXEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GRAD_OPACITY)->ShowWindow(SW_HIDE);

	
}

void CDlgVRCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_ctrlGrad.GetSafeHwnd())
		return;

	int iLeft=5,iTop=50;
	
	GetDlgItem(IDC_TEXT_PIXEL)->MoveWindow(cx-iLeft-180,iTop,30,17);
	GetDlgItem(IDC_TEXT_OPACITY)->MoveWindow(cx-iLeft-90,iTop,40,17);

	
	GetDlgItem(IDC_BUTTON_GRAD)->MoveWindow(cx-iLeft-300,iTop,100,17);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY_PIXEL)->MoveWindow(cx-iLeft-150,iTop,50,17);
	GetDlgItem(IDC_EDIT_GRAD_OPACITY)->MoveWindow(cx-iLeft-50,iTop,50,17);
	GetDlgItem(IDC_STATIC_GRAD_OPACITY)->MoveWindow(iLeft,iTop+20,cx-iLeft*2,cy-iTop-20-4);

	
	GetDlgItem(IDC_BTN_OPACITY)->MoveWindow(cx-iLeft-300,iTop,100,17);
	GetDlgItem(IDC_EDIT_OPACITY_PIXEL)->MoveWindow(cx-iLeft-150,iTop,50,17);
	GetDlgItem(IDC_EDIT_OPACITY)->MoveWindow(cx-iLeft-50,iTop,50,17);
	GetDlgItem(IDC_STATIC_OPACITY)->MoveWindow(iLeft,iTop+20,cx-iLeft*2,cy-iTop-20-4);

	OnSetfocusComboOpacity();
}

void CDlgVRCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(&rc);

	CPen penBlack(PS_SOLID, 1, RGB(0,0,0));
	CPen* pOldPen = dc.SelectObject(&penBlack);
		
	dc.MoveTo(rc.left+2,rc.bottom-2);
	dc.LineTo(rc.right-2,rc.bottom-2);
	dc.SelectObject(pOldPen);
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgVRCtrl::OnReleasedcaptureSliderLod(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int pos=m_lodSlider.GetPos();
	float lod=(pos/100.0) * (m_pVolConfig->lodRange[1]-m_pVolConfig->lodRange[0]) + m_pVolConfig->lodRange[0];
	m_pVolConfig->LOD=lod;

	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);

	*pResult = 0;
}

void CDlgVRCtrl::OnRadioFixpoint() 
{
	// TODO: Add your control notification handler code here
	m_pVolConfig->method=VOLRENDER_FIXPOINT;
	CString sTmp;
	SendCommand(CMD_REFRESH_VOLUMERENDING,sTmp);
}


