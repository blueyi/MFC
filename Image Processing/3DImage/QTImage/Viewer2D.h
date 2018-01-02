#if !defined(AFX_VIEWER2D_H__ACECF80F_7023_4C84_A843_835EE22668F6__INCLUDED_)
#define AFX_VIEWER2D_H__ACECF80F_7023_4C84_A843_835EE22668F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Viewer2D.h : header file
//
#include "ImageViewer.h"
#include "SeriesManager.h"
/////////////////////////////////////////////////////////////////////////////
// C2DViewer dialog

class C2DViewer : public CImageViewer
{
// Construction
public:
	int GetCurIndex();
	void ResetWindowLevel();
	void SetGroundColor(COLORREF color);
	vtkImageData* GetSeries();
	void UpdateSelectedStatus(BOOL bSelected);
	void DisableSlider();
	
	void SetSeries(vtkImageData* pData);
	C2DViewer(CWnd* pParent = NULL);   // standard constructor

	vtkImageViewer2 *m_pViewer;
	vtkCornerAnnotation *m_pCorAnnotate;
	
	CSeriesManager *m_pManager;
	CList<C2DViewer*,C2DViewer*> *m_pList;

// Dialog Data
	//{{AFX_DATA(C2DViewer)
	enum { IDD = IDD_IMAGE_VIEW2D };
	CSliderCtrl	m_pSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DViewer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DViewer)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCustomdrawSliderSlice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnCallCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ClearContour();
	void UpdateImageContour();
	void SetupImageViewer();
	void SetCurImage(int index);

	static void MouseDownCallBack(vtkObject *obj, unsigned long event , void *clientdata, void *calldata);
	static void MoveMouseCallBack(vtkObject *obj, unsigned long event , void *clientdata, void *calldata);
	
	CList<vtkActor*,vtkActor*> m_pContourActorList;
	
	vtkImageData* m_pImage;
	int m_iCurSlice;

	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWER2D_H__ACECF80F_7023_4C84_A843_835EE22668F6__INCLUDED_)
