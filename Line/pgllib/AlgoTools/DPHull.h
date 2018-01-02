
#if !defined(AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_)
#define AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef UINT
	#define UINT unsigned int
#endif

#include <vector>
#include "PathHull.h"

namespace hull
{

/*! \brief Douglas-Peukler Appromixation algorithm

*/
template <class T>
class TDPHull : public TLineApproximator<T>
{
public:
	//! \name Constructors
	//@{
	//! Default constructor
	TDPHull<T>(): m_pPHtag(NULL){};
	//! Destructor
	virtual ~TDPHull<T>(){};
	//@}

protected:
	virtual void ComputeKeys()
	{
		TLineApproximator<T>::ComputeKeys();
		PointContainer& pc=GetPoints();

		// prepraring path if needed...
		m_phLeft.SetMaxSize(pc.size()+1);
		m_phRight.SetMaxSize(pc.size()+1);

		// building hull
		Build(pc.begin(), pc.end());	/* Build the initial path hull */	
		OutputVertex(pc.begin());
		OutputVertex( DP(pc.begin(), pc.end()) ); /* Simplify */

		if (GetKeySize() > 2)
			GetKeys().pop_back();
	}

	//! \name Hull methods
	//@{
	PointContainer::iterator DP(PointContainer::iterator it, PointContainer::iterator jt);
	void Build(PointContainer::iterator it, PointContainer::iterator jt);
	void OutputVertex(PointContainer::const_iterator it) {	GetKeys().push_back(it);};
	//@}

protected:
	//! \name Attributes
	//@{
	TPathHull<T> m_phRight;
	TPathHull<T> m_phLeft;
	SPoint* m_pPHtag;
	//@}
};

template <class T>
void TDPHull<T>::Build(PointContainer::iterator it, PointContainer::iterator jt)
{
	SPoint* i=&(*it);
	SPoint* j=&(*jt);
	SPoint *k;
	int topflag, botflag;
	
	m_pPHtag = i + (j - i) / 2;	/* Assign tag vertex */
	
	
	m_phLeft.Init(m_pPHtag, m_pPHtag - 1); /* \va{left} hull */
	for (k = m_pPHtag - 2; k >= i; k--)
    {
		topflag = m_phLeft.LeftOfTop(k);
		botflag = m_phLeft.LeftOfBot(k);
		if ((topflag || botflag) && !(topflag && botflag))
		{
			while (topflag)
			{
				m_phLeft.PopTop();
				topflag = m_phLeft.LeftOfTop(k);
			}
			while (botflag)
			{
				m_phLeft.PopBot();
				botflag = m_phLeft.LeftOfBot(k);
			}
			m_phLeft.Push(k);
		}
    }

	m_phRight.Init(m_pPHtag, m_pPHtag + 1); /* \va{right} hull */
	for (k = m_pPHtag + 2; k <= j; k++)
    {
		topflag = m_phRight.LeftOfTop(k);
		botflag = m_phRight.LeftOfBot(k);
		if ((topflag || botflag) && !(topflag && botflag))
		{
			while (topflag)
			{
				m_phRight.PopTop();
				topflag = m_phRight.LeftOfTop(k);
			}
			while (botflag)
			{
				m_phRight.PopBot();
				botflag = m_phRight.LeftOfBot(k);
			}
			m_phRight.Push(k);
		}
    }
}

template <class T>
TLineApproximator<T>::PointContainer::iterator TDPHull<T>::DP(PointContainer::iterator it, PointContainer::iterator jt)
{
	static double ld, rd, len_sq;
	static SHomog l;
	register SPoint *le;
	register SPoint *re;

	SPoint* i=&(*it);
	SPoint* j=&(*jt);	

	SPoint::CrossProduct(*i, *j, l);
	len_sq = l.x * l.x + l.y * l.y;
	
	if (j - i < 8)
    {		/* chain small */
		rd  = 0.0;
		for (le = i + 1; le < j; le++)
		{
			ld = SPoint::DotProduct(*le, l);
			if (ld < 0) ld = - ld;
			if (ld > rd) 
			{
				rd = ld;
				re = le;
			}
		}
		if (rd * rd > GetTol() * len_sq)
		{
			OutputVertex(DP(i, re)); 
			return(DP(re, j));
		}
		else
			return(j);
    }
	else
    {				/* chain large */
		int sbase, sbrk, mid, lo, m1, brk, m2, hi;
		double d1, d2;
		if ((m_phLeft.GetTop() - m_phLeft.GetBot()) > 8) 
		{
			/* left hull large */
			lo = m_phLeft.GetBot(); 
			hi = m_phLeft.GetTop() - 1;
			sbase = m_phLeft.SlopeSign(hi, lo, l);
			do
			{
				brk = (lo + hi) / 2;
				if (sbase == (sbrk = m_phLeft.SlopeSign(brk, brk+1, l)))
					if (sbase == (m_phLeft.SlopeSign(lo, brk+1, l)))
						lo = brk + 1;
					else
						hi = brk;
			}
			while (sbase == sbrk && lo < hi);
			
			m1 = brk;
			while (lo < m1)
			{
				mid = (lo + m1) / 2;
				if (sbase == (m_phLeft.SlopeSign(mid, mid+1, l)))
					lo = mid + 1;
				else
					m1 = mid;
			}
			
			m2 = brk;
			while (m2 < hi) 
			{
				mid = (m2 + hi) / 2;
				if (sbase == (m_phLeft.SlopeSign(mid, mid+1, l)))
					hi = mid;
				else
					m2 = mid + 1;
			};
			
			
			if ((d1 = SPoint::DotProduct(*m_phLeft.GetpElt(lo), l)) < 0) d1 = - d1;
			if ((d2 = SPoint::DotProduct(*m_phLeft.GetpElt(m2), l)) < 0) d2 = - d2;
			ld = (d1 > d2 ? (le = m_phLeft.GetpElt(lo), d1) : (le = m_phLeft.GetpElt(m2), d2));
		}
		else
		{			/* Few SPoints in left hull */
			ld = 0.0;
			for (mid = m_phLeft.GetBot(); mid < m_phLeft.GetTop(); mid++)
			{
				if ((d1 = SPoint::DotProduct(*m_phLeft.GetpElt(mid), l)) < 0) d1 = - d1;
				if (d1 > ld)
				{
					ld = d1;
					le = m_phLeft.GetpElt(mid);
				}
			}
		}
		
		if ((m_phRight.GetTop() - m_phRight.GetBot()) > 8)
		{			/* right hull large */
			lo = m_phRight.GetBot(); hi = m_phRight.GetTop() - 1;
			sbase = m_phRight.SlopeSign(hi, lo, l);
			do
			{
				brk = (lo + hi) / 2;
				if (sbase == (sbrk = m_phRight.SlopeSign(brk, brk+1, l)))
					if (sbase == (m_phRight.SlopeSign(lo, brk+1, l)))
						lo = brk + 1;
					else
						hi = brk;
			}
			while (sbase == sbrk && lo < hi);
			
			m1 = brk;
			while (lo < m1)
			{
				mid = (lo + m1) / 2;
				if (sbase == (m_phRight.SlopeSign(mid, mid+1, l)))
					lo = mid + 1;
				else
					m1 = mid;
			}
			
			m2 = brk;
			while (m2 < hi) 
			{
				mid = (m2 + hi) / 2;
				if (sbase == (m_phRight.SlopeSign(mid, mid+1, l)))
					hi = mid;
				else
					m2 = mid + 1;
			};
					
			if ((d1 = SPoint::DotProduct(*m_phRight.GetpElt(lo), l)) < 0) d1 = - d1;
			if ((d2 = SPoint::DotProduct(*m_phRight.GetpElt(m2), l)) < 0) d2 = - d2;
			rd = (d1 > d2 ? (re = m_phRight.GetpElt(lo), d1) : (re = m_phRight.GetpElt(m2), d2));
		}
		else
		{			/* Few SPoints in righthull */
			rd = 0.0;
			for (mid = m_phRight.GetBot(); mid < m_phRight.GetTop(); mid++)
			{
				if ((d1 = SPoint::DotProduct(*m_phRight.GetpElt(mid), l)) < 0) d1 = - d1;
				if (d1 > rd)
				{
					rd = d1;
					re = m_phRight.GetpElt(mid);
				}
			}
		}
    }
	
	
	if (ld > rd)
		if (ld * ld > GetTol() * len_sq)
		{				/* split left */
			register int tmpo; 
			
			while ((m_phLeft.GetHp() >= 0) 
				&& ( (tmpo = m_phLeft.GetpOp()[m_phLeft.GetHp()] ), 
				((re = m_phLeft.GetpHelt(m_phLeft.GetHp())) != le) || (tmpo != TPathHull<T>::StackPushOp)))
			{
				m_phLeft.DownHp();
				switch (tmpo)
				{
				case TPathHull<T>::StackPushOp:
					m_phLeft.DownTop();
					m_phLeft.UpBot();
					break;
				case TPathHull<T>::StackTopOp:
					m_phLeft.UpTop();
					m_phLeft.SetTopElt(re);
					break;
				case TPathHull<T>::StackBotOp:
					m_phLeft.DownBot();
					m_phLeft.SetBotElt(re);
					break;
				}
			}
			
			Build(i, le);
			OutputVertex(DP(i, le));
			Build(le, j);
			return DP(le, j);
		}
		else
			return(j);
		else				/* extreme on right */
			if (rd * rd > GetTol() * len_sq)
			{				/* split right or both */
				if (m_pPHtag == re)
					Build(i, re);
				else
				{			/* split right */
					register int tmpo;
					
					while ((m_phRight.GetHp() >= 0) 
						&& ((tmpo = m_phRight.GetpOp()[m_phRight.GetHp()]), 
						((le = m_phRight.GetpHelt(m_phRight.GetHp())) != re) || (tmpo != TPathHull<T>::StackPushOp)))
					{
						m_phRight.DownHp();
						switch (tmpo)
						{
						case TPathHull<T>::StackPushOp:
							m_phRight.DownTop();
							m_phRight.UpBot();
							break;
						case TPathHull<T>::StackTopOp:
							m_phRight.UpTop();
							m_phRight.SetTopElt(le);
							break;
						case TPathHull<T>::StackBotOp:
							m_phRight.DownBot();
							m_phRight.SetBotElt(le);
							break;
						}
					}
				}
				OutputVertex(DP(i, re));
				Build(re, j);
				return(DP(re, j));
			}
			else
				return(j);	
}


};

#endif // !defined(AFX_DPHULL1_H__6CE88E63_3AC7_4E18_87FB_CACF5BE62BE4__INCLUDED_)
