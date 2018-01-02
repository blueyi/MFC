// PGLRegion.cpp: implementation of the CPGLRegion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include "PGL/pgl.h"
#include "PGL/PGLRegion.h"
#include "PGL/PGLRegionPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPGLRegion,CPGLObject,1);

void CPGLRegion::Serialize(CArchive &archive)
{

    // call base class function first
    // base class is CPGLObject in this case
    CObject::Serialize( archive );

	if (archive.IsLoading())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CPGLRegion::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

    // now do the stuff for our specific class
	// now dumping..
	dc << _T("--- CPGLRegion ---\n")<< endl;
    dc << m_view<<"\n";
}
void CPGLRegion::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check members...
	m_view.AssertValid();
    // check members...
	m_axe.AssertValid();
	m_mObjects.AssertValid();

	if (sm_mClipboard!=NULL)
		ASSERT_VALID(sm_mClipboard);
} 
#endif

CPGLRegion::CPGLRegion()
{
	m_background=CPGLColor(1.0f,1.0f,1.0f,1.0f);
	m_axe.SetView(&m_view);

	m_pNormBBox[0]=m_pNormBBox[1]=0;
	m_pNormBBox[2]=m_pNormBBox[3]=1;

	LoadBitmap(IDB_PGL_REGION_BITMAP);
}

CPGLRegion::CPGLRegion(const CPGLRegion& g)
: CPGLObject(g)
{
	m_view=g.m_view;
	m_background=g.m_background;
	m_axe=g.m_axe;
	m_mObjects=g.m_mObjects;

	for (int i=0;i<4;i++)
	{
		m_pNormBBox[i] = g.m_pNormBBox[i];
	}

	PostUpdateGraph();
}

CPGLRegion& CPGLRegion::operator =(const CPGLRegion& g)
{
	if (&g!=this)
	{
		CPGLObject::operator =(g);

		m_view=g.m_view;
		m_background=g.m_background;
		m_axe=g.m_axe;


		for (int i=0;i<4;i++)
		{
			m_pNormBBox[i] = g.m_pNormBBox[i];
		}

		m_mObjects=g.m_mObjects;
		PostUpdateGraph();
	}
	return *this;
}

CPGLRegion::~CPGLRegion()
{
	// cleaning objects
	m_mObjects.DeleteAll();
	PGL_TRACE("PGL-Region: Objects deleted\n");
	ASSERT(m_mObjects.IsEmpty());
}

/// adds pObject to the graph (memory must be allowed by user)
void CPGLRegion::AddObject(CPGLObject* pObject)
{	
	ASSERT_VALID(pObject);

	ASSERT(! pObject->IsKindOf( RUNTIME_CLASS(CPGLRegion) ) );

	// adding pointer
	m_mObjects.AddHead(pObject); 
	// updating graph
	PostUpdateGraph();
}


CPGLRegion* CPGLRegion::AddRegion()
{
	CPGLRegion* pNewRegion = new CPGLRegion();

	// adding pointer
	m_mChilds.AddHead(pNewRegion); 

	// updating graph
	PostUpdateGraph();

	return pNewRegion;
}

/// removes the selected object from the graph
void CPGLRegion::DeleteSelection()
{	
	// deleting objects
	m_mObjects.DeleteSelection();

	POSITION pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		((CPGLRegion*)m_mChilds.GetNext(pos))->DeleteSelection();
	}

	// updating graph
	PostUpdateGraph();
};

void CPGLRegion::SelectAll()
{
	POSITION pos;

	pos=m_mObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mObjects.GetNext(pos)->Select();
	}

	pos=m_mChilds.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mChilds.GetNext(pos)->Select();
	}
}

void CPGLRegion::UnhideAll()
{
	POSITION pos;

	pos=m_mObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mObjects.GetNext(pos)->Show();
	}

	pos=m_mChilds.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mChilds.GetNext(pos)->Show();
	}
}

void CPGLRegion::UnselectAll()
{
	POSITION pos;

	// unselect axe
	m_axe.Deselect();

	// unselect objects
	pos=m_mObjects.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mObjects.GetNext(pos)->Deselect();
	}

	// unselect objects
	pos=m_mChilds.GetHeadPosition();
	while(pos!=NULL)
	{
		m_mChilds.GetNext(pos)->Deselect();
	}
}

// finding an object by it's ID
CPGLObject* CPGLRegion::FindObject(UINT ID)
{
	POSITION pos;
	CPGLObject* pObject;
	CPGLObject* pRegion;

	// testing if it is itself
	if (CheckID(ID))
		return this;

	// test m_axe
	pObject=m_axe.FindObject(ID);
	if (pObject)
		return pObject;

	// test objects
	pos=m_mObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_mObjects.GetNext(pos);
		if (pObject->CheckID(ID))
			return pObject;
	}

	// test objects
	pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		pRegion=m_mChilds.GetNext(pos);
		pObject = ((CPGLRegion*)pRegion)->FindObject(ID);
		if (pObject)
			return pObject;
	}

	// not found
	return NULL;
}

double* CPGLRegion::GetExtent()
{
	POSITION pos;
	CPGLObject* pObject;
	double* locExtent;
	bool first=true;

	// no object case
	if (m_mObjects.IsEmpty())
	{
		m_extent[0]=0;
		m_extent[1]=1;
		m_extent[2]=0;
		m_extent[3]=1;

		return m_extent;
	}

	// first, non text objects.
	pos=m_mObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_mObjects.GetNext(pos);
		ASSERT_VALID(pObject);

		if (!pObject->IsVisible())
			continue;

		// skip text for the moment
		if (pObject->GetRuntimeClass()==RUNTIME_CLASS(CPGLText)
			|| pObject->GetRuntimeClass()==RUNTIME_CLASS(CPGLLineVer)
			|| pObject->GetRuntimeClass()==RUNTIME_CLASS(CPGLLineHor))
			continue;

		// test for type...
		locExtent=pObject->GetExtent(&m_view);

		// testing...
		if (first)
		{
			m_extent[0]=locExtent[0];
			m_extent[1]=locExtent[1];
			m_extent[2]=locExtent[2];
			m_extent[3]=locExtent[3];
			first=false;
		}
		else
		{
			m_extent[0]=__min(m_extent[0],locExtent[0]);	//left
			m_extent[1]=__max(m_extent[1],locExtent[1]);	//right
			m_extent[2]=__min(m_extent[2],locExtent[2]);	//bottom
			m_extent[3]=__max(m_extent[3],locExtent[3]);	//up
		}
	}
	
	return m_extent;
}

void CPGLRegion::Delete()
{
	PGL_TRACE("PGL-Region: Starting cleaning\n");

	// deleting axe
	m_axe.Delete();
	PGL_TRACE("PGL-Graph: Axe deleted\n");

	// deleting objects
	DeleteAllObjects();

	PGL_TRACE("PGL-Region: Fonts unassigned\n");

	// cleaning clipboard
	if (sm_mClipboard!=NULL)
	{
		sm_mClipboard->DeleteAll();
		delete sm_mClipboard;
		sm_mClipboard=NULL;
	}
	// Post updating
	PostUpdateGraph();
	PGL_TRACE("PGL-Region: Cleaning success, processing childs\n");
}

void CPGLRegion::UpdateGraph()
{	
	double pExt[4];
	// retreive info
	m_axe.GetLimits(0,pExt);
	m_axe.GetLimits(1,pExt+2);

	// updating extent to put axis
	m_axe.GrowExtent(pExt);

	// updating view
	m_view.ZoomAll(pExt[0],pExt[1],pExt[2],pExt[3]);
	
	// update labels
	m_axe.UpdateLabels();
	m_bNeedUpdate=FALSE;

	// computing child viewports
	CPGLRegion* pRegion;
	POSITION pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		pRegion=(CPGLRegion*)m_mChilds.GetNext(pos);
		ASSERT_VALID(pRegion);
		pRegion->UpdateGraph();
	}
};

void CPGLRegion::SetViewport(int tx, int ty, int width, int height)
{
	CPGLRegion* pRegion;

	// computing own viewport
	m_view.SetViewport(
		tx + (int) floor(width * m_pNormBBox[0]),
		ty + (int) floor(height * m_pNormBBox[1]),
		(int) floor(width * (m_pNormBBox[2]-m_pNormBBox[0])),
		(int) floor(height * (m_pNormBBox[3]-m_pNormBBox[1])));

	// computing child viewports
	POSITION pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		pRegion=(CPGLRegion*)m_mChilds.GetNext(pos);
		ASSERT_VALID(pRegion);
		pRegion->SetViewport(m_view.GetTx(), m_view.GetTy(), m_view.GetWidth(), m_view.GetHeight());
	}
};

void CPGLRegion::ZoomAll(BOOL recurse)
{
//	ASSERT_VALID(m_pDC);
	// getting extent
	double* pExt=GetExtent();

	// updating extent to put axis
	double pExtNew[4];
	for (int i=0;i<4;i++)
		pExtNew[i]=pExt[i];

	// updating axis
	m_axe.SetLimits(0,pExtNew[0],pExtNew[1]);
	m_axe.SetLimits(1,pExtNew[2],pExtNew[3]);

	// retreive info
	m_axe.GetLimits(0,pExtNew);
	m_axe.GetLimits(1,pExtNew+2);

	// grow window
	m_axe.GrowExtent(pExtNew);

	// updating view
	m_view.ZoomAll(pExtNew[0],pExtNew[1],pExtNew[2],pExtNew[3]);

	if (recurse)
	{
		POSITION pos=m_mChilds.GetHeadPosition();
		while (pos!=NULL)
		{
			((CPGLRegion*)m_mChilds.GetNext(pos))->ZoomAll(TRUE);
		}
	}
}

void CPGLRegion::ZoomRegion(double* pExt)
{
	// updating axis
	m_axe.SetLimits(0,pExt[0],pExt[1]);
	m_axe.SetLimits(1,pExt[2],pExt[3]);

	// retreive info
	m_axe.GetLimits(0,pExt);
	m_axe.GetLimits(1,pExt+2);

	// updating extent to put axis
	m_axe.GrowExtent(pExt);

	// updating view
	m_view.ZoomAll(pExt[0],pExt[1],pExt[2],pExt[3]);
}

void CPGLRegion::ZoomBox(int xStart, int yStart, int xEnd, int yEnd)
{
	// putting start and end in order
	int temp;
	if (xStart>xEnd)
	{
		temp=xStart;
		xStart=xEnd;
		xEnd=temp;
	}
	// y is going down
	if (yStart<yEnd)
	{
		temp=yStart;
		yStart=yEnd;
		yEnd=temp;
	}
	// checking that box has at least 1 of size
	if (xStart==xEnd)
		xEnd++;
	if (yStart==yEnd)
		yEnd++;

	// step 1 setting axis
	// sending dimension of box to axe and computing box
	m_axe.SetLimits(0, 
		m_view.PixelToWorldCoord(0,xStart), //left
		m_view.PixelToWorldCoord(0,xEnd)); //right
	m_axe.SetLimits(1, 
		m_view.PixelToWorldCoord(1,yStart), //bottom
		m_view.PixelToWorldCoord(1,yEnd)); //top

	// retreivinf info
	double pExt[4];
	m_axe.GetLimits(0,pExt);
	m_axe.GetLimits(1,pExt+2);

	// Step 2 grow extent
	m_axe.GrowExtent(pExt);

	// Step 3, updating view
	m_view.ZoomAll(pExt[0],pExt[1],pExt[2],pExt[3]);
}

void CPGLRegion::ZoomIn()
{
	// step 1 zoom in of view
	m_view.ZoomIn();

	// step 2 set axis
	m_axe.SetLimits(0, 
		m_view.GetLeft(), //left
		m_view.GetRight()); //right
	m_axe.SetLimits(1, 
		m_view.GetBottom(), //bottom
		m_view.GetTop()); //top

	// retreivinf info
	double pExt[4];
	m_axe.GetLimits(0,pExt);
	m_axe.GetLimits(1,pExt+2);

	// Step 2 grow extent
	m_axe.GrowExtent(pExt);

	// Step 3, updating view
	m_view.ZoomAll(pExt[0],pExt[1],pExt[2],pExt[3]);
}

void CPGLRegion::ZoomOut()
{
	// step 1 zoom in of view
	m_view.ZoomOut();

	// step 2 set axis
	m_axe.SetLimits(0, 
		m_view.GetLeft(), //left
		m_view.GetRight()); //right
	m_axe.SetLimits(1, 
		m_view.GetBottom(), //bottom
		m_view.GetTop()); //top

	// retreivinf info
	double pExt[4];
	m_axe.GetLimits(0,pExt);
	m_axe.GetLimits(1,pExt+2);

	// Step 2 grow extent
	m_axe.GrowExtent(pExt);

	// Step 3, updating view
	m_view.ZoomAll(pExt[0],pExt[1],pExt[2],pExt[3]);
}


void CPGLRegion::Pan(int x, int y)
{
	// step 1 pan view
	m_view.Pan(x,y);

	m_axe.Pan(m_view.PixelToWorld(0,x),m_view.PixelToWorld(1,y));
}


void CPGLRegion::DeleteAllObjects()
{
	// Remove objects
	m_mObjects.DeleteAll();

	// remove region
	CPGLRegion* pRegion;
	POSITION pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		pRegion = (CPGLRegion*)m_mChilds.GetNext(pos);
		pRegion->Delete();
	}
	m_mChilds.DeleteAll();
}

const float* CPGLRegion::GetNormBBox() const
{
	return m_pNormBBox;
}

void CPGLRegion::SetNormBBox(float BBox[])
{
	// make lower left corner and upper right are ordered
	m_pNormBBox[0] = __max(0, __min(BBox[0], BBox[2]));
	m_pNormBBox[2] = __min(1, __max(BBox[0], BBox[2]));
	m_pNormBBox[1] = __max(0, __min(BBox[1], BBox[3]));
	m_pNormBBox[3] = __min(1, __max(BBox[1], BBox[3]));
	ASSERT(m_pNormBBox[0] != 1);
	ASSERT(m_pNormBBox[1] != 1);
	ASSERT(m_pNormBBox[2] != 0);
	ASSERT(m_pNormBBox[3] != 0);
	ASSERT(m_pNormBBox[0] != m_pNormBBox[2]);
	ASSERT(m_pNormBBox[1] != m_pNormBBox[3]);
}

void CPGLRegion::SetNormBBox(float llx, float lly, float urx, float ury)
{
	// make lower left corner and upper right are ordered
	m_pNormBBox[0] = __max(0, __min(llx, urx));
	m_pNormBBox[2] = __min(1, __max(llx, urx));
	m_pNormBBox[1] = __max(0, __min(lly, ury));
	m_pNormBBox[3] = __min(1, __max(lly, ury));
	ASSERT(m_pNormBBox[0] != 1);
	ASSERT(m_pNormBBox[1] != 1);
	ASSERT(m_pNormBBox[2] != 0);
	ASSERT(m_pNormBBox[3] != 0);
	ASSERT(m_pNormBBox[0] != m_pNormBBox[2]);
	ASSERT(m_pNormBBox[1] != m_pNormBBox[3]);
}

void CPGLRegion::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLRegionPropPage* propPage=new CPGLRegionPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLObject::AddPropertyPage(pPropSheet);
}

HTREEITEM CPGLRegion::AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent)
{
	ASSERT_VALID(pTree);
	CString str;

	CImageList* pImgList=pTree->GetImageList(TVSIL_NORMAL);
	ASSERT_VALID(pImgList);
	ASSERT(hParent);
	COLORREF crMask=0;

	// adding bitmap
	pImgList->Add(CBitmap::FromHandle(GetBitmap()),crMask);

	// adding to tree
	POSITION pos;
	CPGLObject* pObject;
	CPGLRegion* pRegion;
	HTREEITEM pRegionItem;
	HTREEITEM pObjItem;
	HTREEITEM pRgnItem;

	// inserting object root
	pRegionItem=pTree->InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM   /* nMask*/, 
				GetName() /* lpszItem*/, 
				pImgList->GetImageCount()-1 /* nImage */, 
				0 /* nSelectedImage */, 
				0  /* nState */, 
				0 /* nStateMask */, 
				GetID() /*  lParam */, 
				hParent /* hParent */, 
				TVI_LAST /* hInsertAfter */);
	ASSERT(pRegionItem!=NULL);

	// insert axis
	// adding to tree
	HTREEITEM pAxeItem=m_axe.AddPropTree(pTree,pRegionItem);
	ASSERT(pAxeItem!=NULL);
	// check if selected...
//	if ((long)m_axe.GetID()==m_lSelID)
//		pTree->SelectItem(pAxeItem);

	// filling up insert structure with objects
	pos=m_mObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		pObject=m_mObjects.GetNext(pos);
		ASSERT_VALID(pObject);

		pObjItem=pObject->AddPropTree(pTree,pRegionItem);
		ASSERT(pObjItem!=NULL);
		// check if selected...
//		if ((long)pObject->GetID()==m_lSelID)
//			pTree->SelectItem(pObjItem);
	}

	// filling up insert structure with subplots
	pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		pRegion=(CPGLRegion*)m_mChilds.GetNext(pos);
		ASSERT_VALID(pRegion);

		pRgnItem=pRegion->AddPropTree(pTree,pRegionItem);
		ASSERT(pRgnItem!=NULL);
		// check if selected...
//		if ((long)pRegion->GetID()==m_lSelID)
//			pTree->SelectItem(pRgnItem);
	}

	return pRegionItem;
}

void CPGLRegion::Divide(int nrows, int ncols)
{
	float llx, lly, urx, ury;
	CString str;

	if ((nrows == 0) || (ncols == 0))
		return;

	// deleting all objects
	DeleteAllObjects();
	// hiding axis
	m_axe.Hide();

	// adding new regions...
	CPGLRegion* pRegion;
	int i,j;

	for (i=0;i<nrows;i++)
	{
		lly = (float)((double) i / (double) (nrows));
		ury = (float)((double) (i+1) / (double) (nrows));
		for (j=ncols-1;j>=0;j--)
		{
			llx = (float)((double) j / (double) (ncols));
			urx = (float)((double) (j+1) / (double) (ncols));

			pRegion = AddRegion();
			pRegion->SetNormBBox(llx, lly, urx, ury);
			str.Format("Subplot (%i,%i)",i+1,j+1);
			pRegion->SetName(str);
		}
	}
}

CPGLRegion* CPGLRegion::GetChild(int i)
{
	POSITION pos = m_mChilds.FindIndex(i);

	if (pos)
		return (CPGLRegion*)m_mChilds.GetAt(pos);
	else
		return NULL;
}

void CPGLRegion::PlotGfx(gfxinterface::CGfxInterface& gfx)
{	
	CPGLObject::PlotGfx(gfx);
	CString str;

	POSITION pos;
	// updating graph
	UpdateGraph();

	str.Format("--- CPGLRegion %s ---", GetName());
	gfx.AddComment(str);
	gfx.PushState();
	// setting bounding box
	m_view.PlotGfx(gfx);

	// drawing background...
	gfx.PushState();
	gfx.SetFillColor(m_background.GetRed(), m_background.GetGreen(), m_background.GetBlue(), m_background.GetAlpha());
	gfx.SetColor(m_background.GetRed(), m_background.GetGreen(), m_background.GetBlue(), m_background.GetAlpha());
	gfx.DrawRect( m_view.GetLeft(), m_view.GetBottom(), m_view.GetRight(), m_view.GetTop() , TRUE);
	gfx.PopState();

	// setting clipping path
	m_axe.ClipGfx(gfx);

	// now plotting the objects
	pos=m_mObjects.GetHeadPosition();
	while (pos!=NULL)
	{
		m_mObjects.GetNext(pos)->PlotGfx(gfx);
	}
	// remove clipping path
	m_axe.UnClipGfx(gfx);
	// plotting the axe
	m_axe.PlotGfx(gfx);
	gfx.PopState();
	
	// Drawing childs
	pos=m_mChilds.GetHeadPosition();
	while (pos!=NULL)
	{
		m_mChilds.GetNext(pos)->PlotGfx(gfx);
	}
};
