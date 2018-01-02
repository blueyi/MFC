/********************************************************************
    File:	        ChartFrame	
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
// ChartFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ChartFrame.h"


// CChartFrame

IMPLEMENT_DYNCREATE(CChartFrame, CMDIChildWndEx)

CChartFrame::CChartFrame()
{

}

CChartFrame::~CChartFrame()
{
}


BEGIN_MESSAGE_MAP(CChartFrame, CMDIChildWndEx)
END_MESSAGE_MAP()



// CChartFrame message handlers



BOOL CChartFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION /*| WS_SYSMENU*/
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MAXIMIZE;

	return TRUE;
}
