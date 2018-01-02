#if !defined(AFX_IMAGEVIEW3D_H__CA003DA0_5403_4C2E_A680_F8A531F61BF5__INCLUDED_)
#define AFX_IMAGEVIEW3D_H__CA003DA0_5403_4C2E_A680_F8A531F61BF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageView3D.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVRView dialog
#include "resource.h"
#include "vtkHeader.h"
#include "vtkMarchingCubes.h"
#include "GlobalHeader.h"
#include "vtkFixedPointVolumeRayCastMapper.h"


class CDlgVRView : public CDialog
{
// Construction
public:
	
	void SetGroundColor(COLORREF color);
	BOOL SetVRImage(vtkImageData *pImage);
	
	CDlgVRView(CWnd* pParent = NULL);   // standard constructor
	

	IA_PIXEL_ITEM* m_grayHistogram;
	unsigned short m_pixelMin,m_pixelMax;
	vtkImageData *m_pImage;

	

	vtkRenderer            *m_pRenderer;
	vtkRenderWindowInteractor *m_pInteractor;

	VOLRENDER_CONFIG m_volConfig;
	

// Dialog Data
	//{{AFX_DATA(CDlgVRView)
	enum { IDD = IDD_IMAGE_VRVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVRView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVRView)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnCallCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	
	void setRenderMode(short modeID);
	void setEngine(short engineID);

	static void KeyPressCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata);
	static void MouseDownCallBack(vtkObject *obj, unsigned long event , void *clientdata, void *calldata);
	static void MoveMouseCallBack(vtkObject *obj, unsigned long event , void *clientdata, void *calldata);
	static void RenderAbortCheckCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata);
	

	void UpdateHistogram();
	void UpdateGradMethod();
	void UpdateColorOpacity();
	void InitialVRActor();
	void UpdateView();

	vtkMFCWindow          *m_pMFCWindow;

	vtkColorTransferFunction *m_colorTransferFunction;
	vtkPiecewiseFunction *m_opacityTransferFunction;
	vtkPiecewiseFunction *m_gradOpacityTransferFunction;
	vtkFixedPointVolumeRayCastMapper *m_volumeMapper;
	vtkOpenGLVolumeTextureMapper3D *m_textureMapper;
	vtkVolumeRayCastCompositeFunction *m_rayCastCompositeFunction;
	vtkVolumeRayCastMIPFunction *m_rayCastMIPFunction;
	vtkVolumeRayCastMapper *m_rayCastMapper;
	vtkVolumeProperty *m_volumeProperty;
	vtkVolume *m_volume;

	vtkColorTransferFunction *m_blendingColorTransferFunction;
	vtkPiecewiseFunction *m_blendingOpacityTransferFunction;
	vtkPiecewiseFunction *m_blendingGradOpacityTransferFunction;
	vtkFixedPointVolumeRayCastMapper *m_blendingVolumeMapper;
	vtkOpenGLVolumeTextureMapper3D *m_blendingTextureMapper;
	vtkVolumeRayCastCompositeFunction *m_blendingRayCastCompositeFunction;
	vtkVolumeRayCastMIPFunction *m_blendingRayCastMIPFunction;
	vtkVolumeRayCastMapper *m_blendingRayCastMapper;
	vtkVolumeProperty *m_blendingVolumeProperty;
	vtkVolume *m_blendingVolume;

	vtkCornerAnnotation *m_pCorAnnotate;
	
	COLORREF m_groundColor;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEW3D_H__CA003DA0_5403_4C2E_A680_F8A531F61BF5__INCLUDED_)
