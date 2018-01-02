/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 9/16/98 2:20:55 PM
  Comments: QComboBox.h : header file
 ************************************/

#if !defined(AFX_QCOMBOBOX_H__1385ADA1_4D4F_11D2_8693_0040055C08D9__INCLUDED_)
#define AFX_QCOMBOBOX_H__1385ADA1_4D4F_11D2_8693_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CQComboBox window

#include <afxtempl.h>

#define defaultRGBBkGnd RGB(192,192,192)
#define wndClassName _T("QComboBox")
#define IDListBox	0x3E8
#define IDEDIT		0x3E9
#define defaultEditStyle ES_AUTOHSCROLL | ES_NOHIDESEL | 0x200
#define defaultListBoxStyle LBS_DISABLENOSCROLL
#define defaultSizeDY 21
#define defaultSizeDX 13
#define defaultDropDownKey VK_F4
#define defaultSelChange _T("QCBN_SELCHANGE")
#define defaultLoading _T("QCBN_LOADING")
#define defaultLoaded _T("QCBN_LOADED")
#define QIDTIMERFIRST 1000
#define QIDTIMERSTARTLOADITEMS QIDTIMERFIRST
#define QIDTIMERLOADITEMS QIDTIMERFIRST + 1
#define QTIMESTARTLOADITEMS 3000
#define QTIMELOADITEMS 128

class CQComboBox;
typedef LPCTSTR (*TLine) (int iLine, LPARAM& lParamItem, LPARAM lParam = 0);
typedef int (*TLinePartial) (LPCTSTR lpszItempartial, LPARAM lParam = 0);
typedef int (CQComboBox::*TLoadFunction) (int nLineFrom, int nHowMany = +1); 

class CQComboBox : public CWnd
{
// Construction
public:
	class CWindowProcs
	{
	public:
		CWindowProcs()
		{
		};
	protected:
		// Store infos about one window, such as window procedure
		struct SWindowProcedure
		{
			CWnd* m_pWnd;
			WNDPROC m_oldWndProcWnd;
			SWindowProcedure(CWnd* pWnd, WNDPROC wndProc)
			{
				if (m_pWnd = pWnd)
					m_oldWndProcWnd = (WNDPROC)::SetWindowLong(m_pWnd->m_hWnd, GWL_WNDPROC, (long)wndProc);
			};
			virtual ~SWindowProcedure()
			{
				if (m_pWnd)
					::SetWindowLong(m_pWnd->m_hWnd, GWL_WNDPROC, (long)m_oldWndProcWnd);
			}
		};
		// Maps with window procedure of all windows controls registered
		CMap<HWND,HWND, SWindowProcedure*, SWindowProcedure*> m_mapWindowProcedureEdit;
		CMap<HWND,HWND, SWindowProcedure*, SWindowProcedure*> m_mapWindowProcedureListBox;
		CMap<HWND,HWND, SWindowProcedure*, SWindowProcedure*> m_mapWindowProcedureParent;
	public:
			// Add, Get, Remove Edit elements
			void AddEdit(CWnd* pEdit, WNDPROC wndProc)
			{
				m_mapWindowProcedureEdit[pEdit->m_hWnd] = new SWindowProcedure(pEdit, wndProc);
			};
			SWindowProcedure* GetEditStructure(HWND hWnd)
			{
				SWindowProcedure* pEditSW = NULL;
				m_mapWindowProcedureEdit.Lookup(hWnd, pEditSW);
				return pEditSW;
			};
			WNDPROC GetOldEditProcedure(HWND hWnd)
			{
				return GetEditStructure(hWnd)->m_oldWndProcWnd;
			}
			void RemoveEdit(CWnd* pEdit)
			{
				if (SWindowProcedure* pSW = GetEditStructure(pEdit->m_hWnd))
				{
					delete pSW;
					m_mapWindowProcedureEdit.RemoveKey(pEdit->m_hWnd);
				}
			};
			// Add, Get, Remove ListControl elements
			void AddListBox(CWnd* pListBox, WNDPROC wndProc)
			{
				m_mapWindowProcedureListBox[pListBox->m_hWnd] = new SWindowProcedure(pListBox, wndProc);
			};
			SWindowProcedure* GetListBoxStructure(HWND hWnd)
			{
				SWindowProcedure* pListBoxSW = NULL;
				m_mapWindowProcedureListBox.Lookup(hWnd, pListBoxSW);
				return pListBoxSW;
			};
			WNDPROC GetOldListBoxProcedure(HWND hWnd)
			{
				return GetListBoxStructure(hWnd)->m_oldWndProcWnd;
			}
			void RemoveListBox(CWnd* pListBox)
			{
				if (SWindowProcedure* pSW = GetListBoxStructure(pListBox->m_hWnd))
				{
					delete pSW;
					m_mapWindowProcedureListBox.RemoveKey(pListBox->m_hWnd);
				}
			};
			// Add, Get, Remove Parent elements
			void AddParent(CWnd* pParentWnd, WNDPROC wndProc)
			{
				if (!GetParentStructure(pParentWnd->m_hWnd))
					m_mapWindowProcedureParent[pParentWnd->m_hWnd] = new SWindowProcedure( pParentWnd, wndProc );
			};
			SWindowProcedure* GetParentStructure(HWND hWnd)
			{
				SWindowProcedure* pParentSW = NULL;
				m_mapWindowProcedureParent.Lookup(hWnd, pParentSW);
				return pParentSW;
			};
			WNDPROC GetOldParentProcedure(HWND hWnd)
			{
				return GetParentStructure(hWnd)->m_oldWndProcWnd;
			}
			void RemoveParent(CWnd* pParent)
			{
				if (SWindowProcedure* pSW = GetParentStructure(pParent->m_hWnd))
				{
					delete pSW;
					m_mapWindowProcedureParent.RemoveKey(pParent->m_hWnd);
				}
			};
	};

	static CWindowProcs m_wndProcs;

	CQComboBox(TLine fctLine, TLinePartial fctLinePartial, LPARAM lParam = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQComboBox)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual int GetCountItem();
	virtual void SetCountItems(int nCount);
	virtual int GetVisibleCount();
	virtual int SetMultipleHeight(int nMHeight = 5);
	virtual double SetRateWidth(double dWidthList = 0);
	virtual void SetCurrentItem(int nIndex);
	virtual int GetCurrentItem();
	BOOL ForwardMessage(UINT nMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL IsDropedDown();
	virtual void DropDown(BOOL bDown = TRUE);
	virtual CListBox* GetListBox();
	virtual CEdit* GetEdit();
	static BOOL RegClassQComboBox();
	virtual ~CQComboBox();
	virtual LPCTSTR Line(int nLine, LPARAM& lParamItem);
	virtual int LinePartial(LPCTSTR lpszItemPartial);
	virtual int LoadPartial(int nLineFrom, int nHowMany = +1);

	// Statical functions
	static LRESULT CALLBACK ListBoxWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK EditWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ParentWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
protected:
	static UINT m_nSelChange;
	static UINT m_nLoading;
	static UINT m_nLoaded;
	static CMap<CQComboBox*,CQComboBox*, BOOL, BOOL> m_mapUnloadedQCombos;
	//
	struct QSnapLoader
	{
		CQComboBox* m_pParent;
		struct SNodeItemsInfo
		{
			static int m_nCountRef;
			int m_nItemLine;
			int m_nCount;
			int m_nItemLB;
			SNodeItemsInfo* m_pNextNode;
			SNodeItemsInfo* m_pPrevNode;
			SNodeItemsInfo(int nItemLine, int nCount, int nItemLB)
			{
				m_nItemLine = nItemLine;
				m_nCount = nCount;
				m_nItemLB = nItemLB;
				m_pNextNode = NULL;
				m_pPrevNode = NULL;
				m_nCountRef++;
			}
			~SNodeItemsInfo()
			{
				m_nCountRef--;
			}
			int GetLastLine()
			{
				return m_nItemLine + m_nCount;
			}
			int GetLastItem()
			{
				return m_nItemLB + m_nCount;
			}
		};
		SNodeItemsInfo* m_pFirstNode;
	public:
		virtual int GetItemLine(int nItemLB);
		virtual CString GetListNodes();
		void SetParent(CQComboBox* pParent);
		 QSnapLoader();
		virtual int Load(int nItemFrom, int nHowMany);
		virtual  ~QSnapLoader();
	};

	friend struct CQComboBox::QSnapLoader;
	public:
		static CQComboBox* GetFirstQComboBox();
		virtual BOOL IsAlreadyLoad();
	QSnapLoader m_QuickLoader;
	protected:
	int m_nCountItems;
	virtual int LoadPartialListBox(int nLineFrom, int nHowMany = +1);
	virtual int AlreadyLoadPartialListBox(int nLineFrom, int nHowMany = +1);
	int m_nCountVisible;
	//
	TLine m_fctLine;
	TLinePartial m_fctLinePartial;
	TLoadFunction m_fctLoadFunction;
	int m_nMultipleHeight;
	double m_dWidthList;
	virtual void SelectCurrentItem();
	virtual void Search(LPCTSTR lpszFindItem);
	BOOL OnInit();
	static CQComboBox* m_pActiveMCBox;
	virtual void DrawButton(CDC* pDC, CRect r, BOOL bDown = FALSE);
	virtual void Resize();
	CListBox* m_pListBox;
	CEdit* m_pEdit;
	static CFont m_font;
	static CBrush m_brBkGnd;
	//{{AFX_MSG(CQComboBox)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPARAM m_lParam;
	BOOL m_bCaptured;
	void SetButton();
	void ReleaseButton();
	CRect m_rectBtn;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QCOMBOBOX_H__1385ADA1_4D4F_11D2_8693_0040055C08D9__INCLUDED_)
