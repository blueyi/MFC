/********************************************************************
    File:	        TestsCollection	
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
#include "TestsCollection.h"



CTestsFile* CTestsFile::createFromXML( std::string path )
{
	CTestsFile* pHist=new CTestsFile(path);

	XMLNode xMainNode=XMLNode::openFileHelper(path.c_str(),"profilingData");

	int nSessions=xMainNode.nChildNode("test");
	int it=0;

	for (int i=0;i<nSessions;i++)
	{
		XMLNode xSession=xMainNode.getChildNode("test",&it);
		CTest* pTest=CTest::createFromXML(xSession);
		pHist->testSessionVector.push_back(pTest);
		pTest->setTestsFile(pHist);
	}

	return pHist;
}

CTestsFile::CTestsFile( std::string filePath )
{
	this->fileName=filePath;
}

TestsVector& CTestsFile::getTestsVector()
{
	return testSessionVector;
}

std::string CTestsFile::GetFilePath()
{
	return fileName;
}

void CTestsFile::updateTestDescriptionInXML( CTest* pTest,std::string newDescription )
{
	std::string regionName=pTest->getName();
	std::string dateTime=pTest->getDateTime();

	XMLNode xMainNode=XMLNode::openFileHelper(fileName.c_str(),"profilingData");

	int nSessions=xMainNode.nChildNode("test");
	int it=0;

	for (int i=0;i<nSessions;i++)
	{
		XMLNode xSession=xMainNode.getChildNode("test",&it);


		//
		std::string xRegionName=xSession.getAttribute("regionName");
		std::string xDateTime=xSession.getAttribute("dateTime");

		if (xRegionName==regionName && dateTime==xDateTime)
		{
			xSession.updateAttribute(newDescription.c_str(),NULL,"description");
		}
	}
	//
	xMainNode.writeToFile(fileName.c_str());

	pTest->setDescription(newDescription);
	/*
	//Now remove from the vector :
		for (TestsVector::iterator myIt=testSessionVector.begin();myIt!=testSessionVector.end();myIt++)
		{
			if(pTest==*myIt)
			{
				testSessionVector.erase(myIt);
				delete pTest;
				return;
			}
		}*/
	
}

void CTestsFile::removeTestFromXML( CTest* pTest )
{
	std::string regionName=pTest->getName();
	std::string dateTime=pTest->getDateTime();

	XMLNode xMainNode=XMLNode::openFileHelper(fileName.c_str(),"profilingData");

	int nSessions=xMainNode.nChildNode("test");
	int it=0;

	for (int i=0;i<nSessions;i++)
	{
		XMLNode xSession=xMainNode.getChildNode("test",&it);


		//
		std::string xRegionName=xSession.getAttribute("regionName");
		std::string xDateTime=xSession.getAttribute("dateTime");

		if (xRegionName==regionName && dateTime==xDateTime)
		{
			xSession.deleteNodeContent();
		}
	}
	//
	xMainNode.writeToFile(fileName.c_str());

	//Now remove from the vector :
	for (TestsVector::iterator myIt=testSessionVector.begin();myIt!=testSessionVector.end();myIt++)
	{
		if(pTest==*myIt)
		{
			testSessionVector.erase(myIt);
			delete pTest;
			return;
		}
	}
}

void CTestsFile::releaseFile( CTestsFile* pFile )
{
	delete pFile;
}

void CTestsFile::setParentFolder( std::string parentFolder )
{
	this->parentFolder=parentFolder;
}

std::string CTestsFile::GetParentFolder()
{
	return parentFolder;
}