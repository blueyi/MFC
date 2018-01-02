/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
// PGLRegion.h: interface for the CPGLRegion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLREGION_H__DAD08248_1E11_4C95_A77D_4968F1077BFD__INCLUDED_)
#define AFX_PGLREGION_H__DAD08248_1E11_4C95_A77D_4968F1077BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLObject.h"
#include "PGLObjectManager.h"
#include "PGLView2D.h"
#include "PGLAxe.h"
#include "PGLLegend.h"

/*!
	\defgroup PGLRegionGroup Graphical regions (such as graph, sub-plots)
\ingroup PGLObjectGroup
*/

/*! \brief A base class to create graphic regions.

\ingroup PGLRegionGroup
This is the base class for all graphical regions. It controls common carateristics
of all graphical objects but also has added features to handle the view, resizing.
*/
class PGL_EXT_CLASS CPGLRegion : public CPGLObject  
{
public:
	CPGLRegion* GetChild(int i);
	int GetNChilds() const
	{	return m_mChilds.GetCount();};
	void Divide(int nrows, int ncols);
	HTREEITEM AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent);
	void AddPropertyPage(CPropertySheet* pPropSheet);
	void SetNormBBox(float BBox[4]);
	void SetNormBBox(float llx, float lly, float urx, float ury);
	const float* GetNormBBox() const;
	DECLARE_SERIAL(CPGLRegion);
	/*! \name Class Members*/
	//@{
	//!  constructor
	CPGLRegion();
	//!  copy constructor
	CPGLRegion(const CPGLRegion& r);
	//!  assignement constructor
	CPGLRegion& operator =(const CPGLRegion& g);
	//!  returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLRegion(*this); return pCopy; };
	//! Destructor
	virtual ~CPGLRegion();
	//! Delete all objects in graph and destroy it.
	virtual void Delete();
	virtual void DeleteAllObjects();

	CPGLAxe2D* GetAxe()
	{	return &m_axe;};

	//!  a classical paste function
	void PasteSelection()	{	m_mObjects.PasteSelection(sm_mClipboard); PostUpdateGraph();};
	//!  a classical copy function
	void CopySelection()	{	sm_mClipboard=m_mObjects.CopySelection();};
	//!  a classical cut function
	void CutSelection()		{	sm_mClipboard=m_mObjects.CutSelection(); PostUpdateGraph();};

	//!  adds pObject to the graph (memory must be allowed by user)
	void AddObject(CPGLObject* pObject);

	//!  removes the selected object from the graph
	void DeleteSelection();

	//!  unselect all objects in the graph
	void UnselectAll();
	//!  unhide all objects in the graph
	void UnhideAll();
	//!  select all objects in the graph
	void SelectAll();

	//!  test if there's anything in clipboard, return TRUE if empty
	static inline BOOL IsClipBoardEmpty();
	//! TRUE if no object selected
	BOOL IsSelectionEmpty()
	{	return m_mObjects.IsSelectionEmpty();};
	//! TRUE if multiple objects (nb>1) selected
	BOOL IsMultipleSelection()
	{	return m_mObjects.IsMultipleSelection();};

	/*! \brief Gets the extents of the graph

	\retval {{left, right, bottom, top }

	Computes and returns the extents of all objects in the graph.
	\sa CPGLObject::GetExtent
	\sa ZoomAll
	\sa ZoomBox
	\sa ZoomRegion
	\sa ZoomIn
	\sa ZoomOut
	*/
	virtual double* GetExtent();

	//! returns a pointer to the object manager. Use with care.
	CPGLObjectManager* GetObjectManager()
	{	return &m_mObjects;};

	/*! \brief Sets viewport dimensions.

	\param tx lower left position (in pixels)
	\param ty upper left position (in pixels)
	\param width width of view (in pixels)
	\param height height of view (in pixels)
	\sa CPGLView::SetViewport
	\sa CPGLView2D::SetViewport
	*/
	void SetViewport(int tx, int ty, int width, int height);

	/*! Returns viewport dimensions

	\param vp a double[4]
	\retval vp tx,ty,width,height
	\sa SetViewport
	*/
	void GetViewport(int* vp)
	{	vp[0]=m_view.GetTx(); vp[1]=m_view.GetTy(); vp[2]=m_view.GetWidth(); vp[3]=m_view.GetHeight();};
	
	//!  sets the view object
	void SetView(const CPGLView2D& pView)
	{	m_view=pView;};
	//!  returns the view object
	CPGLView* GetView()
	{	return (CPGLView*)(&m_view);};

	/*! \brief Move view.
	
	Translate view of \a x pixels horizontaly and \a y verticaly. The view
	limits are updated and axe limits are modified accordingly.
	\sa CPGLView::Pan
	\sa CPGLView2D::Pan
	\sa CPGLAxe2D::Pan
	\sa ZoomAll
	\sa ZoomBox
	\sa ZoomRegion
	\sa ZoomIn
	\sa ZoomOut
	*/
	virtual void Pan(int x, int y);

	/*! \brief Zooms out.
	
	Extends the limits of the view. The axe limits are "processed" and
	the view limits are modified accordingly.
	\sa CPGLView::ZoomOut
	\sa CPGLView2D::ZoomOut
	\sa GrowExt
	\sa CPGLView2D::ZoomRegion
	\sa ZoomAll
	\sa ZoomBox
	\sa ZoomRegion
	\sa ZoomIn
	\sa Pan
	*/	
	virtual void ZoomOut();

	/*! \brief Zooms in.
	
	Extends the limits of the view. The axe limits are "processed" and
	the view limits are modified accordingly.
	\sa CPGLView::ZoomOut
	\sa CPGLView2D::ZoomOut
	\sa GrowExt
	\sa Pan
	\sa ZoomAll
	\sa ZoomBox
	\sa ZoomRegion
	\sa ZoomOut
	*/	
	virtual void ZoomIn();

	/*! \brief Show all objects.
	
	Extends the limits to show all objects. The axe limits are "processed" and
	the view limits are modified accordingly.
	\sa GrowExt
	\sa Pan
	\sa ZoomBox
	\sa ZoomRegion
	\sa ZoomIn
	\sa ZoomOut
	*/	
	virtual void ZoomAll(BOOL recurse = FALSE);

	/*! \brief Zooms a region in view units.
	
	  \param pExt {left, right, bottom , top}
	Extends the limits to region describe in \a pExt. 
	The axe limits are "processed" and
	the view limits are modified accordingly.
	\sa GrowExt
	\sa Pan
	\sa ZoomBox
	\sa ZoomAll
	\sa ZoomIn
	\sa ZoomOut
	*/	
	virtual void ZoomRegion(double* pExt);

	/*! \brief Zooms a region in viewport unit.
	
	Extends the limits to region describe by the box of opposite
	summit (\a xStart, \a yStart) - (\a xEnd \a yEnd). 
	The axe limits are "processed" and
	the view limits are modified accordingly.
	\sa GrowExt
	\sa Pan
	\sa ZoomBox
	\sa ZoomAll
	\sa ZoomIn
	\sa ZoomOut
	*/	
	virtual void ZoomBox(int xStart,int yStart,int xEnd,int yEnd);

	//! Set updating graph at next draw
	void PostUpdateGraph()
	{	m_bNeedUpdate=TRUE; PostUpdateExtent();};
	BOOL NeedUpdate()
	{	return m_bNeedUpdate;};
	//! Update graph.
	virtual void UpdateGraph();

	/*! \brief plots the graph to DC

	\param renderToSelect This boolean controls the selection process.

	If you want to select object, i.e. you want them to load thier ID in the selection
	buffer, you set this value to TRUE, otherwise FALSE.
	\sa PlotAndSelectOne
	\sa PlotAndSelectBox
	\sa PlotToEPS
	\sa CPGLObject::PlotToEPS
	*/

	/*! \brief plots the graph to an EPS file

	\param pFile a pointer to an opened CStioFile.

	\sa Plot
	\sa PlotAndSelectOne
	\sa PlotAndSelectBox
	*/
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	//!  finding an object by it's ID
	CPGLObject* FindObject(UINT ID);

	//!  sets the background color
	void SetBackground(const CPGLColor& c) {	m_background=c;};
	//!  gets the background color
	CPGLColor GetBackground() const { return m_background;};

	CPGLRegion* AddRegion();
	//!  Serialize functions
	void Serialize(CArchive& archive);

	//!  Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif
	//@}
protected:
	//!  object manager
	CPGLObjectManager m_mObjects;
	//!  child regions manager
	CPGLObjectManager m_mChilds;
	//!  an x-y axe
	CPGLAxe2D m_axe;
	//!  the view describing the graph (viewport + extent)
	CPGLView2D m_view;
	//!  background color
	CPGLColor m_background;
	/*! \brief Normalized viewport extent

	Array of size 4 containing : llx, lly, urx, ury where (llx,lly) are the coordinate of the lower
	left corner and (urx,ury) are the coordinates of the upper right corner in normalized coordinates [0,1]
	*/
	float m_pNormBBox[4];
	//! clipboard
	static CPGLObjectManager* sm_mClipboard;
	//@}
private:
	//!  TRUE if graph needs update
	BOOL m_bNeedUpdate;
};

#endif // !defined(AFX_PGLREGION_H__DAD08248_1E11_4C95_A77D_4968F1077BFD__INCLUDED_)


//!  test if there's anything in clipboard, return TRUE if empty
inline BOOL CPGLRegion::IsClipBoardEmpty() 
{
	if (sm_mClipboard==NULL)
		return TRUE;

	ASSERT_VALID(sm_mClipboard);
	return sm_mClipboard->IsEmpty(); 
};
