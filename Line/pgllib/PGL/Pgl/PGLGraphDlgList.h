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
// PGLGraphDlgList.h: interface for the CPGLGraphDlgList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLGRAPHDLGLIST_H__3DD7E6E3_3FDB_4FEE_B845_19C6FE7DE1A7__INCLUDED_)
#define AFX_PGLGRAPHDLGLIST_H__3DD7E6E3_3FDB_4FEE_B845_19C6FE7DE1A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
typedef CTypedPtrList<CPtrList, CPGLGraphBitDlg*> CGraphDlgList;

/*! \brief A manager class for all PGL dialog boxes

\ingroup PGLManagerGroup
*/
class PGL_EXT_CLASS CPGLGraphDlgList : public CObject
{
public:
	void RemoveHidden();
	void RemoveAll();
	CPGLGraphDlgList();
	virtual ~CPGLGraphDlgList();

	void AddHead(CPGLGraphBitDlg* pGraphDlg);
	void Remove(CPGLGraphBitDlg* _pGraphDlg);
	void ShowAll();

protected:
	CGraphDlgList m_GraphList;
	CMutex m_ThreadLock;
};

#endif // !defined(AFX_PGLGRAPHDLGLIST_H__3DD7E6E3_3FDB_4FEE_B845_19C6FE7DE1A7__INCLUDED_)
