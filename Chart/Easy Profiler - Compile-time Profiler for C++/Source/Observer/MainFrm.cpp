// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Observer.h"

#include "MainFrm.h"
#include "uicontroller.h"
#include "ChartControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame


/*
#define  (tabHomeOffset+1)
#define WM_OPEN_TEST_SUITE (tabHomeOffset+2)
#define WM_CONNECT_REMOTE (tabHomeOffset+3)
#define WM_UPDATE_SUITE (tabHomeOffset+4)
#define WM_SET_SUITE_MONITOR (tabHomeOffset+5)*/



IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)	

	ON_COMMAND(WM_SELECT_FILEFOLDER,OnHomeSelectFileFolder)
	ON_COMMAND(WM_SELECT_TEST,OnHomeSelectTestItem)
	ON_COMMAND(WM_UPDATE_SUITE,OnUpdateFileFolder)
	ON_COMMAND(WM_TEST_DESCRIPTION,OnSetTestDescription)
	ON_COMMAND(WM_TESTS_CLOSE,OnCloseFileFolder)
	ON_COMMAND(WM_TEST_DELETE,OnDeleteTest)

/*
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TEXT_ANTILIASING,updateSetTextAntiliasingQuality)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TEXT_ANTILIASING,updateSetTextAntiliasingQuality)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TEXT_ANTILIASING,updateSetTextAntiliasingQuality)
*/



	ON_COMMAND(WM_OPEN_TEST_SUITE,OnOpenTestSuite)
	ON_COMMAND(ID_STATUSBAR_LINK,OnStatusBarWebSiteLink)
	
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,OnPrintPreview)
	ON_COMMAND(ID_FILE_PRINT_SETUP,OnPrintSetup)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,OnPrint)
	ON_COMMAND(ID_FILE_PRINT,OnPrint)


	ON_COMMAND(WM_CHART_DESIGN_PALETTE,voidhandler)
	ON_COMMAND(WM_EXPORT_IMAGE, OnExportImageToFile)
	
	ON_COMMAND_RANGE(ID_PALETTE_GRAYSCALE,ID_PALETTE_FIRE,OnChartPaletteToolCommand)
	ON_COMMAND(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_STACKED,onMenuItem1)
	ON_UPDATE_COMMAND_UI(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_STACKED,onUpdateMenuItem1)
	ON_COMMAND(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_TOTAL,onMenuItem2)
	ON_UPDATE_COMMAND_UI(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_TOTAL,onUpdateMenuItem2)
	//
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	
	//
	ON_COMMAND(WM_OPEN_TEST_FILE,&CMainFrame::OnOpenTestFile)

	ON_COMMAND_RANGE(WM_SUPPORT_CONTENTS, WM_SUPPORT_BLOG, OnSupportToolCommand)

//Chart Tools :
	//Chart Title :	
	ON_COMMAND(WM_CHART_LAYOUT_TITLE,voidhandler)
	ON_COMMAND(ID_CHARTTITLE_NONE,hideChartTitle)
	ON_COMMAND(ID_CHARTTITLE_SHOWOUTSIDE,showChartTitle)
	ON_COMMAND(ID_CHARTTITLE_DOCKTOAREA,dockChartTitle)
	ON_UPDATE_COMMAND_UI(ID_CHARTTITLE_NONE,updateHideChartTitle)
	ON_UPDATE_COMMAND_UI(ID_CHARTTITLE_SHOWOUTSIDE,updateShowChartTitle)
	ON_UPDATE_COMMAND_UI(ID_CHARTTITLE_DOCKTOAREA,updateDockChartTitle)
	//
	ON_COMMAND(WM_CHART_FORMAT_SEL_COMBO,formatSelectionCombo)
	//

	ON_COMMAND(WM_CHART_DESIGN_TYPE_COLUMN,chartTypeColumn)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_LINE,chartTypeLine)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_PIE,chartTypePie)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_HCOLUMN,chartTypeHColumn)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_AREA,chartTypeArea)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_SNOW,chartTypeSnow)
	ON_COMMAND(WM_CHART_DESIGN_TYPE_DOUGHNUT,chartTypeDoughnut)

	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_COLUMN,updateChartTypeColumn)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_LINE,updateChartTypeLine)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_PIE,updateChartTypePie)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_HCOLUMN,updateChartTypeHColumn)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_AREA,updateChartTypeArea)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_SNOW,updateChartTypeSnow)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TYPE_DOUGHNUT,updateChartTypeDoughnut)

	ON_COMMAND(WM_CHART_DESIGN_ENABLE3D,enable3D)
	ON_COMMAND(WM_CHART_DESIGN_WALL_WIDTH,setWallWidth)
	ON_COMMAND(WM_CHART_DESIGN_POINT_DEPTH,setPointDepth)
	ON_COMMAND(WM_CHART_DESIGN_GAP_DEPTH,setGapDepth)
	ON_COMMAND(WM_CHART_DESIGN_PERSPECTIVE,setPerspective)
	ON_COMMAND(WM_CHART_DESIGN_ROTATEX,setRotateX)
	ON_COMMAND(WM_CHART_DESIGN_ROTATEY,setRotateY)

	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_ENABLE3D,updateEnable3D)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_WALL_WIDTH,updateSetWallWidth)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_POINT_DEPTH,updateSetPointDepth)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_GAP_DEPTH,updateSetGapDepth)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_PERSPECTIVE,updateSetPerspective)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_ROTATEX,updateSetRotateX)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_ROTATEY,updateSetRotateY)

	//
	ON_COMMAND(WM_CHART_FORMAT_TEXT,setText)
	ON_COMMAND(WM_CHART_FORMAT_FILL_COLOR1,setFillColor1)
	ON_COMMAND(WM_CHART_FORMAT_FILL_COLOR2,setFillColor2)
	ON_COMMAND(WM_CHART_FORMAT_FILL_GRADIENT,setGradient)
	ON_COMMAND(WM_CHART_FORMAT_FILL_HATCH,setHatchStyle)
	//
	ON_COMMAND(WM_CHART_FORMAT_OUTLINE_COLOR,setOutlineColor)
	ON_COMMAND(WM_CHART_FORMAT_OUTLINE_STYLE,setOutlineStyle)
	ON_COMMAND(WM_CHART_FORMAT_OUTLINE_SIZE,setOutlineSize)

	ON_COMMAND(WM_CHART_FORMAT_ORIENTATION_ALIGN,setAlign)
	ON_COMMAND(WM_CHART_FORMAT_ORIENTATION_DOCKING,setDocking)
	ON_COMMAND(WM_CHART_FORMAT_ORIENTATION_REVERSE,setReverse)
	//

	ON_COMMAND_RANGE(tabAnalysis, tabAnalysisEnd, OnAnalysisToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(tabAnalysis, tabAnalysisEnd, OnUpdateAnalysisToolCommand)

	ON_COMMAND(WM_ANALYSIS_TEST_SELECT,onAnalysisSelectTest)
	ON_COMMAND(WM_ANALYSIS_ITEM_SELECT,onAnalysisSelectItem)

	ON_COMMAND(WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL,onAnalysisSingleActivitySelTask)
	ON_COMMAND(WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL,onAnalysisSingleActivitySelWorker)
	ON_COMMAND(WM_ANALYSIS_SINGLEWORKER_CB_SELTASK,onAnalysisSingleWorkerSelTask)

	//////////////////////////////////////////////////////////////////////////
	ON_COMMAND_RANGE(tabCompare, tabCompareEnd, OnCompareToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(tabCompare, tabCompareEnd, OnUpdateCompareToolCommand)

	ON_COMMAND(WM_COMPARE_FOCUS_SELTEST,onCompareSelectTest)
	ON_COMMAND(WM_COMPARE_FOCUS_SELITEM,onCompareSelectItem)
	ON_COMMAND(WM_COMPARE_SINGLEACTIVITY_SELTASK,onCompareSingleActivitySelTask)
	ON_COMMAND(WM_COMPARE_SINGLEACTIVITY_SELWORKER,OnCompareSingleActivitySelWorker)
	ON_COMMAND(WM_COMPARE_SINGLEWORKER_SELTASK,onCompareSingleWorkerSelTask)

	//Chart Layout :
	ON_COMMAND(WM_CHART_LAYOUT_AXIS_TITLES,onChartLayout_AxisTitles)
	ON_COMMAND_RANGE(ID_XAXIS_SHOW, ID_YAXIS_DONOTSHOW, onChartLayout_AxisTitlesToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_XAXIS_SHOW, ID_YAXIS_DONOTSHOW, OnUpdateChartLayout_AxisTitlesToolCommand)
	//
	ON_COMMAND(WM_CHART_LAYOUT_LEGEND, onChartLayout_ShowLegend)
	ON_UPDATE_COMMAND_UI(WM_CHART_LAYOUT_LEGEND,OnUpdateChartLayout_ShowLegend)
	//
	ON_COMMAND(WM_CHART_LAYOUT_POINTS_LABELS, onChartLayout_ShowPointsLabels)
	ON_UPDATE_COMMAND_UI(WM_CHART_LAYOUT_POINTS_LABELS,OnUpdateChartLayout_ShowPointsLabels)
	//
	ON_COMMAND(WM_CHART_LAYOUT_AXIS,onChartLayout_Axis)
	ON_COMMAND_RANGE(ID_AXIS_XAXIS_SHOW, ID_AXIS_YAXIS_DONOTSHOW, onChartLayout_AxisToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_AXIS_XAXIS_SHOW, ID_AXIS_YAXIS_DONOTSHOW, OnUpdateChartLayout_AxisToolCommand)
	//
	ON_COMMAND(WM_CHART_LAYOUT_GRID, onChartLayout_ShowGrid)
	//
	//
	ON_COMMAND(WM_CHART_FORMAT_FONT_NAME ,onFontName)
	ON_COMMAND(WM_CHART_FORMAT_FONT_SIZE ,onFontSize)
	//Docking :
	ON_COMMAND_RANGE(ID_CHART_DOCK_TOP, ID_CHART_DOCK_BOTTOM, OnDockingToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CHART_DOCK_TOP, ID_CHART_DOCK_BOTTOM, OnUpdateDockingToolCommand)
	//Align :
	ON_COMMAND_RANGE(ID_ALIGN_MIDDLECENTER, ID_ALIGN_BOTTOMRIGHT, OnAlignToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ALIGN_MIDDLECENTER, ID_ALIGN_BOTTOMRIGHT, OnUpdateAlignToolCommand)
	//Outline Style :
	ON_COMMAND_RANGE(ID_OUTLINESTYLE_NOTSET, ID_OUTLINESTYLE_SOLID, OnOutlineStyleToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OUTLINESTYLE_NOTSET, ID_OUTLINESTYLE_SOLID, OnUpdateOutlineStyleToolCommand)
	//Shape Gradient :
	ON_COMMAND_RANGE(ID_GRADIENT_NONE, ID_GRADIENT_VERTICALCENTER, onShapeGradientToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GRADIENT_NONE, ID_GRADIENT_VERTICALCENTER, onUpdateShapeGradientToolCommand)
	//Shape Hatching
	ON_COMMAND_RANGE(ID_HATCHING_NONE, ID_HATCHING_VERTICAL, onShapeHatchingToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_HATCHING_NONE, ID_HATCHING_VERTICAL, onUpdateHatchingToolCommand)
	//Outline Width :
	ON_COMMAND_RANGE(ID_OUTLINE_WIDTH_1, ID_OUTLINE_WIDTH_4, onOutlineWidthToolCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OUTLINE_WIDTH_1, ID_OUTLINE_WIDTH_4, onUpdateOutlineWidthToolCommand)
	//Format Size X and Y :
	ON_COMMAND(WM_CHART_FORMAT_SIZEX,OnFormatSizeX)
	ON_COMMAND(WM_CHART_FORMAT_SIZEY,OnFormatSizeY)

	//
	ON_COMMAND(ID_FONT_BOLD,OnFont_Bold)
	ON_COMMAND(ID_FONT_ITALIC,OnFontItalic)
	ON_COMMAND(ID_FONT_STRIKETHROUGH,OnFontStroke)
	ON_COMMAND(ID_FONT_UNDERLINE,OnFontUnderline)
	ON_COMMAND(ID_FONT_SUBSCRIPT,OnFontLeft)
	ON_COMMAND(ID_FONT_SUPERSCRIPT,OnFontCenter)
	ON_COMMAND(ID_FONT_CHANGECASE,OnFontRight)
	//
	ON_COMMAND(WM_CHART_DESIGN_GRAPHICS_ANTILIASING,setGraphicsAntiliasing)
	ON_COMMAND(WM_CHART_DESIGN_TEXT_ANTILIASING,setTextAntiliasingQuality)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_GRAPHICS_ANTILIASING,updateSetGraphicsAntiliasing)
	ON_UPDATE_COMMAND_UI(WM_CHART_DESIGN_TEXT_ANTILIASING,updateSetTextAntiliasingQuality)

END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	/*
CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

*/
	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	strTitlePane1=_T("Ready");
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);


	m_wndStatusBar.AddExtendedElement(new CMFCRibbonLinkCtrl(ID_STATUSBAR_LINK, _T("www.potatosoftware.com"), _T("http://www.potatosoftware.com")), _T("Visit Potato software Website"));

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Create and setup "Outlook" navigation bar:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, 250))
	{
		TRACE0("Failed to create navigation pane\n");
		return -1;      // fail to create
	}

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	EnableDocking(CBRS_ALIGN_ANY);


	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}



BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, int nInitialWidth)
{
	CWindowDC dc(NULL);

	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // fail to create
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);

	m_TreeBar.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,rectDummy,&bar,1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&m_TreeBar, _T("Test data"), 0, TRUE, dwStyle);

	m_selectionPane.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,rectDummy, &bar, 1201);
	pOutlookBar->AddControl(&m_selectionPane, _T("Compare target"), 1, TRUE, dwStyle);



	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnOpenTestFile()
{
	theMachine.openHistoryFile();
}
void CMainFrame::OnOpenTestSuite()
{
	theMachine.OnOpenTestSuite();
}
void CMainFrame::hideChartTitle()
{
	chartControl.chartTitle.SetLayout(CChartControl::Hide);
}

void CMainFrame::showChartTitle()
{
	chartControl.chartTitle.SetLayout(CChartControl::Show);
}

void CMainFrame::dockChartTitle()
{
	chartControl.chartTitle.SetLayout(CChartControl::Dock);
}

void CMainFrame::updateHideChartTitle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(chartControl.chartTitle.layout== CChartControl::Hide ? 1 : 0);
}

void CMainFrame::updateShowChartTitle( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.chartTitle.layout== CChartControl::Show ? 1 : 0);
}

void CMainFrame::updateDockChartTitle( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.chartTitle.layout== CChartControl::Dock ? 1 : 0);
}

void CMainFrame::formatSelectionCombo()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
	{
		return;
	}
	chartControl.setSelectedFormatItem(pFormatSelCombo->GetCurSel());
}

void CMainFrame::chartTypeColumn()
{
	chartControl.setChartType(CChartControl::Column);
}

void CMainFrame::chartTypeLine()
{
	chartControl.setChartType(CChartControl::Spline);
}

void CMainFrame::chartTypePie()
{
	chartControl.setChartType(CChartControl::Pie);
}

void CMainFrame::chartTypeHColumn()
{
	chartControl.setChartType(CChartControl::HColumn);
}

void CMainFrame::chartTypeArea()
{
	chartControl.setChartType(CChartControl::Area);
}

void CMainFrame::chartTypeSnow()
{
	chartControl.setChartType(CChartControl::Snow);
}

void CMainFrame::chartTypeDoughnut()
{
	chartControl.setChartType(CChartControl::Doughnut);
}

void CMainFrame::updateChartTypeColumn(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Column);
}

void CMainFrame::updateChartTypeLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Spline);
}

void CMainFrame::updateChartTypePie(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Pie);
}

void CMainFrame::updateChartTypeHColumn(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::HColumn);
}

void CMainFrame::updateChartTypeArea(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Area);
}

void CMainFrame::updateChartTypeSnow(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Snow);
}

void CMainFrame::updateChartTypeDoughnut(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(chartControl.chartType==CChartControl::Doughnut);
}

void CMainFrame::enable3D()
{
	chartControl.setGlobalBoolProperty(CChartControl::PropEnable3D,!chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::setWallWidth()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_WALL_WIDTH));
	chartControl.setGlobalIntProperty(CChartControl::PropWallWidth,_ttoi(pEdit->GetEditText()));	
}

void CMainFrame::setPointDepth()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_POINT_DEPTH));
	chartControl.setGlobalIntProperty(CChartControl::PropPointDepth,_ttoi(pEdit->GetEditText()));	
}

void CMainFrame::setGapDepth()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_GAP_DEPTH));
	chartControl.setGlobalIntProperty(CChartControl::PropGapDepth,_ttoi(pEdit->GetEditText()));
}

void CMainFrame::setPerspective()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_PERSPECTIVE));
	chartControl.setGlobalIntProperty(CChartControl::PropPerspective,_ttoi(pEdit->GetEditText()));
}

void CMainFrame::setRotateX()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_ROTATEX));
	chartControl.setGlobalIntProperty(CChartControl::PropRotateX,_ttoi(pEdit->GetEditText()));
}

void CMainFrame::setRotateY()
{
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_ROTATEY));
	chartControl.setGlobalIntProperty(CChartControl::PropRotateY,_ttoi(pEdit->GetEditText()));
}

void CMainFrame::updateEnable3D( CCmdUI* pCmdUI )
{
	pCmdUI->SetRadio(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::updateSetWallWidth( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));

	/*
	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_DESIGN_WALL_WIDTH));
		if (pEdit == NULL)
		{
			return;
		}
		CString str;
		str.Format(_T("%d"),chartControl.getGlobalIntProperty(CChartControl::PropWallWidth));
		pEdit->SetEditText(str);*/
	
}

void CMainFrame::updateSetPointDepth( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::updateSetGapDepth( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::updateSetPerspective( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::updateSetRotateX( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}

void CMainFrame::updateSetRotateY( CCmdUI* pCmdUI )
{
	pCmdUI->Enable(chartControl.getGlobalBoolProperty(CChartControl::PropEnable3D));
}



void CMainFrame::setGradient()
{
	//
}
void CMainFrame::setHatchStyle()
{
	//
}
void CMainFrame::setText()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();
	//
	//AfxMessageBox(pFormatSelCombo->GetItem(iFormatElement));

	CMFCRibbonEdit* pTextEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_TEXT));
	//
	//AfxMessageBox(pTextEdit->GetEditText());

	chartControl.setFormat(iFormatElement,CChartControl::Format_Text,pTextEdit->GetEditText());
}

/////////// HANDLING COMBOS ////////////////////////////////////////////////////////////
//Analysis :
void CMainFrame::onAnalysisSelectTest()
{
	//Synchrnoize the feature target combos with the new selected test.
	theMachine.updateAnalysisFeatureTargetCombos();
}
void CMainFrame::onAnalysisSelectItem()
{
	//Nothing, this remains empty.
}

void CMainFrame::onAnalysisSingleActivitySelTask()
{
	//Nothing, this remains empty
}
void CMainFrame::onAnalysisSingleWorkerSelTask()
{
	//Nothing, this remains empty
}
void CMainFrame::onAnalysisSingleActivitySelWorker()
{
	//Nothing, this remains empty
}
//The remaining tools commands :
void CMainFrame::OnAnalysisToolCommand( UINT id )
{
	CString str;
	str.Format(_T(" OnAnalysisToolCommand  :  %d"),id);

	//AfxMessageBox(str);

	theMachine.routeAnalysisCommand(id);
}

///Compare :
void CMainFrame::onCompareSelectTest()
{
	theMachine.updateCompareFeatureTargetCombos();
}
void CMainFrame::onCompareSelectItem()
{
	//Nothing, this remains empty
}
void CMainFrame::onCompareSingleActivitySelTask()
{
	//Nothing, this remains empty
}
void CMainFrame::OnCompareSingleActivitySelWorker()
{
	//Nothing, this remains empty
}
void CMainFrame::onCompareSingleWorkerSelTask()
{
	//Nothing, this remains empty
}

void CMainFrame::OnCompareToolCommand( UINT id )
{
	/*
CString str;
	str.Format(_T(" OnCompareToolCommand  :  %d"),id);

	AfxMessageBox(str);
*/

	theMachine.routeCompareCommand(id);
}
void CMainFrame::OnUpdateCompareToolCommand( CCmdUI* pCmdUI )
{
	pCmdUI->SetRadio(pCmdUI->m_nID==theMachine.getCurToolCommandID());
}

void CMainFrame::OnUpdateAnalysisToolCommand( CCmdUI* pCmdUI )
{
	pCmdUI->SetRadio(pCmdUI->m_nID==theMachine.getCurToolCommandID());
}

void CMainFrame::OnSupportToolCommand( UINT id )
{
	if(id==WM_SUPPORT_CONTENTS){
		PostMessage(ID_HELP_FINDER);
		
		//HtmlHelp(NULL,HH_DISPLAY_TOPIC);
	}
	if(id==WM_SUPPORT_TIPOFTHEDAY)
	{
		CTipOfTheDayDlg TipDialog;
		TipDialog.DoModal();
	}
	if (id==WM_SUPPORT_HELPDESK)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/redir/?linkID=5"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_FORUMS)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/redir/?linkID=6"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_TUTORIALS)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/redir/?linkID=4"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_FAQ)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/index.php?option=com_content&view=article&id=67&Itemid=78"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_UPDATE)
		::ShellExecute (NULL, NULL, _T("http://code.google.com/p/easyprofiler/downloads/list"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_COPYRIGHT)
		::ShellExecute (NULL, NULL, _T("http://www.apache.org/licenses/LICENSE-2.0"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_VISIT)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_INVITE)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/redir/?linkID=5"), NULL, NULL, NULL);
	if (id==WM_SUPPORT_NEWS)
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/index.php?option=com_potatonews&view=list&Itemid=83"), NULL, NULL, NULL);

	if(id==WM_SUPPORT_MAILSUPPORT)
	{
		::ShellExecute (NULL, NULL, _T("mailto:support@potatosoftware.com?subject=Easy Profiler"), NULL, NULL, NULL);
	}
	if (id==WM_SUPPORT_PARTNER)
	{
		::ShellExecute (NULL, NULL, _T("mailto:info@potatosoftware.com?subject=Partner"), NULL, NULL, NULL);
	}
	if (id == WM_SUPPORT_CODE_PROJECT)
	{
		//Link to code project article.
		//Once the article is published, linkID 13 will point to the new address.
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/redir?linkID=13"), NULL, NULL, NULL);
	}
	if (id == WM_SUPPORT_GOOGLE_CODE)
	{
		::ShellExecute (NULL, NULL, _T("http://code.google.com/p/easyprofiler/"), NULL, NULL, NULL);
	}
	if (id == WM_SUPPORT_BLOG)
	{
		::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com/index.php?option=com_myblog&Itemid=93"), NULL, NULL, NULL);
	}
	
	if (id==WM_SUPPORT_ABOUT)
	{
		CAboutDlg aboutDlg;
		aboutDlg.DoModal();
	}
	if (id == WM_SUPPORT_ACTIVATE_PRODUCT || id==WM_SUPPORT_LICENCEKEY)
	{
		AfxMessageBox(_T("One day this will be implemented ! :)"));
	}

}

void CMainFrame::onFontName()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	CMFCRibbonFontComboBox* pFontNameCombo = DYNAMIC_DOWNCAST(CMFCRibbonFontComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_FONT_NAME));
	if (pFontNameCombo == NULL)
		return;
	


	chartControl.setFormat(iFormatElement,CChartControl::Format_FontName,pFontNameCombo->GetEditText());
	
	/*
	const CMFCFontInfo* pFontInfo=pFontNameCombo->GetFontDesc(pFontNameCombo->GetCurSel());
	
		pFontInfo->
		AfxMessageBox(pFontInfo->GetFullName());*/
	

	return;
	

}

void CMainFrame::onFontSize()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	CMFCRibbonComboBox* pFonSize = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_FONT_SIZE));
	if (pFonSize == NULL)
		return;


	chartControl.setFormat(iFormatElement,CChartControl::Format_FontSize,pFonSize->GetEditText());

	//
}
void CMainFrame::OnDockingToolCommand( UINT id )
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	/*
	#define ID_CHART_DOCK_TOP               32829
	#define ID_CHART_DOCK_LEFT              32830
	#define ID_CHART_DOCK_RIGHT             32831
	#define ID_CHART_DOCK_BOTTOM            32832

	*/
	CString str;
	str.Format(_T("%d"),id-ID_CHART_DOCK_TOP);
	chartControl.setFormat(iFormatElement,CChartControl::Format_OrientationDocking,str);
}
void CMainFrame::OnAlignToolCommand( UINT id )
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	/*
	#define ID_ALIGN_MIDDLECENTER           32811
	#define ID_ALIGN_TOPLEFT                32812
	#define ID_ALIGN_TOPCENTER              32813
	#define ID_ALIGN_TOPRIGHT               32814
	#define ID_ALIGN_MIDDLELEFT             32815
	#define ID_ALIGN_MIDDLERIGHT            32816
	#define ID_ALIGN_BOTTOMCENTER           32817
	#define ID_ALIGN_BOTTOMLEFT             32818
	#define ID_ALIGN_BOTTOMRIGHT            32819
	*/
	CString str;
	str.Format(_T("%d"),id-ID_ALIGN_MIDDLECENTER);
	chartControl.setFormat(iFormatElement,CChartControl::Format_OrientationAlignment,str);

}
void CMainFrame::OnOutlineStyleToolCommand( UINT id )
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	/*
	#define ID_OUTLINESTYLE_NOTSET          33100
	#define ID_OUTLINESTYLE_DASH            33101
	#define ID_OUTLINESTYLE_DASHDOT         33102
	#define ID_OUTLINESTYLE_DASHDOTDOT      33103
	#define ID_OUTLINESTYLE_DOT             33104
	#define ID_OUTLINESTYLE_SOLID           33105
	*/
	CString str;
	str.Format(_T("%d"),id-ID_OUTLINESTYLE_NOTSET);
	chartControl.setFormat(iFormatElement,CChartControl::Format_OutlineStyle,str);
}

void CMainFrame::setFillColor1()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	CMFCRibbonColorButton* pFillColor1Combo = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_FILL_COLOR1));
	if (pFillColor1Combo == NULL)
		return;

	CString str;
	str.Format(_T("%.3d%.3d%.3d"),GetRValue(pFillColor1Combo->GetColor()),
		GetGValue(pFillColor1Combo->GetColor()),
		GetBValue(pFillColor1Combo->GetColor()));
	AfxMessageBox(str);

	chartControl.setFormat(iFormatElement,CChartControl::Format_ShapeColor1,str);
}

void CMainFrame::setFillColor2()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	CMFCRibbonColorButton* pFillColor2Combo = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_FILL_COLOR2));
	if (pFillColor2Combo == NULL)
		return;

	CString str;
	str.Format(_T("%.3d%.3d%.3d"),GetRValue(pFillColor2Combo->GetColor()),
		GetGValue(pFillColor2Combo->GetColor()),
		GetBValue(pFillColor2Combo->GetColor()));
	AfxMessageBox(str);

	

	chartControl.setFormat(iFormatElement,CChartControl::Format_ShapeColor2,str);

}
void CMainFrame::onShapeGradientToolCommand( UINT id )
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	/*
	#define ID_GRADIENT_NONE                32777
	#define ID_GRADIENT_LEFTRIGHT           32778
	#define ID_GRADIENT_TOPBOTTOM           32779
	#define ID_GRADIENT_CENTER              32780
	#define ID_GRADIENT_DIAGONALLEFT        32781
	#define ID_GRADIENT_DIAGONALRIGHT       32782
	#define ID_GRADIENT_HORIZONTALCENTER    32783
	#define ID_GRADIENT_VERTICALCENTER      32784
	*/
	CString str;
	str.Format(_T("%d"),id-ID_GRADIENT_NONE);
	chartControl.setFormat(iFormatElement,CChartControl::Format_ShapeGradient,str);

}

void CMainFrame::onShapeHatchingToolCommand( UINT id )
{	
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	/*
	#define ID_HATCHING_NONE                32853
	#define ID_HATCHING_CROSS               32854
	#define ID_HATCHING_DIVOT               32855
	#define ID_HATCHING_HORIZONTAL          32856
	#define ID_HATCHING_VERTICAL            32857
	*/
	CString str;
	str.Format(_T("%d"),id-ID_HATCHING_NONE);
	chartControl.setFormat(iFormatElement,CChartControl::Format_ShapeHatch,str);

}

void CMainFrame::setOutlineColor()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	CMFCRibbonColorButton* pOutlineColorBtn = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_OUTLINE_COLOR));
	if (pOutlineColorBtn == NULL)
		return;

	CString str;
	str.Format(_T("%.3d%.3d%.3d"),GetRValue(pOutlineColorBtn->GetColor()),
		GetGValue(pOutlineColorBtn->GetColor()),
		GetBValue(pOutlineColorBtn->GetColor()));
	AfxMessageBox(str);



	chartControl.setFormat(iFormatElement,CChartControl::Format_OutlineColor,str);
}
void CMainFrame::onOutlineWidthToolCommand( UINT id )
{
	

	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	/*
	#define ID_OUTLINE_WIDTH_1              
	#define ID_OUTLINE_WIDTH_2              
	#define ID_OUTLINE_WIDTH_3              
	#define ID_OUTLINE_WIDTH_4              
	*/
	CString str;
	str.Format(_T("%d"),id-ID_OUTLINE_WIDTH_1+1);
	chartControl.setFormat(iFormatElement,CChartControl::Format_OutlineSize,str);

}
void CMainFrame::OnFormatSizeY()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SIZEX));
	chartControl.setFormat(iFormatElement,CChartControl::Format_SizeWidth,pEdit->GetEditText());
}
void CMainFrame::OnFormatSizeX()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();


	CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SIZEY));
	chartControl.setFormat(iFormatElement,CChartControl::Format_SizeLength,pEdit->GetEditText());
}
void CMainFrame::setReverse()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_OrientationReverse,_T(""));
}

void CMainFrame::OnFontRight()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontRight,_T(""));


}
void CMainFrame::OnFontCenter()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontCenter,_T(""));


}
void CMainFrame::OnFontLeft()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontLeft,_T(""));


}
void CMainFrame::OnFontStroke()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontDeleted,_T(""));


}
void CMainFrame::OnFontItalic()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontItalic,_T(""));


}
void CMainFrame::OnFontUnderline()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontUnderline,_T(""));

}
void CMainFrame::OnFont_Bold()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
		return;
	int iFormatElement=pFormatSelCombo->GetCurSel();

	chartControl.setFormat(iFormatElement,CChartControl::Format_FontBold,_T(""));

}
void CMainFrame::onChartLayout_AxisToolCommand( UINT id )
{
	/*
	#define ID_AXIS_XAXIS_SHOW              32848
	#define ID_AXIS_XAXIS_DONOTSHOW         32849
	#define ID_AXIS_YAXIS_SHOW              32850
	#define ID_AXIS_YAXIS_DONOTSHOW         32851
	*/
	chartControl.setGlobalIntProperty(CChartControl::PropAxisShowState,id-ID_AXIS_XAXIS_SHOW);
}
void CMainFrame::OnUpdateChartLayout_ShowPointsLabels( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.getGlobalBoolProperty(CChartControl::PropDataLabelShowState));
}
void CMainFrame::onChartLayout_ShowPointsLabels()
{
	chartControl.setGlobalIntProperty(CChartControl::PropDataLabelShowState,0);
}
void CMainFrame::OnUpdateChartLayout_ShowLegend( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.getGlobalBoolProperty(CChartControl::PropLegendShowState));
}
void CMainFrame::onChartLayout_ShowLegend()
{
	chartControl.setGlobalIntProperty(CChartControl::PropLegendShowState,0);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::setTextAntiliasingQuality()
{
	chartControl.setGlobalIntProperty(CChartControl::PropTextAntiliasingQuality,0);
}
void CMainFrame::setGraphicsAntiliasing()
{
	chartControl.setGlobalIntProperty(CChartControl::PropGraphicsAntiliasing,0);
}
void CMainFrame::updateSetTextAntiliasingQuality( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.getGlobalBoolProperty(CChartControl::PropTextAntiliasingQuality));
}
void CMainFrame::updateSetGraphicsAntiliasing( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck(chartControl.getGlobalBoolProperty(CChartControl::PropGraphicsAntiliasing));
}
void CMainFrame::OnChartPaletteToolCommand( UINT id )
{
	chartControl.setGlobalIntProperty(CChartControl::PropChartPalette,id-ID_PALETTE_GRAYSCALE);
}


void CMainFrame::OnExportImageToFile()
{
	TCHAR  szFilters[]=
		_T("Bitmap (*.bmp)|*.bmp|JPEG (*.jpg)|*.jpg|EMF (*.emf)|*.emf|PNG (*.png)|*.png|GIF (*.gif)|*.gif|TIFF (*.tif)|*.tif");
	CFileDialog fileDlg(TRUE,_T("bmp"),_T("*.bmp"),0,szFilters);
	if( fileDlg.DoModal ()!=IDOK )
	{
		return;
	}
	
	chartControl.saveImageToFile(fileDlg.GetPathName(),fileDlg.GetFileExt());

}
void CMainFrame::OnPrint()
{
	chartControl.printPreview(2);
}
void CMainFrame::OnPrintSetup()
{
	chartControl.printPreview(0);
}
void CMainFrame::OnPrintPreview()
{
	chartControl.printPreview(1);
}
void CMainFrame::OnStatusBarWebSiteLink()
{
	CMFCRibbonLinkCtrl* pLink = (CMFCRibbonLinkCtrl*) m_wndStatusBar.FindByID(ID_STATUSBAR_LINK);

	if (pLink != NULL)
	{
		pLink->OpenLink();
	}
}
void CMainFrame::SetStatusBarText( CString text )
{
	CMFCRibbonStatusBarPane* pInfoBar = DYNAMIC_DOWNCAST (
		CMFCRibbonStatusBarPane,
		m_wndStatusBar.FindElement (ID_STATUSBAR_PANE1));
	ASSERT_VALID (pInfoBar);

	pInfoBar->SetAlmostLargeText(text);
	pInfoBar->SetText (text);

	m_wndStatusBar.RecalcLayout ();
	m_wndStatusBar.RedrawWindow ();

	pInfoBar->Redraw ();
}

//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnDeleteTest()
{
	theMachine.OnDeleteTest();
}
void CMainFrame::OnCloseFileFolder()
{
	theMachine.OnCloseFileFolder();
}
void CMainFrame::OnSetTestDescription()
{
	theMachine.OnSetTestDescription();
}
void CMainFrame::OnUpdateFileFolder()
{
	theMachine.OnUpdateFileFolder();
}
void CMainFrame::OnHomeSelectTestItem()
{
	//Nothing !
}
void CMainFrame::OnHomeSelectFileFolder()
{
	theMachine.updateTestHomeCombo();
}