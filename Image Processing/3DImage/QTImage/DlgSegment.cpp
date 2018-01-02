// DlgSegment.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "DlgSegment.h"
#include "QTImageDlg.h"
#include "DlgScaleCtrl.h"
#include "itkPlugs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSegment dialog

CDlgSegment *gSegmentDlg;
extern CString g_sProgramPath;
extern CQTImageDlg* gpMainDlg;

void VolUpdateProgress(void *info, float progress, const char *msg)
{
	CString sTmp;
	if(progress>0.0 && progress<=0.99)
	{
		sTmp.Format("%s %.0f",msg,progress*100);
	}else
	{
		sTmp.Format("%s",msg);
	}
	gSegmentDlg->UpdateLog(sTmp);

	if(gSegmentDlg->m_bEnableDrawROIInProcess)
	{
		gSegmentDlg->m_pDlgMPR->DrawROI();
	}
}

void VolSetProperty(void *info, int property, const char *value)
{
	CString sTmp;
	sTmp.Format("%s",value);
	
	switch(property)
	{
	case VVP_NAME:
		sprintf(gSegmentDlg->m_vvProp.sVVP_NAME,"%s",value);
		break;
	case VVP_TERSE_DOCUMENTATION:
		sprintf(gSegmentDlg->m_vvProp.sVVP_TERSE_DOCUMENTATION,"%s",value);
		break;
	case VVP_FULL_DOCUMENTATION:
		sprintf(gSegmentDlg->m_vvProp.sVVP_FULL_DOCUMENTATION,"%s",value);
		//gSegmentDlg->m_btnApply.SetTooltipText(sTmp,TRUE);
		break;
	
	case VVP_NUMBER_OF_GUI_ITEMS:
		sprintf(gSegmentDlg->m_vvProp.sVVP_NUMBER_OF_GUI_ITEMS,"%s",value);
		break;
	
	case VVP_ABORT_PROCESSING:
		sprintf(gSegmentDlg->m_vvProp.sVVP_ABORT_PROCESSING,"%s",value);
		break;
	case VVP_REPORT_TEXT:
		sprintf(gSegmentDlg->m_vvProp.sVVP_REPORT_TEXT,"%s",value);
		break;
	case VVP_ERROR:
		AfxMessageBox(sTmp);
		break;
	default:
		AfxMessageBox("SetProperty error");
	}
}

const char* VolGetProperty(void *info, int property)
{
	char *pChar;
	pChar=NULL;
	switch(property)
	{
	case VVP_NAME:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_NAME;
		break;
	case VVP_TERSE_DOCUMENTATION:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_TERSE_DOCUMENTATION;
		break;
	case VVP_FULL_DOCUMENTATION:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_FULL_DOCUMENTATION;
		break;
	
	case VVP_NUMBER_OF_GUI_ITEMS:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_NUMBER_OF_GUI_ITEMS;
		break;
	case VVP_ABORT_PROCESSING:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_ABORT_PROCESSING;
		break;
	case VVP_REPORT_TEXT:
		pChar=(char *)gSegmentDlg->m_vvProp.sVVP_REPORT_TEXT;
		break;
	}
	if(pChar==NULL)
		AfxMessageBox("GetProperty error");
	return pChar;
}

void VolSetGUIProperty(void *info, int num, int property, const char *value)
{

	if(num>gSegmentDlg->m_iMaxCtrlCount-1)
	{
		AfxMessageBox("Ctrl count is not enough.");
		return;
	}
	
	gSegmentDlg->m_iCtrlCount=num+1;
	POSITION pos;
	pos=gSegmentDlg->m_wndList.FindIndex(num);
	CDlgScaleCtrl *pCtrl=(CDlgScaleCtrl *)gSegmentDlg->m_wndList.GetNext(pos);
	pCtrl->SetGUIProperty(property,value);

	
}

const char* VolGetGUIProperty(void *info, int num, int property)
{
	char *pChar;
	pChar=NULL;
	if(num>gSegmentDlg->m_iMaxCtrlCount-1)
	{
		AfxMessageBox("Ctrl count is not enough.");
		return pChar;
	}
	POSITION pos;
	pos=gSegmentDlg->m_wndList.FindIndex(num);
	CDlgScaleCtrl *pCtrl=(CDlgScaleCtrl *)gSegmentDlg->m_wndList.GetNext(pos);
	pChar=pCtrl->GetGUIProperty(property);
	
	return pChar;
}

CDlgSegment::CDlgSegment(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSegment::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSegment)
	//}}AFX_DATA_INIT

	m_bInitialized=FALSE;
	m_pROIManager=NULL;

	m_iMaxCtrlCount=10;

	m_vvData.inData=NULL;
	m_vvData.outData=NULL;
	m_vvData.StartSlice=0;
	m_vvData.NumberOfSlicesToProcess=0;
	
	m_vvInfo.SetProperty=VolSetProperty;
	m_vvInfo.GetProperty=VolGetProperty;
	m_vvInfo.SetGUIProperty=VolSetGUIProperty;
	m_vvInfo.GetGUIProperty=VolGetGUIProperty;
	m_vvInfo.UpdateProgress=VolUpdateProgress;
	m_vvInfo.NumberOfMarkers=0;
	m_vvInfo.Markers=NULL;

	m_pSegmentedImage=NULL;
	m_pSegmentingImage=NULL;

	m_hItkPlug=NULL;

	m_iLastPos=0;

	m_bEnableDrawROIInProcess=TRUE;

	initLib();
}

CDlgSegment::~CDlgSegment()
{
	ClearGUICtrl();
	if(m_vvInfo.Markers!=NULL){delete []m_vvInfo.Markers; m_vvInfo.Markers=NULL;}
	Clear();
	
	if ( m_hItkPlug )
	{
		FreeLibrary(m_hItkPlug);	
	}
}

void CDlgSegment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSegment)
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_STATIC_BTN_BOX, m_btnBox);
	DDX_Control(pDX, IDC_STATIC_LOG, m_log);
	DDX_Control(pDX, IDC_STATIC_ALGORITHM, m_algorithmText);
	DDX_Control(pDX, IDC_COMBO_METHOD, m_algorithmList);
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_BUTTON_MESH, m_btnMesh);
	DDX_Control(pDX, IDC_BUTTON_MANUAL_SEG, m_btnManual);
	DDX_Control(pDX, IDC_BUTTON_CROSS, m_btnCross);
	DDX_Control(pDX, IDC_BUTTON_BRUSH_SEG, m_btnBrush);
	DDX_Control(pDX, IDC_BUTTON_AUTO_SEG, m_btnAuto);
	DDX_Control(pDX, IDC_EDIT_ROINAME, m_ROIName);
	DDX_Control(pDX, IDC_COMBO_ROI, m_ROIList);
	DDX_Control(pDX, IDC_SLIDER_ROI_OPACITY, m_OpacitySlider);
	DDX_Control(pDX, IDC_STATIC_OPACITY, m_Opacity);
	DDX_Control(pDX, IDC_STATIC_OPTION, m_Options);
	DDX_Control(pDX, IDC_BUTTON_ADDROI, m_btnAddROI);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSegment, CDialog)
	//{{AFX_MSG_MAP(CDlgSegment)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ROI_OPACITY, OnCustomdrawSliderRoiOpacity)
	ON_CBN_SELCHANGE(IDC_COMBO_ROI, OnSelchangeComboRoi)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_ADDROI, OnButtonAddroi)
	ON_EN_CHANGE(IDC_EDIT_ROINAME, OnChangeEditRoiname)
	ON_BN_CLICKED(IDC_BUTTON_CROSS, OnButtonCross)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SEG, OnButtonManualSeg)
	ON_BN_CLICKED(IDC_BUTTON_BRUSH_SEG, OnButtonBrushSeg)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_SEG, OnButtonAutoSeg)
	ON_BN_CLICKED(IDC_BUTTON_MESH, OnButtonMesh)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_MESSAGE(WM_IMAGEPROCESS_END,OnImageProcessEnd)
	ON_MESSAGE(WM_INTIME_SEGMENTED,OnIntimeSegmented)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD, OnSelchangeComboMethod)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSegment message handlers

BOOL CDlgSegment::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bInitialized=TRUE;
	gSegmentDlg=this;

	CQTImageDlg* pMainDlg = gpMainDlg;

	m_pROIManager=&pMainDlg->m_roiManager;

	m_OpacitySlider.SetRange(0,255);
	m_OpacitySlider.SetPageSize(1);

	m_btnCross.LoadBitmaps(IDB_BITMAP_CROSS);
	m_btnManual.LoadBitmaps(IDB_BITMAP_MANUAL);
	m_btnAuto.LoadBitmaps(IDB_BITMAP_AUTOSEG);
	m_btnBrush.LoadBitmaps(IDB_BITMAP_BRUSH);
	m_btnMesh.LoadBitmaps(IDB_BITMAP_MESH);

	for(int i=0;i<m_iMaxCtrlCount;i++)
	{
		CDlgScaleCtrl *pCtrl;
		pCtrl=new CDlgScaleCtrl(NULL);
		pCtrl->Create(IDD_SCALE_CTRL,this);
		pCtrl->SetParent(this);
		pCtrl->ShowWindow(SW_HIDE);
		m_wndList.AddTail(pCtrl);	
	}
	m_iCtrlCount=3;
	
	m_algorithmList.AddString("Simple Threshold");
	m_algorithmList.AddString("Connected Threshold");
	m_algorithmList.AddString("Confidence Connected");
	m_algorithmList.AddString("Isolated Connected");

	m_algorithmList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSegment::OnCustomdrawSliderRoiOpacity(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int i=m_OpacitySlider.GetPos();
	if(i==m_iLastPos)
		return;
	m_iLastPos=i;

	CString sTmp;
	sTmp.Format("%i",i);
	m_Opacity.SetWindowText(sTmp);

	CString sName;
	m_ROIList.GetWindowText(sName);

	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);
	pROI->SetOpacity(i);

	m_pDlgMPR->DrawROI();

	
}

void CDlgSegment::OnSelchangeComboRoi() 
{
	// TODO: Add your control notification handler code here
	m_iCurSelectROI=m_ROIList.GetCurSel();
	CString sName;
	m_ROIList.GetWindowText(sName);
	m_ROIName.SetWindowText(sName);

	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);
	int opacity=pROI->GetOpacity();
	m_OpacitySlider.SetPos(opacity);
	CString sTmp;
	sTmp.Format("%i",opacity);
	m_Opacity.SetWindowText(sTmp);
}

void CDlgSegment::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bInitialized)
		return;

	CRect rc;
	GetClientRect(&rc);

	CRect rcTmp(2,rc.bottom-150,rc.Width()-4,rc.bottom-30);
	m_Options.MoveWindow(&rcTmp);
	m_log.MoveWindow(2,rc.bottom-25,rc.Width()-4,rc.bottom-5);
	
	rcTmp.left=5;
	rcTmp.top+=25;
	rcTmp.right-=5;
	rcTmp.bottom=rcTmp.top+20;
	m_ROIList.MoveWindow(rcTmp);

	rcTmp.right=30;
	rcTmp.top+=30;
	rcTmp.bottom=rcTmp.top+20;
	m_Opacity.MoveWindow(&rcTmp);
	rcTmp.left=rcTmp.right+1;
	rcTmp.right=rc.Width()-8;
	m_OpacitySlider.MoveWindow(&rcTmp);

	rcTmp.top+=30;
	rcTmp.bottom=rcTmp.top+25;
	rcTmp.left=(rc.Width()-90)/2-30;
	rcTmp.right=rcTmp.left+90;
	m_btnAddROI.MoveWindow(&rcTmp);

	rcTmp.left=rc.Width()-8-100;
	rcTmp.right=rc.Width()-8;
	m_ROIName.MoveWindow(&rcTmp);


	//buttons
	m_btnBox.MoveWindow(3,0,rc.Width()-8,50);
	rcTmp.left=10;
	rcTmp.top=10;
	rcTmp.right=rcTmp.left+35;
	rcTmp.bottom=rcTmp.top+35;
	m_btnCross.MoveWindow(&rcTmp);

	rcTmp.left+=40;
	rcTmp.top=10;
	rcTmp.right=rcTmp.left+35;
	rcTmp.bottom=rcTmp.top+35;
	m_btnManual.MoveWindow(&rcTmp);

	rcTmp.left+=40;
	rcTmp.top=10;
	rcTmp.right=rcTmp.left+35;
	rcTmp.bottom=rcTmp.top+35;
	m_btnAuto.MoveWindow(&rcTmp);
	rcTmp.left+=40;
	rcTmp.top=10;
	rcTmp.right=rcTmp.left+35;
	rcTmp.bottom=rcTmp.top+35;
	m_btnBrush.MoveWindow(&rcTmp);
	rcTmp.left+=40;
	rcTmp.top=10;
	rcTmp.right=rcTmp.left+35;
	rcTmp.bottom=rcTmp.top+35;
	m_btnMesh.MoveWindow(&rcTmp);

	ResetGUICtrl();
}

void CDlgSegment::OnButtonAddroi() 
{
	// TODO: Add your control notification handler code here
	CROI *pROI=m_pROIManager->AddROI();
	pROI->SetImage(m_pImage);
	pROI->SetName("ROI New");
	m_ROIList.AddString(pROI->GetName());

	CString sName;
	m_ROIList.GetWindowText(sName);

	pROI=m_pROIManager->GetByName(sName);
	int opacity=pROI->GetOpacity();
	m_OpacitySlider.SetPos(opacity);
	CString sTmp;
	sTmp.Format("%i",opacity);
	m_Opacity.SetWindowText(sTmp);
}

void CDlgSegment::SetSeries(vtkImageData *pImage)
{
	m_pImage=pImage;
	int iCount=m_pROIManager->GetROICount(pImage);
	if(iCount==0)
	{
		CROI *pROI=m_pROIManager->AddROI();
		pROI->SetImage(pImage);
		pROI->SetName("ROI New");
		m_ROIList.ResetContent();
		m_ROIList.AddString(pROI->GetName());
	}else
	{
		m_ROIList.ResetContent();
		for(int i=0;i<iCount;i++)
		{
			CROI *pROI=m_pROIManager->GetROIAt(pImage,i);
			m_ROIList.AddString(pROI->GetName());
		}
	}

	m_ROIList.SetCurSel(0);
	m_iCurSelectROI=0;
	CString sName;
	m_ROIList.GetWindowText(sName);
	m_ROIName.SetWindowText(sName);

	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);
	int opacity=pROI->GetOpacity();
	m_OpacitySlider.SetPos(opacity);
	CString sTmp;
	sTmp.Format("%i",opacity);
	m_Opacity.SetWindowText(sTmp);

	CQTImageDlg* pMainDlg = gpMainDlg;
	
	if(pMainDlg->m_seriesManager.GetSegmentedImage(m_pImage))
	{
		m_pSegmentedImage=pMainDlg->m_seriesManager.GetSegmentedImage(m_pImage);
	}else
	{
		m_pSegmentedImage=vtkImageData::New();
		pMainDlg->m_seriesManager.SetSegmentedImage(m_pImage,m_pSegmentedImage);
		m_pSegmentedImage->DeepCopy(m_pImage);

		int *dim=m_pSegmentedImage->GetDimensions();
		unsigned short *pData=(unsigned short *)m_pSegmentedImage->GetScalarPointer(0,0,0);
		if(!pData)
		{
			MessageBox("No enough memory.");
			return;
		}

		memset(pData,0,sizeof(short)*dim[0]*dim[1]*dim[2]);
	}

	if(m_pSegmentingImage)
	{
		m_pSegmentingImage->Delete();
	}
	m_pSegmentingImage=vtkImageData::New();
	
	m_pSegmentingImage->DeepCopy(m_pImage);

	int *dim=m_pSegmentingImage->GetDimensions();
	unsigned short *pData=(unsigned short *)m_pSegmentingImage->GetScalarPointer(0,0,0);
	if(!pData)
	{
		MessageBox("No enough memory.");
		return;
	}

	memset(pData,0,sizeof(short)*dim[0]*dim[1]*dim[2]);

	OnSelchangeComboMethod();

}

void CDlgSegment::OnChangeEditRoiname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString sName;
	m_ROIName.GetWindowText(sName);
	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);
	pROI->SetName(sName);

	if(m_iCurSelectROI==m_ROIList.GetCount())
	{
		m_ROIList.DeleteString(m_iCurSelectROI);
		m_ROIList.AddString(sName);
		m_ROIList.SetCurSel(m_iCurSelectROI);
	}else
	{
		m_ROIList.DeleteString(m_iCurSelectROI);
		m_ROIList.InsertString(m_iCurSelectROI,sName);
		m_ROIList.SetCurSel(m_iCurSelectROI);
	}
}

CROI* CDlgSegment::GetCurROI()
{
	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);
	return pROI;
}

void CDlgSegment::OnButtonCross() 
{
	// TODO: Add your control notification handler code here
	m_pDlgMPR->EnableManualSeg(FALSE);
	m_pDlgMPR->EnableCross(TRUE);
}

void CDlgSegment::OnButtonManualSeg() 
{
	// TODO: Add your control notification handler code here
	m_pDlgMPR->EnableManualSeg(TRUE);
	m_pDlgMPR->EnableCross(FALSE);
}

void CDlgSegment::OnButtonBrushSeg() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSegment::OnButtonAutoSeg() 
{
	// TODO: Add your control notification handler code here
	
}

int CDlgSegment::GetROICount()
{
	return m_pROIManager->GetROICount(m_pImage);
}

CROI* CDlgSegment::GetROIAt(int index)
{
	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,index);
	return pROI;
}

void CDlgSegment::OnButtonMesh() 
{
	// TODO: Add your control notification handler code here
	m_pDlgSR->UpdateMesh();
	//MESH_OPTIONS option;
	//option.label=1200;
	//m_pDlgSR->AddMesh(m_pImage,option);
}

BOOL CDlgSegment::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN){   
		switch(pMsg->wParam){   
		case   VK_ESCAPE:   
			 return   TRUE;   
			 break;
		case VK_RETURN:
			return TRUE;
			break;
		}   
	}   
	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgSegment::ClearGUICtrl()
{
	POSITION pos;
	pos=m_wndList.GetHeadPosition();
	CWnd *pWnd;
	for(int i=0;i<m_wndList.GetCount();i++)
	{
		pWnd=m_wndList.GetNext(pos);
		if(pWnd->m_hWnd)
		{
			pWnd->DestroyWindow();
		}
		delete pWnd;
	}
	m_wndList.RemoveAll();
}

void CDlgSegment::ResetGUICtrl()
{
	CRect rs;
	GetClientRect(rs);

	int iHeight;

	if(!m_btnApply.GetSafeHwnd())
		return;

	m_algorithmText.MoveWindow(5,62,50,30);
	m_algorithmList.MoveWindow(55,60,rs.right-15-55,230);

	CRect rsSelf;
	iHeight=90;

	POSITION pos;
	pos=m_wndList.GetHeadPosition();
	CDlgScaleCtrl *pCtrl;
	for(int i=0;i<m_wndList.GetCount();i++)
	{
		pCtrl=(CDlgScaleCtrl *)m_wndList.GetNext(pos);
				
		if(i<m_iCtrlCount)
		{
			pCtrl->MoveWindow(10,iHeight,rs.Width()-20,55);
			pCtrl->ShowWindow(SW_SHOW);
			pCtrl->RefreshCtrl();
			iHeight+=60;
		}else
		{
			pCtrl->ShowWindow(SW_HIDE);
		}
		
		
	}
	
	m_btnApply.GetClientRect(rsSelf);
	m_btnApply.MoveWindow(10,iHeight+10,65,25);
	m_btnUpdate.MoveWindow(10+65+10,iHeight+10,65,25);
	//m_btnRedo.MoveWindow(10+rsSelf.Width()*2+20,iHeight+10,rsSelf.Width(),rsSelf.Height());

	iHeight+=10+25;

	//m_dlgSeeds.GetClientRect(rsSelf);
	//m_dlgSeeds.MoveWindow(10,iHeight+10,rs.Width()-10,rsSelf.Height());
	//iHeight+=10+rsSelf.Height();
	//m_dlgSeeds.ShowWindow(SW_SHOW);


}

void CDlgSegment::ResetVVData()
{
	if(!m_pImage)
		return;

	m_vvData.StartSlice=0;
	m_vvData.NumberOfSlicesToProcess=0;
	
	m_vvInfo.SetProperty=VolSetProperty;
	m_vvInfo.GetProperty=VolGetProperty;
	m_vvInfo.SetGUIProperty=VolSetGUIProperty;
	m_vvInfo.GetGUIProperty=VolGetGUIProperty;
	m_vvInfo.UpdateProgress=VolUpdateProgress;

	m_vvInfo.NumberOfMarkers=0;
	if(m_vvInfo.Markers!=NULL){delete []m_vvInfo.Markers; m_vvInfo.Markers=NULL;}
	
	if(m_pImage==NULL)
		return;

	m_vvInfo.InputVolumeScalarType=VTK_UNSIGNED_SHORT; 
    m_vvInfo.InputVolumeScalarSize=VTK_SIZEOF_SHORT;
    m_pImage->GetDimensions(m_vvInfo.InputVolumeDimensions);
	
	m_vvInfo.OutputVolumeScalarType=VTK_UNSIGNED_CHAR;

	double dData[3];
    m_pImage->GetSpacing(dData);
	m_vvInfo.InputVolumeSpacing[0]=(float)dData[0];
	m_vvInfo.InputVolumeSpacing[1]=(float)dData[1];
	m_vvInfo.InputVolumeSpacing[2]=(float)dData[2];
    m_pImage->GetOrigin(dData);
	m_vvInfo.InputVolumeOrigin[0]=(float)dData[0];
	m_vvInfo.InputVolumeOrigin[1]=(float)dData[1];
	m_vvInfo.InputVolumeOrigin[2]=(float)dData[2];

	m_pImage->GetScalarRange(dData);
    m_vvInfo.InputVolumeScalarRange[0]=dData[0]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[1]=dData[1]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[2]=dData[0]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[3]=dData[1]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[4]=dData[0]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[5]=dData[1]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[6]=dData[0]; /* actual scalar range */
	m_vvInfo.InputVolumeScalarRange[7]=dData[1]; /* actual scalar range */
    m_vvInfo.InputVolumeScalarTypeRange[0]=VTK_SHORT_MIN; /* possible scalar range */
	m_vvInfo.InputVolumeScalarTypeRange[1]=VTK_SHORT_MAX; /* possible scalar range */

	m_iCtrlCount=0;
}



UINT ImageProcess( LPVOID pParam)
{
	//	HWND hWnd = (HWND)pParam;
	CDlgSegment* pDlg = (CDlgSegment*)pParam;

	pDlg->m_vvInfo.ProcessData(&pDlg->m_vvInfo,&pDlg->m_vvData);
			
	::SendMessage( pDlg->m_hWnd, WM_IMAGEPROCESS_END, 0, 0 );
		
	AfxEndThread( 0, TRUE );
	return 0;
} 

LONG CDlgSegment::OnImageProcessEnd( UINT wParam, LONG lParam )
{
		
	m_btnApply.SetWindowText("Apply");
	VolUpdateProgress(&m_vvInfo,1.0,"End.");

	//UpdateImage();

	return 0;
}

LONG CDlgSegment::OnIntimeSegmented( UINT wParam, LONG lParam )
{

	
	if(!m_pImage)
		return 0;

	short *pSrc=(short *)m_pImage->GetScalarPointer(0,0,0);
	pSrc+=m_vvInfo.InputVolumeDimensions[0]*m_vvInfo.InputVolumeDimensions[1]*m_pDlgMPR->m_iCurSlice1;
	short *pNewSrc=new short[m_vvInfo.InputVolumeDimensions[0]*m_vvInfo.InputVolumeDimensions[1]];
	memcpy(pNewSrc,pSrc,sizeof(short)*m_vvInfo.InputVolumeDimensions[0]*m_vvInfo.InputVolumeDimensions[1]);
	m_vvData.inData=(void *)pNewSrc;
			
	m_vvData.StartSlice=0;
	m_vvData.NumberOfSlicesToProcess=1;

	m_vvInfo.NumberOfMarkers=0;
	if(m_vvInfo.Markers!=NULL){delete []m_vvInfo.Markers; m_vvInfo.Markers=NULL;}
	m_vvInfo.NumberOfMarkers=1;
	m_vvInfo.Markers=new float[3];
	m_vvInfo.Markers[0]=m_pDlgMPR->m_pntCross1.x * m_vvInfo.InputVolumeSpacing[0];
	m_vvInfo.Markers[1]=m_pDlgMPR->m_pntCross1.y * m_vvInfo.InputVolumeSpacing[1];
	m_vvInfo.Markers[2]=0;
	

	short *pDest=(short*)m_pSegmentingImage->GetScalarPointer(0,0,0);
	memset(pDest,0,sizeof(short)*m_vvInfo.OutputVolumeDimensions[0]*m_vvInfo.OutputVolumeDimensions[1]*
				m_vvInfo.OutputVolumeDimensions[2]);
	pDest+=m_vvInfo.OutputVolumeDimensions[0]*m_vvInfo.OutputVolumeDimensions[1]*m_pDlgMPR->m_iCurSlice1;

	short *pNewDest=new short[m_vvInfo.OutputVolumeDimensions[0]*m_vvInfo.OutputVolumeDimensions[1]];
	m_vvData.outData=(void*)pNewDest;

	m_bEnableDrawROIInProcess=FALSE;
	m_vvInfo.ProcessData(&m_vvInfo,&m_vvData);
	m_bEnableDrawROIInProcess=TRUE;

	memcpy(pDest,pNewDest,sizeof(short)*m_vvInfo.OutputVolumeDimensions[0]*m_vvInfo.OutputVolumeDimensions[1]);
	
	delete []pNewSrc;
	delete []pNewDest;

	m_pDlgMPR->DrawROI();

	UpdateLog("End.");

	return 0;
}


void CDlgSegment::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if(!m_pImage)
		return;

	CString sTmp;
	m_btnApply.GetWindowText(sTmp);
	if(sTmp=="Cancel")
	{
		sprintf(m_vvProp.sVVP_ABORT_PROCESSING,"1");
		return;
	}

	InitInputData();
	InitOutputData();
	
	m_btnApply.SetWindowText("Cancel");
	sprintf(m_vvProp.sVVP_ABORT_PROCESSING,"0");
	AfxBeginThread(ImageProcess,(LPVOID)this,THREAD_PRIORITY_LOWEST,0,0,NULL);

}

void CDlgSegment::InitInputData()
{
	
	m_vvData.inData=(void*)m_pImage->GetScalarPointer(0,0,0);
			
	m_vvData.StartSlice=0;
	m_vvData.NumberOfSlicesToProcess=m_vvInfo.InputVolumeDimensions[2];

	m_vvInfo.NumberOfMarkers=0;
	if(m_vvInfo.Markers!=NULL){delete []m_vvInfo.Markers; m_vvInfo.Markers=NULL;}
	
	m_vvInfo.NumberOfMarkers=1;
	m_vvInfo.Markers=new float[3];
	m_vvInfo.Markers[0]=m_pDlgMPR->m_pntCross1.x * m_vvInfo.InputVolumeSpacing[0];
	m_vvInfo.Markers[1]=m_pDlgMPR->m_pntCross1.y * m_vvInfo.InputVolumeSpacing[1];
	m_vvInfo.Markers[2]=m_pDlgMPR->m_iCurSlice1  * m_vvInfo.InputVolumeSpacing[2];

	/*SendCommand(this,CMD_GET_SEED_COUNT,sTmp);
	m_vvInfo.NumberOfMarkers=atoi(sTmp);
	if(m_vvInfo.NumberOfMarkers>0)
	{
		m_vvInfo.Markers=new float[3*m_vvInfo.NumberOfMarkers];
		int iAddress=(int)m_vvInfo.Markers;
		sTmp.Format("%i",iAddress);
		SendCommand(this,CMD_GET_SEEDS,sTmp);
	}*/

}

void CDlgSegment::InitOutputData()
{
	short *pChar=(short*)m_pSegmentingImage->GetScalarPointer(0,0,0);
	m_vvData.outData=(void*)pChar;
	memset(pChar,0,sizeof(short)*m_vvInfo.OutputVolumeDimensions[0]*m_vvInfo.OutputVolumeDimensions[1]*
				m_vvInfo.OutputVolumeDimensions[2]);
	
}

void CDlgSegment::OnSelchangeComboMethod() 
{
	// TODO: Add your control notification handler code here
	int i=m_algorithmList.GetCurSel();
	switch(i)
	{
	case SEGMENT_SIMPLE_THRESHOLD:
		{
			ResetVVData();
			m_vvITKSimpleThresholdInit((void*)&m_vvInfo);
			m_vvInfo.UpdateGUI(&m_vvInfo);
			ResetGUICtrl();
		}
		break;
	case SEGMENT_CONNECTED_THRESHOLD:
		{
			ResetVVData();
			m_vvITKConnectedThresholdInit(&m_vvInfo);
			m_vvInfo.UpdateGUI(&m_vvInfo);
			ResetGUICtrl();
		}
		break;
	case SEGMENT_CONFIDENCE_CONNECTED:
		{
			ResetVVData();
			m_vvITKConfidenceConnectedInit(&m_vvInfo);
			m_vvInfo.UpdateGUI(&m_vvInfo);
			ResetGUICtrl();
		}
		break;
	case SEGMENT_ISOLATED_CONNECTED:
		break;
	}
}

void CDlgSegment::UpdateLog(CString sMsg)
{
	m_log.SetWindowText(sMsg);
}

void CDlgSegment::initLib()
{
	CString sTmp;
	sTmp.Format("%sitkPlug.Dll",g_sProgramPath);

	m_hItkPlug = LoadLibrary(sTmp);
	m_vvITKSimpleThresholdInit = (vvITKSimpleThresholdInit)GetProcAddress(m_hItkPlug, "vvITKSimpleThresholdInit");
	m_vvITKMedianInit = (vvITKMedianInit)GetProcAddress(m_hItkPlug, "vvITKMedianInit");
	m_vvITKConnectedThresholdInit = (vvITKConnectedThresholdInit)GetProcAddress(m_hItkPlug,"vvITKConnectedThresholdInit");
	m_vvITKConfidenceConnectedInit=(vvITKConfidenceConnectedInit)GetProcAddress(m_hItkPlug,"vvITKConfidenceConnectedInit");
}





void CDlgSegment::Clear()
{
	if(m_pSegmentingImage)
	{
		m_pSegmentingImage->Delete();
		m_pSegmentingImage=NULL;
	}
}

void CDlgSegment::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	m_iCurSelectROI=m_ROIList.GetCurSel();
	
	CROI *pROI=m_pROIManager->GetROIAt(m_pImage,m_iCurSelectROI);

	
	int *dim=m_pSegmentingImage->GetDimensions();
	unsigned short *pSrc=(unsigned short *)m_pSegmentingImage->GetScalarPointer(0,0,0);
	unsigned short *pDest=(unsigned short *)m_pSegmentedImage->GetScalarPointer(0,0,0);
	
	int iCount=dim[0]*dim[1]*dim[2];
	int rate,ratePre=0;
	CString sTmp;
	for(int i=0;i<iCount;i++)
	{
		rate=100.0*i/iCount;
		if(rate%5==0 && rate!=ratePre)
		{
			sTmp.Format("Update... %i",rate);
			UpdateLog(sTmp);
			ratePre=rate;
		}
		if(pSrc[i]>0)
		{
			pDest[i]=pROI->GetLabel();
		}
	}

	

	UpdateLog("end.");

}
