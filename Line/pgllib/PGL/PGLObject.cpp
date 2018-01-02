// ObjectGL.cpp: implementation of the CPGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLObject.h"
#include "PGL/PGLObjectPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLObject, CObject, 1);

UINT CPGLObject::m_uNextID=1;
CPGLColor CPGLObject::m_selectionColor(1.0f,0.0f,0.0f,0.8f);	//red

void CPGLObject::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

	// CPGLObject serialization
	m_color.Serialize(archive);
	m_selectionColor.Serialize(archive);

    // now do the stuff for our specific class
	int i;
    if( archive.IsStoring() )
	{
        archive << m_bSelected << m_bVisible << m_uID << m_sName;
		for (i=0;i<4;i++)
			archive<<m_extent[i];
	}
    else
	{
        archive >> m_bSelected >> m_bVisible >> m_uID >> m_sName;
		for (i=0;i<4;i++)
			archive>>m_extent[i];
		m_uNextID=__max(m_uID+1,m_uNextID);
		PostUpdateExtent();
	}
}

#ifdef _DEBUG
void CPGLObject::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

    // now do the stuff for our specific class
	// now dumping
	dc << _T("CPGLOBject m_uID ") << GetID() << endl;
}

void CPGLObject::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check CPerson members...
	m_color.AssertValid();
	m_selectionColor.AssertValid();
    ASSERT( !m_sName.IsEmpty()); // Must have a m_sName
	ASSERT( m_extent[0]<=m_extent[1]);
	ASSERT( m_extent[2]<=m_extent[3]);
} 

#endif

/// default constructor
CPGLObject::CPGLObject(const CPGLColor& _color)
{ 
	m_hBitmap=NULL;
	m_bSelected=FALSE;
	m_bVisible=TRUE;
	// setting ID number and making sur it's unique
	m_uID=m_uNextID++;
	m_sName.Format("ID = %u",m_uID);

	m_color=_color;

	m_extent=new double[4];
	for (int i=0;i<4;i++)
		m_extent[i]=0;
	PostUpdateExtent();
};

///  copy constructor
CPGLObject::CPGLObject(const CPGLObject& o)
{
	m_bSelected=o.m_bSelected;
	m_bVisible=o.m_bVisible;
	m_uID=m_uNextID++;
	m_sName=o.m_sName;
	m_color=o.m_color;
	m_extent=new double[4];
	for (int i=0;i<4;i++)
		m_extent[i]=o.m_extent[i];
};
/// assignement constructor
CPGLObject& CPGLObject::operator = (const CPGLObject& o)
{
	// prevent self-assignement
	if (&o != this)
	{
		// copy the operand
		m_bSelected=o.m_bSelected;
		m_bVisible=o.m_bVisible;
		m_uID=m_uNextID++;
		m_sName=o.m_sName;
		m_color=o.m_color;
		for (int i=0;i<4;i++)
			m_extent[i]=o.m_extent[i];
	}
	return *this;
}

void CPGLObject::AddPropertyPage(CPropertySheet *pPropSheet)
{
	CPGLObjectPropPage* propPage=new CPGLObjectPropPage(this);

	pPropSheet->AddPage(propPage);
}

HTREEITEM CPGLObject::AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent)
{
	ASSERT_VALID(pTree);
	CImageList* pImgList=pTree->GetImageList(TVSIL_NORMAL);
	ASSERT_VALID(pImgList);
	ASSERT(hParent);
	// adding bitmap
	COLORREF crMask=0;
	pImgList->Add(CBitmap::FromHandle(GetBitmap()),crMask);
	// adding to tree
	return pTree->InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM  /* nMask*/, 
				GetName() /* lpszItem*/, 
				pImgList->GetImageCount()-1 /* nImage */, 
				0 /* nSelectedImage */, 
				0 /* nState */, 
				0 /* nStateMask */, 
				GetID() /*  lParam */, 
				hParent /* hParent */, 
				TVI_LAST /* hInsertAfter */);
}

void CPGLObject::PlotGfx(gfxinterface::CGfxInterface& gfx)
{	
	gfx.AddComment("--- CPGLObject ---\n");
	gfx.AddComment("set object color\n");
	gfx.SetColor(m_color.GetRed(),m_color.GetGreen(),m_color.GetBlue(),m_color.GetAlpha());
};

void CPGLObject::LoadBitmap(DWORD ID_RESSOURCE)
{
	HMODULE hInst=CPGLGlobal::GetInstance();
			
	ASSERT(hInst);
	if (m_hBitmap)
		::DeleteObject(m_hBitmap);

	m_hBitmap=::LoadBitmap(hInst, MAKEINTRESOURCE(ID_RESSOURCE));
}