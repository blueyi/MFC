#if !defined(AFX_DLGSCALECTRL_H__100FCA5B_A1B5_440A_8C16_3A3FE9FDE0CD__INCLUDED_)
#define AFX_DLGSCALECTRL_H__100FCA5B_A1B5_440A_8C16_3A3FE9FDE0CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScaleCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleCtrl dialog

class CDlgScaleCtrl : public CDialog
{
// Construction
public:
	void RefreshCtrl();
	CDlgScaleCtrl(CWnd* pParent = NULL);   // standard constructor

	char *GetGUIProperty(int property);
	void SetGUIProperty(int property, const char *value);

	

// Dialog Data
	//{{AFX_DATA(CDlgScaleCtrl)
	enum { IDD = IDD_SCALE_CTRL };
	CEdit	m_value;
	CStatic	m_caption;
	CSliderCtrl	m_slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScaleCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScaleCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	float m_min,m_max,m_step;
	int m_iMin,m_iMax;
	char m_sValue[256];
	float m_fCurSlice;

	CString m_ctrlType;
	CString m_sSliderTxt;
	CString m_sHelp;

	int m_iLastPos;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCALECTRL_H__100FCA5B_A1B5_440A_8C16_3A3FE9FDE0CD__INCLUDED_)
