/********************************************************************
    File:	        ChartLegendElement	
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
    
	Note :	  		chart tools Ribbon tabs do synchronize with "chart ppties". Getters needed here.
*********************************************************************/
#include "StdAfx.h"
#include "ChartLegendElement.h"

CChartLegendElement::CChartLegendElement(void)
{
}

void CChartLegendElement::setText( System::String^ value )
{
	chart->Legends["Legend1"]->Title=value;
}

void CChartLegendElement::setShapePrimaryColor( System::Drawing::Color color )
{
chart->Legends["Legend1"]->BackColor=color;
}

void CChartLegendElement::setShapeSecondaryColor( System::Drawing::Color color )
{
chart->Legends["Legend1"]->BackSecondaryColor=color;
}

void CChartLegendElement::setShapeFill( Charting::GradientStyle style )
{
chart->Legends["Legend1"]->BackGradientStyle=style;
}

void CChartLegendElement::setShapeHatching( Charting::ChartHatchStyle hatch )
{
	chart->Legends["Legend1"]->BackHatchStyle=hatch;

}

void CChartLegendElement::setFontFamily( System::String^ value )
{
	System::Drawing::FontFamily^ family= gcnew System::Drawing::FontFamily(value);

	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;
	int size=chart->Legends["Legend1"]->Font->SizeInPoints;

	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartLegendElement::setBoldFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Legends["Legend1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;
	int size=chart->Legends["Legend1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Bold;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Bold;

	bOK=!bOK;

	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartLegendElement::setFontSize( int size )
{
	System::Drawing::FontFamily^ family=chart->Legends["Legend1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;

	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}


void CChartLegendElement::setIFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Legends["Legend1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Italic;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Italic;

	bOK=!bOK;


	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartLegendElement::setUFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Legends["Legend1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;
	int size=chart->Legends["Legend1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Underline;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Underline;

	bOK=!bOK;

	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartLegendElement::setDeleteFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Legends["Legend1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Legends["Legend1"]->Font->Style;
	int size=chart->Legends["Legend1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Strikeout;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Strikeout;

	bOK=!bOK;


	chart->Legends["Legend1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartLegendElement::setAlignment( System::Drawing::ContentAlignment align )
{
	//chart->Legends["Legend1"]->Alignment=align;
}

void CChartLegendElement::setDocking( Charting::Docking dock )
{
	chart->Legends["Legend1"]->Docking=dock;
}