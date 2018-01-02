#pragma once
#include "thumbnailcontrol.h"


// CChildDialog dialog

class CChildDialog : public CDialog
{
	DECLARE_DYNAMIC(CChildDialog)

public:
	CChildDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChildDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CThumbNailControl m_ChildThumbNailControl;
    virtual BOOL OnInitDialog();
};
