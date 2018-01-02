// PathHull.h: interface for the CPathHull class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_)
#define AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LineApproximator.h"

namespace hull
{


#define DP_SGN(a) (a >= 0)

/*! \brief A path
	\ingroup 
*/
template<class T>
class TPathHull  
{
public:
	static enum EStackOp
	{
		StackPushOp=0,
		StackTopOp=1,
		StackBotOp=2
	};

	TPathHull(): m_iHullMax(0), m_pOp(NULL), m_ppElt(NULL),m_ppHelt(NULL)
	{};
	virtual ~TPathHull()
	{
		if (m_pOp)
			delete[] m_pOp;
		if (m_ppElt)
			delete[] m_ppElt;
		if (m_ppHelt)
			delete[] m_ppHelt;
	};

	void SetMaxSize(int iHullMax);

	int GetHp() const								{	return m_iHp;};
	int GetBot() const								{	return m_iBot;};
	int GetTop() const								{	return m_iTop;};
	TLineApproximator<T>::SPoint* GetpElt(int i)	{	return m_ppElt[i];};
	TLineApproximator<T>::SPoint* GetpHelt(int i)	{	return m_ppHelt[i];};
	int* GetpOp()									{	return m_pOp;};

	void SetHp(int hp)								{	m_iHp=hp;};

	void UpHp()		{	m_iHp++;};
	void UpTop()	{	m_iTop++;};
	void UpBot()	{	m_iBot++;};
	void DownHp()	{	m_iHp--;};
	void DownTop()	{	m_iTop--;};
	void DownBot()	{	m_iBot--;};

	void SetTopElt(TLineApproximator<T>::SPoint* p)		{	m_ppElt[m_iTop]=p;};
	void SetBotElt(TLineApproximator<T>::SPoint* p)		{	m_ppElt[m_iBot]=p;};

	void Split(TLineApproximator<T>::SPoint* e)
	{
		TLineApproximator<T>::SPoint *tmpe;
		int tmpo;
		
		while ((m_iHp >= 0) 
			&& ((tmpo = m_pOp[m_iHp]), 
			((tmpe = m_ppHelt[m_iHp]) != e) || (tmpo != StackPushOp)))
		{
			m_iHp--;
			switch (tmpo)
			{
			case StackPushOp:
				m_iTop--;
				m_iBot++;
				break;
			case StackTopOp:
				m_ppElt[++m_iTop] = tmpe;
				break;
			case StackBotOp:
				m_ppElt[--m_iBot] = tmpe;
				break;
			}
		}
	}

	void FindExtreme(const TLineApproximator<T>::SHomog& line, TLineApproximator<T>::SPoint ** e, double& dist);

	void Init(TLineApproximator<T>::SPoint* e1, TLineApproximator<T>::SPoint* e2)
	{
		/* Initialize path hull and history  */
		m_ppElt[m_iHullMax] = e1;
		m_ppElt[m_iTop = m_iHullMax + 1] = 
			m_ppElt[m_iBot = m_iHullMax - 1] = 
			m_ppHelt[m_iHp = 0] = e2;
		m_pOp[0] = StackPushOp;
	}

	void Push(TLineApproximator<T>::SPoint* e)
	{
		/* Push element $e$ onto path hull $h$ */
		m_ppElt[++m_iTop] = m_ppElt[--m_iBot] = m_ppHelt[++m_iHp] = e;
		m_pOp[m_iHp] = StackPushOp;
	}

	void PopTop()
	{	/* Pop from top */
		m_ppHelt[++m_iHp] = m_ppElt[m_iTop--];
		m_pOp[m_iHp] = StackTopOp;
	}

	void PopBot()
	{
		/* Pop from bottom */
		m_ppHelt[++m_iHp] = m_ppElt[m_iBot++];
		m_pOp[m_iHp] = StackBotOp;
	}
	
	void Add(TLineApproximator<T>::SPoint* p)
	{
		int topflag, botflag;
		
		topflag = LeftOfTop(p);
		botflag = LeftOfBot(p);
		
		if (topflag || botflag)
		{
			while (topflag)
			{
				PopTop();
				topflag = LeftOfTop(p);
			}
			while (botflag)
			{
				PopBot();
				botflag = LeftOfBot(p);
			}
			Push(p);
		}
	}

	int LeftOfTop(TLineApproximator<T>::SPoint* c)
	{
		/* Determine if point c is left of line a to b */
		return (((*m_ppElt[m_iTop]).x - c->x)*((*m_ppElt[m_iTop-1]).y - c->y) 
			>= ((*m_ppElt[m_iTop-1]).x - c->x)*((*m_ppElt[m_iTop]).y - c->y));
	}

	int LeftOfBot(TLineApproximator<T>::SPoint* c)
	{
		/* Determine if point c is left of line a to b */
		return (((*m_ppElt[m_iBot+1]).x - c->x)*((*m_ppElt[m_iBot]).y - c->y) 
			>= ((*m_ppElt[m_iBot]).x - c->x)*((*m_ppElt[m_iBot+1]).y - c->y));
	}


	int SlopeSign(int p, int q, const TLineApproximator<T>::SHomog& l)
	{
		/* Return the sign of the projection 
				   of $h[q] - h[p]$ onto the normal 
				   to line $l$ */ 
		return (int) (DP_SGN( 
			(l.x)*((*m_ppElt[q]).x - (*m_ppElt[p]).x) 
			+ (l.y)*((*m_ppElt[q]).y - (*m_ppElt[p]).y) ) ) ;
	};

protected:
	/// Maxium number of elements in hull
	int m_iHullMax;
	
	/// internal values
	int m_iTop;
	int m_iBot; 
	int m_iHp;
	int *m_pOp;	
	TLineApproximator<T>::SPoint**m_ppElt; 
	TLineApproximator<T>::SPoint**m_ppHelt;
};

template<class T>
void TPathHull<T>::FindExtreme(const TLineApproximator<T>::SHomog& line, TLineApproximator<T>::SPoint **e, double& dist)
{
	int 
		sbase, sbrk, mid,
		lo, m1, brk, m2, hi;
	double d1, d2;
	
	if ((m_iTop - m_iBot) > 8) 
    {
		lo = m_iBot; hi = m_iTop - 1;
		sbase = SlopeSign(hi, lo, line);
		do
		{
			brk = (lo + hi) / 2;
			if (sbase == (sbrk = SlopeSign(brk, brk+1, line)))
				if (sbase == (SlopeSign(lo, brk+1, line)))
					lo = brk + 1;
				else
					hi = brk;
		}
		while (sbase == sbrk);
		
		m1 = brk;
		while (lo < m1)
		{
			mid = (lo + m1) / 2;
			if (sbase == (SlopeSign(mid, mid+1, line)))
				lo = mid + 1;
			else
				m1 = mid;
		}
		
		m2 = brk;
		while (m2 < hi) 
		{
			mid = (m2 + hi) / 2;
			if (sbase == (SlopeSign(mid, mid+1, line)))
				hi = mid;
			else
				m2 = mid + 1;
		}
		
		if ((d1 = TLineApproximator<T>::SPoint::DotProduct(*m_ppElt[lo], line)) < 0) d1 = - d1;
		if ((d2 = TLineApproximator<T>::SPoint::DotProduct(*m_ppElt[m2], line)) < 0) d2 = - d2;
		dist = (d1 > d2 ? (*e = m_ppElt[lo], d1) : (*e = m_ppElt[m2], d2));
    }
	else				/* Few DP_POINTs in hull */
    {
		dist = 0.0;
		for (mid = m_iBot; mid < m_iTop; mid++)
		{
			
			if ((d1 = TLineApproximator<T>::SPoint::DotProduct(*m_ppElt[mid], line)) < 0) d1 = - d1;
			if (d1 > *dist)
			{
				dist = d1;
				*e = m_ppElt[mid];
			}
		}
    }
}

template <class T>
void TPathHull<T>::SetMaxSize(int iHullMax)
{
	if (m_iHullMax == iHullMax)
		return;

	m_iHullMax=iHullMax;
	
	// deleting vector if existing
	if (m_pOp)
		delete[] m_pOp;
	if (m_ppElt)
		delete[] m_ppElt;
	if (m_ppHelt)
		delete[] m_ppHelt;
	
	// allocating memory	
	m_pOp=new int[3*m_iHullMax];
	m_ppElt=new TLineApproximator<T>::SPoint*[2*m_iHullMax];
	m_ppHelt=new TLineApproximator<T>::SPoint*[3*m_iHullMax];	
}

};

#endif // !defined(AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_)
