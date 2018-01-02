/********************************************************************
    File:	        ChartControl	
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

class CMyRibbonBar;


extern "C" AFX_EXT_API void WINAPI LoadExtDll_CFormView();
extern "C" AFX_EXT_API void WINAPI addPointToSeries(CString seriesName,CString xValue,DOUBLE dwValue);
extern "C" AFX_EXT_API void WINAPI resetChart();
extern "C" AFX_EXT_API void WINAPI setupNewSeries(CString seriesName,int seriesType);
extern "C" AFX_EXT_API void WINAPI setElementLayout(int elementType,int layout);
extern "C" AFX_EXT_API void WINAPI setGlobalProperty(int propertyID,int value);
extern "C" AFX_EXT_API int WINAPI getGlobalProperty(int propertyID);
extern "C" AFX_EXT_API void WINAPI setCustomProperty(CString seriesName,CString customProperty);
extern "C" AFX_EXT_API void WINAPI setChartTypeForAllSeries(int seriesType);
extern "C" AFX_EXT_API void WINAPI setFormat(int FormatElement, int FormatCommand,CString value);
extern "C" AFX_EXT_API void WINAPI saveImageToFile(CString filePath,CString format);
extern "C" AFX_EXT_API void WINAPI printPreview(int command);
extern "C" AFX_EXT_API void WINAPI setSeriesColor(CString seriesName,CString seriesColor);
/*
extern "C" AFX_EXT_API void WINAPI setElementProperty(int elementType, int elementID, int elementProperty,int elementVal);
*/


class CChartControl
{
public:
	CChartControl(void);
	~CChartControl(void);
	enum GlobalProperty{
		PropEnable3D=1,
		PropWallWidth,
		PropAxisShowState,
		PropDataLabelShowState,
		PropLegendShowState,//
		PropPointDepth,
		PropGapDepth,
		PropPerspective,
		PropRotateX,
		PropRotateY,
		PropGraphicsAntiliasing,
		PropTextAntiliasingQuality,
		PropChartPalette,
	};
	enum ChartType{
		Spline=1,
		Column,
		StackedColumn,
		Pie,
		HColumn,
		Area,
		Snow,
		Doughnut
	} chartType;

	enum FormatCommandType{
		Format_Text=1,
		Format_ShapeColor1,
		Format_ShapeColor2,
		Format_ShapeGradient,
		Format_ShapeHatch,
		Format_OutlineColor,
		Format_OutlineStyle,
		Format_OutlineSize,
		Format_SizeWidth,
		Format_SizeLength,
		Format_OrientationAlignment,
		Format_OrientationDocking,
		Format_OrientationReverse,
		Format_FontName,
		Format_FontSize,
		Format_FontBold,
		Format_FontItalic,
		Format_FontUnderline,
		Format_FontDeleted,
		Format_FontLeft,
		Format_FontCenter,
		Format_FontRight
	};

	void setFormat(int FormatElement, int FormatCommand,CString value);
	void saveImageToFile(CString filePath,CString format);
	void printPreview(int command);

	void setChartType(ChartType chartType){
		this->chartType=chartType;
		//Call function.
		setChartTypeForAllSeries(chartType);
	}
	bool getGlobalBoolProperty(GlobalProperty prop){
		return getGlobalProperty(prop)==1;
	}
	int getGlobalIntProperty(GlobalProperty prop){
		return getGlobalProperty(prop);
	}
	void setGlobalBoolProperty(GlobalProperty prop,bool bValue)
	{
		setGlobalProperty(prop,bValue ? 1 : 0);
	}
	void setGlobalIntProperty(GlobalProperty prop,int iValue){
		setGlobalProperty(prop,iValue);
	}
	void setCustomProperty(std::string seriesName,CString customProperty){
		::setCustomProperty(CCommonUtilities::toMFCString(seriesName),customProperty);
	}

	enum DisplayType{
		Hide=0,
		Show,
		Dock
	};
	class CChartTitle{
	public:
		int layout;
		void SetLayout(DisplayType _layout)
		{
			layout=_layout;
			setElementLayout(1,_layout);
		}
	} chartTitle;
	
	void resetSeries();
	void addSeries(CString seriesName,ChartType seriesType);
	void addSeries(std::string seriesName,ChartType seriesType)
	{
		addSeries(CCommonUtilities::toMFCString(seriesName),seriesType);
	}
	void addPoint(CString seriesName,CString pointName,double pointVal)
	{
		addPointToSeries(CCommonUtilities::toMFCString(seriesName),
			CCommonUtilities::toMFCString(pointName),pointVal);
	}
	void addPoint(std::string seriesName,std::string pointName,double pointVal)
	{
		addPointToSeries(CCommonUtilities::toMFCString(seriesName),
			CCommonUtilities::toMFCString(pointName),pointVal);
	}
	void addPoint(CString seriesName,std::string pointName,double pointVal)
	{
		addPointToSeries(CCommonUtilities::toMFCString(seriesName),
			CCommonUtilities::toMFCString(pointName),pointVal);
	}
	void addPoint(std::string seriesName,CString pointName,double pointVal)
	{
		addPointToSeries(CCommonUtilities::toMFCString(seriesName),
			CCommonUtilities::toMFCString(pointName),pointVal);
	}
	void setSeriesColor(std::string seriesName,COLORREF cl)
	{
		setSeriesColor(CCommonUtilities::toMFCString(seriesName),cl);
	}
	void setSeriesColor(CString seriesName,COLORREF cl)
	{
		CString str;
		str.Format(_T("%.3d%.3d%.3d"),GetRValue(cl),
			GetGValue(cl),
			GetBValue(cl));

		::setSeriesColor(seriesName,str);
	}

	//
	int wallWidth;
	void setWallWidth(int wallWidth){
		this->wallWidth=wallWidth;
	}
	int GetWallWidth(){
		return wallWidth;
	}
public:
	void setRibbonBar(CMyRibbonBar* pRibbonBar){
		this->pRibbonBar=pRibbonBar;
	}
	void setSelectedFormatItem(int selectedItem);
private:
	CMyRibbonBar* pRibbonBar;
	int selectedItem;
};


extern CChartControl chartControl;