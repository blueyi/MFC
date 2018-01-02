// PGLLineVer.h: interface for the CPGLLineVer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLLINEVER_H__469C5D6F_CF3F_436F_BADE_BBA9620146D4__INCLUDED_)
#define AFX_PGLLINEVER_H__469C5D6F_CF3F_436F_BADE_BBA9620146D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLLine.h"

/*! \brief A vertical line.

\ingroup PGLLineGroup
*/
class PGL_EXT_CLASS CPGLLineVer : public CPGLLine 
{
public:
    DECLARE_SERIAL(CPGLLineVer);

	//! Default construtor
	CPGLLineVer();
	//! copy constructor
	CPGLLineVer(const CPGLLineVer& lv);
	//! assignement constructor
	CPGLLineVer& operator = (const CPGLLineVer& lv);
    //! returns a pointer to a copy of the object
    virtual CPGLObject* MakeCopy()
    {   CPGLObject* pCopy=new CPGLLineVer(*this); return pCopy; };
	//! Default destructor
	virtual ~CPGLLineVer();
	
	//! Sets horizontal position
	void SetX(double X) {	m_dX = X;};
	//! Returns horizontal position
	double GetX() const {	return m_dX;};
	//! Sets caption
	void SetCaption( const CPGLText& caption)	{ m_tCaption = caption;};
	void SetCaption( const CString& caption)	{ m_tCaption.SetString(caption);};
	const CPGLText& GetCaption() const	{	return m_tCaption;};
	const CString& GetCaptionString() const	{	return m_tCaption.GetString();};

    /** returns the extent of the datas
    The array extent is filled like this :
    \begin{itemize}
        \item extent[0] : min(x)
        \item extent[1] : __max(x)
        \item extent[2] : min(y)
        \item extent[3] : __max(y)
    \end{itemize}
    */
    virtual double* GetExtent(CPGLView* pView);
    ///virtual function to override in derived classes
    virtual void UpdateExtent(CPGLView* pView);


	void PlotGfx(gfxinterface::CGfxInterface& gfx);

    //! Serialize functions
    void Serialize(CArchive& archive);

    //! Debuggin functions
    #ifdef _DEBUG
        virtual void Dump( CDumpContext& dc ) const;
        virtual void AssertValid() const;    // Override
    #endif
    //@}

protected:

protected:
	/*! \name Attributes
	*/
	//@{
	//! vertical position
	double m_dX;
	//! Caption
	CPGLText m_tCaption;
	//@}
};

#endif // !defined(AFX_PGLLINEVER_H__469C5D6F_CF3F_436F_BADE_BBA9620146D4__INCLUDED_)
