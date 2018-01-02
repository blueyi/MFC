#pragma once


// CPPThree dialog

class CPPThree : public CPropertyPage
{
	DECLARE_DYNAMIC(CPPThree)

public:
	CPPThree();
	virtual ~CPPThree();

// Dialog Data
	enum { IDD = IDD_PP_THREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
