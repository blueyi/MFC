// PGLGraphDlgList.cpp: implementation of the CPGLGraphDlgList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLGraphDlgList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPGLGraphDlgList::CPGLGraphDlgList()
{
}

CPGLGraphDlgList::~CPGLGraphDlgList()
{
	RemoveAll();
}

void CPGLGraphDlgList::AddHead(CPGLGraphBitDlg *pGraphDlg)
{	
	PGL_TRACE("PGL-GraphDlgList: Adding CPGLGraphBitDlg to List of dialogs.\n");
	ASSERT_VALID(pGraphDlg);
	BOOL created=TRUE;
	CString str;

	CSingleLock synchro(&m_ThreadLock);

	synchro.Lock();
	if (synchro.IsLocked())
	{
		// creating if needed
		if (! pGraphDlg->GetSafeHwnd() )
		{
			// saving old ressource.
			HINSTANCE hOldInst=AfxGetResourceHandle();
			// setting dll ressource
			AfxSetResourceHandle(AfxGetInstanceHandle());
			// creating dialog
			created=pGraphDlg->Create(IDD_PGL_DIALOG_GRAPH);
			// restoring old ressource.
			AfxSetResourceHandle(hOldInst);
		}
	
		if (created)
		{
			m_GraphList.AddHead(pGraphDlg);
			pGraphDlg->ShowWindow(SW_SHOWNORMAL);   
		}
		else
		{
			pGraphDlg->GetWindowText(str);
			AfxMessageBox("Failed to create dialog box for graph "+str);
		}

		// release thread
		synchro.Unlock();
	}

	PGL_TRACE("PGL-GraphDlgList: Graph added\n");
}

void CPGLGraphDlgList::ShowAll()
{
	ASSERT_VALID(&m_GraphList);
	POSITION pos;
	CPGLGraphBitDlg* pGraphDlg;

	pos = m_GraphList.GetHeadPosition();
	while(pos!=NULL)
	{
		pGraphDlg=m_GraphList.GetNext(pos);

		if (!pGraphDlg->GetSafeHwnd())
		{
			// saving old ressource.
			HINSTANCE hOldInst=AfxGetResourceHandle();
			// setting dll ressource
			AfxSetResourceHandle(AfxGetInstanceHandle());
			// creating dialog
			pGraphDlg->Create(IDD_PGL_DIALOG_GRAPH);
			// restoring old ressource.
			AfxSetResourceHandle(hOldInst);
		}

		pGraphDlg->ShowWindow(SW_SHOWNORMAL);   
	}
	TRACE("PGL-GraphDlgList: Graph Showed\n");
}

void CPGLGraphDlgList::Remove(CPGLGraphBitDlg *_pGraphDlg)
{
	POSITION pos, posNext;
	CPGLGraphBitDlg* pGraphDlg;

	if (_pGraphDlg==NULL)
		return;

	if (_pGraphDlg->IsWindowVisible())
		return;


	CSingleLock synchro(&m_ThreadLock);
	// locking thread
	synchro.Lock();
	if (synchro.IsLocked())
	{
		posNext = pos = m_GraphList.GetHeadPosition();
		while(pos!=NULL)
		{
			pGraphDlg=m_GraphList.GetNext(posNext);
			if (pGraphDlg==_pGraphDlg)
			{
				// removing from list
				m_GraphList.RemoveAt(pos);
				pGraphDlg->DestroyWindow();
				delete pGraphDlg;
				pGraphDlg=NULL;
				return;
			}
			pos=posNext;
		}
		// release thread
		synchro.Unlock();
	}
}	
	
void CPGLGraphDlgList::RemoveAll()
{
	POSITION pos;
	CPGLGraphBitDlg* pGraphDlg;

	TRACE("PGL-GraphDlgList::RemoveAll: Removing all graph dialogs\n");

	CSingleLock synchro(&m_ThreadLock);
	// locking thread
	synchro.Lock();
	if (synchro.IsLocked())
	{
		TRACE("PGL-GraphDlgList::RemoveAll: List locked, starting\n");
		pos = m_GraphList.GetHeadPosition();
		while(pos!=NULL)
		{
			pGraphDlg=m_GraphList.GetNext(pos);
			// cleaning graph
			if (pGraphDlg)
			{
				pGraphDlg->DestroyWindow();
				delete pGraphDlg;
				pGraphDlg=NULL;
			}
		}
		m_GraphList.RemoveAll();

		// release thread
		synchro.Unlock();
	}

	TRACE("PGL-GraphDlgList: Graphs dialogs removed\n");
}


void CPGLGraphDlgList::RemoveHidden()
{
	POSITION pos,oldpos;
	CPGLGraphBitDlg* pGraphDlg;

	CSingleLock synchro(&m_ThreadLock);
	// locking thread
	synchro.Lock();
	if (synchro.IsLocked())
	{
		pos = m_GraphList.GetHeadPosition();
		while(pos!=NULL)
		{
			oldpos=pos;
			pGraphDlg=m_GraphList.GetNext(pos);
			ASSERT(pGraphDlg);
			if (! pGraphDlg->IsWindowVisible() )
			{
				VERIFY(pGraphDlg->DestroyWindow());
				delete pGraphDlg;

				// removing pointer
				m_GraphList.RemoveAt(oldpos);				
			}
		}

		// release thread
		synchro.Unlock();
	}
}
