#pragma once

#include "cgdiplusbitmap.h"

class CChildView : public CWnd
{
public:
	CChildView();

// Attributes
public:
	CGdiPlusBitmapResource m_bitmap;

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLoadJpg();
	afx_msg void OnLoadPng();
	afx_msg void OnLoadBmp();
};

