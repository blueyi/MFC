// Property.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog

class CPropertyDlg : public CPropertyPage
{
public:
	CPropertyDlg();	// standard constructor
	BOOL StoreData();
	BOOL IsValidHotKey()	{ return m_wKey; }

	//{{AFX_DATA(CPropertyDlg)
	enum { IDD = IDD_PROPERTIES_DIALOG };
	CSpinButtonCtrl	m_widthSpin;
	CSpinButtonCtrl	m_factorSpin;
	CHotKeyCtrl	m_hotKey;
	UINT	m_nFactor;
	UINT	m_nWidth;
	BOOL	m_bNoPersist;
	//}}AFX_DATA

	WORD m_wKey, m_wMod;

	//{{AFX_VIRTUAL(CPropertyDlg)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPropertyDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPropertyChanged();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
