/********************************************************************
    File:	        TestSourceBase	
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


#define  TESTSOURCE_FILE 1
#define  TESTSOURCE_FOLDER 2
class CTestSourceBase
{
public:
	CTestSourceBase(int type);
	~CTestSourceBase(void);
private:
	int type;
public:
	int GetType();
};


class CFileSourceTest : public CTestSourceBase
{
public:
	CFileSourceTest(CString filePath,CTestsFile* pTests):CTestSourceBase(TESTSOURCE_FILE)
	{
		this->filePath=filePath;
		this->pTests=pTests;
	}
private:
	CString filePath;
	CTestsFile* pTests;
public:
	CString GetFilePath()
	{
		return filePath;
	}
	CTestsFile* GetFragmentedTests()
	{
		return pTests;
	}
};

class CFolderSourceTest : public CTestSourceBase
{
public:
	CFolderSourceTest(CString folderPath) : CTestSourceBase(TESTSOURCE_FOLDER)
	{
		this->folderPath=folderPath;
	}
private:
	CString folderPath;
	CArray<CTestsFile*> filesArray;
public:
	CString GetFolderPath()
	{
		return folderPath;
	}
	//
   
};