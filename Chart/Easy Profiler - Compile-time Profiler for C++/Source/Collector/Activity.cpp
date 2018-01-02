/********************************************************************
    File:	        Activity	
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
#include "Activity.h"




CActivity::CActivity( std::string blocName,TIMESTAMP start )
:CFeature(Activity)
{
	this->blocName=blocName;
	insertPoint("start",start);
}

CActivity::CActivity( std::string blocName )
:CFeature(Activity)
{
	this->blocName=blocName;
}

CActivity::PointsVector& CActivity::getPoints()
{
	return pointVector;
}

void CActivity::insertPoint( std::string pointName,TIMESTAMP time )
{
	pointVector.push_back(new CCheckPoint(pointName,time));
}

void CActivity::insertPoint( std::string pointName,std::string timeValue )
{
	double dwTimeVal=atof(timeValue.c_str());
	insertPoint(pointName,dwTimeVal);
}
void CActivity::endMainBloc( TIMESTAMP time )
{
	insertPoint("stop",time);
}

void CActivity::flush( XMLNode& blocNode )
{
	for (PointsVector::iterator myIt = pointVector.begin(); myIt != pointVector.end(); myIt++ ){
		CCheckPoint* pPoint=*myIt;

		XMLNode pointNode=blocNode.addChild("point");
		//adding attributes.
		pointNode.addAttribute("pointName",pPoint->getName().c_str());
		pointNode.addAttribute("timeValue",CUtilities::GetFormattedTime(pPoint->getTime()).c_str());
	}
}