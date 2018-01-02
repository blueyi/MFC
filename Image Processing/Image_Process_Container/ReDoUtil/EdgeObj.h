// EdgeObj.h: interface for the CEdgeObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGEOBJ_H__CF7B64BB_FB76_4832_9930_2BBF8AB71D42__INCLUDED_)
#define AFX_EDGEOBJ_H__CF7B64BB_FB76_4832_9930_2BBF8AB71D42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <stack>
using namespace std;

enum eUndoRedoType
{
	UNDOREDO_TYPE_NULL,
	UNDOREDO_TYPE_EDGE,
	UNDOREDO_TYPE_ROI
};

typedef std::vector<CPoint> PtContainer ;
typedef int OperationType;

class CEdgeObj  
{
public:
	CEdgeObj();
	virtual ~CEdgeObj();

	PtContainer m_objEdgePts;
	PtContainer m_objTissue;	// for mask, Subordinate of m_objEdgePts
	PtContainer m_objTissuePreview;
	PtContainer m_objROIPts;
	OperationType m_operaType;

};

#endif // !defined(AFX_EDGEOBJ_H__CF7B64BB_FB76_4832_9930_2BBF8AB71D42__INCLUDED_)
