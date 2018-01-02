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
#pragma once
#include "Feature.h"

class CTest;
class PROFILER_API CActivity : public CFeature
{
public:
	//Class CCheckPoint.
	class CCheckPoint{
	public:
		CCheckPoint(std::string pointName,TIMESTAMP time)
		{
			this->pointName=pointName;
			this->time=time;
		}
	private:
		std::string pointName;
		TIMESTAMP time;
	public:
		std::string getName()
		{
			return pointName;
		}
		TIMESTAMP getTime()
		{
			return time;
		}
	};
	typedef std::vector<CCheckPoint*> PointsVector;

	//

	CActivity(std::string blocName,TIMESTAMP start);
	CActivity(std::string blocName);
	~CActivity(void);
private:
	std::string blocName;
	PointsVector pointVector;
	//std::vector<CCheckPoint*>::iterator pointIt;
public:
	PointsVector& getPoints();
	std::string getName(){
		return blocName;
	}
	void insertPoint(std::string pointName,std::string timeValue);
	void insertPoint(std::string pointName,TIMESTAMP time);
	void endMainBloc(TIMESTAMP time);
	TIMESTAMP getStart(){
		return pointVector.front()->getTime();
	}
	TIMESTAMP getStop(){
		return pointVector.back()->getTime();
	}
	double getTimeElapse()
	{
		return getStop()-getStart();
	}
	int getPointsCount()
	{
		int count=0;
		std::vector<CCheckPoint*>::iterator myIt;
		for (myIt = pointVector.begin(); myIt != pointVector.end(); myIt++ ){
			count++;
		}
		return count;
	}
	void flush(XMLNode& blocNode);

	static CActivity* createFromXML(XMLNode& xMainNode,CTest* pParentTest){
		std::string blocName=xMainNode.getAttribute("name");
		CActivity* pBloc=new CActivity(blocName);
		pBloc->setParentTest(pParentTest);

		int nPoints=xMainNode.nChildNode("point");
		int it=0;

		for (int i=0;i<nPoints;i++)
		{
			XMLNode xPoint=xMainNode.getChildNode("point",&it);

			std::string name=xPoint.getAttribute("pointName");
			std::string value=xPoint.getAttribute("timeValue");

			pBloc->insertPoint(name,value);
		}

		return pBloc;
	}
	//
	CTest* pParentTest;//
	CTest* getParentTest()
	{
		return pParentTest;
	}
	void setParentTest(CTest* pParentTest)
	{
		this->pParentTest=pParentTest;
	}
};
