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
// PGLObjectManager.h: interface for the CPGLObjectManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLOBJECTMANAGER_H__6BC55A62_1D34_49EE_B5DE_371EC2DB9E01__INCLUDED_)
#define AFX_PGLOBJECTMANAGER_H__6BC55A62_1D34_49EE_B5DE_371EC2DB9E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef CTypedPtrList<CObList, CPGLObject*> CPGLObList;

/*! 
	\defgroup PGLManagerGroup Manager and containers.
	\ingroup PGLGroup
*/

/*! \brief An object container - manager

\ingroup PGLManagerGroup
*/
class PGL_EXT_CLASS CPGLObjectManager : public CObject
{
DECLARE_SERIAL(CPGLObjectManager);
public:
	CPGLObjectManager();
	CPGLObjectManager(const CPGLObjectManager& om);
	CPGLObjectManager& operator=(const CPGLObjectManager& om);
	virtual ~CPGLObjectManager();

	/// IsEmpty
	BOOL IsEmpty() { return m_lObjects.IsEmpty();};
	/// GetHeadPosition
	POSITION GetHeadPosition() { return m_lObjects.GetHeadPosition();};
	/// GetNext	
	CPGLObject* GetNext(POSITION& pos) {	return m_lObjects.GetNext(pos);};
	/// AddHead
	void AddHead(CPGLObject* pObject) { m_lObjects.AddHead(pObject);};
	/// AddTail
	void AddTail(CPGLObject* pObject) { m_lObjects.AddTail(pObject);};
	// get count
	int GetCount( ) const
	{	return m_lObjects.GetCount();};
	POSITION FindIndex(int i) const {	return m_lObjects.FindIndex(i);};
	CPGLObject* GetAt(POSITION i) const { return m_lObjects.GetAt(i);};
	CPGLObject*& GetAt(POSITION i) {	return m_lObjects.GetAt(i);};

	/// returns TRUE if no object selected
	inline BOOL IsSelectionEmpty();
	/// returns TRUE if it is a multiple selection
	inline BOOL IsMultipleSelection();
	/// returns a list of pointers to the selected objects
	CPGLObjectManager* GetSelection();
	CPGLObjectManager* GetTextSelection();
	/// returns a list of pointers to copy of the selected objects
	CPGLObjectManager* GetSelectionCopy();
	/// adds the objets in the clipboard to the \_objectList list
	void PasteSelection(CPGLObjectManager* pClipboard);
	/// copies the objets in \_objectList list to the clipboard (the clipboard is emptied before)
	CPGLObjectManager* CopySelection();
	/// copies the objets in \_objectList list to the clipboard and delete them from \_objectList (the clipboard is emptied before)
	CPGLObjectManager* CutSelection();

	/// delete and removes the pointer pObject
	void DeleteObject(CPGLObject* pObject);
	/// delete and removes the pointer to object with Id number = ID
	void DeleteObject(UINT ID);
	/// delete and removes the pointer of selected objects
	void DeleteSelection();
	/// delete and removes the pointer pObject
	void RemoveObject(CPGLObject* pObject);
	/// removes the pointer to object with Id number = ID
	void RemoveObject(UINT ID);
	/// removes the pointer of selected objects
	void RemoveSelection();
	/// deleting objects in list and emptying it
	void DeleteAll();

	CBitmap* GetBitmap()
	{	return &m_bmp;};
	/// Serialization
	void Serialize( CArchive& archive );

	/// Debuggin functions
#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;    // Override
#endif

protected:
	/// object list
	CPGLObList m_lObjects;
	CBitmap m_bmp;
};

#endif // !defined(AFX_PGLOBJECTMANAGER_H__6BC55A62_1D34_49EE_B5DE_371EC2DB9E01__INCLUDED_)


inline BOOL CPGLObjectManager::IsSelectionEmpty()
{ 
	// object List
	POSITION pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		if (m_lObjects.GetNext(pos)->IsSelected())
			return FALSE;
	}
	return TRUE;
}

inline BOOL CPGLObjectManager::IsMultipleSelection()
{ 
	// object List
	BOOL foundOne=FALSE;
	POSITION pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		if (m_lObjects.GetNext(pos)->IsSelected())
		{
			if (foundOne)
				return TRUE;
			else
				foundOne=TRUE;
		}
	}

	return FALSE;
}
