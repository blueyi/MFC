/********************************************************************
    File:	        CompareTool	
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
#include "Factory.h"
#include "ChartControl.h"

class CCompareTool
{
public:
	CCompareTool(void);
	~CCompareTool(void);
	//
	virtual void execute(std::vector<CTest*> tests,std::string targetName,std::string extraTargetName)=0;
	virtual void render()=0;
private:
	CFeature::Type targetType;
	CFeature::Type extraTargetType;
protected:
	void setParams(CFeature::Type targetType,CFeature::Type extraTargetType)
	{
		this->targetType=targetType;
		this->extraTargetType=extraTargetType;
	}
public:
	CFeature::Type getTargetType(){
		return targetType;
	}
	CFeature::Type getExtraTargetType(){
		return extraTargetType;
	}

private:
	COLORREF blue,red,green;
	int nBlueRanges,nRegRanges,nGreenRanges;
	int nCurrentBlueIndex,nCurrentRedIndex,nCurrentGreenIndex;
protected:
	void setupBlueColor(int nRanges)
	{
		nBlueRanges=nRanges;
		blue=RGB(143,177,213);
		nCurrentBlueIndex=0;
	}
	COLORREF GetNextBlue()
	{
		int startRed=143,startBlue=213,startGreen=177;
		int endRed=38,endBlue=94,endGreen=66;

		int offsetRed=(startRed-endRed)/nBlueRanges;
		int offsetGreen=(startGreen-endGreen)/nBlueRanges;
		int offsetBlue=(startBlue-endBlue)/nBlueRanges;

		COLORREF retCl= RGB(startRed- (offsetRed*nCurrentBlueIndex), startGreen- (offsetGreen*nCurrentGreenIndex), startBlue-(offsetBlue*nCurrentBlueIndex));
		nCurrentBlueIndex++;
		return retCl;
	}
};

DECLARE_CLASS_FACTORY_EXT(CCompareTool, factory2)