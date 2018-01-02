
#include "StdAfx.h"
#include "TreeCtrlXML.h"

#include <direct.h>		// Needed for getcwd()

CTreeCtrlXML::CTreeCtrlXML(void)
{
}

CTreeCtrlXML::~CTreeCtrlXML(void)
{
}

bool CTreeCtrlXML::LoadFromXML( const CString& a_strFile )
{
	TiXmlNode* pXML = NULL;
	TiXmlDocument xmlDoc;

	char szBuf[ _MAX_PATH + 1 ];
	CString strTemp = a_strFile;

	getcwd( szBuf, sizeof( szBuf ) );
	strcat( szBuf, "\\" );
	strcat( szBuf, strTemp.GetBuffer( 1 ) );

	if( xmlDoc.LoadFile( szBuf ) )
	{
		// XML root
		pXML = xmlDoc.FirstChild( "XML" );

		if( NULL == pXML )
			return false;

		// Load our tree control
		Load( pXML );

		// Expand all entries
		Expand( GetRootItem(), TVE_EXPAND );

		return true;
	}
    
	return false;
}

bool CTreeCtrlXML::SaveToXML( const CString& a_strFile )
{
	// Save XML
	TiXmlNode* pXML = NULL;
	TiXmlDocument xmlDoc;

	// XML header
	xmlDoc.InsertEndChild( TiXmlDeclaration( "1.0", "UTF-8", "yes" ) );

	// XML root
	pXML = xmlDoc.InsertEndChild( TiXmlElement( "XML" ) );

	// Save our tree control
	Save( pXML );

	// Save XML
	CString strFile = a_strFile;

	return xmlDoc.SaveFile( strFile.GetBuffer( 1 ) );
}

void CTreeCtrlXML::Load( TiXmlNode* a_pNode )
{
	ASSERT( NULL != a_pNode );

	// Get node "Items"
	TiXmlNode* pItems = a_pNode->FirstChild( "Items" );
	TiXmlNode* pItem = NULL;

	if( NULL == pItems )
		return;

	// Get first item
	pItem = pItems->FirstChild( "Item" );

	// Iterate all siblings
	while( NULL != pItem )
	{
		LoadItem( pItem, NULL );
		pItem = pItem->NextSibling( "Item" );
	}
}

void CTreeCtrlXML::Save( TiXmlNode* a_pNode )
{
	ASSERT( NULL != a_pNode );

	TiXmlNode* pItems = a_pNode->InsertEndChild( TiXmlElement( "Items" ) );
	TiXmlNode* pParent = pItems;
	TiXmlNode* pNewNode = NULL;
	HTREEITEM hItem = GetRootItem();
	int iIndent = 0; int iLastIndent = 0;

	while( hItem )
	{
		iIndent = GetIndentLevel( hItem );

		int iDiff = iIndent - iLastIndent;
		if( iDiff > 0 )
		{
			ASSERT( NULL != pNewNode );

			while( iDiff-- )
				pNewNode = pNewNode->InsertEndChild( TiXmlElement( "Item" ) );

			ASSERT( NULL != pNewNode );
			pParent = pNewNode->Parent();
		}
		else if( iDiff < 0 )
		{
			iDiff--;					// Correct difference to get the right parent
			pParent = pNewNode;

			while( iDiff++ < 0 )
				pParent = pParent->Parent();

			ASSERT( NULL != pParent );
			pNewNode = pParent->InsertEndChild( TiXmlElement( "Item" ) );
		}
		else 
		{
			ASSERT( NULL != pParent );
			pNewNode = pParent->InsertEndChild( TiXmlElement( "Item" ) );
		}

		iLastIndent = iIndent;			

		// Save current item
		TiXmlElement* pElement = pNewNode->ToElement();
		ASSERT( NULL != pElement );

		pElement->SetValue( "Item" );
		pElement->SetAttribute( "Title", GetItemText( hItem ) );

		// The next item, please ...
		hItem = GetNextItem( hItem );
	}
}

void CTreeCtrlXML::LoadItem( TiXmlNode* a_pNode, HTREEITEM a_hTreeParent )
{
	ASSERT( NULL != a_pNode );

	TiXmlElement* pEl = a_pNode->ToElement();
	ASSERT( NULL != pEl );

	HTREEITEM hItem = NULL;

	TiXmlNode* pChild = NULL;

	if( NULL == a_hTreeParent )
		hItem = InsertItem( pEl->Attribute( "Title" ), TVI_ROOT );
	else
		hItem = InsertItem( pEl->Attribute( "Title" ), a_hTreeParent );

	pChild = a_pNode->IterateChildren( "Item", NULL );

	while( pChild )
	{
		LoadItem( pChild, hItem );
		pChild = a_pNode->IterateChildren( "Item", pChild );
	}
}

int CTreeCtrlXML::GetIndentLevel( HTREEITEM hItem )
{
	int iIndent = 0;

	while( (hItem = GetParentItem( hItem )) != NULL )
		iIndent++;

	return iIndent;
}

HTREEITEM CTreeCtrlXML::GetNextItem( HTREEITEM hItem )
{
	HTREEITEM hItemRet = NULL;

	if( false == ItemHasChildren( hItem ) )
	{
		while( ( hItemRet = GetNextSiblingItem( hItem ) ) == NULL )
		{
			if( ( hItem = GetParentItem( hItem ) ) == NULL )
				return NULL;
		}
	}
	else
	{
		return GetChildItem( hItem );
	}

	return hItemRet;
}