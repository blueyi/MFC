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
// ObjectGL.h: interface for the CPGLObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTGL_H__4DACBB82_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_OBJECTGL_H__4DACBB82_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#include "PGLColor.h"   // Added by ClassView
#include "PGLView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "PGLView.h"

/*!
	\defgroup PGLObjectGroup Graphical Objects
\ingroup PGLGroup
*/

/*! \brief A base class to create graphic objects.

\ingroup PGLObjectGroup
This is the base class for all graphical objects. It controls common carateristics
of all graphical objects such as
<ul>
    <li> selection state (selected - not selected)
    <li> visibility state (visible - hidden)
    <li> an identification number (for selection purpose)
    <li> a name
    <li> a color
</ul>
*/
class PGL_EXT_CLASS CPGLObject : public CObject
{
public:
    DECLARE_SERIAL(CPGLObject);

    /*! \name Members:*/
    //@{
    //! default constructor
    CPGLObject(const CPGLColor& _color=CPGLColor());
    //!  copy constructor
    CPGLObject(const CPGLObject& o);
    //! assignement constructor
    CPGLObject& operator = (const CPGLObject& o);
    //! returns a pointer to a copy of the object
    virtual CPGLObject* MakeCopy()
    {   CPGLObject* pCopy=new CPGLObject(*this); return pCopy; };

    //! destructor
    virtual ~CPGLObject(){ delete[] m_extent; };

    //! virtual function to override in derived classes
    virtual void UpdateExtent(CPGLView* pView)     { ASSERT_VALID(pView); m_bNeedUpdateExtent=FALSE;}
    //! tells object to update it limits next time getextent is called
    void PostUpdateExtent()         {   m_bNeedUpdateExtent=TRUE;};
    //! returns true if object needs to update it limits
    BOOL NeedUpdateExtent()         {   return m_bNeedUpdateExtent;};
    //! returns extents of objects...
    virtual double* GetExtent(CPGLView* pView)
    { return m_extent;};

    //! adds context menu items...
    virtual void AddContextMenuItems(CMenu* pMenu){};
    //! adds the object property page to the property dialog
    virtual void AddPropertyPage(CPropertySheet* pPropSheet);
    //! adds the object in the tree
	virtual HTREEITEM AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent);
    //! createa Property sheet dialog, adds all parent property page and DoModal...
    virtual void ShowModalPropertySheet(){};

    //! virtual function to override in derived classes

    //! writing EPS file
    virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

    //! returns TRUE if \_ID is the identification number of the object, FALSE otherwize
    BOOL CheckID(UINT _ID)
    { return (m_uID==_ID);};
    //! returns the identification number of the object
    UINT GetID() const
    { return m_uID;};

    //! set the object as selected
    void Select() {m_bSelected=TRUE;};
    //! set the object as not selected
    void Deselect() { m_bSelected=FALSE;};
    //! returns TRUE if the object is selected, FALSE otherwise
    BOOL IsSelected() { return m_bSelected;};
    //! switch selection state (ex: selected $\rightarrow$ not selected)
    void SwitchSelectionState() { m_bSelected=!m_bSelected;};

    //! set the object as visible
    void Show(BOOL show = TRUE) { m_bVisible=show;};
    //! set the object as hidden
    void Hide() { m_bVisible=FALSE;};
    //! returns TRUE if the object is visible, FALSE otherwise
    BOOL IsVisible() const { return m_bVisible;};
    //! switch visibility state (ex: visible $\rightarrow$ hidden)
    void SwitchVisibilityState() { m_bVisible=!m_bVisible;};

    //! sets the name of the object
    void SetName(const CString& _name) { m_sName=_name;};
    //! returns the name
    CString GetName() { return m_sName;};

    //! sets red component of object's color (must be in [0,1])
    void SetRed(float red) { m_color.SetRed(red);}; 
    //! sets green component of object's color (must be in [0,1])
    void SetGreen(float green) { m_color.SetGreen(green);}; 
    //! sets blue component of object's color (must be in [0,1])
    void SetBlue(float blue) { m_color.SetBlue(blue);}; 
    //! sets alpha component of object's color (must be in [0,1])
    void SetAlpha(float alpha) { m_color.SetAlpha(alpha);}; 
    //! sets the object's color
    void SetColor(const CPGLColor& _color) { m_color=_color;};
    //! sets the object's color
    void SetColor(float red=1.0,float green=1.0,float blue=1.0,float alpha=1.0)
    { m_color=CPGLColor(red,green,blue,alpha);};
    //! returns the object color
    const CPGLColor& GetColor() const { return m_color;};

    //! sets the selection color (this is a static property)
    static void SetSelectionColor(const CPGLColor& _selectionColor) { m_selectionColor=_selectionColor;};
    //! gets the selection color
    static CPGLColor GetSelectionColor() { return m_selectionColor;};

	//! returns the bitmap.
	virtual CBitmap* GetBitmap()
	{	return &m_bmp;};
    //! Serialization
    void Serialize( CArchive& archive );

    //! Debuggin functions
#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;    // Override
#endif
    //@}
protected:
    //! extent of the object left, right, bottom, top
    double* m_extent;
	//! a small bitmap describing the object...
	CBitmap m_bmp;
private:
    /*! \name Class Private Parameters*/
    //@{
    //! visibility state
    BOOL m_bVisible;
    //! selection state
    BOOL m_bSelected;
    //! identification number
    UINT m_uID;
    //! object's name
    CString m_sName;
    //! object's color
    CPGLColor m_color;
    //! object needs to update it's limits
    BOOL m_bNeedUpdateExtent;
    //! next identification number to assign
    static UINT m_uNextID;
    //! the selection color
    static CPGLColor m_selectionColor;
    //@}
};

#endif // !defined(AFX_OBJECTGL_H__4DACBB82_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
