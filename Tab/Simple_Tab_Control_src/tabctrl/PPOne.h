#pragma once


// CPPOne dialog

class CPPOne : public CPropertyPage
{
	DECLARE_DYNAMIC(CPPOne)

public:
	CPPOne();
	virtual ~CPPOne();

// Dialog Data
	enum { IDD = IDD_PP_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMsg();
};
