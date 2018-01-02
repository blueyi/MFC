// RectangleROI.h: interface for the CRectangleROI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLEROI_H__81D7C403_D2B2_4BD7_9EEF_4709AB12BFF6__INCLUDED_)
#define AFX_RECTANGLEROI_H__81D7C403_D2B2_4BD7_9EEF_4709AB12BFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CRectangleROI  
{
public:
	void	UnLockMouse();
	void	RePaint(CWnd *pWnd);
	void	MouseMove(CWnd *pWnd, CPoint point);
	void	LButtonUp(CWnd *pWnd, CPoint point);
	void	LButtonDown(CWnd *pWnd, CPoint point);

	void	SetShowROI(BOOL bShowROI);
	void	SetSelectROI(BOOL bSelectROI);

	CPoint	GetTopLeftPt()		{return m_ptTopLeft;}
	CPoint	GetBottomRightPt()	{return m_ptBottomRight;}
	BOOL	GetShowROI()		{return m_bShowROI;}
	BOOL	GetSelectROI()		{return m_bSelectROI;}
	
	CRectangleROI();
	virtual ~CRectangleROI();
	void	InitializePara(int iImageWidth, int iImageHeight);	//*** should take attention ***//

private:
	BOOL	m_bShowROI;
	BOOL	m_bSelectROI;

	BOOL	m_btopleftCaptured;			//the flag of whether ROI top left point be selected
	BOOL	m_bleftCaptured;			//the flag of whether ROI left point be selected
	BOOL	m_bTopMiddleCaptured;		//the flag of whether ROI top middle point be selected
	BOOL	m_brighttopCaptured;		//the flag of whether ROI top right point be selected
	BOOL	m_brightmiddleCaptured;		//the flag of whether ROI right middle point be selected
	BOOL	m_bleftbottomCaptured;		//the flag of whether ROI bottom left point be selected
	BOOL	m_bbottommiddleCaptured;	//the flag of whether ROI bottom middle point be selected
	BOOL	m_brightbottomCaptured;		//the flag of whether ROI bottom right point be selected
	BOOL	m_bTotalCaputured;			//the flag of whether full ROI window be selected

	CPoint	m_ptTopLeft;
	CPoint	m_ptBottomRight;
	CSize	m_sizeSelected;				// the size of control point for the ROI rectangle window
	CSize	m_sizeOffsetTL;				//the displacement of full ROI window moved
	CSize	m_sizeOffsetBR;				//the displacement of full ROI window moved

	int		m_iImageWidth;
	int		m_iImageHeight;

	BOOL	m_bInitializePara;
};

#endif // !defined(AFX_RECTANGLEROI_H__81D7C403_D2B2_4BD7_9EEF_4709AB12BFF6__INCLUDED_)
