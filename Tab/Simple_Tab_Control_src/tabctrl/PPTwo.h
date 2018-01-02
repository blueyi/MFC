#pragma once


// CPPTwo dialog

class CPPTwo : public CPropertyPage
{
	DECLARE_DYNAMIC(CPPTwo)

public:
	CPPTwo();
	virtual ~CPPTwo();

// Dialog Data
	enum { IDD = IDD_PP_TWO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_strEDITName;
};
