/********************************************************************
    File:	        FormatElementBase	
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
#include "FormatElementBase.h"
#include "Chart ProviderControl.h"

#include "ChartTitleElement.h"
#include "ChartLegendElement.h"
#include "ChartAreaElement.h"
#include "ChartXAxisElement.h"
#include "ChartYAxisElement.h"
#include "ChartSerieElement.h"

CFormatElementBase::CFormatElementBase(void)
{
}

CFormatElementBase^ CFormatElementBase::createFormatElement(int id)
{
	switch (id)
	{
	case 0:
		return gcnew CChartTitleElement;
	case 1:
		return gcnew CChartAreaElement;
	case 2:
		return gcnew CChartLegendElement;
	case 3:
		return gcnew CChartXAxisElement;
	case 4:
		return gcnew CChartYAxisElement;
	}
	id-=5;
	return gcnew CChartSerieElement(id);	
}

void CFormatElementBase::setText(System::String^ value)
{
	throw(gcnew System::NotImplementedException);
}

void CFormatElementBase::setChart(Charting::Chart^ chart )
{
	this->chart=chart;
}

void CFormatElementBase::setShapePrimaryColor( System::Drawing::Color color )
{
	throw(gcnew System::NotImplementedException);
}

void CFormatElementBase::setShapeSecondaryColor( System::Drawing::Color color )
{
	throw(gcnew System::NotImplementedException);
}

void CFormatElementBase::setShapeFill( Charting::GradientStyle style )
{
	//
}

void CFormatElementBase::setShapeHatching( Charting::ChartHatchStyle hatch )
{
	//
}

void CFormatElementBase::setAlignment( System::Drawing::ContentAlignment align )
{
	//
}

void CFormatElementBase::setDocking( Charting::Docking dock )
{
	//
}

void CFormatElementBase::reverse()
{
	//
}

void CFormatElementBase::setFontFamily( System::String^ value )
{
	//
}

void CFormatElementBase::setFontSize( int size )
{
	//
}

void CFormatElementBase::setBoldFont()
{
	//
}

void CFormatElementBase::setOutlineColor( System::Drawing::Color color )
{

}

void CFormatElementBase::setOutlineStyle( Charting::ChartDashStyle dashStyle )
{

}

void CFormatElementBase::setOutlineSize( int size )
{

}