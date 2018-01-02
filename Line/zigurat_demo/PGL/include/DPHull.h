// DPHull1.h: interface for the CDPHull class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_)
#define AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PathHull.h"

class CDPHull  
{
public:
	CDPHull();
	virtual ~CDPHull();

	/// sets the tolerance for DP algorithm
	void SetTol(double tol)
	{	m_dEpsilonSQ=(tol > 0 ? tol : 0);};

	/// sets the data to approximate
	void SetCurve(int iN,DP_POINT* pV);

	DP_POINT* GetCurve()
	{	return m_pV;};
	DP_POINT** GetDPCurve()
	{	return m_ppR;};

	/// Delete curve array
	void DeleteCurve()
	{	m_iN=0; if (m_pV) delete[] m_pV; m_pV=NULL;};

	/// returns tolerance for DP algorithm
	double GetTol() const
	{	return m_dEpsilonSQ;};

	/// returns number of points in original
	int GetNPoints() const
	{	return m_iN;};

	/// returns number of points in DP curve
	int GetDPNPoints() const
	{	return m_iNumResult;};

	/// DP algorithm
	void Simplify();
	
	/// rewritte solution on base vector
	void InjectDPInOriginal();

	/// allocate new memory for solution
	DP_POINT* GetNewDPCurve();

	/// prints results
	void PrintResult();

protected:
	DP_POINT* DP(DP_POINT* i, DP_POINT *j);
	void Build(DP_POINT* i, DP_POINT* j);
	void OutputVertex(DP_POINT* v) 
	{	m_ppR[m_iNumResult++] = v;};

protected:
	int m_iN;
	DP_POINT *m_pV;
	DP_POINT **m_ppR;
	int m_iNumResult;
	CPathHull m_phRight;
	CPathHull m_phLeft;
	DP_POINT* m_pPHtag;
	double m_dEpsilonSQ;
};

#endif // !defined(AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_)
