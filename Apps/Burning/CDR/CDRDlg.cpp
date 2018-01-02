// CDRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDR.h"
#include "CDRDlg.h"
#include "LabelDlg.h"
#include "winioctl.h"
#include "scsi2.h"
#include "osta_udf.h"
#include "ecma_167.h"
#include "scsireg.h"
#include <math.h>
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Uint16 udf_crc(Uchar *data, Uint32 size);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//----------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
//----------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
//----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDRDlg dialog
//----------------------------------------------------------------------------
CCDRDlg::CCDRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDRDlg)
	m_str_offset = _T("0000");
	m_str_length = _T("1");
	m_HA = 0;
	m_ID = 0;
	m_LUN = 0;
	m_fileName = _T("");
	m_track = 0;
	m_header = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}
//----------------------------------------------------------------------------
CCDRDlg::~CCDRDlg(){
	m_bus.ASPIStop();
	delete m_menu;
}
//----------------------------------------------------------------------------
void CCDRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDRDlg)
	DDX_Control(pDX, IDC_LIST1, m_fileList);
	DDX_Control(pDX, IDC_COMBO1, m_driveCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_str_offset);
	DDX_Text(pDX, IDC_EDIT2, m_str_length);
	DDX_Control(pDX, IDC_EDIT3, m_edit);
	DDX_Text(pDX, IDC_HA, m_HA);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDX_Text(pDX, IDC_LUN, m_LUN);
	DDX_Text(pDX, IDC_TRACK, m_track);
	DDX_Check(pDX, IDC_HEADER, m_header);
	//}}AFX_DATA_MAP
}
//----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CCDRDlg, CDialog)
	//{{AFX_MSG_MAP(CCDRDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_READ, OnRead)
	ON_BN_CLICKED(ID_EJECT, OnEject)
	ON_BN_CLICKED(ID_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_WRITE_FILES, OnWriteFiles)
	ON_BN_CLICKED(ID_FORMAT_DISC, OnFormatDisc)
	ON_BN_CLICKED(ID_CLOSE_SESSION, OnCloseSession)
	ON_BN_CLICKED(IDC_CONTENT, OnContent)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_COMMAND(ID_READ_TRACK_INFO, OnReadTrackInfo)
	ON_COMMAND(ID_READ_DISK_INFO, OnReadDiskInfo)
	ON_COMMAND(ID_ATIP, OnAtip)
	ON_COMMAND(ID_PMA, OnPma)
	ON_COMMAND(ID_TOC, OnToc)
	ON_COMMAND(ID_BUS_SCAN, OnBusScan)
	ON_COMMAND(ID_INQUIRY, OnInquiry)
	ON_COMMAND(ID_WRITE_PARAMETERS, OnWriteParameters)
	ON_COMMAND(ID_SET_MODE1, OnSetMode1)
	ON_COMMAND(ID_SET_MODE2, OnSetMode2)
	ON_COMMAND(ID_APP_ABOUT, OnAbout)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelectchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, OnPosChange)
	ON_EN_CHANGE(IDC_ID, OnDeviceChange)
	ON_EN_CHANGE(IDC_LUN, OnDeviceChange)
	ON_EN_CHANGE(IDC_HA, OnDeviceChange)
	ON_EN_CHANGE(IDC_EDIT2, OnPosChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//----------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// CCDRDlg message handlers

BOOL CCDRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_menu=new CMenu;
	m_menu->LoadMenu(IDR_MENU1);
	SetMenu(m_menu);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	OnPosChange();

	m_edit.SetReadOnly(true);
	m_bus.ASPIStart();
	int count=m_bus.SCSIBusScan(info,DTYPE_CDROM);
	for(int i=0;i<count;i++)
		m_driveCtrl.AddString(info[i].m_name);
	m_HA=info[0].m_HA;
	m_ID=info[0].m_ID;
	m_LUN=info[0].m_LUN;
	m_bus.SCSISelectDevice(m_HA,m_ID,m_LUN);
	UpdateData(false);
	m_driveCtrl.SetCurSel(0);

	RECT listRect;
	m_fileList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);
	int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 
	int nCol1Width = nListWidth - nVScrollBarWidth -2;
	m_fileList.InsertColumn(0, _T("Files"), LVCFMT_LEFT, nCol1Width);	
	
	m_fileList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	m_ImageList.Create(IDR_FILE_IMAGES, 16, 16, RGB(255,0,255));
	m_fileList.SetImageList(&m_ImageList, LVSIL_SMALL);

	CFileDropListCtrl::DROPLISTMODE dropMode;
	dropMode.iMask = CFileDropListCtrl::DL_ACCEPT_FILES;
	m_fileList.SetDropMode(dropMode);
	
	return TRUE; 
}
//----------------------------------------------------------------------------

void CCDRDlg::OnAbout(){
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

//----------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//----------------------------------------------------------------------------
void CCDRDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//----------------------------------------------------------------------------

HCURSOR CCDRDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//----------------------------------------------------------------------------
void CCDRDlg::OnSelchangeCombo1() 
{
	UpdateData();	
}

//----------------------------------------------------------------------------
void CCDRDlg::OnDeviceChange() 
{
	UpdateData();
	m_bus.SCSISelectDevice(m_HA,m_ID,m_LUN);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnPosChange() 
{
	UpdateData();
	char* stop;
	m_length=strtol(m_str_length,&stop,16);
	m_offset=strtol(m_str_offset,&stop,16);
}
//----------------------------------------------------------------------------
void CCDRDlg::OnEject() 
{
	m_bus.LoadUnload(false);
}
//----------------------------------------------------------------------------
void CCDRDlg::OnClose() 
{
	m_bus.LoadUnload(true);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnAtip() 
{
	AfxMessageBox(m_bus.ATIP());
}
//----------------------------------------------------------------------------

void CCDRDlg::OnPma() 
{
	AfxMessageBox(m_bus.PMA());
}
//----------------------------------------------------------------------------

void CCDRDlg::OnToc() 
{
	AfxMessageBox(m_bus.TOC());		
}
//----------------------------------------------------------------------------

void CCDRDlg::OnBusScan() 
{	
	m_bus.SCSIBusScan(info,0xff,false);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnInquiry() 
{
	AfxMessageBox(m_bus.SCSIInquiry());
	AfxMessageBox(m_bus.SCSICapabilities ());
}
//----------------------------------------------------------------------------
void CCDRDlg::OnRead() 
{
	UpdateData();
	BYTE *buffer=new BYTE[m_length*2448];
	int readCount=(int)ceil((double)m_length/0x10);
	for(int i=0;i<readCount;i++){
		if(!m_bus.SCSIRead(buffer+i*0x10*(m_header?block_size+8:block_size),
			m_offset+i*0x10,m_length-i*0x10<0x10?m_length-i*0x10:0x10,
			m_header!=0)){
			delete buffer;
			return;
		}
	}
	//m_edit.m_baseAddress=m_offset*2048;
	m_edit.SetData(buffer,m_length*(m_header?block_size+8:block_size));
	FILE* file=fopen("new.txt","wb");
	fwrite(buffer,block_size,m_length,file);
	fclose(file);
	delete buffer;
	m_offset+=m_length;
	CString s;
	s.Format("%X",m_offset);
	m_str_offset=s;
	UpdateData(false);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnWriteParameters() 
{
	AfxMessageBox(m_bus.WriteParameters());
}
//----------------------------------------------------------------------------

void CCDRDlg::OnBrowse() 
{
	static char BASED_CODE szFilter[] = "All Files (*.*)|*.*||";
	CFileDialog dlg(true,NULL,NULL,
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT,
				szFilter,NULL);
	if(dlg.DoModal()==IDOK ){
		m_fileName.Empty();
		m_fileList.DeleteAllItems ();
		POSITION pos=dlg.GetStartPosition();
		while(pos)	{
			CString name=dlg.GetNextPathName(pos);
			m_fileName+=name+"\r\n";
			m_fileList.InsertItem(0,name);
		}
		UpdateData(false);
		m_upload=true;
	}
}

//----------------------------------------------------------------------------

void CCDRDlg::OnWriteFiles() 
{
	m_fileName.Empty();
	for(int i=0;i<m_fileList.GetItemCount();i++){
		m_fileName+=m_fileList.GetItemText(i,0)+"\r\n";
	}
	if(m_fileName.IsEmpty())	return;
	m_bus.setLBA(m_offset);
	AfxMessageBox(m_bus.WriteFiles(m_fileName)?"Write Successful!":"Write Failed!");
	CString s;
	s.Format("%X",m_offset=m_bus.getLBA());
	m_str_offset=s;
	UpdateData(false);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnWriteAsTemplate() 
{
	m_fileName.TrimRight();
	m_bus.setLBA(m_offset);
	FILE* file=fopen(m_fileName,"rb");
	if(file==NULL){
		AfxMessageBox("Failed to open input file.");
		return;
	}
	fseek(file,0,SEEK_END);
	unsigned int len=ftell(file);
	BYTE* buffer=new BYTE[len];
	fseek(file,0,SEEK_SET);
	ASSERT(fread(buffer,1,len,file)==len);
	m_edit.SetData(buffer,len);
	fclose(file);
	m_bus.WritePacket(buffer,m_offset,len/2048)?
		AfxMessageBox("Write Successful."):	
		AfxMessageBox("Write Failure.");

	delete buffer;
	CString s;
	s.Format("%X",m_offset=m_bus.getLBA());
	m_str_offset=s;
	UpdateData(false);
	
}
//----------------------------------------------------------------------------

void CCDRDlg::OnFormatDisc() 
{
	track_info ti;
	m_bus.ReadTrackInfo(m_track,&ti);
	if(!(ti.blank&&SCSI2::toInt32(ti.next_writtable_addr)==0)){
		AfxMessageBox("Disk is not blank.");
		return;
	}
	CLabelDlg dlg;
	dlg.m_hint="Please input disc label";
	if(dlg.DoModal()==IDOK){
		AfxMessageBox(m_bus.FormatDisc(LPCSTR(dlg.m_label))?
			"Disk Formatting Successful!":
			"Disk Formatting Failed!");
		CString s;
		s.Format("%X",m_offset=m_bus.getLBA());
		m_str_offset=s;
		UpdateData(false);
	}
}

//----------------------------------------------------------------------------

void CCDRDlg::OnCloseSession() 
{
	m_bus.setLBA(m_offset);
	AfxMessageBox(m_bus.CloseSession()?
		"CloseSession Successful!":
		"CloseSession Failed!");
	CString s;
	s.Format("%X",m_offset=m_bus.getLBA());
	m_str_offset=s;
	UpdateData(false);
}

//----------------------------------------------------------------------------

void CCDRDlg::OnReadTrackInfo() 
{
	UpdateData();
	AfxMessageBox(m_bus.ReadTrackInfo(m_track));
}
//----------------------------------------------------------------------------

void CCDRDlg::OnReadDiskInfo() 
{
	AfxMessageBox(m_bus.ReadDiskInfo());
}
//----------------------------------------------------------------------------
void CCDRDlg::OnReserveTrack() 
{
	AfxMessageBox(m_bus.ReserveTrack(0x168)?"Track Reserved Successful!":"Track Reservation Failure.");
}
//----------------------------------------------------------------------------

void CCDRDlg::OnSetMode2() 
{
	AfxMessageBox(m_bus.SetWriteParameters(0,10,5,0x20)?
		"Mode Set Successful!":
		"Mode Set Failed!");
}
//----------------------------------------------------------------------------

void CCDRDlg::OnSetMode1() 
{
	AfxMessageBox(m_bus.SetWriteParameters(1,10,4,0x20)?
		"Mode Set Successful!":
		"Mode Set Failed!");
}
//----------------------------------------------------------------------------

void CCDRDlg::OnSelectchangeCombo1() 
{
	CString curSel;
	m_driveCtrl.GetLBText(m_driveCtrl.GetCurSel(),curSel);
	for(int i=0;i<m_driveCtrl.GetCount();i++)
		if(info[i].m_name==curSel)	break;

	m_HA=info[i].m_HA;
	m_ID=info[i].m_ID;
	m_LUN=info[i].m_LUN;
	m_bus.SCSISelectDevice(m_HA,m_ID,m_LUN);
	UpdateData(false);
}
//----------------------------------------------------------------------------

void CCDRDlg::OnContent() 
{
	m_fileName=m_bus.ListFiles();
	m_fileList.DeleteAllItems();
	bool flag=false;
	int	 end=0;
	CString s=m_fileName;
	while(!s.IsEmpty()){
		end=s.FindOneOf(",;\t\r\n");
		CString singleFileName;
		if(end==-1)	{
			end=s.GetLength();
			singleFileName=s.Mid(0,end);
			s.Empty();
			continue;
		}
		else{
			singleFileName=s.Mid(0,end);
			s=s.Mid(end+1);
			s.TrimLeft();
		}
		singleFileName.TrimRight();
		m_fileList.InsertItem(0,singleFileName);
	}
	UpdateData(false);
	m_upload=false;
}
//----------------------------------------------------------------------------

void CCDRDlg::OnSave() 
{
	int total=m_fileList.GetSelectedCount();
	if(total<1){
		AfxMessageBox("Please Select the file(s) to save");
		return;
	}

	CLabelDlg dlg;
	dlg.m_hint="Please input directory to save files";
	if(dlg.DoModal()==IDOK){
		CString dir=dlg.m_label;
		//while(dir.Right(1)=="\\")	dir=dir.Left(dir.GetLength()-1);
		
		CFileFind finder;
		if(!PathFileExists(dir)&&
			!CreateDirectory(dir,NULL)){
			AfxMessageBox("Failed to create directory:\r\n"+dir);
		}
		int count=0;
		int* index=new int[total];
		POSITION pos = m_fileList.GetFirstSelectedItemPosition();
		while (pos)		  index[count++] = m_fileList.GetNextSelectedItem(pos);
		
		count=0;
		for(int i=0;i<total;i++){
			if(m_bus.SaveFileAs(index[i],dir+"\\"+m_fileList.GetItemText(index[i],0)))	
				count++;
		}
		CString s;
		s.Format("%d files are saved successfuly",count);
		AfxMessageBox(s);
		m_fileList.SetSelectionMark(-1);
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
