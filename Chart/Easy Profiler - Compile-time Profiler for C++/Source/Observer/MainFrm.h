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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "TipOfTheDayDlg.h"

#include "MyRibbonBar.h"

#include "CalendarBar.h"
#include "ParentBar.h"
#include "SelectionPane.h"

#include "Resource.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); }
};

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CMyRibbonBar     m_wndRibbonBar;
	
	
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutlookBar       m_wndNavigationBar;
	CParentBar m_TreeBar;
	CSelectionPane m_selectionPane;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, int nInitialWidth);

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;

private:
	void OnOpenTestFile();
	void OnOpenTestSuite();
	//
#pragma region chartTools
	void hideChartTitle();
	void showChartTitle();
	void dockChartTitle();
	//
	void updateHideChartTitle(CCmdUI* pCmdUI);
	void updateShowChartTitle(CCmdUI* pCmdUI);
	void updateDockChartTitle(CCmdUI* pCmdUI);
	//
	void formatSelectionCombo();
	//
	void chartTypeColumn();;
	void chartTypeLine();
	void chartTypePie();
	void chartTypeHColumn();
	void chartTypeArea();
	void chartTypeSnow();
	void chartTypeDoughnut();
	//
	void updateChartTypeColumn(CCmdUI* pCmdUI);
	void updateChartTypeLine(CCmdUI* pCmdUI);
	void updateChartTypePie(CCmdUI* pCmdUI);
	void updateChartTypeHColumn(CCmdUI* pCmdUI);
	void updateChartTypeArea(CCmdUI* pCmdUI);
	void updateChartTypeSnow(CCmdUI* pCmdUI);
	void updateChartTypeDoughnut(CCmdUI* pCmdUI);


	void enable3D();
	void setWallWidth();
	void setPointDepth();
	void setGapDepth();
	void setPerspective();
	void setRotateX();
	void setRotateY();
	void setGraphicsAntiliasing();
	void setTextAntiliasingQuality();

	//
	void updateEnable3D(CCmdUI* pCmdUI);
	void updateSetWallWidth(CCmdUI* pCmdUI);
	void updateSetPointDepth(CCmdUI* pCmdUI);
	void updateSetGapDepth(CCmdUI* pCmdUI);
	void updateSetPerspective(CCmdUI* pCmdUI);
	void updateSetRotateX(CCmdUI* pCmdUI);
	void updateSetRotateY(CCmdUI* pCmdUI);
	void updateSetGraphicsAntiliasing(CCmdUI* pCmdUI);
	void updateSetTextAntiliasingQuality(CCmdUI* pCmdUI);


	afx_msg void OnChartPaletteToolCommand(UINT id);

	void setText();
	void setFillColor1();
	void setFillColor2();
	void setGradient();
	void setHatchStyle();

	void setOutlineColor();
	void setOutlineStyle(){
		//
	}
	void setOutlineSize(){
		//
	}
	//
	void setAlign(){
		//
	}
	void setDocking(){
		//
	}
	afx_msg void OnDockingToolCommand(UINT id);
	afx_msg void OnUpdateDockingToolCommand(CCmdUI* pCmdUI)
	{
		//
	}
	afx_msg void OnAlignToolCommand(UINT id);
	afx_msg void OnUpdateAlignToolCommand(CCmdUI* pCmdUI)
	{
		//
	}

	afx_msg void OnOutlineStyleToolCommand(UINT id);
	afx_msg void OnUpdateOutlineStyleToolCommand(CCmdUI* pCmdUI)
	{
		//
	}

	void setReverse();

	//Chart Layout :
	void onChartLayout_AxisTitles()
	{
		//Just empty
	}
	afx_msg void onChartLayout_AxisTitlesToolCommand(UINT id)
	{
		/*
		#define ID_XAXIS_SHOW                   32840
		#define ID_XAXIS_DONOTSHOW              32841
		#define ID_YAXIS_SHOW                   32842
		#define ID_YAXIS_DONOTSHOW              32843
		*/
	}
	afx_msg void OnUpdateChartLayout_AxisTitlesToolCommand(CCmdUI* pCmdUI)
	{
		//
	}
	void onChartLayout_ShowLegend();
	void OnUpdateChartLayout_ShowLegend(CCmdUI* pCmdUI);
	void onChartLayout_ShowPointsLabels();
	void OnUpdateChartLayout_ShowPointsLabels(CCmdUI* pCmdUI); 
	void onChartLayout_Axis()
	{
		//Just empty
	}
	afx_msg void onChartLayout_AxisToolCommand(UINT id);
	afx_msg void OnUpdateChartLayout_AxisToolCommand(CCmdUI* pCmdUI)
	{
		//
	}
	void onChartLayout_ShowGrid(){
		//
	}
	//Font :
	void onFontName();
	void onFontSize();
	//
	afx_msg void onShapeGradientToolCommand(UINT id);
	afx_msg void onUpdateShapeGradientToolCommand(CCmdUI* pCmdUI){}
	//
	afx_msg void onShapeHatchingToolCommand(UINT id);
	afx_msg void onUpdateHatchingToolCommand(CCmdUI* pCmdUI)
	{
		//
	}
	//
	afx_msg void onOutlineWidthToolCommand(UINT id);
	afx_msg void onUpdateOutlineWidthToolCommand(CCmdUI* pCmdUI)
	{
		//
	}
	void OnFormatSizeX();
	void OnFormatSizeY();

	//
	void OnFont_Bold();
	void OnFontItalic();
	void OnFontStroke();
	void OnFontUnderline();
	void OnFontLeft();
	void OnFontCenter();
	void OnFontRight();

#pragma endregion chartTools

#pragma region ANALYSIS
	afx_msg void OnAnalysisToolCommand(UINT id);
	afx_msg void OnUpdateAnalysisToolCommand(CCmdUI* pCmdUI);
	void onAnalysisSelectTest();
	void onAnalysisSelectItem();
	void onAnalysisSingleActivitySelTask();
	void onAnalysisSingleActivitySelWorker();
	void onAnalysisSingleWorkerSelTask();

	//
	void onMenuItem1()
	{
		OnAnalysisToolCommand(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_STACKED);
	}
	void onUpdateMenuItem1(CCmdUI* pCmdUI)
	{
		OnUpdateAnalysisToolCommand(pCmdUI);
	}
	void onMenuItem2()
	{
		OnAnalysisToolCommand(WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_TOTAL);
	}
	void onUpdateMenuItem2(CCmdUI* pCmdUI)
	{
		OnUpdateAnalysisToolCommand(pCmdUI);
	}

#pragma endregion ANALYSIS

#pragma region COMPARE
	afx_msg void OnCompareToolCommand(UINT id);
	afx_msg void OnUpdateCompareToolCommand(CCmdUI* pCmdUI);
	void onCompareSelectTest();
	void onCompareSelectItem();
	void onCompareSingleActivitySelTask();
	void OnCompareSingleActivitySelWorker();
	void onCompareSingleWorkerSelTask();
	

#pragma endregion COMPARE


#pragma region SUPPORT
	afx_msg void OnSupportToolCommand(UINT id);
#pragma endregion
	void voidhandler()
	{
		//
	}

	//
	void OnExportImageToFile();
	void OnPrint();
	void OnPrintPreview();
	void OnPrintSetup();
	//
	void OnStatusBarWebSiteLink();

	//
	void SetStatusBarText(CString text);

	//
	void OnHomeSelectFileFolder();
	void OnHomeSelectTestItem();
	void OnUpdateFileFolder();
	void OnSetTestDescription();
	void OnCloseFileFolder();
	void OnDeleteTest();
};


