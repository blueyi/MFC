#if !defined(AFX_EFFECTDLG_H__7ACECE1C_9DCC_4348_9CE9_38330118B83C__INCLUDED_)
#define AFX_EFFECTDLG_H__7ACECE1C_9DCC_4348_9CE9_38330118B83C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

#include "resource.h"
#include "sviztabctrl.h"
class CFillGradientDlg;
class CFillPatternDlg;
class CFillPictureDlg;

/////////////////////////////////////////////////////////////////////////////
// CEffectDlg dialog

class SVIZDLLEXPORT CEffectDlg : public CDialog
{
// Construction
public:
	CEffectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEffectDlg)
	enum { IDD = IDD_SVIZ_FILL_DLG };
	CSVizTabCtrl	m_Tab;
	//}}AFX_DATA

	int				   m_effectpage;
	CFillGradientDlg   *m_pGradientDlg;
	CFillPatternDlg    *m_pPatternDlg;
	CFillPictureDlg    *m_pPictureDlg;

	//using GDI+
    Color				m_StartColor;
	Color				m_EndColor;
	BrushType			m_BrushType;
	LinearGradientMode	m_linearFillMode;
	CString				m_fileName;
	HatchStyle			m_hatchStyle;
	BYTE				m_nColor;
	WrapMode			m_wrapMode;
	BYTE				m_nStyle;
	BYTE				m_nStretch;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEffectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/** @class CEffectDlg
 *  @brief Dialog for the property of GDI brush
 *
 * CEffectDlg is used with CColourPopupWnd to set up advancde features for a GDI+ brush
 * including gradient brush, textture brush, hatch brush.
 *  *
 * For more information on CEffectDlg, see CColourPopupWnd.
 */

#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
