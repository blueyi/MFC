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
#include "StdAfx.h"
#include "ChartControl.h"

#include "MyRibbonBar.h"

CChartControl::CChartControl(void)
{
}

CChartControl::~CChartControl(void)
{
}

void CChartControl::resetSeries()
{
	resetChart();
	pRibbonBar->OnAfterResetSeries();
		//The ribbon recalculates its layout in case combo selection was deleted.
}

void CChartControl::addSeries( CString seriesName,ChartType seriesType )
{
	setupNewSeries(seriesName,seriesType);
	pRibbonBar->OnAfterAddSeries(seriesName);
		//adds a series item in the format combo.
	this->chartType=seriesType;
	pRibbonBar->RecalcLayout();

}

void CChartControl::setSelectedFormatItem( int selectedItem )
{
	this->selectedItem=selectedItem;
	pRibbonBar->RecalcLayout();
}

void CChartControl::setFormat( int FormatElement, int FormatCommand,CString value )
{
	::setFormat(FormatElement,FormatCommand,value);
}

void CChartControl::saveImageToFile( CString filePath,CString format )
{
	::saveImageToFile( filePath,format );
}

void CChartControl::printPreview(int command)
{
	::printPreview(command);
}
CChartControl chartControl;