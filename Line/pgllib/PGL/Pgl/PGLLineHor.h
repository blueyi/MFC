// PGLLineHor.h: interface for the CPGLLineHor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLLINEHOR_H__C503FBE7_5D5B_49D1_9A81_8E1B24EEFB12__INCLUDED_)
#define AFX_PGLLINEHOR_H__C503FBE7_5D5B_49D1_9A81_8E1B24EEFB12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLLine.h"

class PGL_EXT_CLASS CPGLLineHor : public CPGLLine  
{
public:
    DECLARE_SERIAL(CPGLLineHor);

	//! Default construtor
	CPGLLineHor();
	//! copy constructor
	CPGLLineHor(const CPGLLineHor& lv);
	//! assignement constructor
	CPGLLineHor& operator = (const CPGLLineHor& lv);
    //! returns a pointer to a copy of the object
    virtual CPGLObject* MakeCopy()
    {   CPGLObject* pCopy=new CPGLLineHor(*this); return pCopy; };
	//! Default destructor
	virtual ~CPGLLineHor();
	
	//! Sets horizontal position
	void SetY(double Y) {	m_dY = Y;};
	//! Returns horizontal position
	double GetY() const {	return m_dY;};
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
	double m_dY;
	//! Caption
	CPGLText m_tCaption;
	//@}
};

#endif // !defined(AFX_PGLLINEHOR_H__C503FBE7_5D5B_49D1_9A81_8E1B24EEFB12__INCLUDED_)
