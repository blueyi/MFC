// ThumbViewerDoc.h : interface of the CThumbViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUMBVIEWERDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_)
#define AFX_THUMBVIEWERDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ximage.h"

#include <vector>

using namespace std;

class CThumbViewerDoc : public CDocument
{
protected: // create from serialization only
	CThumbViewerDoc();
	DECLARE_DYNCREATE(CThumbViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetTypeFromFileName(LPCTSTR pstr);
	void SelectItem(int nIndex);
	CString m_strCurrentDirectory;
	vector<CString> m_vFileName;
	void SelectDirectory(LPCTSTR pstr);
	CxImage* m_pSelectedImage;
	virtual ~CThumbViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_nSelectedItem;  // For avoiding load selected image twice
	void QuickSortString(vector<CString>& vString, int left, int right, CString& temp);
	//{{AFX_MSG(CThumbViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBVIEWERDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_)
