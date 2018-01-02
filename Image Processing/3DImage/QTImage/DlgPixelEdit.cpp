// DlgHistogram.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPixelEdit.h"
#include "Commands.h"
#include "Viewer2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPixelEdit dialog


CDlgPixelEdit::CDlgPixelEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPixelEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPixelEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pView=NULL;
}


void CDlgPixelEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPixelEdit)
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_image);
	DDX_Control(pDX, IDC_STATIC_OPACITY, m_ctrlOpacity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPixelEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgPixelEdit)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPixelEdit message handlers

BOOL CDlgPixelEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	CRect rc;
	GetClientRect(&rc);
	CRect rcSelf;
	m_image.GetWindowRect(&rcSelf);
	ScreenToClient(&rcSelf);
	m_image.MoveWindow((rc.Width()-rcSelf.Width())/2,
		rcSelf.top,rcSelf.Width(),rcSelf.Width());

	m_ctrlOpacity.SetPixelRange(0,4096);
	m_ctrlOpacity.m_grayHistogram=NULL;
	m_ctrlOpacity.DrawLine();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPixelEdit::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	int iResult=*((int *)wParam);
	IA_PIXEL_ITEM item;

	if(iResult==10 || iResult==20)
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
		
		//UpdateImage();
	}

	if(iResult==11)
	{
		UpdateImage();
	}

	
	return TRUE; //CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgPixelEdit::SendCommand(int nCmdID,CString& sPara)
{
	if(m_pView)
	{
		m_pView->SendMessage(WM_CALL_COMMAND,WPARAM(nCmdID),LPARAM(&sPara));
	}
}


void CDlgPixelEdit::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	if(!m_pView)
		return;
	C2DViewer *pView=(C2DViewer *)m_pView;

	vtkImageData *pImage=pView->GetSeries();
	if(!pImage)
		return;

	int *pDim=pImage->GetDimensions();
	
	unsigned short *pData=(unsigned short *)pImage->GetScalarPointer(0,0,0);
	
	float opacity;
	CString sTmp;
	int rate,ratePre=0;
	for(int i=0;i<pDim[0]*pDim[1]*pDim[2];i++)
	{
		rate=100.0*i/float(pDim[0]*pDim[1]*pDim[2]);
		if(rate%5==0 && rate!=ratePre)
		{
			sTmp.Format("Update %i",rate);
			GetDlgItem(IDC_BTN_UPDATE)->SetWindowText(sTmp);
			ratePre=rate;
		}
		m_ctrlOpacity.GetPixelOpacity(pData[i],opacity);
		pData[i]=pData[i]*opacity;
	}

	GetDlgItem(IDC_BTN_UPDATE)->SetWindowText("Update");
	m_pView->Invalidate(FALSE);

}

void CDlgPixelEdit::UpdateImage()
{
	if(!m_pView)
		return;
	if(!this->IsWindowVisible())
		return;
	C2DViewer *pView=(C2DViewer *)m_pView;

	vtkImageData *pImage=pView->GetSeries();
	if(!pImage)
		return;
	int index=pView->GetCurIndex();
	if(index<0)
		return;

	int *pDim=pImage->GetDimensions();
	
	unsigned short *pData=(unsigned short *)pImage->GetScalarPointer(0,0,0);
	pData+=index*pDim[0]*pDim[1];

	unsigned short *pNewData=new unsigned short[pDim[0]*pDim[1]];
	float opacity;
	for(int i=0;i<pDim[0]*pDim[1];i++)
	{
		m_ctrlOpacity.GetPixelOpacity(pData[i],opacity);
		pNewData[i]=pData[i]*opacity;
	}
	

	vtkImageData *pNewImage=vtkImageData::New();
	vtkUnsignedShortArray *array =  vtkUnsignedShortArray::New();
	array ->SetArray(pNewData, pDim[0]*pDim[1],0) ;
	pNewImage->GetPointData()->SetScalars(array);
	pNewImage ->SetDimensions(pDim[0],pDim[1],1);
	pNewImage ->SetScalarType(VTK_UNSIGNED_SHORT);
	pNewImage ->SetSpacing(1,1,1);
	pNewImage ->SetOrigin(0.0, 0.0, 0.0);
	array->Delete();

	m_image.Update(pNewImage,0);

	pNewImage->Delete();
}

void CDlgPixelEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPixelEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgPixelEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPixelEdit::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
