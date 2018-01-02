// DPHullGL.h: interface for the CDPHullGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPHULLGL_H__CC98539B_1112_42CF_9E10_C31D46DA9771__INCLUDED_)
#define AFX_DPHULLGL_H__CC98539B_1112_42CF_9E10_C31D46DA9771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KeyFramer.h"
#include "DPHull.h"

using namespace hull;

class CDPHullGL
{
public:
	typedef std::vector< hull::TPoint< float > > PointContainer;
	typedef std::list< PointContainer::const_iterator > KeyContainer;
	typedef hull::TDPHull<float, PointContainer, KeyContainer> Hull;

	CDPHullGL();
	virtual ~CDPHullGL();
	
	void SetTol( double dTol);
	double GetTol() const				{	return m_dpHull.GetTol();};
	UINT GetPointSize() const			{	return m_dpHull.GetPointSize();};
	UINT GetKeySize() const				{	return m_dpHull.GetKeySize();};
	Hull& GetHull() {	return m_dpHull;};


	void SetPoint( UINT i, double x, double y);
	void ResizePoints(UINT nPoints);

	void ComputeBoundingBox();
	void Simplify();
	UINT ShrinkNorm(double dScale, double dScaleTol=0.05, double eTolRight=0.1,UINT nMaxIter=100);

	void PlotPoints();
	void PlotKeys(CWGL& wgl);



	Hull m_dpHull;
	static void PlotKeyMethod( const TLineApproximator<float,PointContainer, KeyContainer>& la);

	UINT m_iterHull;


	bool m_bHull;

};

#endif // !defined(AFX_DPHULLGL_H__CC98539B_1112_42CF_9E10_C31D46DA9771__INCLUDED_)
