/********************************************************************
    File:	        ChartTitleElement	
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
#include "ChartTitleElement.h"

CChartTitleElement::CChartTitleElement(void)
{
}

void CChartTitleElement::setText( System::String^ value )
{
	chart->Titles["Title1"]->Text=value;
}

void CChartTitleElement::setShapePrimaryColor( System::Drawing::Color color )
{
	chart->Titles["Title1"]->BackColor = color;
}

void CChartTitleElement::setShapeSecondaryColor( System::Drawing::Color color )
{
	chart->Titles["Title1"]->BackSecondaryColor=color;
}

void CChartTitleElement::setShapeFill( Charting::GradientStyle style )
{
	chart->Titles["Title1"]->BackGradientStyle=style;
}

void CChartTitleElement::setShapeHatching( Charting::ChartHatchStyle hatch )
{
	chart->Titles["Title1"]->BackHatchStyle=hatch;
}

void CChartTitleElement::setOutlineColor( System::Drawing::Color color )
{
	chart->Titles["Title1"]->ForeColor=color;
}

void CChartTitleElement::setOutlineStyle( Charting::ChartDashStyle dashStyle )
{
	chart->Titles["Title1"]->BorderDashStyle=dashStyle;
}

void CChartTitleElement::setOutlineSize( int size )
{
	chart->Titles["Title1"]->BorderWidth=size;
}

void CChartTitleElement::setAlignment( System::Drawing::ContentAlignment align )
{
	chart->Titles["Title1"]->Alignment=align;
}

void CChartTitleElement::setDocking( Charting::Docking dock )
{
	chart->Titles["Title1"]->Docking=dock;
}

void CChartTitleElement::setFontFamily( System::String^ value )
{
	System::Drawing::FontFamily^ family= gcnew System::Drawing::FontFamily(value);
	
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;

	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));


}

void CChartTitleElement::setBoldFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Titles["Title1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Bold;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Bold;

	bOK=!bOK;
	
	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
}

void CChartTitleElement::setIFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Titles["Title1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Italic;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Italic;

	bOK=!bOK;


	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartTitleElement::setUFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Titles["Title1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Underline;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Underline;

	bOK=!bOK;

	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartTitleElement::setDeleteFont()
{
	static bool bOK=true;

	System::Drawing::FontFamily^ family=chart->Titles["Title1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	int size=chart->Titles["Title1"]->Font->SizeInPoints;
	//chart->Titles["Title1"]->Font->Bold=!chart->Titles["Title1"]->Font->Bold;

	if(bOK)
		fontStyle = fontStyle | System::Drawing::FontStyle::Strikeout;
	else
		fontStyle =fontStyle - System::Drawing::FontStyle::Strikeout;

	bOK=!bOK;


	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}

void CChartTitleElement::setFontSize( int size )
{
	System::Drawing::FontFamily^ family=chart->Titles["Title1"]->Font->FontFamily;
	System::Drawing::FontStyle fontStyle=chart->Titles["Title1"]->Font->Style;
	
	chart->Titles["Title1"]->Font=(gcnew System::Drawing::Font(family, size,fontStyle , System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

}