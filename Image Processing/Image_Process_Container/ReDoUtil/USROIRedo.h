// USROIRedo.h: interface for the CUSROIRedo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USROIREDO_H__54584F16_A637_4F9F_877B_5496C2CDC86F__INCLUDED_)
#define AFX_USROIREDO_H__54584F16_A637_4F9F_877B_5496C2CDC86F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "edgeobj.h"

class AFX_EXT_CLASS CUSROIRedo
{
public:
	void ClearRedoStack();
	CEdgeObj *m_CurrentObj;
	int GetRedoStackSize();
	CUSROIRedo();
	virtual ~CUSROIRedo();

	int Push(PtContainer pts, PtContainer tissuePts, PtContainer tissuePreviewPts, OperationType operaType);
	int Undo(PtContainer &pts, PtContainer &tissuePts, PtContainer &tissuePreviewPts, OperationType &operaType);
	int Redo(PtContainer &pts, PtContainer &tissuePts, PtContainer &tissuePreviewPts, OperationType &operaType);
	void Clear() ;

protected:
	stack<CEdgeObj*>m_undoStack;
	stack<CEdgeObj*>m_redoStack;

};

#endif // !defined(AFX_USROIREDO_H__54584F16_A637_4F9F_877B_5496C2CDC86F__INCLUDED_)
