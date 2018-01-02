// USROIRedo.cpp: implementation of the CUSROIRedo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "USROIRedo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUSROIRedo::CUSROIRedo()
{
	m_CurrentObj = new CEdgeObj();
	CPoint pt(0, 0);
	m_CurrentObj->m_objEdgePts.push_back(pt);
	m_CurrentObj->m_objROIPts.push_back(pt);
	m_CurrentObj->m_operaType = UNDOREDO_TYPE_NULL;
}

CUSROIRedo::~CUSROIRedo()
{
	if (m_CurrentObj) 
	{
		delete m_CurrentObj;
	}
	Clear();
}

int CUSROIRedo::Push(PtContainer pts, PtContainer tissuePts, PtContainer tissuePreviewPts, OperationType operaType)
{
	CEdgeObj* pObjPts;

	pObjPts = new CEdgeObj();
	if (NULL == pObjPts)
	{
		return -1;  //no memory ;
	}

	switch(operaType) {
	case UNDOREDO_TYPE_EDGE:
		pObjPts->m_operaType = operaType;
		pObjPts->m_objEdgePts = pts;
		pObjPts->m_objTissue = tissuePts;
		pObjPts->m_objTissuePreview = tissuePreviewPts;
		break;
	case UNDOREDO_TYPE_ROI:
		pObjPts->m_operaType = operaType;
		pObjPts->m_objROIPts = pts;
		break;
	default:
		;
	}

	m_undoStack.push(pObjPts);

	return m_undoStack.size();
}

int CUSROIRedo::Undo(PtContainer &pts, PtContainer &tissuePts, PtContainer &tissuePreviewPts, OperationType &operaType)
{
	CEdgeObj* pObjPts;
	if (m_undoStack.size() <= 0)
	{
		return -2;   //The Undo stack is null;
	}

	m_redoStack.push(m_CurrentObj);

	pObjPts = m_undoStack.top();
	m_undoStack.pop();
	if (pObjPts)
	{
		switch(pObjPts->m_operaType) {
		case UNDOREDO_TYPE_EDGE:
			pts = pObjPts->m_objEdgePts;
			tissuePts = pObjPts->m_objTissue;
			tissuePreviewPts = pObjPts->m_objTissuePreview;
			operaType = UNDOREDO_TYPE_EDGE;
			break;
		case UNDOREDO_TYPE_ROI:
			pts = pObjPts->m_objROIPts;
			operaType = UNDOREDO_TYPE_ROI;
			break;
		default:
			;
		}
	}
	m_CurrentObj = pObjPts;

	return m_undoStack.size();
}

int CUSROIRedo::Redo(PtContainer &pts, PtContainer &tissuePts, PtContainer &tissuePreviewPts, OperationType &operaType)
{
	CEdgeObj* pObjPts;

	if (m_redoStack.size() <= 0)
	{
		return -3;   //The Redo stack is null;
	}

	m_undoStack.push(m_CurrentObj);

	pObjPts = m_redoStack.top();
	m_redoStack.pop();
	if (pObjPts)
	{
		switch(pObjPts->m_operaType) {
		case UNDOREDO_TYPE_EDGE:
			pts = pObjPts->m_objEdgePts;
			tissuePts = pObjPts->m_objTissue;
			tissuePreviewPts = pObjPts->m_objTissuePreview;
			operaType = UNDOREDO_TYPE_EDGE;
			break;
		case UNDOREDO_TYPE_ROI:
			pts = pObjPts->m_objROIPts;
			operaType = UNDOREDO_TYPE_ROI;
			break;
		default:
			;
		}
	}
	m_CurrentObj = pObjPts;

	return m_redoStack.size();
}

void CUSROIRedo::Clear()
{
	int i;
	CEdgeObj* pObjPts;

	int nStackSize = m_undoStack.size();
	for (i=0; i<nStackSize; i++)
	{
		pObjPts = m_undoStack.top();
		m_undoStack.pop();
		if (pObjPts)
		{
			delete pObjPts;
		}
	}

	nStackSize = m_redoStack.size();
	for (i=0; i<nStackSize; i++)
	{
		pObjPts = m_redoStack.top();
		m_redoStack.pop();
		if (pObjPts)
		{
			delete pObjPts;
		}
	}
}

inline int CUSROIRedo::GetRedoStackSize()
{
	return m_redoStack.size();
}

void CUSROIRedo::ClearRedoStack()
{
	int i;
	CEdgeObj* pObjPts;
	
	int nStackSize = m_redoStack.size();
	for (i=0; i<nStackSize; i++)
	{
		pObjPts = m_redoStack.top();
		m_redoStack.pop();
		if (pObjPts)
		{
			delete pObjPts;
		}
	}
}





















