// viewGL2D.h: interface for the CViewGL2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW2DCLASS1_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_VIEW2DCLASS1_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "viewGL.h"

/**A 2D view
This type of view is used for 2D graphs or drawings. It is 
written for maximum performance.
*/
class CViewGL2D : public CViewGL  
{
DECLARE_SERIAL(CViewGL2D);

public:
	void DrawGrids(CWGL* pWGL);

	CViewGL2D(GLdouble _left=0.0,GLdouble _right=1.0,GLdouble _top=1.0,GLdouble _bottom=0.0);
	CViewGL2D& operator = (const CViewGL2D& v2D);
	CViewGL2D(const CViewGL2D& v2D);
	virtual ~CViewGL2D()
	{};

	/// rebuilding reshape matrices...
	void Reshape();

	void GetLimits(GLdouble dLimits[])
	{	dLimits[0]=m_dLeft; dLimits[1]=m_dRight; dLimits[2]=m_dBottom; dLimits[3]=m_dTop;};
	void SetLimits(GLdouble dLimits[])
	{	m_dLeft=dLimits[0]; m_dRight=dLimits[1]; m_dBottom=dLimits[2]; m_dTop=dLimits[3];};
	/// initialize the grid list (lists are used in openGL for performance matters)
	void InitGLState();

	/// Debugging stuff
#ifdef _DEBUG
    virtual void AssertValid() const;    // Override
    virtual void Dump( CDumpContext& dc ) const;
#endif
    /// Serialization
    void Serialize( CArchive& archive );

protected:
	/// left limit of the viewport
	GLdouble m_dLeft;
	/// right limit of the viewport
	GLdouble m_dRight;
	/// top limit of the viewport
	GLdouble m_dTop;
	/// bottom limit of the viewport
	GLdouble m_dBottom;
};

#endif // !defined(AFX_VIEW2DCLASS1_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_)
