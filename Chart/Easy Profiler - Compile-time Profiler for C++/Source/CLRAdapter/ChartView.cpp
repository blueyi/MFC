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
// TestView.cpp : implementation file
//

#include "stdafx.h"

#include "ChartView.h"
// CChartView

IMPLEMENT_DYNCREATE(CChartView, CWinFormsView)

CChartView* pThisView=NULL;

CChartView::CChartView() : CWinFormsView(ChartProviderControl::typeid)
{
	pThisView=this;
}

CChartView::~CChartView()
{
}

BEGIN_MESSAGE_MAP(CChartView, CWinFormsView)
END_MESSAGE_MAP()



// CChartView drawing

void CChartView::OnDraw(CDC* pDC)
{
	//
}


// CChartView diagnostics

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CWinFormsView::AssertValid();
}

#ifndef _WIN32_WCE
void CChartView::Dump(CDumpContext& dc) const
{
	CWinFormsView::Dump(dc);
}
#endif

#endif //_DEBUG

ChartProviderControl^ CChartView::GetControl()
{
	System::Windows::Forms::Control^ control = CWinFormsView::GetControl();
	return safe_cast<ChartProviderControl^>(control);
}



BOOL CChartView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CWinFormsView::PreCreateWindow(cs);
}

void CChartView::OnInitialUpdate()
{
	CWinFormsView::OnInitialUpdate();
}

void CChartView::PostNcDestroy()
{
	CWinFormsView::PostNcDestroy();
}



// CDummyDoc : a do-nothing document that can be used with non-data views

IMPLEMENT_DYNCREATE(CDummyDoc, CDocument)

BEGIN_MESSAGE_MAP(CDummyDoc, CDocument)
END_MESSAGE_MAP()



void CChartView::addPointToSeries(CString seriesName,CString xValue,DOUBLE dwValue)
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->addNewPoint(gcnew System::String(seriesName),gcnew System::String(xValue),dwValue);

}

void CChartView::resetChart()
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->resetChart();
}

void CChartView::setupNewSeries( CString seriesName,int seriesType )
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->setupNewSeries(gcnew System::String(seriesName),seriesType);
}

void CChartView::setElementLayout( int elementType,int layout )
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->setElementLayout(elementType,layout);
}

void CChartView::setGlobalProperty( int propertyID,int value )
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->setGlobalProperty(propertyID,value);
}

int CChartView::getGlobalProperty( int propertyID )
{
	ChartProviderControl^ viewControl = GetControl();

	return viewControl->getGlobalProperty(propertyID);
}

void CChartView::setCustomProperty( CString seriesName,CString customProperty )
{
	ChartProviderControl^ viewControl = GetControl();

	viewControl->setCustomPropety(gcnew System::String(seriesName),gcnew System::String(customProperty));
}

void CChartView::setChartTypeForAllSeries( int seriesType )
{
	ChartProviderControl^ viewControl = GetControl();
	viewControl->setChartTypeForAllSeries(seriesType);
}

void CChartView::setFormat( int FormatElement, int FormatCommand,CString value )
{
	ChartProviderControl^ viewControl = GetControl();
	viewControl->setFormat(FormatElement,FormatCommand,gcnew System::String(value));
}

void CChartView::saveImageToFile( CString filePath,CString format )
{
	ChartProviderControl^ viewControl = GetControl();
	viewControl->saveImageToFile(gcnew System::String(filePath),gcnew System::String(format));
}

void CChartView::printPreview(int command)
{
	ChartProviderControl^ viewControl = GetControl();
	viewControl->printPreview(command);
}

void CChartView::setSeriesColor( CString seriesName,CString seriesColor )
{
	ChartProviderControl^ viewControl = GetControl();
	viewControl->setSeriesColor(gcnew System::String(seriesName),gcnew System::String(seriesColor));
}