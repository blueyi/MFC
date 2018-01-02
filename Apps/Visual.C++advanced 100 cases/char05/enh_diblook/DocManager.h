#if !defined(AFX_DOCMANAGER_H__188308B4_0AAD_11D2_8A47_0000E81D3D27__INCLUDED_)
#define AFX_DOCMANAGER_H__188308B4_0AAD_11D2_8A47_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DocManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocManagerEx

class CDocManagerEx : public CDocManager
{
	DECLARE_DYNAMIC(CDocManagerEx)

// Construction
public:
	CDocManagerEx();

// Attributes
public:

// Operations
public:

// Overrides
	// helper for standard commdlg dialogs
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);

// Implementation
public:
	virtual ~CDocManagerEx();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCMANAGER_H__188308B4_0AAD_11D2_8A47_0000E81D3D27__INCLUDED_)
