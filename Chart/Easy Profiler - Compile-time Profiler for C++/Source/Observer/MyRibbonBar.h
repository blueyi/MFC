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
#pragma once


// CMyRibbonBar

class CMyRibbonBar : public CMFCRibbonBar
{
	DECLARE_DYNAMIC(CMyRibbonBar)

public:
	CMyRibbonBar();
	virtual ~CMyRibbonBar();

	void InitializeRibbon();
	void addTabHome();
	void addTabAnalyze();
	void addTabCompare();
	void addTabExport();
	void addTabAddins()
	{
		//
	}
	void addTabSupport();
	void addChartTools();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;


	//


	// Document colors for demo:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;


	void CreateDocumentColors();
public:
	void testUpdate();
	void OnAfterResetSeries(){
		CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, FindByID(WM_CHART_FORMAT_SEL_COMBO));
		if (pFormatSelCombo == NULL)
		{
			return;
		}
		int selItem=pFormatSelCombo->GetCurSel();
		

		while (pFormatSelCombo->GetCount() > 5)
		{
			pFormatSelCombo->DeleteItem(pFormatSelCombo->GetCount()-1);
		}
		
		if(selItem >= 5)
		{
			pFormatSelCombo->SelectItem(0);
			RecalcLayout();
		}
	}
	void OnAfterAddSeries(CString name){
		CMFCRibbonComboBox* pFormatSelCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, FindByID(WM_CHART_FORMAT_SEL_COMBO));
		if (pFormatSelCombo == NULL)
		{
			return;
		}
		CString str;
		str.Format(_T("Series \"%s\""),name);
		pFormatSelCombo->AddItem(str);
		
	}

};


