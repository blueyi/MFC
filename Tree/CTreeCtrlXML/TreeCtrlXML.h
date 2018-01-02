
#pragma once

#include "afxcmn.h"

// Don't forget the TinyXML include :-)
#include "TinyXML/tinyxml.h"

class CTreeCtrlXML : public CTreeCtrl
{

public:
	
	CTreeCtrlXML(void);
	
	virtual ~CTreeCtrlXML(void);

public:

	bool LoadFromXML( const CString& a_strFile );

	bool SaveToXML( const CString& a_strFile );

public:

	void Load( TiXmlNode* a_pNode );

	void Save( TiXmlNode* a_pNode );

protected:

	void LoadItem( TiXmlNode* a_pNode, HTREEITEM a_hTreeParent );

	int GetIndentLevel( HTREEITEM hItem );

	HTREEITEM GetNextItem( HTREEITEM hItem );
};
