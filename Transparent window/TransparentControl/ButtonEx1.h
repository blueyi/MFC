#pragma once


#include "TransparentHelper.h"
// CButtonEx1

class CButtonEx1 : public CButton
{
	DECLARE_DYNAMIC(CButtonEx1)

public:
	CButtonEx1();
	virtual ~CButtonEx1();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();


public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	CBitmap m_bitmapNor;
	CBitmap m_bitmapOver;
	CBitmap m_bitmapDown;

	BOOL m_bTracking;
	CTransparentHelper m_objTransparent;
};


