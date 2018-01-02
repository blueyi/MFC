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
    
	Note :	  		chart tools Ribbon tabs do synchronize with "chart ppties". Getters needed here.
*********************************************************************/
#pragma once
using namespace System::Windows::Forms::DataVisualization;
ref class CFormatElementBase
{
public:
	CFormatElementBase();
	static CFormatElementBase^ createFormatElement(int id);
	void setChart(Charting::Chart^  chart);
protected:
	Charting::Chart^  chart;
public:
	virtual void setText(System::String^ value);
	//Shape Functions :
	virtual void setShapePrimaryColor(System::Drawing::Color color);
	virtual void setShapeSecondaryColor(System::Drawing::Color color);
	virtual void setShapeFill(Charting::GradientStyle style);
	virtual void setShapeHatching(Charting::ChartHatchStyle hatch);
	//Outline functions :
	virtual void setOutlineColor(System::Drawing::Color color);
	virtual void setOutlineStyle(Charting::ChartDashStyle dashStyle);
	virtual void setOutlineSize(int size);
	//Size :
	virtual void setSizeWidth(int width){};
	virtual void setSizeHeight(int heigth){};
	//Orientation :
	virtual void setAlignment(System::Drawing::ContentAlignment align);
	virtual void setDocking(Charting::Docking dock);
	virtual void reverse();
	//Font
	virtual void setFontFamily(System::String^ value);
	virtual void setFontSize(int size);
	virtual void setBoldFont();
	virtual void setIFont(){};
	virtual void setUFont(){};
	virtual void setDeleteFont(){};
	virtual void setFontLeft(){};
	virtual void setFontCenter(){};
	virtual void setFontRight(){};
};
