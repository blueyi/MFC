// SampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
	DDX_Control(pDX, IDC_CHOICE_PRODUCTS, m_choProducts);
	DDX_Control(pDX, IDC_CHOICE_COUNTRIES, m_choCountries);
	DDX_Control(pDX, IDC_CHOICE_CITIES, m_choCities);
	DDX_Control(pDX, IDC_CHOICE_BRANDS, m_choBrands);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//## INIT Countries =================================================================
	m_choCountries.AddString(TEXT("North America"));
		m_choCountries.AddString(TEXT("USA"),		5,  ROOT_LEVEL + 2);
		m_choCountries.AddString(TEXT("Canada"),	6,  ROOT_LEVEL + 2);
	m_choCountries.AddString(TEXT("Europe"));
		m_choCountries.AddString(TEXT("UK"),		7,  ROOT_LEVEL + 2);
		m_choCountries.AddString(TEXT("Germany"),	8,  ROOT_LEVEL + 2);
		m_choCountries.AddString(TEXT("Russia"),	9,  ROOT_LEVEL + 2);
	m_choCountries.AddString(TEXT("Asia"));
		m_choCountries.AddString(TEXT("Israel"),	10, ROOT_LEVEL + 2);
	m_choCountries.CheckAll(TRUE);
	
	//## INIT Cities ====================================================================
	m_choCities.AddString(TEXT("North America"));
		m_choCities.AddString(TEXT("New York"),		5,  ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Boston"),		6,  ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Chicago"),		21, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("San Francisco"),22, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Atlanta"),		23, ROOT_LEVEL + 2);
	m_choCities.AddString(TEXT("Europe"));
		m_choCities.AddString(TEXT("London"),		7,  ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Madrid"),		8,  ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Brussels"),		9,  ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Athens"),		10, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Prague"),		11, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Bratislava"),	12, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Edinburgh"),	14, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Lisbon"),		15, ROOT_LEVEL + 2);
		m_choCities.AddString(TEXT("Zagreb"),		17, ROOT_LEVEL + 2);
	m_choCities.CheckAll(TRUE);
	m_choCities.SetCheck(14, FALSE);

	//## INIT Products ==================================================================
	m_choProducts.AddString(TEXT("Milk"));
		m_choProducts.AddString(TEXT("Tnuva 1L"),		1,  ROOT_LEVEL + 2);
	m_choProducts.AddString(TEXT("Beer"));
		m_choProducts.AddString(TEXT("Interbrew"),		INVALID_ID,	ROOT_LEVEL + 2);
			m_choProducts.AddString(TEXT("Stella 0.5"),	2,  ROOT_LEVEL + 3);
			m_choProducts.AddString(TEXT("Aramia 0.5"),	3,  ROOT_LEVEL + 3);
		m_choProducts.AddString(TEXT("Karlovacko 0.5"),	4,  ROOT_LEVEL + 2);
		m_choProducts.AddString(TEXT("Lowenbrau 0.5"),	5,  ROOT_LEVEL + 2);
	m_choProducts.AddString(TEXT("Spoon"),	6);
	m_choProducts.AddString(TEXT("Oil"),	7);
	m_choProducts.CheckAll(TRUE);

	//## SET DroppedWidth
	m_choProducts.SetDroppedWidth( m_choProducts.GetDroppedWidth() + 75 );

	//## INIT Brands ====================================================================
	for(long i=0; i<10; i++)
		for(long j=0; j<26; j++)
			m_choBrands.AddString((CString)"Brand " + char('A' + i) + char('A' + j), i*26 + j);
	m_choBrands.CheckAll(TRUE);

	//## CREATE a ImageList =============================================================
	CImageList imgList;
	imgList.Create(IDB_TREE_ICONS, 18, 1, RGB(0xFF, 0xFF, 0xFF));

	//## SET ImageList
	m_choCountries.SetImageList( &imgList );
	m_choCities.SetImageList( &imgList );
	m_choProducts.SetImageList( &imgList );
	m_choBrands.SetImageList( &imgList );
	
	//## UPDATE the query
	OnButtonUpdate();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSampleDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnButtonUpdate() 
{
	//## QUERY
	CString str = "";
	str += "SELECT *\n";
	str += "FROM Products\n";
	str += "		LEFT JOIN Brands ON (Product.BrandID = Brands.ID)\n";
	str += "		LEFT JOIN Distributors ON (Product.DistributorID = Distributors.ID)\n";
	str += "		LEFT JOIN Cities ON (Distributors.CityID = Cities.ID)\n";
	str += "		LEFT JOIN Countries ON (Cities.CountryID = Countries.ID)\n";

	//## FILTER
	CString strFilter = "";
	if (m_choCountries.GetCheckedIDs().GetLength() > 1) strFilter += (CString)(strFilter.IsEmpty() ? "" : " AND ") +  "( Countries.ID IN " + m_choCountries.GetCheckedIDs() + ")\n";
	if (m_choCities.GetCheckedIDs().GetLength() > 1) strFilter += (CString)(strFilter.IsEmpty() ? "" : " AND ") +  "( Cities.ID IN " + m_choCities.GetCheckedIDs() + ")\n";
	if (m_choBrands.GetCheckedIDs().GetLength() > 1) strFilter += (CString)(strFilter.IsEmpty() ? "" : " AND ") +  "( Brands.ID IN " + m_choBrands.GetCheckedIDs() + ")\n";
	if (m_choProducts.GetCheckedIDs().GetLength() > 1) strFilter += (CString)(strFilter.IsEmpty() ? "" : " AND ") +  "( Products.ID IN " + m_choProducts.GetCheckedIDs() + ")\n";
	if (strFilter.GetLength() > 0)
		str += "WHERE " + strFilter;
	
	//## SHOW it
	GetDlgItem(IDC_STATIC_UPDATE)->SetWindowText(str);
}
