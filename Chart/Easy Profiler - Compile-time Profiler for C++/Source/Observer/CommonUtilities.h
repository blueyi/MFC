/********************************************************************
    File:	        CommonUtilities	
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

class CCommonUtilities
{
public:
	static std::string toBasicString(CString strMFC){
		char  buffer[800];

		sprintf(buffer,"%S",strMFC);

		std::string strSTL(buffer);

		return strSTL;

	}
	static CString toMFCString(std::string stl_str){
		CString str;
		str.Format(_T("%S"),stl_str.c_str());

		return str;
	}
	static CString toMFCString(CString str){
		return str;
	}

	static std::string DWORD2String(DWORD dwValue)
	{
		char  buffer[800];
		sprintf(buffer,"0x%x",dwValue);
		std::string strSTL(buffer);
		return strSTL;
	}
	
	DWORD String2DWORD(std::string str)
	{
		DWORD _dwReadValue;
		sscanf(str.c_str() , "%x", &_dwReadValue );  // C4996
		return _dwReadValue;
	}
	static void CopyToClipBoard(CStringA source)
	{
		if(OpenClipboard(NULL))
		{
			HGLOBAL clipbuffer;
			char * buffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(source));
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_TEXT,clipbuffer);
			CloseClipboard();
		}		
	}
	static CStringA GetClipBoardContent()
	{
		char * buffer = NULL;

		CStringA fromClipboard;
		if ( OpenClipboard(NULL) ) 
		{
			HANDLE hData = GetClipboardData( CF_TEXT );
			char * buffer = (char*)GlobalLock( hData );
			fromClipboard = buffer;
			GlobalUnlock( hData );
			CloseClipboard();
		}

		return fromClipboard;
	}
	//////////////////////////////////////////////////////////////////////////
#define MAC_DIM					6

	static CString GetSerialKey(bool bTirets=true)
	{
		RETVALUE lResult = SUCCESS;

		// Retrieve the MAC address
		BYTE lMACaddress[MAC_DIM];
		lResult = RetrieveMACAddress(lMACaddress);
		if(lResult!=SUCCESS)
			return _T("Failed");
		BYTE pMachineCode[6];
		//
		pMachineCode[0] = lMACaddress[5];
		pMachineCode[1] = lMACaddress[0];
		pMachineCode[2] = lMACaddress[4];
		pMachineCode[3] = lMACaddress[1];
		pMachineCode[4] = lMACaddress[3];
		pMachineCode[5] = lMACaddress[2];

		
		CString first=GetEncrypt4Char(pMachineCode[0],pMachineCode[1]);
		CString second=GetEncrypt4Char(pMachineCode[2],pMachineCode[3]);
		CString third=GetEncrypt4Char(pMachineCode[4],pMachineCode[5]);
		CString fourth=GetEncrypt4Char(pMachineCode[5],pMachineCode[3]);
		//
		if(bTirets)
			return first.MakeUpper().Left(4)+_T("-")+second.MakeUpper().Left(4)+_T("-")+third.MakeUpper().Left(4)+_T("-")+fourth.MakeUpper().Left(4);
		else
			return first.MakeUpper().Left(4)+second.MakeUpper().Left(4)+third.MakeUpper().Left(4)+fourth.MakeUpper().Left(4);

		//return _T("0000-0000-0000-1234");
	}
	static CString GetEncrypt4Char(BYTE byte1,BYTE byte2)
	{
		unsigned int b    = 378551;
		unsigned int a    = 63689;
		unsigned int hash = 0;

		//
		hash = hash * a + (int)byte1;
		a    = a * b;
		//
		hash = hash * a + (int)byte2;

		//Compute from Hash :
		CString str;
		str.Format(_T("%4x"),hash);

		return str;
	}
	enum RETVALUE
	{
		SUCCESS,
		ERROR_API_CALL_FAILED,
		ERROR_FAILURE_WHILE_LOADING_LIBRARY,
		ERROR_OS_VERSION_NOT_SUPPORTED,
		ERROR_SOFTWAREKEY_NOT_FOUND,
		ERROR_CONVERSION_CHAR_2_WCHAR_FAILED
	};
	static RETVALUE RetrieveMACAddress(BYTE pMACaddress[MAC_DIM])
	{
		RETVALUE		lReturnValue = SUCCESS;
		GUID			lGUID;
		OSVERSIONINFO	lVersionInfo;

		lVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		BOOL lResult = GetVersionEx(&lVersionInfo);	

		if (!lResult)
		{
			return ERROR_API_CALL_FAILED;
		}

		// Win 2000, Win XP, Win Me
		if	( 
			( lVersionInfo.dwMajorVersion == 5 ) 
			|| 
			( 
			( lVersionInfo.dwMajorVersion == 4 ) 
			&& 
			( lVersionInfo.dwMinorVersion == 90 ) 
			)
			)
		{
			typedef VOID  (CALLBACK* PROC)(UUID*); 

			HINSTANCE		lLib; 
			PROC			UuidCreateSequential; 

			lLib = LoadLibraryA("RPCRT4"); 

			if (lLib != NULL) 
			{ 
				UuidCreateSequential = (PROC) GetProcAddress(
					lLib, 
					"UuidCreateSequential"); 

				if (UuidCreateSequential != NULL) 
				{
					UuidCreateSequential(&lGUID); 
				}
				else
				{
					return ERROR_API_CALL_FAILED;
				}

				lResult = FreeLibrary(lLib); 
			}
			else
			{
				return ERROR_FAILURE_WHILE_LOADING_LIBRARY;
			}
		}
		else
			// Win NT (without any service pack)
			// NOTE: The string field  szCSDVersion of the structure OSVERSIONINFO 
			// give us information about the installed service pack. If the string 
			// is empty, then no service pack has been installed. If the string is 
			// something like "Service Pack 3", this means that service pack 3 
			// has been installed.
			if	( lVersionInfo.dwMajorVersion < 5 ) 
			{
				HRESULT h = CoCreateGuid(&lGUID);
			}
			else
			{
				return ERROR_OS_VERSION_NOT_SUPPORTED;
			}

			// Retrieve the MAC address 
			// (Bytes 2 through 7 of Data4 keeps the MAC address).
			for (int i=0;i<MAC_DIM;i++)
			{
				pMACaddress[i]=lGUID.Data4[i+2];
			}

			return lReturnValue;
	}

	static CString GetActivationKey(CString serialKey)
	{
		CString activationKey;
		for (int i=0;i<serialKey.GetLength();i++)
		{
			int iValue=_ttoi(serialKey.Mid(i,1));
			iValue=i*255+iValue+12;
			iValue=iValue%16;
			CString str;
			str.Format(_T("%x"),iValue);
			activationKey+=str.Left(1);
		}
		return activationKey.MakeUpper();
	}
	




	//////////////////////////////////////////////////////////////////////////
};

#define tabHomeOffset (WM_USER+1)
#define WM_OPEN_TEST_FILE (tabHomeOffset+1)
#define WM_OPEN_TEST_SUITE (tabHomeOffset+2)
#define WM_CONNECT_REMOTE (tabHomeOffset+3)
#define WM_UPDATE_SUITE (tabHomeOffset+4)
#define WM_TEST_DESCRIPTION (tabHomeOffset+5)
#define WM_TEST_DELETE (tabHomeOffset+6)
#define WM_TESTS_CLOSE (tabHomeOffset+7)
#define WM_SELECT_FILEFOLDER (tabHomeOffset+8)
#define WM_SELECT_TEST (tabHomeOffset+9)


#define tabChartLayout (WM_USER+100)
#define WM_CHART_LAYOUT_TITLE (tabChartLayout+1)
#define WM_CHART_LAYOUT_AXIS_TITLES (tabChartLayout+2)
#define WM_CHART_LAYOUT_LEGEND (tabChartLayout+3)
#define WM_CHART_LAYOUT_POINTS_LABELS (tabChartLayout+4)
#define WM_CHART_LAYOUT_AXIS (tabChartLayout+5)
#define WM_CHART_LAYOUT_GRID (tabChartLayout+6)

#define tabChartFormat (WM_USER+200)
#define WM_CHART_FORMAT_SEL_COMBO (tabChartFormat+1)
#define WM_CHART_FORMAT_TEXT (tabChartFormat+2)
#define WM_CHART_FORMAT_FILL_COLOR1 (tabChartFormat+3)
#define WM_CHART_FORMAT_FILL_COLOR2 (tabChartFormat+4)
#define WM_CHART_FORMAT_FILL_GRADIENT (tabChartFormat+5)
#define WM_CHART_FORMAT_FILL_HATCH (tabChartFormat+6)

#define WM_CHART_FORMAT_OUTLINE_COLOR (tabChartFormat+7)
#define WM_CHART_FORMAT_OUTLINE_STYLE (tabChartFormat+8)
#define WM_CHART_FORMAT_OUTLINE_SIZE (tabChartFormat+9)

#define WM_CHART_FORMAT_ORIENTATION_ALIGN (tabChartFormat+10)
#define WM_CHART_FORMAT_ORIENTATION_DOCKING (tabChartFormat+11)
#define WM_CHART_FORMAT_ORIENTATION_REVERSE (tabChartFormat+12)

#define WM_CHART_FORMAT_FONT_NAME (tabChartFormat+13)
#define WM_CHART_FORMAT_FONT_SIZE (tabChartFormat+14)
#define WM_CHART_FORMAT_FONT_BOLD (tabChartFormat+15)
#define WM_CHART_FORMAT_FONT_I (tabChartFormat+16)
#define WM_CHART_FORMAT_FONT_U (tabChartFormat+17)
#define WM_CHART_FORMAT_FONT_DELETED (tabChartFormat+18)
#define WM_CHART_FORMAT_FONT_LEFT (tabChartFormat+19)
#define WM_CHART_FORMAT_FONT_CENTER (tabChartFormat+20)
#define WM_CHART_FORMAT_FONT_RIGHT (tabChartFormat+21)

#define WM_CHART_FORMAT_SIZEX (tabChartFormat+22)
#define WM_CHART_FORMAT_SIZEY (tabChartFormat+23)


#define tabChartDesign (WM_USER+300)
#define WM_CHART_DESIGN_TYPE_COLUMN (tabChartDesign+1)
#define WM_CHART_DESIGN_TYPE_LINE (tabChartDesign+2)
#define WM_CHART_DESIGN_TYPE_PIE (tabChartDesign+3)
#define WM_CHART_DESIGN_TYPE_HCOLUMN (tabChartDesign+4)
#define WM_CHART_DESIGN_TYPE_AREA (tabChartDesign+5)
#define WM_CHART_DESIGN_TYPE_SNOW (tabChartDesign+6)
#define WM_CHART_DESIGN_TYPE_DOUGHNUT (tabChartDesign+7)
#define WM_CHART_DESIGN_PALETTE (tabChartDesign+8)

#define WM_CHART_DESIGN_ENABLE3D (tabChartDesign+9)
#define WM_CHART_DESIGN_WALL_WIDTH (tabChartDesign+10)
#define WM_CHART_DESIGN_POINT_DEPTH (tabChartDesign+11)
#define WM_CHART_DESIGN_GAP_DEPTH (tabChartDesign+12)
#define WM_CHART_DESIGN_PERSPECTIVE (tabChartDesign+13)
#define WM_CHART_DESIGN_ROTATEX (tabChartDesign+14)
#define WM_CHART_DESIGN_ROTATEY (tabChartDesign+15)
#define WM_CHART_DESIGN_GRAPHICS_ANTILIASING (tabChartDesign+16)
#define WM_CHART_DESIGN_TEXT_ANTILIASING (tabChartDesign+17)

#define tabAnalysisPreTools (WM_USER+380)
#define WM_ANALYSIS_TEST_SELECT (tabAnalysisPreTools+1)
#define WM_ANALYSIS_ITEM_SELECT (tabAnalysisPreTools+2)

#define WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL (tabAnalysisPreTools+4)
#define WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL (tabAnalysisPreTools+5)
#define WM_ANALYSIS_SINGLEWORKER_CB_SELTASK (tabAnalysisPreTools+6)


#define tabAnalysis (WM_USER+400)

#define WM_ANALYSIS_SINGLEACTIVITY_TIMELINE (tabAnalysis+4)
#define WM_ANALYSIS_SINGLEACTIVITY_STAGES (tabAnalysis+5)
#define WM_ANALYSIS_SINGLEACTIVITY_TOTALTIME (tabAnalysis+6)

#define WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_STACKED (tabAnalysis+7)
#define WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_TOTAL (tabAnalysis+8)
#define WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_STACKED (tabAnalysis+9)
#define WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_TOTAL (tabAnalysis+10)


#define WM_ANALYSIS_SINGLEACTIVITY_WITHWORKER_TOTALTIME (tabAnalysis+11)

#define WM_ANALYSIS_ALLACTIVITIES_TOTAL (tabAnalysis+12)

#define WM_ANALYSIS_SINGLETASK_RUNSHISTORY (tabAnalysis+13)
#define WM_ANALYSIS_SINGLETASK_TOTAL (tabAnalysis+14)

#define WM_ANALYSIS_ALLTASKS_TOTAL (tabAnalysis+15)

#define WM_ANALYSIS_SINGLEWORKER_RUNPAUSE (tabAnalysis+16)

#define WM_ANALYSIS_SINGLEWORKER_WITHTASK_MULTIPLESTACKED (tabAnalysis+18)
#define WM_ANALYSIS_SINGLEWORKER_WITHTASK_TIMETOTAL (tabAnalysis+19)

#define WM_ANALYSIS_ALLWORKERS_TOTAL (tabAnalysis+20)
#define tabAnalysisEnd (tabAnalysis+22)



#define tabComparePreTools (WM_USER+450)
#define WM_COMPARE_FOCUS_SELTEST (tabComparePreTools+1)
#define WM_COMPARE_FOCUS_SELITEM (tabComparePreTools+2)


#define WM_COMPARE_SINGLEACTIVITY_SELTASK (tabComparePreTools+5)
#define WM_COMPARE_SINGLEACTIVITY_SELWORKER (tabComparePreTools+8)
#define WM_COMPARE_SINGLEWORKER_SELTASK (tabComparePreTools+16)

#define tabCompare (WM_USER+470)

#define WM_COMPARE_SINGLEACTIVITY_TIMELINE (tabCompare+3)
#define WM_COMPARE_SINGLEACTIVITY_STAGES (tabCompare+4)

#define WM_COMPARE_SINGLEACTIVITY_WITHTASK_STACKED (tabCompare+6)
#define WM_COMPARE_SINGLEACTIVITY_WITHTASK_TOTAL (tabCompare+7)

#define WM_COMPARE_SINGLEACTIVITY_WITHWORKER_TOTAL (tabCompare+9)

#define WM_COMPARE_SALLACTIVITIES_TOTAL (tabCompare+10)

#define WM_COMPARE_SINGLETASK_RUNHISTO (tabCompare+11)
#define WM_COMPARE_SINGLETASK_TOTAL (tabCompare+12)

#define WM_COMPARE_ALLTASKS_TOTAL (tabCompare+13)

#define WM_COMPARE_SINGLEWORKER_RUNPAUSE (tabCompare+14)
#define WM_COMPARE_SINGLEWORKER_RUNHISTO (tabCompare+15)

#define WM_COMPARE_SINGLEWORKER_WITHTASK_STACKED (tabCompare+17)
#define WM_COMPARE_SINGLEWORKER_WITHTASK_TOTAL (tabCompare+18)

#define WM_COMPARE_ALLWORKERS_TOTAL (tabCompare+19)
#define tabCompareEnd (tabCompare+20)

#define tabSupport (WM_USER+500)

#define WM_SUPPORT_CONTENTS (tabSupport+1)
#define WM_SUPPORT_TIPOFTHEDAY (tabSupport+2)
#define WM_SUPPORT_HELPDESK (tabSupport+3)
#define WM_SUPPORT_FORUMS (tabSupport+4)
#define WM_SUPPORT_MAILSUPPORT (tabSupport+5)
#define WM_SUPPORT_TUTORIALS (tabSupport+6)
#define WM_SUPPORT_FAQ (tabSupport+7)
#define WM_SUPPORT_UPDATE (tabSupport+8)
#define WM_SUPPORT_COPYRIGHT (tabSupport+9)
#define WM_SUPPORT_LICENCEKEY (tabSupport+10)
#define WM_SUPPORT_ACTIVATE_PRODUCT (tabSupport+11)
#define WM_SUPPORT_ABOUT (tabSupport+12)
#define WM_SUPPORT_VISIT (tabSupport+13)
#define WM_SUPPORT_INVITE (tabSupport+14)
#define WM_SUPPORT_NEWS (tabSupport+15)
#define WM_SUPPORT_PARTNER (tabSupport+16)
#define WM_SUPPORT_GOOGLE_CODE (tabSupport+17)
#define WM_SUPPORT_CODE_PROJECT (tabSupport+18)
#define WM_SUPPORT_BLOG (tabSupport+19)


//
#define  OddCommands (WM_USER + 550)
#define WM_EXPORT_IMAGE (OddCommands+1)
#define ID_STATUSBAR_LINK (OddCommands+2)
//
//#define 

/*Menus :
ID_CHARTTITLE_NONE
ID_CHARTTITLE_SHOWOUTSIDE
ID_CHARTTITLE_DOCKTOAREA
*/

