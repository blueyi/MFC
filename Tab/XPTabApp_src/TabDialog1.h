#pragma once
#include "resource.h"

// CTabDialog1 dialog

class CTabDialog1 : public CDialog
{
	DECLARE_DYNAMIC(CTabDialog1)

public:
	CTabDialog1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabDialog1();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
