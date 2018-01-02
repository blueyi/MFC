//////////////////////////////////////////////////////////
//
//  만든이 : 서우석
// ----------------------------------------------------
//  이 소스는 공개 소스이며, 이 소스를 사용할 경우
//  반드시 저의 이름을 같이 올려주시면 감사하겠습니다. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////


#include "stdafx.h"
#include "EasyFavorite.h"
#include "OleURLDropTarget.h"

#include "CtrView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COleURLDropTarget::COleURLDropTarget(CWnd* pParent)
{
	m_pParent = pParent;
}

COleURLDropTarget::~COleURLDropTarget()
{

}



//
// OnDragEnter is called by OLE dll's when drag cursor enters
// a window that is REGISTERed with the OLE dll's
//
DROPEFFECT COleURLDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* 
           pDataObject, DWORD dwKeyState, CPoint point )
{
	if (!pDataObject->IsDataAvailable(CF_TEXT))
	{
		return DROPEFFECT_NONE;
	
	}

    // if the control key is held down, return a drop effect COPY 
    if((dwKeyState&MK_CONTROL) == MK_CONTROL)
        return DROPEFFECT_COPY;
    // Otherwise return a drop effect of MOVE
    else
        return DROPEFFECT_MOVE;    
}

//
// OnDragLeave is called by OLE dll's when drag cursor leaves
// a window that is REGISTERed with the OLE dll's
//
void COleURLDropTarget::OnDragLeave(CWnd* pWnd)
{
    // Call base class implementation
    COleDropTarget::OnDragLeave(pWnd);
}

// 
// OnDragOver is called by OLE dll's when cursor is dragged over 
// a window that is REGISTERed with the OLE dll's
//
DROPEFFECT COleURLDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* 
           pDataObject, DWORD dwKeyState, CPoint point )
{     
	if (!pDataObject->IsDataAvailable(CF_TEXT))
		return DROPEFFECT_NONE;

    if((dwKeyState&MK_CONTROL) == MK_CONTROL)
        return DROPEFFECT_NONE;  
    else
        return DROPEFFECT_MOVE;  // move source
}


BOOL COleURLDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, 
                 DROPEFFECT dropEffect, CPoint point )
{           
    HGLOBAL  hGlobal;
    LPCSTR   pData;                     

	if (pDataObject->IsDataAvailable(CF_TEXT))
	{		
		STGMEDIUM Stg;
		BOOL bValue = pDataObject->GetData(CF_TEXT, &Stg);		

		TCHAR *strText = (TCHAR*)GlobalLock(Stg.hGlobal);
		
		CString strUrl;
		strUrl.Format("%s",strText);

		((CCtrView *)m_pParent)->AddFavorite(strUrl);

		GlobalUnlock(Stg.hGlobal);
		GlobalFree(Stg.hGlobal);		

	}

    if((dropEffect&DROPEFFECT_MOVE) != DROPEFFECT_MOVE)
        return FALSE;

    // Get text data from COleDataObject
    hGlobal=pDataObject->GetGlobalData(CF_TEXT);

    // Get pointer to data
    pData=(LPCSTR)GlobalLock(hGlobal);    
    ASSERT(pData!=NULL); 

    // Unlock memory - Send dropped text into the "bit-bucket"
    GlobalUnlock(hGlobal);

    return TRUE;
}


void COleURLDropTarget::SetParent(CWnd *pParent)
{
	m_pParent = pParent;
}
