/////////////////////////////////////////////////////////////////////////////
// MainView.h : interface of the CMainView class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#include "ListCtrlEx\ListCtrlEx.h"
	#include "ListCtrlEx\HeaderCtrlEx.h"

	/////////////////////////////////////////////////////////////////////////////
	// Class CMainView
	/////////////////////////////////////////////////////////////////////////////
	class CMainView : public CFormView {
		DECLARE_DYNCREATE(CMainView)

		protected: // create from serialization only
			CMainView();

		public:
			//{{AFX_DATA(CMainView)
			enum{ IDD = IDD_MAIN_FORM };
				// NOTE: the ClassWizard will add data members here
			//}}AFX_DATA
		
		// Attributes
		public:
			//CMainDoc *GetDocument();

		// Operations
		public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMainView)
		public:
			//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		
		protected:
			//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
			//virtual void OnInitialUpdate(); // called first time after construct
		//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CMainView();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
		#endif

		protected:

		// Generated message map functions
		protected:
			//{{AFX_MSG(CMainView)
				// NOTE - the ClassWizard will add and remove member functions here.
				//    DO NOT EDIT what you see in these blocks of generated code !
			//}}AFX_MSG
		
		protected:
			afx_msg int OnCreate(LPCREATESTRUCT pCS);

		DECLARE_MESSAGE_MAP()
	};  // class CMainView : public CFormView
	/*
	#ifndef _DEBUG  // debug version in MainView.cpp
		inline CMainDoc* CMainView::GetDocument()
			 {return (CMainDoc *) m_pDocument;}
	#endif
	*/
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINVIEW_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
