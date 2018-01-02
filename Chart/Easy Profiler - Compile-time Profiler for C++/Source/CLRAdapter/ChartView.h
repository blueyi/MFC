/********************************************************************
    File:	        ChartView	
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

// CChartView view
#include <afxwinforms.h>
#using <Chart Provider.dll>
using namespace ChartProvider;


 class CChartView : public CWinFormsView
{
	DECLARE_DYNCREATE(CChartView)

protected:
	CChartView();           // protected constructor used by dynamic creation
	virtual ~CChartView();

public:
	ChartProviderControl^ GetControl();



public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnInitialUpdate();
protected:
	virtual void PostNcDestroy();

public:

	BEGIN_DELEGATE_MAP( CChartView )
	END_DELEGATE_MAP()

	
	void addPointToSeries(CString seriesName,CString xValue,DOUBLE dwValue);
	void resetChart();
	void setupNewSeries(CString seriesName,int seriesType);
	void setElementLayout(int elementType,int layout);
	//
	void setGlobalProperty(int propertyID,int value);
	int getGlobalProperty(int propertyID);

	void setCustomProperty(CString seriesName,CString customProperty);
	void setChartTypeForAllSeries(int seriesType);
	void setFormat(int FormatElement, int FormatCommand,CString value);
	void saveImageToFile(CString filePath,CString format);
	void printPreview(int command);
	void setSeriesColor(CString seriesName,CString seriesColor);
};

class AFX_EXT_CLASS CDummyDoc : public CDocument
{
	DECLARE_DYNCREATE(CDummyDoc)

protected:
	DECLARE_MESSAGE_MAP()
};


extern CChartView* pThisView;