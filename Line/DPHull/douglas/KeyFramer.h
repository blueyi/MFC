// KeyFramer.h: interface for the CKeyFramer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYFRAMER_H__9586909E_03FD_496D_A4A0_6C4EF82C5078__INCLUDED_)
#define AFX_KEYFRAMER_H__9586909E_03FD_496D_A4A0_6C4EF82C5078__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LineApproximator.h"

namespace hull
{

/*
template<class T, class TPointContainer, class TKeyExporter>
class TKeyFramer : public TLineApproximator<T,TPointContainer>
{
protected:
	void ComputeKeys()
	{
		TLineApproximator<T,TPointContainer>::ComputeKeys();

		KeyContainer& kc = GetKeys();
		PointContainer& pc=GetPoints();
		ASSERT(pc.size()>=2);
		PointContainer::iterator itp1,it,itm1;
			
		it=itm1=itp1=pc.begin();
		kc.push_back(pc.begin());

		it++;
		itp1++; itp1++;
		for (; itp1 != pc.end() ; itm1++,it++,itp1++)
		{
			ASSERT(it!=pc.end());
			ASSERT(itm1!=pc.end());

			if ( !CanBeRemoved(*itp1,*it,*itm1) ) 
				kc.push_back(it);
		}

		// adding last point if needed ...
		kc.push_back(it);
	}

	virtual bool CanBeRemoved( const SPoint& pp1, const SPoint& p, const SPoint& pm1) const = 0;
};

template<class T, class TPointContainer, class TKeyExporter>
class TGlobalMoveKeyFramer : public TKeyFramer<T,TPointContainer,TKeyExporter>
{
protected:
	virtual bool CanBeRemoved(const SPoint& pp1, const SPoint& p, const SPoint& pm1) const
	{
		T dx=fabs(p.x-pm1.x);
		T dy=fabs(p.y-pm1.y);
		return __max ( dx,dy  ) < GetTol();
	}

};

template<class T, class TPointContainer, class TKeyExporter>
class TDisplacementKeyFramer : public TKeyFramer<T,TPointContainer,TKeyExporter>
{
protected:
	virtual bool CanBeRemoved(const SPoint& pp1, const SPoint& p, const SPoint& pm1) const
	{
		T Ux=(p.x-pm1.x);
		T Uy=(p.y-pm1.y);
		T Vx=(pp1.x-p.x);
		T Vy=(pp1.y-p.y);
	
		return fabs( (Ux*Vy-Vx*Uy)/(Ux*Vx+Uy*Vy) ) < pow(GetTol(),2);
	}
};

template<class T, class TKeyExporter>
class TVectorialKeyFramer : public TKeyFramer<T,TKeyExporter>
{
protected:
	virtual bool CanBeRemoved(const SPoint& pp1, const SPoint& p, const SPoint& pm1) const
	{
		T Ux=(p.x-pm1.x);
		T Uy=(p.y-pm1.y);
		T Vx=(pp1.x-p.x);
		T Vy=(pp1.y-p.y);

		T Ex=Ux-Vx;
		T Ey=Uy-Vy;

		return Ex*Ex+Ey*Ey < pow(GetTol(),2);
	}
};
*/

};
#endif // !defined(AFX_KEYFRAMER_H__9586909E_03FD_496D_A4A0_6C4EF82C5078__INCLUDED_)
