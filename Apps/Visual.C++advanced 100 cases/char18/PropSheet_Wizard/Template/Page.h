// $$PAGE_FILE$$.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// $$PAGE_CLASS$$ dialog

class $$PAGE_CLASS$$ : public CPropertyPage
{
	DECLARE_DYNCREATE($$PAGE_CLASS$$)

// Construction
public:
	$$PAGE_CLASS$$();
	~$$PAGE_CLASS$$();

$$IF(TOOLTIPS)
	virtual BOOL PreTranslateMessage (MSG* pMsg);
$$ENDIF	//TOOLTIPS

// Dialog Data
	//{{AFX_DATA($$PAGE_CLASS$$)
	enum { IDD = $$PAGE_ID$$ };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL($$PAGE_CLASS$$)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG($$PAGE_CLASS$$)
$$IF(TOOLTIPS)
	virtual BOOL OnInitDialog();
$$ELSE
		// NOTE: the ClassWizard will add member functions here
$$ENDIF	//TOOLTIPS
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

$$IF(TOOLTIPS)
protected:
	CToolTipCtrl m_tooltip;
$$ENDIF	//TOOLTIPS
};
