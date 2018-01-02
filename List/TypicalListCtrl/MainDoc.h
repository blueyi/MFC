/////////////////////////////////////////////////////////////////////////////
// MainDoc.h : interface of the CMainDoc class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDOC_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_MAINDOC_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000


	/////////////////////////////////////////////////////////////////////////////
	// MainDoc.h : interface of the CMainDoc class
	/////////////////////////////////////////////////////////////////////////////
	class CMainDoc : public CDocument {
		DECLARE_DYNCREATE(CMainDoc)

		protected: // create from serialization only
			CMainDoc();

		// Attributes
		public:

		// Operations
		public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMainDoc)
		public:
			virtual BOOL OnNewDocument();
			virtual void Serialize(CArchive& ar);
		//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CMainDoc();
		#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
		#endif

		protected:

		// Generated message map functions
		protected:
			//{{AFX_MSG(CMainDoc)
				// NOTE - the ClassWizard will add and remove member functions here.
				//    DO NOT EDIT what you see in these blocks of generated code !
			//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINDOC_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
