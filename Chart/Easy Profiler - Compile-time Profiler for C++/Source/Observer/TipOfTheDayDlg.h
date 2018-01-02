/********************************************************************
    File:	        TipOfTheDayDlg	
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
/*
#include "HtmlCtrl.h"
*/
#include "resource.h"



// CTipOfTheDayDlg dialog

class CTipOfTheDayDlg : public CDialog
{
	DECLARE_DYNAMIC(CTipOfTheDayDlg)

public:
	CTipOfTheDayDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTipOfTheDayDlg();

// Dialog Data
	enum { IDD = IDD_TIPOFTHEDAYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedNext();
	BOOL m_bActive;
	int lastShown;
	CString progDir;
	virtual void OnOK();
};
