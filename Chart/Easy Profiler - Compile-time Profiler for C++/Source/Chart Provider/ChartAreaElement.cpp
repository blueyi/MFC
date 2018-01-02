/********************************************************************
    File:	        ChartAreaElement	
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
#include "ChartAreaElement.h"

CChartAreaElement::CChartAreaElement(void)
{
}

void CChartAreaElement::setSizeWidth( int width )
{
	chart->ChartAreas["ChartArea1"]->Position->Width=width;
}

void CChartAreaElement::setSizeHeight( int heigth )
{
	chart->ChartAreas["ChartArea1"]->Position->Height=heigth;
}

void CChartAreaElement::setShapePrimaryColor( System::Drawing::Color color )
{
	chart->ChartAreas["ChartArea1"]->BackColor = color;
}

void CChartAreaElement::setShapeSecondaryColor( System::Drawing::Color color )
{
	chart->ChartAreas["ChartArea1"]->BackSecondaryColor=color;
}

void CChartAreaElement::setShapeFill( Charting::GradientStyle style )
{
	chart->ChartAreas["ChartArea1"]->BackGradientStyle=style;
}

void CChartAreaElement::setShapeHatching( Charting::ChartHatchStyle hatch )
{
	chart->ChartAreas["ChartArea1"]->BackHatchStyle=hatch;
}