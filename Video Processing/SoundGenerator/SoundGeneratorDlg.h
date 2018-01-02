// SoundGeneratorDlg.h : header file
//

#if !defined(AFX_SOUNDGENERATORDLG_H__AA0BFDED_2C97_4F40_A776_98E19C607384__INCLUDED_)
#define AFX_SOUNDGENERATORDLG_H__AA0BFDED_2C97_4F40_A776_98E19C607384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MathExpression.h"
#include "IPlayer.h"
#include "Mutex.h"

/////////////////////////////////////////////////////////////////////////////
// CSoundGeneratorDlg dialog

class CSoundGeneratorDlg : public CDialog, public IPlayer::SoundEventListener
{

	MathExpression *m_pVarExpr;	
	MathExpression *m_pShapeExpr;
	
	IPlayer *m_pSoundPlayer;

	unsigned int m_soundPlayerEventNbSamples;	// size in samples between each sound event
	unsigned int m_soundPlayerEventSize;		// size in bytes
	unsigned int m_nbVars;
	unsigned int m_nbShapes;
	unsigned int m_nbSoudPlayerEvents;			// number of sound player events
	unsigned int m_maxEventComputeTime;			// time available to compute soud samples during an event (msec) 
	unsigned int m_sampleScaleVal;

	EXPR_VALTYPE m_t;	
	EXPR_VALTYPE *m_pUserVar;
	double m_tStep;
	double *m_pShapeVolume;
	bool *m_pShapeActive;
	short *m_pSamples;

	HDC m_hdc;
	HPEN m_hRedPen;
	HPEN m_hBgPen;
	HBRUSH m_hBgBrush;

	unsigned int m_graphStep;
	unsigned int m_graphMaxLines;
	unsigned int m_graphCursor;
	RECT m_graphRect;
	short m_graphLastVal;

	Mutex m_exprMutex;
	CString m_warningMsg;

// Construction
public:
	CSoundGeneratorDlg(CWnd* pParent = NULL);	// standard constructor
	~CSoundGeneratorDlg();

	virtual void OnSoundPlayerNotify(int eventNumber);
	void drawWave();

// Dialog Data
	//{{AFX_DATA(CSoundGeneratorDlg)
	enum { IDD = IDD_SOUNDGENERATOR_DIALOG };
	CSliderCtrl	m_volumeShape3;
	CSliderCtrl	m_volumeShape2;
	CSliderCtrl	m_volumeShape1;
	CString	m_shape1;
	CString	m_shape3;
	CString	m_shape2;
	CString	m_varx;
	CString	m_vary;
	CString	m_varz;
	CString	m_msg;
	BOOL	m_shape1Active;
	BOOL	m_shape2Active;
	BOOL	m_shape3Active;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundGeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSoundGeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnActiveShape1();
	afx_msg void OnActiveShape2();
	afx_msg void OnActiveShape3();
	afx_msg void OnApplyShape1();
	afx_msg void OnApplyShape2();
	afx_msg void OnApplyShape3();
	afx_msg void OnChangeShape1();
	afx_msg void OnChangeShape2();
	afx_msg void OnChangeShape3();
	afx_msg void OnApplyVarx();
	afx_msg void OnApplyVary();
	afx_msg void OnApplyVarz();
	afx_msg void OnChangeVarx();
	afx_msg void OnChangeVary();
	afx_msg void OnChangeVarz();
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDGENERATORDLG_H__AA0BFDED_2C97_4F40_A776_98E19C607384__INCLUDED_)
