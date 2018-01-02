/********************************************************************
    File:	        ChartYAxisElement	
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
#pragma once
#include "formatelementbase.h"

ref class CChartYAxisElement :
public CFormatElementBase
{
public:
	CChartYAxisElement(void);
public:
	virtual void setText(System::String^ value) override;;
	//Shape Functions :
	virtual void setShapePrimaryColor(System::Drawing::Color color) override{};
	virtual void setShapeSecondaryColor(System::Drawing::Color color) override{};
	virtual void setShapeFill(Charting::GradientStyle style) override{};
	virtual void setShapeHatching(Charting::ChartHatchStyle hatch) override{};
	//Outline functions :
	virtual void setOutlineColor(System::Drawing::Color color) override{};
	virtual void setOutlineStyle(Charting::ChartDashStyle dashStyle) override{};
	virtual void setOutlineSize(int size) override{};
	//Orientation :
	virtual void setAlignment(System::Drawing::ContentAlignment align) override{};
	virtual void setDocking(Charting::Docking dock) override{};
	//Reverse
	//Font
	virtual void setFontFamily(System::String^ value) override{};
	virtual void setFontSize(int size) override{};
	virtual void setBoldFont() override{};
	virtual void setIFont() override{};
	virtual void setUFont() override{};
	virtual void setDeleteFont() override{};
	virtual void setFontLeft() override;;
	virtual void setFontCenter() override;;
	virtual void setFontRight() override;;
};
