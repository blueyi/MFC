/********************************************************************
    File:	        Export	
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

#include "stdafx.h"
#include "Resource.h"
#include "ChartView.h"
#include "ChartFrame.h"


extern "C" AFX_EXT_API void WINAPI resetChart(){
	pThisView->resetChart();
}
extern "C" AFX_EXT_API void WINAPI setupNewSeries(CString seriesName,int seriesType){
	pThisView->setupNewSeries(seriesName,seriesType);
}
extern "C" AFX_EXT_API void WINAPI setCustomProperty(CString seriesName,CString customProperty){
	pThisView->setCustomProperty(seriesName,customProperty);
}

extern "C" AFX_EXT_API void WINAPI addPointToSeries(CString seriesName,CString xValue,DOUBLE dwValue){
	pThisView->addPointToSeries(seriesName,xValue,dwValue);
}
extern "C" AFX_EXT_API void WINAPI setElementLayout(int elementType,int layout)
{
	pThisView->setElementLayout(elementType,layout);
}

extern "C" AFX_EXT_API void WINAPI setGlobalProperty(int propertyID,int value)
{
	pThisView->setGlobalProperty(propertyID,value);
}
extern "C" AFX_EXT_API int WINAPI getGlobalProperty(int propertyID)
{
	return pThisView->getGlobalProperty(propertyID);
}
extern "C" AFX_EXT_API void WINAPI setChartTypeForAllSeries(int seriesType)
{
	pThisView->setChartTypeForAllSeries(seriesType);
}
extern "C" AFX_EXT_API void WINAPI setFormat(int FormatElement, int FormatCommand,CString value)
{
	pThisView->setFormat(FormatElement, FormatCommand,value);
}
extern "C" AFX_EXT_API void WINAPI saveImageToFile(CString filePath,CString format)
{
	pThisView->saveImageToFile(filePath,format);
}
extern "C" AFX_EXT_API void WINAPI printPreview(int command)
{
	pThisView->printPreview(command);
}
extern "C" AFX_EXT_API void WINAPI setSeriesColor(CString seriesName,CString seriesColor)
{
	pThisView->setSeriesColor(seriesName,seriesColor);
}
// Exported DLL initialization is run in context of running application
extern "C" AFX_EXT_API void WINAPI LoadExtDll_CFormView()
{
	// Register the doc templates we provide to the app
	CWinApp* pApp = AfxGetApp();


	ASSERT(pApp != NULL);
	CMultiDocTemplate* pTemplate=new CMultiDocTemplate(IDR_EXTTMPL_CHART,
		RUNTIME_CLASS(CDummyDoc),
		RUNTIME_CLASS(CChartFrame),
		RUNTIME_CLASS(CChartView));
	pApp->AddDocTemplate(pTemplate);
	/*
	CDocument* pDoc=pTemplate->OpenDocumentFile(NULL);
		pDoc->SetTitle(_T("Graph View"));*/
	

	/*
	POSITION pos = pDoc->GetFirstViewPosition();
		if (pos==NULL)
		{
			AfxMessageBox(_T("fault"));
			return NULL;
		}
		CView* pFirstView = pDoc->GetNextView(pos);*/
	


}