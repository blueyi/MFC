#if !defined(AFX_INPUT_H__D4FCAA4F_5EBE_43F2_A70E_2C2849567A6D__INCLUDED_)
#define AFX_INPUT_H__D4FCAA4F_5EBE_43F2_A70E_2C2849567A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

class CInput : public CDialog
{
public:
	CInput(CWnd* pParent = NULL);   
	MYDATA  xData;

	//{{AFX_DATA(CInput)
	enum { IDD = IDD_INPUT };
	BOOL	m_x1;
	BOOL	m_x2;
	BOOL	m_x3;
	BOOL	m_c1;
	BOOL	m_c2;
	BOOL	m_c3;
	int		m_m;
	CString	m_add;
	CString	m_attrib;
	CString	m_contact;
	CString	m_industry;
	CString	m_introdu;
	CString	m_name;
	CString	m_npost;
	CString	m_salary;
	CString	m_scale;
	CString	m_source;
	CString	m_level;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CInput)
	virtual void OnOK();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};

//{{AFX_INSERT_LOCATION}}

#endif
