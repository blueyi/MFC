/********************************************************************
    File:	        MyRibbonBar	
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
// MyRibbonBar.cpp : implementation file
//

#include "stdafx.h"
#include "Observer.h"
#include "MyRibbonBar.h"

#include "ChartControl.h"
// CMyRibbonBar

IMPLEMENT_DYNAMIC(CMyRibbonBar, CMFCRibbonBar)

CMyRibbonBar::CMyRibbonBar()
{
	CreateDocumentColors();
	chartControl.setRibbonBar(this);

}

CMyRibbonBar::~CMyRibbonBar()
{
}

void CMyRibbonBar::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// Load panel images:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// Init main button:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(WM_OPEN_TEST_FILE, _T("Open.."), 1, 1));
	pMainPanel->Add(new CMFCRibbonButton(WM_OPEN_TEST_SUITE, _T("Open Suite.."), 1, 1));


	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(WM_EXPORT_IMAGE, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	/*
	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
		ASSERT(bNameValid);
		pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));*/
	

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	
	addTabHome();
	addTabAnalyze();
	addTabCompare();
//	addTabExport();
	addTabAddins();
	addChartTools();
	ShowContextCategories(IDB_CHART);
	ActivateContextCategory(IDB_CHART);

	addTabSupport();


	// Add elements to the right side of tabs:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* No default command */, TRUE /* Right align */);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	AddToTabs(pVisualStyleButton);

	// Add quick access toolbar commands:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	SetQuickAccessCommands(lstQATCmds);
	AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}


BEGIN_MESSAGE_MAP(CMyRibbonBar, CMFCRibbonBar)
END_MESSAGE_MAP()



// CMyRibbonBar message handlers


void CMyRibbonBar::addTabHome()
{
	BOOL bNameValid;
	CString strTemp;


	CMFCRibbonCategory* pCategory = AddCategory(_T("Home"), IDB_WRITESMALL, IDB_WRITELARGE);

	// Create panel:
	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Connect to Data Sources"), m_PanelImages.ExtractIcon(3));

	pPanel->Add(new CMFCRibbonButton(WM_OPEN_TEST_FILE, _T("Single Test file"), -1, 5));
	pPanel->Add(new CMFCRibbonButton(WM_OPEN_TEST_SUITE, _T("Test suite"), -1, 4));
	pPanel->Add(new CMFCRibbonButton(WM_CONNECT_REMOTE, _T("connect to remote source"), -1, 1));

	pPanel = pCategory->AddPanel(_T("Edit and Synchronize"), m_PanelImages.ExtractIcon(3));


	pPanel->Add(new CMFCRibbonLabel(_T("Set Focus :")));
	CMFCRibbonComboBox* pCombo= new CMFCRibbonComboBox(WM_SELECT_FILEFOLDER, TRUE, -1,_T("Select File/Folder"),0);
	pPanel->Add(pCombo);
	pCombo = new CMFCRibbonComboBox(WM_SELECT_TEST, TRUE, -1,_T("Select Test"),7);
	pPanel->Add(pCombo);

	pPanel->SetJustifyColumns();



	pPanel->Add(new CMFCRibbonButton(WM_UPDATE_SUITE, _T("Update tests"), -1, 3));


	pPanel->InsertSeparator(5);

	pPanel->Add(new CMFCRibbonButton(WM_TEST_DESCRIPTION, _T("Description"), -1, 8));
	pPanel->Add(new CMFCRibbonButton(WM_TEST_DELETE, _T("Delete"), -1, 6));
	pPanel->Add(new CMFCRibbonButton(WM_TESTS_CLOSE, _T("Close"), -1, 7));

}

void CMyRibbonBar::addTabAnalyze()
{
	CMFCRibbonCategory* pCategory = AddCategory(_T("Analyze"), IDB_ANALYZE16, IDB_ANALYZE);

	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Selection"), m_PanelImages.ExtractIcon(13));

	pPanel->Add(new CMFCRibbonLabel(_T("Set Focus :")));
	CMFCRibbonComboBox* pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_TEST_SELECT, TRUE, -1,_T("Select Test"),0);
	/*
	pSelectionCB->AddItem(_T("Test1"),0);
		pSelectionCB->AddItem(_T("Test2"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);

	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_ITEM_SELECT, TRUE, -1,_T("Select Item"),7);
	/*
	pSelectionCB->AddItem(_T("ActivityA"),0);
		pSelectionCB->AddItem(_T("Task T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);

	pPanel->SetJustifyColumns();

	//
	pPanel = pCategory->AddPanel(_T("Single Activity"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_TIMELINE, _T("TimeLines"), -1, 0));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_STAGES, _T("Clustered stages"), -1, 2));
	//pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_TOTALTIME, _T("Total Times"), -1, 0));
		//send to compare.
	
	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL, TRUE, -1,_T("Task :"),3);
	pPanel->Add(pSelectionCB);

	CMFCRibbonButton* pBtn = new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_STACKED, _T("Stacked"), 0, 1);
	pBtn->SetMenu(IDR_MENU_RIBBON_ACTIVITY1, TRUE);
	pPanel->Add(pBtn);

	pBtn = new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_TOTAL, _T("Total Times"), 0, 4);
	pBtn->SetMenu(IDR_MENU_RIBBON_ACTIVITY2, TRUE);
	pPanel->Add(pBtn);

	//
	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Worker :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL, TRUE, -1,_T("Thread :"),1);
/*
	pSelectionCB->AddItem(_T("Worker T0"),0);
	pSelectionCB->AddItem(_T("Thread T1"));
	pSelectionCB->SelectItem(0);*/

	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHWORKER_TOTALTIME, _T("Time Total"), 0, 5));

	pPanel = pCategory->AddPanel(_T("All Activities"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLACTIVITIES_TOTAL, _T("Total time"), 0, 3));


	pPanel = pCategory->AddPanel(_T("Single Task"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLETASK_RUNSHISTORY, _T("Runs History"), 0, 6));
	//pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLETASK_TOTAL, _T("Total Time"), 0, 0));
		//send to compare.

	pPanel = pCategory->AddPanel(_T("All Tasks"), m_PanelImages.ExtractIcon(19));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLTASKS_TOTAL, _T("Total Time"), 0, 10));
			//add average time ?



	pPanel = pCategory->AddPanel(_T("Worker"), m_PanelImages.ExtractIcon(17));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_RUNPAUSE, _T("Run|Pause Time"), 0, 12));
	pPanel->AddSeparator();

	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEWORKER_CB_SELTASK, TRUE, -1,_T("Task :"),3);
	/*
	pSelectionCB->AddItem(_T("Task T0"),0);
		pSelectionCB->AddItem(_T("Task T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_WITHTASK_MULTIPLESTACKED, _T("Multiple Stacked"), 0, 13));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_WITHTASK_TIMETOTAL, _T("Time Total"), 0, 14));

	pPanel = pCategory->AddPanel(_T("All Workers"), m_PanelImages.ExtractIcon(27));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLWORKERS_TOTAL, _T("Total Times"), 0, 11));


	/*
pPanel = pCategory->AddPanel(_T("Tasks and activity"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Pie"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Pie"), 0, 0));

	pPanel = pCategory->AddPanel(_T("Tasks and thread"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Pie"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Pie"), 0, 0));

	pPanel = pCategory->AddPanel(_T("Threads and activity"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("All Threads Column"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("all Threads Vs Activity Time two columns"), 0, 0));
*/


}

void CMyRibbonBar::addTabCompare()
{
	CMFCRibbonCategory* pCategory = AddCategory(_T("Compare"), IDB_ANALYZE16, IDB_COMPARE);

	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Selection"), m_PanelImages.ExtractIcon(13));

	pPanel->Add(new CMFCRibbonLabel(_T("Set Focus :")));
	CMFCRibbonComboBox* pSelectionCB = new CMFCRibbonComboBox(WM_COMPARE_FOCUS_SELTEST, TRUE, -1,_T("Select Test"),0);
/*
	pSelectionCB->AddItem(_T("Test1"),0);
	pSelectionCB->AddItem(_T("Test2"));
	pSelectionCB->SelectItem(0);*/

	pPanel->Add(pSelectionCB);

	pSelectionCB = new CMFCRibbonComboBox(WM_COMPARE_FOCUS_SELITEM, TRUE, -1,_T("Select Item"),7);
/*
	pSelectionCB->AddItem(_T("ActivityA"),0);
	pSelectionCB->AddItem(_T("Task T1"));
	pSelectionCB->SelectItem(0);*/

	pPanel->Add(pSelectionCB);

	pPanel->SetJustifyColumns();

//
	pPanel = pCategory->AddPanel(_T("Single Activity"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEACTIVITY_TIMELINE, _T("Show TimeLine"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEACTIVITY_STAGES, _T("Differenced events"), -1, 1));

	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_COMPARE_SINGLEACTIVITY_SELTASK, TRUE, -1,_T("Task :"),3);
/*
	pSelectionCB->AddItem(_T("Task T0"),0);
	pSelectionCB->AddItem(_T("Task T1"));
	pSelectionCB->SelectItem(0);*/

	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEACTIVITY_WITHTASK_STACKED, _T("Stacked"), 0, 2));
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEACTIVITY_WITHTASK_TOTAL, _T("Total Times"), 0, 3));
	//
	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Worker :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_COMPARE_SINGLEACTIVITY_SELWORKER, TRUE, -1,_T("Thread :"),1);
	/*
	pSelectionCB->AddItem(_T("Worker T0"),0);
		pSelectionCB->AddItem(_T("Thread T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEACTIVITY_WITHWORKER_TOTAL, _T("Time Total"), 0, 4));

	pPanel = pCategory->AddPanel(_T("All Activities"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SALLACTIVITIES_TOTAL, _T("Total time"), 0, 7));


	pPanel = pCategory->AddPanel(_T("Single Task"), m_PanelImages.ExtractIcon(19));

	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLETASK_RUNHISTO, _T("Runs History"), 0, 5));
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLETASK_TOTAL, _T("Total Time"), -1, 6));

	pPanel = pCategory->AddPanel(_T("All Tasks"), m_PanelImages.ExtractIcon(19));

	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_ALLTASKS_TOTAL, _T("Total Time"), 0, 8));


	pPanel = pCategory->AddPanel(_T("Worker"), m_PanelImages.ExtractIcon(17));

	//pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEWORKER_RUNPAUSE, _T("Run|Pause Time"), 0, 10));
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEWORKER_RUNHISTO, _T("Run History"), 0, 11));
	pPanel->AddSeparator();

	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_COMPARE_SINGLEWORKER_SELTASK, TRUE, -1,_T("Task :"),3);
	/*
	pSelectionCB->AddItem(_T("Task T0"),0);
		pSelectionCB->AddItem(_T("Task T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);
	/*pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEWORKER_WITHTASK_STACKED, _T("Stacked"), 0, 0));*/
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_SINGLEWORKER_WITHTASK_TOTAL, _T("Time Total"), 0, 12));

	pPanel = pCategory->AddPanel(_T("All Workers"), m_PanelImages.ExtractIcon(27));
	pPanel->Add(new CMFCRibbonButton(WM_COMPARE_ALLWORKERS_TOTAL, _T("Total Times"), 0, 13));

	

}

void CMyRibbonBar::addTabExport()
{
	CMFCRibbonCategory* pCategory = AddCategory(_T("Export"), IDB_EXPORT16, IDB_EXPORT);



	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Chart"), m_PanelImages.ExtractIcon(20));
	pPanel->Add(new CMFCRibbonButton(ID_CHART_DESIGN_TYPE_CHANGE, _T("Save\nc"), -1, 0));
/*
	pPanel->Add(new CMFCRibbonButton(ID_CHART_DESIGN_TYPE_CHANGE, _T("PDF\nc"), -1, 0));
	pPanel->Add(new CMFCRibbonButton(ID_CHART_DESIGN_TYPE_CHANGE, _T("Image\nc"), -1, 0));
*/

	pPanel = pCategory->AddPanel(_T("Data Values"), m_PanelImages.ExtractIcon(20));
	pPanel->Add(new CMFCRibbonButton(ID_CHART_DESIGN_TYPE_CHANGE, _T("Add CVS\nc"), -1, 2));
	pPanel->Add(new CMFCRibbonButton(ID_CHART_DESIGN_TYPE_CHANGE, _T("Add to Excel\nc"), -1, 1));


}

void CMyRibbonBar::addTabSupport()
{
	CMFCRibbonCategory* pCategory = AddCategory (
		_T("Support"),
		IDB_SUPPORT16,
		IDB_SUPPORT);
	CMFCRibbonPanel* pPanelLocalHelp =pCategory->AddPanel (_T("Local Help System"), m_PanelImages.ExtractIcon(0));
	pPanelLocalHelp->Add (new CMFCRibbonButton (WM_SUPPORT_CONTENTS, _T("Contents"), -1,8));
	//pPanelLocalHelp->Add (new CMFCRibbonButton (WM_MAINFRAME_SUPPORT_LOCAL_EXPERT, _T("Expert Help"), -1,10));
	pPanelLocalHelp->Add(new CMFCRibbonButton(WM_SUPPORT_TIPOFTHEDAY,_T("Tip of the day"),-1,9));

	CMFCRibbonPanel* pPanelOnlineSupport =pCategory->AddPanel (_T("Online support"), m_PanelImages.ExtractIcon(0));
	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_HELPDESK, _T("System Help desk"), 4));
	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_FORUMS, _T("Public forums"), 6));
	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_MAILSUPPORT, _T("Mail Support"), 5));

	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_TUTORIALS, _T("Articles"), 7));
	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_FAQ, _T("FAQ"), 8));
	pPanelOnlineSupport->Add (new CMFCRibbonButton (WM_SUPPORT_UPDATE, _T("Update"), 9));

/*
	CMFCRibbonPanel* pPanelUpdate =pCategory->AddPanel (_T("Update"));
	pPanelUpdate->Add (new CMFCRibbonButton (ID_CHART_DESIGN_TYPE_CHANGE, _T("Update program"), -1,0));
*/


	CMFCRibbonPanel* pPanelLegalAndAbout =pCategory->AddPanel (_T("Product"), m_PanelImages.ExtractIcon(0));
	pPanelLegalAndAbout->Add (new CMFCRibbonButton (WM_SUPPORT_COPYRIGHT, _T("Copyright"), -1,11));
	pPanelLegalAndAbout->Add (new CMFCRibbonButton (WM_SUPPORT_LICENCEKEY, _T("Licence Key"), 10));
	pPanelLegalAndAbout->Add (new CMFCRibbonButton (WM_SUPPORT_ACTIVATE_PRODUCT, _T("Activate Product"), 11));
	pPanelLegalAndAbout->Add (new CMFCRibbonButton (WM_SUPPORT_ABOUT, _T("About"), 12));


	CMFCRibbonPanel* pPanelInvite =pCategory->AddPanel (_T("Links"), m_PanelImages.ExtractIcon(0));
	pPanelInvite->Add (new CMFCRibbonButton (WM_SUPPORT_VISIT, _T("Visit Potato Software"), -1,4));
	pPanelInvite->Add(new CMFCRibbonSeparator());

	pPanelInvite->Add(new CMFCRibbonLinkCtrl(WM_SUPPORT_INVITE, _T("Invite your friends"), _T("Invite your friends")));
	pPanelInvite->Add(new CMFCRibbonLinkCtrl(WM_SUPPORT_NEWS, _T("News"), _T("News")));
	pPanelInvite->Add(new CMFCRibbonLinkCtrl(WM_SUPPORT_PARTNER, _T("Partner with Potato Software"), _T("Partner with Potato Software")));
	pPanelInvite->Add(new CMFCRibbonSeparator());
	pPanelInvite->Add (new CMFCRibbonButton (WM_SUPPORT_GOOGLE_CODE, _T("Google code"), -1,10+4));
	pPanelInvite->Add (new CMFCRibbonButton (WM_SUPPORT_CODE_PROJECT, _T("Code Project"), -1,10+5));
	pPanelInvite->Add (new CMFCRibbonButton (WM_SUPPORT_BLOG, _T("Blog"), -1,13));

	
}

void CMyRibbonBar::addChartTools()
{

	CMFCRibbonButton* pBtn=NULL;

	//
	CMFCRibbonCategory* pCategory = AddContextCategory(_T("Design"), _T("Chart tools"), IDB_CHART, AFX_CategoryColor_Green, IDB_CHART_DESIGN16, IDB_CHART_MENU);
	pCategory->SetKeys(_T("jc"));



	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Chart type"), m_PanelImages.ExtractIcon(20));


	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_COLUMN, _T("Column\nc"), -1, 0));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_LINE, _T("Line\nc"), -1, 1));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_PIE, _T("Pie\nc"), -1, 2));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_HCOLUMN, _T("Horizontal\nc"), -1, 3));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_AREA, _T("Area\nc"), -1, 4));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_SNOW, _T("Snow\nc"), -1, 5));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TYPE_DOUGHNUT, _T("Doughnut\nc"), -1, 6));

	pPanel = pCategory->AddPanel(_T("Design"), m_PanelImages.ExtractIcon(20));

	pBtn=new CMFCRibbonButton(WM_CHART_DESIGN_PALETTE, _T("Palette\nc"), -1, 7);
	pBtn->SetMenu(IDR_CHART_PALETTE,FALSE);
	pPanel->Add (pBtn);



	pPanel = pCategory->AddPanel(_T("3D"), m_PanelImages.ExtractIcon(20));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_ENABLE3D , _T("3D Chart\nc"), -1, 8));

	pPanel->AddSeparator();
	CMFCRibbonEdit* pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_WALL_WIDTH , 50, _T("Wall width:"), 7);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);


	pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_POINT_DEPTH , 50, _T("Point depth:"), 6);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);

	pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_GAP_DEPTH , 50, _T("Gap depth:"), 5);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);

	pPanel->AddSeparator();

	pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_PERSPECTIVE, 50, _T("Perspective:"), 4);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);


	pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_ROTATEX, 50, _T("Rotate X:"), 0);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);

	pEditBtn = new CMFCRibbonEdit(WM_CHART_DESIGN_ROTATEY, 50, _T("Rotate Y:"), 1);
	pEditBtn->EnableSpinButtons(0, 99);
	pEditBtn->SetEditText(_T("0"));
	pPanel->Add(pEditBtn);

	pPanel->SetJustifyColumns();
	//
	pPanel = pCategory->AddPanel(_T("Antiliasing"), m_PanelImages.ExtractIcon(20));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_GRAPHICS_ANTILIASING, _T("Graphic antiliasing\nc"), -1, 0));
	pPanel->Add(new CMFCRibbonButton(WM_CHART_DESIGN_TEXT_ANTILIASING, _T("Text antiliasing\nc"), -1, 9));


	CMFCRibbonCategory* pCategory2 = AddContextCategory(_T("Layout"), _T("Chart tools"), IDB_CHART, AFX_CategoryColor_Green, IDB_CHART_LAYOUT, IDB_CHART_LAYOUTLARGE);
	pCategory2->SetKeys(_T("ja"));


	CMFCRibbonPanel* pPanelLayout_Labels = pCategory2->AddPanel(_T("Labels"), m_PanelImages.ExtractIcon(20));

	pBtn=new CMFCRibbonButton (WM_CHART_LAYOUT_TITLE, _T("Chart Title\nt"),-1, 3);
	pBtn->SetMenu(IDR_CHARTTITLE,FALSE);
	pPanelLayout_Labels->Add (pBtn);

	/*
	pBtn=new CMFCRibbonButton(WM_CHART_LAYOUT_AXIS_TITLES, _T("Axis Titles\ni"), -1, 4);
		pBtn->SetMenu(IDR_AXISTITLES,FALSE);
		pPanelLayout_Labels->Add (pBtn);*/
	

	pPanelLayout_Labels->Add(new CMFCRibbonButton(WM_CHART_LAYOUT_LEGEND, _T("Legend\nl"), 3, 5));
	pPanelLayout_Labels->Add(new CMFCRibbonButton(WM_CHART_LAYOUT_POINTS_LABELS, _T("Data Labels\nb"), 4, 6));

	CMFCRibbonPanel* pPanelLayout_Axes = pCategory2->AddPanel(_T("Axes"), m_PanelImages.ExtractIcon(20));


	pBtn=new CMFCRibbonButton(WM_CHART_LAYOUT_AXIS, _T("Axes\na"), -1, 8);
	pBtn->SetMenu(IDR_AXIS,FALSE);
	pPanelLayout_Axes->Add (pBtn);


	pPanelLayout_Axes->Add(new CMFCRibbonButton(WM_CHART_LAYOUT_GRID, _T("Gridlines\ng"), -1, 9));

	CMFCRibbonCategory* pCategory3 = AddContextCategory(_T("Format"), _T("Chart tools"), IDB_CHART, AFX_CategoryColor_Green, IDB_CHART_FORMAT, IDB_CHART_MENU);
	pCategory3->SetKeys(_T("jo"));

	CMFCRibbonPanel* pPanelFormat_Sel = pCategory3->AddPanel(_T("Current Selection"), m_PanelImages.ExtractIcon(13));

	CMFCRibbonComboBox* pFormatSelCombo = new CMFCRibbonComboBox(WM_CHART_FORMAT_SEL_COMBO, TRUE, -1,_T("Select Item"),0);
	pFormatSelCombo->AddItem(_T("Chart Title"),0);
	pFormatSelCombo->AddItem(_T("Chart Area"));
	pFormatSelCombo->AddItem(_T("Legend"));
	pFormatSelCombo->AddItem(_T("x Axis Title"));
	pFormatSelCombo->AddItem(_T("y Axis Title"));
//	pFormatSelCombo->AddItem(_T("Series \"Series1\""),1);
	pFormatSelCombo->SelectItem(0);
	pPanelFormat_Sel->Add(pFormatSelCombo);

	pPanelFormat_Sel->Add(new CMFCRibbonLabel(_T("Change text :")));
	CMFCRibbonEdit* pBtn1 = new CMFCRibbonEdit(WM_CHART_FORMAT_TEXT , 200);
	pBtn1->SetEditText(_T("Edit"));
	pPanelFormat_Sel->Add(pBtn1);

	pPanel = pCategory3->AddPanel(_T("Shape Fill"), m_PanelImages.ExtractIcon(5));

	CMFCRibbonColorButton* pColorBtn = new CMFCRibbonColorButton(WM_CHART_FORMAT_FILL_COLOR1 , _T("Primary color"), 2);
	pColorBtn->SetDefaultCommand(FALSE);
	pColorBtn->EnableAutomaticButton(_T("&Automatic"), RGB(0, 0, 0));
	pColorBtn->EnableOtherButton(_T("&More Colors..."), _T("More Colors"));
	pColorBtn->SetColumns(10);
	pColorBtn->SetColorBoxSize(CSize(17, 17));
	pColorBtn->AddColorsGroup(_T("Theme Colors"), m_lstMainColors);
	pColorBtn->AddColorsGroup(_T(""), m_lstAdditionalColors, TRUE);
	pColorBtn->AddColorsGroup(_T("Standard Colors"), m_lstStandardColors);
	pPanel->Add(pColorBtn);

	pColorBtn = new CMFCRibbonColorButton(WM_CHART_FORMAT_FILL_COLOR2 , _T("Secondary color"), 2);
	pColorBtn->SetDefaultCommand(FALSE);
	pColorBtn->EnableAutomaticButton(_T("&Automatic"), RGB(0, 0, 0));
	pColorBtn->EnableOtherButton(_T("&More Colors..."), _T("More Colors"));
	pColorBtn->SetColumns(10);
	pColorBtn->SetColorBoxSize(CSize(17, 17));
	pColorBtn->AddColorsGroup(_T("Theme Colors"), m_lstMainColors);
	pColorBtn->AddColorsGroup(_T(""), m_lstAdditionalColors, TRUE);
	pColorBtn->AddColorsGroup(_T("Standard Colors"), m_lstStandardColors);
	pPanel->Add(pColorBtn);

	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_FILL_GRADIENT, _T("Gradient\nt"),2, -1);
	pBtn->SetMenu(IDR_CHART_GRADIENT,FALSE);
	pPanel->Add (pBtn);


	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_FILL_HATCH, _T("Hatch style"),-1, 10);
	pBtn->SetMenu(IDR_CHART_FILLHATCHING,FALSE);
	pPanel->Add (pBtn);

	
	pPanel = pCategory3->AddPanel(_T("Outline"), m_PanelImages.ExtractIcon(4));

	pColorBtn = new CMFCRibbonColorButton(WM_CHART_FORMAT_OUTLINE_COLOR ,_T("Color\nso"), 3, -1);
	pColorBtn->SetDefaultCommand(FALSE);
	pColorBtn->EnableAutomaticButton(_T("&Automatic"), RGB(0, 0, 0));
	pColorBtn->EnableOtherButton(_T("&More Colors..."), _T("More Colors"));
	pColorBtn->SetColumns(10);
	pColorBtn->SetColorBoxSize(CSize(17, 17));
	pColorBtn->AddColorsGroup(_T("Theme Colors"), m_lstMainColors);
	pColorBtn->AddColorsGroup(_T(""), m_lstAdditionalColors, TRUE);
	pColorBtn->AddColorsGroup(_T("Standard Colors"), m_lstStandardColors);
	pPanel->Add(pColorBtn);


	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_FILL_GRADIENT, _T("Style\nt"),3, -1);
	pBtn->SetMenu(IDR_CHART_OUTLINESTYLE,FALSE);
	pPanel->Add (pBtn);
	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_OUTLINE_SIZE, _T("Size\ns"),3, -1);
	pBtn->SetMenu(IDR_OUTLINE_WIDTH,FALSE);
	pPanel->Add (pBtn);
	
	
	pPanel = pCategory3->AddPanel(_T("Size"), m_PanelImages.ExtractIcon(20));
	CMFCRibbonEdit* pBtn5 = new CMFCRibbonEdit(WM_CHART_FORMAT_SIZEX, 45, NULL, 11);
	pBtn5->EnableSpinButtons(0, 99);
	pBtn5->SetEditText(_T("0"));
	pPanel->Add(pBtn5);
	pBtn5 = new CMFCRibbonEdit(WM_CHART_FORMAT_SIZEY, 45, NULL, 12);
	pBtn5->EnableSpinButtons(0, 99);
	pBtn5->SetEditText(_T("0"));
	pPanel->Add(pBtn5);

	pPanel->SetCenterColumnVert (TRUE);


	pPanel = pCategory3->AddPanel(_T("Orientation"), m_PanelImages.ExtractIcon(20));

	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_ORIENTATION_ALIGN, _T("Alignment"),6, -1);
	pBtn->SetMenu(IDR_CHART_ALIGNMENT,FALSE);
	pPanel->Add (pBtn);
	
	pBtn=new CMFCRibbonButton (WM_CHART_FORMAT_ORIENTATION_DOCKING, _T("Docking"),8, -1);
	pBtn->SetMenu(IDR_CHART_DOCKING,FALSE);
	pPanel->Add (pBtn);
	
	pPanel->Add(new CMFCRibbonButton(WM_CHART_FORMAT_ORIENTATION_REVERSE, _T("Reverse\nso"), 10, -1));


	//pPanel->Add(new CMFCRibbonButton(ID_CHART_FORMAT_SHAPES_EFFECTS, _T("Shape Effects\nse"), 4, -1));

	// Create "Font" panel:
	CMFCRibbonPanel* pPanelFont = pCategory3->AddPanel(_T("Font"), m_PanelImages.ExtractIcon(2));
	pPanelFont->SetKeys(_T("zf"));

	// Create a new group with 2 elements: font name and font size:
	CMFCRibbonButtonsGroup* pFontGroup = new CMFCRibbonButtonsGroup;

	CMFCRibbonFontComboBox::m_bDrawUsingFont = TRUE;

	CMFCRibbonFontComboBox* pFontCombo = new CMFCRibbonFontComboBox(WM_CHART_FORMAT_FONT_NAME);
	pFontCombo->SetWidth(55, TRUE); // Width in "floaty" mode
	pFontCombo->SelectItem(10);
	pFontGroup->AddButton(pFontCombo);

	CMFCRibbonComboBox* pFontSizeCombo = new CMFCRibbonComboBox(WM_CHART_FORMAT_FONT_SIZE, TRUE, 39);
	pFontSizeCombo->AddItem(_T("8"));
	pFontSizeCombo->AddItem(_T("9"));
	pFontSizeCombo->AddItem(_T("10"));
	pFontSizeCombo->AddItem(_T("11"));
	pFontSizeCombo->AddItem(_T("12"));
	pFontSizeCombo->AddItem(_T("14"));
	pFontSizeCombo->AddItem(_T("16"));
	pFontSizeCombo->AddItem(_T("18"));
	pFontSizeCombo->AddItem(_T("20"));
	pFontSizeCombo->AddItem(_T("22"));
	pFontSizeCombo->AddItem(_T("24"));
	pFontSizeCombo->AddItem(_T("26"));
	pFontSizeCombo->AddItem(_T("28"));
	pFontSizeCombo->AddItem(_T("36"));
	pFontSizeCombo->AddItem(_T("48"));
	pFontSizeCombo->AddItem(_T("72"));
	pFontSizeCombo->SetWidth(20, TRUE); // Width in "floaty" mode
	pFontSizeCombo->SelectItem(3);
	pFontGroup->AddButton(pFontSizeCombo);

	pPanelFont->Add(pFontGroup);

	// Add toolbar(all toolbar buttons will be automatically
	// converted to ribbon elements:
	pPanelFont->AddToolBar(IDR_FONT);

}


void CMyRibbonBar::CreateDocumentColors()
{
	typedef struct
	{
		COLORREF color;
		TCHAR* szName;
	}
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] = 
	{
		{	RGB (255, 255, 255),	_T("White, Background 1")	},
		{	RGB (0, 0, 0),			_T("Black, Text 1")			},
		{	RGB (238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB (31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB (79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB (192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB (155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB (128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB (75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB (245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional [] = 
	{
		{	RGB (242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB (127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB (214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB (210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB (217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB (244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB (234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB (229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB (216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB (255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB (215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB (89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB (177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB (161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB (179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB (233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB (213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB (203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB (176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB (255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB (190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB (65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB (118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB (115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB (143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB (222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB (192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB (177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB (137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB (255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB (163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB (42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB (61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB (20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB (54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB (149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB (114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB (97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB (41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB (190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB (126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB (20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB (29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB (17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB (38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB (100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB (77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB (67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB (31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB (126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard [] = 
	{
		{	RGB (200, 15, 18),		_T("Dark Red")		},
		{	RGB (255, 20, 24),		_T("Red")			},
		{	RGB (255, 191, 40),		_T("Orange")		},
		{	RGB (255, 255, 49),		_T("Yellow")		},
		{	RGB (138, 207, 87),		_T("Light Green")	},
		{	RGB (0, 175, 84),		_T("Green")			},
		{	RGB (0, 174, 238),		_T("Light Blue")	},
		{	RGB (0, 111, 189),		_T("Blue")			},
		{	RGB (0, 36, 95),		_T("Black")			},
		{	RGB (114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll();
	nNumColours = sizeof(colorsMain) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail(colorsMain [i].color);
		CMFCRibbonColorButton::SetColorName(colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll();
	nNumColours = sizeof(colorsAdditional) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail(colorsAdditional [i].color);
		CMFCRibbonColorButton::SetColorName(colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll();
	nNumColours = sizeof(colorsStandard) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail(colorsStandard [i].color);
		CMFCRibbonColorButton::SetColorName(colorsStandard [i].color, colorsStandard [i].szName);
	};
}

void CMyRibbonBar::testUpdate()
{
	CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, FindByID(WM_CHART_FORMAT_SEL_COMBO));
	if (pFormatSelCombo == NULL)
	{
		return;
	}
	pFormatSelCombo->SelectItem(2);
	return;
	int i=pFormatSelCombo->GetCurSel();
}