// MriLogAnalyserView.h : interface of the CMriLogAnalyserView class
//
/////////////////////////////////////////////////////////////////////////////
#include "ShowLogRecordGrid.h"
#include "Chart.h"

#if !defined(AFX_MRILOGANALYSERVIEW_H__0FAA9FE3_3285_407C_AC11_26B15855BCF8__INCLUDED_)
#define AFX_MRILOGANALYSERVIEW_H__0FAA9FE3_3285_407C_AC11_26B15855BCF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMriLogAnalyserView : public CFormView
{
protected: // create from serialization only
	CMriLogAnalyserView();
	DECLARE_DYNCREATE(CMriLogAnalyserView)

public:
	//{{AFX_DATA(CMriLogAnalyserView)
	enum { IDD = IDD_MRILOGANALYSER_FORM };
	CStatic	m_staticDrawCurveO1;
	CComboBox	m_ctrlSequenceype;
	CComboBox	m_ctrlCoilType;
	CButton	m_ctrlListArea;
	CString	m_sCoilType;
	CString	m_sSequenceType;
	CString	m_sUserName;
	//}}AFX_DATA

// Attributes
public:
	CMriLogAnalyserDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMriLogAnalyserView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMriLogAnalyserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMriLogAnalyserView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnSetWorkingFolder();
	afx_msg void OnBtnSetQueryingTime();
	afx_msg void OnMenuSetWorkingFolder();
	afx_msg void OnMenuSetQueryLogRecord();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboSequenceType();
	afx_msg void OnSelchangeComboCoilType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CShowLogRecordGrid m_oShowLogRecordGrid;	// 扫描参数显示表格
	C2DChart m_o2DCurve_O1;						// O1曲线图
	void InsertToComboBox();
	void InsertToGrid();
	void DrawCurve_O1();
	

};

#ifndef _DEBUG  // debug version in MriLogAnalyserView.cpp
inline CMriLogAnalyserDoc* CMriLogAnalyserView::GetDocument()
   { return (CMriLogAnalyserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRILOGANALYSERVIEW_H__0FAA9FE3_3285_407C_AC11_26B15855BCF8__INCLUDED_)
