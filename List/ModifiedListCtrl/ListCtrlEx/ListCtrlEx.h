/////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_)
	#include "..\Main.h"

	#define AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER >= 1000
		#pragma once
	#endif // _MSC_VER >= 1000

	/////////////////////////////////////////////////////////////////////////////
	// class CListCtrlEx
	/////////////////////////////////////////////////////////////////////////////
	class CListCtrlEx : public CListCtrl {
		// Construction
		public:
			CListCtrlEx();
			
			//*** The list font
			CFont *m_pFont;

			//*** The table list height
			UINT m_nListHeight;

			//*** The table rows count
			UINT m_nRowCount;

			//*** The table columns count
			UINT m_nColCount;

			//*** Table rows array
			// 10 = nRowCount & 6 = nHdrCount in MainView::OnCreate
			static TCHAR *m_apRowText[10][6];
			
		// Operations
		public:
			void TestGetItemText(UINT nRow, UINT nCol, TCHAR *szStr);

		// Overrides
		public:

		protected:
			virtual void SetColItemText(CDC *pDC, CString &sCellText, CRect &TextRect, 
					UINT nJustify);
			virtual void SetRowText(LPDRAWITEMSTRUCT pDIS);

			virtual void DrawItem(LPDRAWITEMSTRUCT pDIS);

		protected:
			virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, 
					LRESULT *pLResult);

		// Implementation
		public:
			virtual ~CListCtrlEx();

		// Generated message map functions
		protected:
			afx_msg void MeasureItem(LPMEASUREITEMSTRUCT pMIS);

		DECLARE_MESSAGE_MAP()
	};
#endif // !defined(AFX_LISTCTRLEX_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
