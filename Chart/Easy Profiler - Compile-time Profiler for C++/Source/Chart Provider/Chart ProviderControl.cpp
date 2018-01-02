// Chart Provider.cpp : main project file.
/********************************************************************
    File:	        Chart ProviderControl	
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
#include "Chart ProviderControl.h"

#include "FormatElementBase.h"
void ChartProvider::ChartProviderControl::addNewPoint( System::String^ seriesName,System::String^ xPointLabel, System::Double yTimeValue )
{
	this->chart1->Series[seriesName]->Points->AddXY(xPointLabel,yTimeValue);

	this->chart1->Refresh();
}

void ChartProvider::ChartProviderControl::setupNewSeries( System::String^ seriesName,int seriesType )
{
	System::Windows::Forms::DataVisualization::Charting::Series^  pNewSeries = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
	/*
	pNewSeries->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
	static_cast<System::Int32>(static_cast<System::Byte>(64)));
	*/
	switch (seriesType)
	{
	case 1:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		break;
	case 2:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Column;
		break;
	case 3:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StackedColumn;
		break;
	case 4:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Pie;
		break;
	case 5:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
		break;
	case 6:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Area;
		break;
	case 7:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
		break;
	case 8:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Doughnut;
		break;
	default:
		pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		break;
	}
	//pNewSeries->CustomAttributes= L"DrawingStyle=Cylinder";
	pNewSeries->Name = seriesName;
	pNewSeries->ShadowOffset = 1;
	this->chart1->Series->Add(pNewSeries);
}

void ChartProvider::ChartProviderControl::resetChart()
{
	this->chart1->Series->Clear();
	this->chart1->Refresh();
}

void ChartProvider::ChartProviderControl::setGlobalProperty( int propertyID,int value )
{
	if(propertyID==PropEnable3D)//3D
		this->chart1->ChartAreas[0]->Area3DStyle->Enable3D=(value==1);
	if(propertyID==PropWallWidth)
		this->chart1->ChartAreas[0]->Area3DStyle->WallWidth=value;
	if (propertyID==PropDataLabelShowState)
	{
		for each(System::Windows::Forms::DataVisualization::Charting::Series^ pNewSeries in this->chart1->Series)
		{
			pNewSeries->IsValueShownAsLabel=!pNewSeries->IsValueShownAsLabel;
		}				
	}
	if(propertyID==PropLegendShowState)
		this->chart1->Legends["Legend1"]->Enabled=!this->chart1->Legends["Legend1"]->Enabled;
	if (propertyID==PropAxisShowState)
	{
		if(value==0)
			this->chart1->ChartAreas["ChartArea1"]->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
		if(value==1)
			this->chart1->ChartAreas["ChartArea1"]->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
		if(value==2)
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
		if(value==3)
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
	}
	if(propertyID==PropPointDepth)
		this->chart1->ChartAreas[0]->Area3DStyle->PointDepth=value;
	if(propertyID==PropGapDepth)
		this->chart1->ChartAreas[0]->Area3DStyle->PointGapDepth=value;
	if(propertyID==PropPerspective)
		this->chart1->ChartAreas[0]->Area3DStyle->Perspective=value;
	if(propertyID==PropRotateX)
		this->chart1->ChartAreas[0]->Area3DStyle->Inclination=value;
	if(propertyID==PropRotateY)
		this->chart1->ChartAreas[0]->Area3DStyle->Rotation=value;
	if(propertyID==PropGraphicsAntiliasing)
	{
		if(this->chart1->AntiAliasing==Charting::AntiAliasingStyles::All)
			this->chart1->AntiAliasing=Charting::AntiAliasingStyles::None;
		else
			this->chart1->AntiAliasing=Charting::AntiAliasingStyles::All;
	}
	if (propertyID==PropTextAntiliasingQuality)
	{
		if(this->chart1->TextAntiAliasingQuality==Charting::TextAntiAliasingQuality::High)
			this->chart1->TextAntiAliasingQuality=Charting::TextAntiAliasingQuality::Normal;
		else
			this->chart1->TextAntiAliasingQuality=Charting::TextAntiAliasingQuality::High;
	}
	if (propertyID==PropChartPalette)
	{
		switch (value)
		{
		case 0:
			this->chart1->Palette = Charting::ChartColorPalette::Grayscale;
		case 1:
			this->chart1->Palette = Charting::ChartColorPalette::Excel;
		case 2:
			this->chart1->Palette = Charting::ChartColorPalette::Light;
		case 3:
			this->chart1->Palette = Charting::ChartColorPalette::Pastel;
		case 4:
			this->chart1->Palette = Charting::ChartColorPalette::EarthTones;
		case 5:
			this->chart1->Palette = Charting::ChartColorPalette::SemiTransparent;
		case 6:
			this->chart1->Palette = Charting::ChartColorPalette::Berry;
		case 7:
			this->chart1->Palette = Charting::ChartColorPalette::Chocolate;
		case 8:
			this->chart1->Palette = Charting::ChartColorPalette::Fire;
		}
		this->chart1->Refresh();
	}
}


int ChartProvider::ChartProviderControl::getGlobalProperty( int propertyID )
{
	if(propertyID==PropEnable3D)//3D
		return this->chart1->ChartAreas[0]->Area3DStyle->Enable3D ? 1 :0;
	if(propertyID==PropWallWidth)
		return this->chart1->ChartAreas[0]->Area3DStyle->WallWidth;
	if (propertyID==PropDataLabelShowState)
	{
		for each(System::Windows::Forms::DataVisualization::Charting::Series^ pNewSeries in this->chart1->Series)
		{
			return pNewSeries->IsValueShownAsLabel;
		}
		return 0;
	}
	if (propertyID==PropLegendShowState)
		return this->chart1->Legends["Legend1"]->Enabled;
	if(propertyID==PropGraphicsAntiliasing)
	{
		return this->chart1->AntiAliasing==Charting::AntiAliasingStyles::All ? 1 : 0 ;
	}
	if (propertyID==PropTextAntiliasingQuality)
	{
		return this->chart1->TextAntiAliasingQuality==Charting::TextAntiAliasingQuality::High ? 1 : 0 ;
	}
}

void ChartProvider::ChartProviderControl::setChartTypeForAllSeries( int seriesType )
{
	//
	for each(System::Windows::Forms::DataVisualization::Charting::Series^ pNewSeries in this->chart1->Series)
	{
		switch (seriesType)
		{
		case 1:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			break;
		case 2:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Column;
			break;
		case 3:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StackedColumn;
			break;
		case 4:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Pie;
			break;
		case 5:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
			break;
		case 6:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Area;
			break;
		case 7:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			break;
		case 8:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Doughnut;
			break;
		default:
			pNewSeries->ChartType=System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			break;
		}
	}
}

void ChartProvider::ChartProviderControl::setFormat( int FormatElement, int FormatCommand,System::String^ value )
{
	



	/*
	this->chart1->Titles["Title1"]->Text=value;
		this->chart1->Refresh();*/
	CFormatElementBase^ elementHandler=CFormatElementBase::createFormatElement(FormatElement);
	elementHandler->setChart(this->chart1);
	//
	if (FormatCommand==Format_Text)
		elementHandler->setText(value);
	if (FormatCommand==Format_FontName)
	{
		elementHandler->setFontFamily(value);
		this->chart1->Titles["Title1"]->Font = (gcnew System::Drawing::Font(value, 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(0)));
	}
	if (FormatCommand==Format_ShapeColor1)
	{
		System::String^ rValue=value->Substring(0,3);
		System::String^ gValue=value->Substring(3,3);
		System::String^ bValue=value->Substring(6,3);

		System::Drawing::Color color=System::Drawing::Color::FromArgb(System::Convert::ToByte(rValue),
			System::Convert::ToByte(gValue),System::Convert::ToByte(bValue));
		elementHandler->setShapePrimaryColor(color);
	}
	if (FormatCommand==Format_ShapeColor2)
	{
		System::String^ rValue=value->Substring(0,3);
		System::String^ gValue=value->Substring(3,3);
		System::String^ bValue=value->Substring(6,3);

		System::Drawing::Color color=System::Drawing::Color::FromArgb(System::Convert::ToByte(rValue),
			System::Convert::ToByte(gValue),System::Convert::ToByte(bValue));
		elementHandler->setShapeSecondaryColor(color);
	}
	if (FormatCommand==Format_ShapeGradient)
	{
		int iValue=System::Convert::ToInt16( value );

		Charting::GradientStyle gradient;
		switch (iValue)
		{
		case 0:
			gradient = Charting::GradientStyle::None;
			break;
		case 1:
			gradient = Charting::GradientStyle::LeftRight;
			break;
		case 2:
			gradient = Charting::GradientStyle::TopBottom;
			break;
		case 3:
			gradient = Charting::GradientStyle::Center;
			break;
		case 4:
			gradient = Charting::GradientStyle::DiagonalLeft;
			break;
		case 5:
			gradient = Charting::GradientStyle::DiagonalRight;
			break;
		case 6:
			gradient = Charting::GradientStyle::HorizontalCenter;
			break;
		case 7:
			gradient = Charting::GradientStyle::VerticalCenter;
			break;
		}
		elementHandler->setShapeFill(gradient);
	}
	if (FormatCommand==Format_ShapeHatch)
	{
		/*
		#define ID_HATCHING_NONE                32853
		#define ID_HATCHING_CROSS               32854
		#define ID_HATCHING_DIVOT               32855
		#define ID_HATCHING_HORIZONTAL          32856
		#define ID_HATCHING_VERTICAL            32857
		*/
		int iValue=System::Convert::ToInt16( value );

		Charting::ChartHatchStyle style;
		switch (iValue)
		{
		case 0:
			style = Charting::ChartHatchStyle::None;
			break;
		case 1:
			style = Charting::ChartHatchStyle::Cross;
			break;
		case 2:
			style = Charting::ChartHatchStyle::Divot;
			break;
		case 3:
			style = Charting::ChartHatchStyle::Horizontal;
			break;
		case 4:
			style = Charting::ChartHatchStyle::Vertical;
			break;
		}
		elementHandler->setShapeHatching(style);
	}
	if (FormatCommand==Format_OutlineColor)
	{
		System::String^ rValue=value->Substring(0,3);
		System::String^ gValue=value->Substring(3,3);
		System::String^ bValue=value->Substring(6,3);

		System::Drawing::Color color=System::Drawing::Color::FromArgb(System::Convert::ToByte(rValue),
			System::Convert::ToByte(gValue),System::Convert::ToByte(bValue));
		elementHandler->setOutlineColor(color);
	}
	if (FormatCommand==Format_OutlineStyle)
	{
		/*
		#define ID_OUTLINESTYLE_NOTSET          33100
		#define ID_OUTLINESTYLE_DASH            33101
		#define ID_OUTLINESTYLE_DASHDOT         33102
		#define ID_OUTLINESTYLE_DASHDOTDOT      33103
		#define ID_OUTLINESTYLE_DOT             33104
		#define ID_OUTLINESTYLE_SOLID           33105
		*/
		int iValue=System::Convert::ToInt16( value );

		Charting::ChartDashStyle dashStyle;
		switch (iValue)
		{
		case 0:
			dashStyle = Charting::ChartDashStyle::NotSet;
			break;
		case 1:
			dashStyle = Charting::ChartDashStyle::Dash;
			break;
		case 2:
			dashStyle = Charting::ChartDashStyle::DashDot;
			break;
		case 3:
			dashStyle = Charting::ChartDashStyle::DashDotDot;
			break;
		case 4:
			dashStyle = Charting::ChartDashStyle::Dot;
			break;
		case 5:
			dashStyle = Charting::ChartDashStyle::Solid;
			break;
		}
		elementHandler->setOutlineStyle(dashStyle);
	}
	if (FormatCommand==Format_OutlineSize)
	{
		int iValue=System::Convert::ToInt16( value );
		elementHandler->setOutlineSize(iValue);
	}
	if (FormatCommand==Format_SizeWidth)
	{
		int iValue=System::Convert::ToInt16( value );
		elementHandler->setSizeWidth(iValue);
	}
	if (FormatCommand==Format_SizeLength)
	{
		int iValue=System::Convert::ToInt16( value );
		elementHandler->setSizeHeight(iValue);
	}
	if (FormatCommand==Format_OrientationAlignment)
	{
		int iValue=System::Convert::ToInt16( value );
		System::Drawing::ContentAlignment alignmentValue;

		/*
		#define ID_ALIGN_MIDDLECENTER           32811
		#define ID_ALIGN_TOPLEFT                32812
		#define ID_ALIGN_TOPCENTER              32813
		#define ID_ALIGN_TOPRIGHT               32814
		#define ID_ALIGN_MIDDLELEFT             32815
		#define ID_ALIGN_MIDDLERIGHT            32816
		#define ID_ALIGN_BOTTOMCENTER           32817
		#define ID_ALIGN_BOTTOMLEFT             32818
		#define ID_ALIGN_BOTTOMRIGHT            32819
		*/
		switch (iValue)
		{
		case 0:
			alignmentValue=System::Drawing::ContentAlignment::MiddleCenter;
			break;
		case 1:
			alignmentValue = System::Drawing::ContentAlignment::TopLeft;
			break;
		case 2:
			alignmentValue = System::Drawing::ContentAlignment::TopCenter;
			break;
		case 3:
			alignmentValue = System::Drawing::ContentAlignment::TopRight;
			break;
		case 4:
			alignmentValue = System::Drawing::ContentAlignment::MiddleLeft;
			break;
		case 5:
			alignmentValue = System::Drawing::ContentAlignment::MiddleRight;
			break;
		case 6:
			alignmentValue = System::Drawing::ContentAlignment::BottomCenter;
			break;
		case 7:
			alignmentValue = System::Drawing::ContentAlignment::BottomLeft;
			break;
		case 8:
			alignmentValue = System::Drawing::ContentAlignment::BottomRight;
			break;
		}
		elementHandler->setAlignment(alignmentValue);
	}
	if (FormatCommand==Format_OrientationDocking)
	{
		int iValue=System::Convert::ToInt16( value );
		Charting::Docking docking;

		switch (iValue)
		{
		case 0:
			docking = System::Windows::Forms::DataVisualization::Charting::Docking::Top;
			break;
		case 1:
			docking = System::Windows::Forms::DataVisualization::Charting::Docking::Left;
			break;
		case 2:
			docking = System::Windows::Forms::DataVisualization::Charting::Docking::Right;
			break;
		case 3:
			docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			break;
		}
		elementHandler->setDocking(docking);
	}
	if (FormatCommand==Format_OrientationReverse)
	{
		elementHandler->reverse();
	}
	if (FormatCommand==Format_FontName)
	{
		elementHandler->setFontFamily(value);
	}
	if (FormatCommand==Format_FontSize)
	{
		int iValue=System::Convert::ToInt16( value );
		elementHandler->setFontSize(iValue);
	}
	if (FormatCommand==Format_FontBold)
	{
		elementHandler->setBoldFont();
	}
	if (FormatCommand==Format_FontItalic)
	{
		elementHandler->setIFont();
	}
	if (FormatCommand==Format_FontUnderline)
	{
		elementHandler->setUFont();
	}
	if (FormatCommand==Format_FontDeleted)
	{
		elementHandler->setDeleteFont();
	}
	if (FormatCommand==Format_FontCenter)
	{
		elementHandler->setFontCenter();
	}
	if (FormatCommand==Format_FontLeft)
	{
		elementHandler->setFontLeft();
	}
	if (FormatCommand==Format_FontRight)
	{
		elementHandler->setFontRight();
	}

	//End of format commands.
}

void ChartProvider::ChartProviderControl::saveImageToFile( System::String^ filePath,System::String^ ext )
{
	Charting::ChartImageFormat format = Charting::ChartImageFormat::Bmp;

	if( ext=="bmp")
	{
		format = Charting::ChartImageFormat::Bmp;
	}
	else if( ext=="jpg" )
	{
		format = Charting::ChartImageFormat::Jpeg;
	}
	else if( ext=="emf" )
	{
		format = Charting::ChartImageFormat::Emf;
	}
	else if( ext=="gif" )
	{
		format = Charting::ChartImageFormat::Gif;
	}
	else if( ext=="png" )
	{
		format = Charting::ChartImageFormat::Png;
	}
	else if( ext=="tif" )
	{
		format = Charting::ChartImageFormat::Tiff;
	}

	this->chart1->SaveImage(filePath,format);
}

void ChartProvider::ChartProviderControl::printPreview( int command )
{
	switch (command)
	{
	case 0:
		this->chart1->Printing->PageSetup();
		break;
	case 1:
		this->chart1->Printing->PrintPreview();
		break;
	default:
		this->chart1->Printing->Print(true);
		break;
	}	
}

void ChartProvider::ChartProviderControl::setSeriesColor( System::String^ seriesName,System::String^ seriesColor )
{
	System::String^ rValue=seriesColor->Substring(0,3);
	System::String^ gValue=seriesColor->Substring(3,3);
	System::String^ bValue=seriesColor->Substring(6,3);

	System::Drawing::Color color=System::Drawing::Color::FromArgb(System::Convert::ToByte(rValue),
		System::Convert::ToByte(gValue),System::Convert::ToByte(bValue));

	this->chart1->Series[seriesName]->Color=color;
}