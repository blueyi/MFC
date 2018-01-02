#pragma once
#include "resource.h"

// CTabDialog2 dialog

class CTabDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CTabDialog2)

public:
	CTabDialog2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabDialog2();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
