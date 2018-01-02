// PGLObjectManager.cpp: implementation of the CPGLObjectManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGL.h"
#include "PGL/PGLObjectManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLObjectManager, CObject, 1);

void CPGLObjectManager::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

	// CPGLObjectManager serialization
	// objects
	m_lObjects.Serialize(archive);
}

#ifdef _DEBUG
void CPGLObjectManager::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

    // now do the stuff for our specific class
	// now dumping
	dc << _T("--- CPGLObjectManager ---")<< endl;
	dc<<m_lObjects;
}

void CPGLObjectManager::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check CPGLObjectManager members...
	m_lObjects.AssertValid();
} 
#endif

CPGLObjectManager::CPGLObjectManager()
{
	// saving old ressource.
	HINSTANCE hOldInst=AfxGetResourceHandle();
	// setting dll ressource
	AfxSetResourceHandle(AfxGetInstanceHandle());
	// creating bitmap
	m_bmp.LoadBitmap(IDB_PGL_OBJMG_BITMAP);
	// restoring old ressource.
	AfxSetResourceHandle(hOldInst);
}

CPGLObjectManager::CPGLObjectManager(const CPGLObjectManager& om)
{
	// copying
	POSITION pos=om.m_lObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		AddHead(om.m_lObjects.GetNext(pos)->MakeCopy());
	}
	// saving old ressource.
	HINSTANCE hOldInst=AfxGetResourceHandle();
	// setting dll ressource
	AfxSetResourceHandle(AfxGetInstanceHandle());
	// creating bitmap
	m_bmp.LoadBitmap(IDB_PGL_OBJMG_BITMAP);
	// restoring old ressource.
	AfxSetResourceHandle(hOldInst);
}

CPGLObjectManager& CPGLObjectManager::operator=(const CPGLObjectManager& om)
{
	if (this!=&om)
	{
		// emptying list...
		DeleteAll();

		// copying
		POSITION pos=om.m_lObjects.GetHeadPosition();
		while (pos!=NULL)
		{
			AddHead(om.m_lObjects.GetNext(pos)->MakeCopy());
		}
	}
	return *this;
}

CPGLObjectManager::~CPGLObjectManager()
{
	DeleteAll();
	ASSERT(m_lObjects.IsEmpty());
}

CPGLObjectManager* CPGLObjectManager::CutSelection()
{
	//get selection list
	CPGLObjectManager* pSelList=GetSelection();

	//remove selection from list
	RemoveSelection();

	return pSelList;
}

CPGLObjectManager* CPGLObjectManager::CopySelection()
{
	//get selection list
	CPGLObjectManager* pSelList=GetSelectionCopy();

	return pSelList;
}

void CPGLObjectManager::PasteSelection(CPGLObjectManager* pClipboard)
{
	if (pClipboard==NULL)
		return;

	ASSERT_VALID(pClipboard);
	// copying objects...
	POSITION pos;
	CPGLObject* pObject;

	pos=pClipboard->GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=pClipboard->m_lObjects.GetNext(pos)->MakeCopy();
		m_lObjects.AddHead(pObject);
	}
}

CPGLObjectManager* CPGLObjectManager::GetSelection()
{
	POSITION pos;
	CPGLObject* pObject;
	CPGLObjectManager* pSelection=new CPGLObjectManager();

	//finding objects to remove
	pos=m_lObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_lObjects.GetNext(pos);
		if (pObject->IsSelected())
		{
			pSelection->m_lObjects.AddHead(pObject);
		}
	}	
	return pSelection;
}

CPGLObjectManager* CPGLObjectManager::GetTextSelection()
{
	POSITION pos;
	CPGLObject* pObject;
	CPGLObjectManager* pSelection=new CPGLObjectManager();

	//finding objects to remove
	pos=m_lObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_lObjects.GetNext(pos);
		if (pObject->IsSelected() && pObject->IsKindOf(RUNTIME_CLASS(CPGLText)))
		{
			pSelection->m_lObjects.AddHead(pObject);
		}
	}	
	return pSelection;
}

CPGLObjectManager* CPGLObjectManager::GetSelectionCopy()
{
	POSITION pos;
	CPGLObject* pObject;
	CPGLObjectManager* pSelection=new CPGLObjectManager();

	//finding objects to remove
	pos=m_lObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_lObjects.GetNext(pos);
		if (pObject->IsSelected())
		{
			pSelection->m_lObjects.AddHead(pObject->MakeCopy());
		}
	}	

	return pSelection;
}

//Remove Object
void CPGLObjectManager::RemoveObject(CPGLObject* pObject)
{
	ASSERT_VALID(pObject);

	POSITION pos;
	
	// testing if pObject is in _objectList
	pos=m_lObjects.Find(pObject);
	if (pos!=NULL)
	{
		// pObject is in _objectList at position pos
		// removing from list
		m_lObjects.RemoveAt(pos);
	}
}

void CPGLObjectManager::RemoveObject(UINT ID)
{
	POSITION pos;
	CPGLObject* pObject;

	// object List
	pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		// getting pointer to ith object
		pObject=m_lObjects.GetNext(pos);
		// testing if object.ID == ID
		if (pObject->CheckID(ID))
		{
			// pObject is in _objectList at position pos
			// removing from list
			m_lObjects.RemoveAt(pos);
			// work is finished
			return;
		}
	}
}

//Delete Object
void CPGLObjectManager::DeleteObject(CPGLObject* pObject)
{
	ASSERT_VALID(pObject);

	POSITION pos;
	
	// testing if pObject is in _objectList
	pos=m_lObjects.Find(pObject);
	if (pos!=NULL)
	{
		// pObject is in _objectList at position pos
		// deleting element
		delete m_lObjects.GetAt(pos);
		
		// removing from list
		m_lObjects.RemoveAt(pos);
	}
}

void CPGLObjectManager::DeleteObject(UINT ID)
{
	POSITION pos;
	CPGLObject* pObject;

	// object List
	pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		// getting pointer to ith object
		pObject=m_lObjects.GetNext(pos);
		// testing if object.ID == ID
		if (pObject->CheckID(ID))
		{
			// pObject is in _objectList at position pos
			// deleting element
			delete m_lObjects.GetAt(pos);
			// removing from list
			m_lObjects.RemoveAt(pos);
			// work is finished
			return;
		}
	}
}

void CPGLObjectManager::DeleteAll()
{
	POSITION pos;

	// first we empty the list...
	pos=m_lObjects.GetHeadPosition();	
	while (pos!=NULL)
	{
		delete m_lObjects.GetNext(pos);
	}
	m_lObjects.RemoveAll();
}

void CPGLObjectManager::RemoveSelection()
{
	POSITION pos,oldpos;
	CPGLObject* pObject;

	oldpos=pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		// getting pointer to ith object
		pObject=m_lObjects.GetNext(pos);
		// testing if object.ID == ID
		if (pObject->IsSelected())
		{
			m_lObjects.RemoveAt(oldpos);
		}
		oldpos=pos;
	}
}

void CPGLObjectManager::DeleteSelection()
{
	POSITION oldpos,pos;
	CPGLObject* pObject;

	oldpos=pos=m_lObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		// getting pointer to ith object
		pObject=m_lObjects.GetNext(pos);
		// testing if object is selected
		if (pObject->IsSelected())
		{
			delete m_lObjects.GetAt(oldpos);
			m_lObjects.RemoveAt(oldpos);
		}
		oldpos=pos;
	}
}
