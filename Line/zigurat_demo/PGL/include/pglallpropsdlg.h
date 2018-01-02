/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
#if !defined(AFX_PGLALLPROPSDLG_H__31979510_637D_41F4_8DCA_B019499F021A__INCLUDED_)
#define AFX_PGLALLPROPSDLG_H__31979510_637D_41F4_8DCA_B019499F021A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLAllPropsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLAllPropsDlg dialog

/*! \brief A property explorer for objects in the graph.
 
   \ingroup PGLDialogGroup

\image html allprops.png "Property explorer"
\image latex allprops.eps "Property explorer"

  This dialog is shown when the user right clicks on an object. The object hierarchy is loaded in
a tree and the property sheets of the selected object is loaded dynamically to the dialog box.

\sa CPGLObject::AddPropTree
\sa CPGLObject::AddPropertyPage
*/
class PGL_EXT_CLASS CPGLAllPropsDlg : public CDialog
{
// Construction
public:
	CPGLAllPropsDlg(CWnd* pParent = NULL, CPGLGraph* _pGraph = NULL);   // standard constructor

	void SetGraph(CPGLGraph* _pGraph)
	{	m_pGraph=_pGraph;};
	void SetSelection(long _lSelID)
	{	m_lSelID=_lSelID;};
	void SetSelection(CPGLObject* pObj)
	{	ASSERT_VALID(pObj); m_lSelID=pObj->GetID();};
// Dialog Data
	//{{AFX_DATA(CPGLAllPropsDlg)
	enum { IDD = IDD_PGL_ALL_PROPS_DIALOG };
	CTreeCtrl	m_tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLAllPropsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_imgList;
	long m_lSelID;
	CBitmap m_bmpSelect;
	void FillTree();
	CPropertySheet* m_pSheet;
	CPGLGraph* m_pGraph;
private:

	// Generated message map functions
	//{{AFX_MSG(CPGLAllPropsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangedPglObjecttree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPglButtonClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLALLPROPSDLG_H__31979510_637D_41F4_8DCA_B019499F021A__INCLUDED_)
