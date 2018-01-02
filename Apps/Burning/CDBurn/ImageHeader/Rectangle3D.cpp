// Rectangle3D.cpp : implemetation file
// 矩形面片类

#include "stdafx.h"
#include "Rectangle3D.h"
#include "TransMatrix3D.h"


// 求空间任意直线与任意平面的交点
CFPoint3D Intersect3D_Line_Plane()
{
	CFPoint3D ptIntersect;
	return ptIntersect;
}



// 求空间直线段与空间矩形面片之间的交点
BOOL Intersect3D_LineSeg_Rectangle(const CFPoint3D& ptStart, const CFPoint3D& ptEnd,
								   const CRectangle& Rectangle,
								   CFPoint3D& ptInstersect)
{
	BOOL bIntersect = FALSE;

	// 用参数式表达空间直线
	CFVector3D V = ptEnd - ptStart;
	// P(t) = ptStart + t * V -------------------------------(1)

	// 用点法式表示空间平面
	CFVector3D N = Rectangle.GetN();
	// N ⊙ (P - Rectangle.m_ptCenter) = 0 ------------------(2)

	// 将(1)代入(2),求出t
	// N ⊙ (t * V + D) = 0,  in which D is
	CFVector3D D = ptStart - Rectangle.GetCenter();
	// t* (N ⊙ V) = -N ⊙ D
	double fNV_DotMul = DotMul(N, V);
	if(! IsZero(fNV_DotMul))
	{
		double t = -DotMul(N, D) / fNV_DotMul;
		if(0.0 <= t && t <= 1.0)
		{
			bIntersect = TRUE;
			ptInstersect = ptStart + t * V;
		}
	}

	return bIntersect;
}

// 方程：
//    c[0][0] * x  +  c[0][1] * y  =  c[0][2]
//    c[1][0] * x  +  c[1][1] * y  =  c[1][2]
// 或者
//    a0 * x  +  b0 * y  =  c0
//    a1 * x  +  b1 * y  =  c1
//
// 解方程：
//    a1 * a0 * x  +  a1 * b0 * y  =  a1 * c0       -----------(1)
//    a0 * a1 * x  +  a0 * b1 * y  =  a0 * c1       -----------(2)
// (1) - (2)，得
//    (a1 * b0  -  a0 * b1) * y  =  a1 * c0  -  a0 * c1
//
// 存在解的条件是，判别行列式 
//    delta = a1 * b0  -  a0 * b1
// 不为零。
//    y = (a1 * c0  -  a0 * c1) / delta
//
// 同样，
//    b1 * a0 * x  +  b1 * b0 * y  =  b1 * c0       -----------(1)
//    b0 * a1 * x  +  b0 * b1 * y  =  b0 * c1       -----------(2)
// (2) - (1)，得
//    delta = a0 * b1  -  a1 * b0
//    x = (b0 * c1  -  b1 * c0) / delta
class CEquation2x2
{
public:
	CEquation2x2()
	{
		for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			c[i][j] = 0.0;
	}

public:
	void Set(const double a0_, const double b0_, const double c0_, 
			const double a1_, const double b1_, const double c1_)
	{
		a0 = a0_, b0 = b0_, c0 = c0_, a1 = a1_, b1 = b1_, c1 = c1_;
	}

	void Set(const double c_[2][3])
	{
		for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			c[i][j] = c_[i][j];
	}


public:
	BOOL GetRoot(double& x, double& y)
	{
		double delta = a1 * b0  -  a0 * b1;
		if(IsZero(delta))
			return FALSE;

		x = (b0 * c1  -  b1 * c0) / delta;
		y = (a1 * c0  -  a0 * c1) / delta;
		return TRUE;
	}

public:
	union
	{
		double c[2][3];
		struct
		{
			double a0, b0, c0, a1, b1, c1;
		};
	};

};

BOOL GetRoot(const double a0, const double b0, const double c0, 
			 const double a1, const double b1, const double c1, 
			 double& x, double& y)
{
	double delta = a1 * b0  -  a0 * b1;
	if(IsZero(delta))
		return FALSE;

	x = (b0 * c1  -  b1 * c0) / delta;
	y = (a1 * c0  -  a0 * c1) / delta;
	return TRUE;
}

#define IsBetween(_value, _minV, _maxV)		( (_minV <= _value) && (_value <= _maxV) )
#define IsBetween01(_value)					IsBetween(_value, 0.0, 1.0)

// 这两条线段: <P0-P1> 与 <Q0-Q1> 一定共面
BOOL LineSeg_LineSeg_Intersect(const CFPoint3D& P0, const CFPoint3D& P1,
							   const CFPoint3D& Q0, const CFPoint3D& Q1,
							   CFPoint3D& ptIntersect)
{
	CFPoint3D V0 = P1 - P0;
	CFPoint3D V1 = Q1 - Q0;

	// 先判断这两条直线段是否平行，如果平行，肯定没有交点
	if(V0.ForkMulWith(V1).IsZeroVector()) // ----------------------------- (0)
	{
		return FALSE;
	}

	// 参数形式表示这两条直线(段)
	// P(s) = P0 + s * V0,  0 <= s <= 1  -------------------------- (1)
	// Q(t) = Q0 + t * V1,  0 <= t <= 1  -------------------------- (2)
	// 令 P(s) = Q(t), 得
	// P0 + s * V0  =  Q0 + t * V1，即
	// s * V0  - t * V1  =  Q0-P0，即
	// s * V0  - t * V1  =  D0，其中 -------------------------------(3)
	CFPoint3D D0 = Q0 - P0;
	// 这是一个二元一次冗余方程组（由3个方程解2个未知数s,t）
	//     V0.x * s - V1.x * t = D0.x
	//     V0.y * s - V1.y * t = D0.y
	//     V0.z * s - V1.z * t = D0.z  -----------------------------(4)
	//
	// 我们只需取其中两个即可，如(x,y)，除非 <P0-P1> 与 <Q0-Q1> 在x-y面的投影是平行/重合的，
	// 这时，我们取x-z或者y-z即可。


	// 选择合适的方程组进行解方程，得到参数s和/或t，从而求出交点
	CEquation2x2  Equation;
	if(! IsEqual(V0.m_fx * V1.m_fy, V0.m_fy * V1.m_fx)) // 判断这两线段在x-y投影是否平行/重合
	{
		// 不平行/重合，用(x,y)方程组计算
		Equation.Set(V0.m_fx, -V1.m_fx, D0.m_fx,   V0.m_fy, -V1.m_fy, D0.m_fy);
	}
	else if(! IsEqual(V0.m_fx * V1.m_fz, V0.m_fz * V1.m_fx)) // 试取(x,z)，看它们在x-z平面的投影是否平行/重合
	{
		Equation.Set(V0.m_fx, -V1.m_fx, D0.m_fx,   V0.m_fz, -V1.m_fz, D0.m_fz);
	}
	else if(! IsEqual(V0.m_fy * V1.m_fz, V0.m_fz * V1.m_fy)) // 此时，它们在y-z平面的投影必定相交，取(y,z)
	{
		Equation.Set(V0.m_fy, -V1.m_fy, D0.m_fy,   V0.m_fz, -V1.m_fz, D0.m_fz);
	}
	else
	{
		// 此种情况下，两条直线段必定平行，这已经被 ---(0) 排除
		ASSERT(0);
		return FALSE;
	}

	double s = 0.0, t = 0.0;
	Equation.GetRoot(s, t);

	if(IsBetween01(s) && IsBetween01(t))
	{
		CFPoint3D P = P0 + s * V0;
		CFPoint3D Q = Q0 + t * V1;

		#ifdef _RODGER_DBG
		ASSERT(P == Q);
		#endif

		ptIntersect = P;

		return TRUE;
	}

	return FALSE;
}

// 求交线段 <P0-P1> 与 <矩形面片rc1> 的交线段，其中 <P0-P1> 与 rc1 共面。
// 如果求出交线段，返回true，并且该交线段放在 <ptStartNew, ptEndNew> 中返回；
// 否则返回false
BOOL LineSeg_Rectangle_Intersect(const CFPoint3D& ptStart, const CFPoint3D& ptEnd,
								 const CRectangle& rc,
								 CFPoint3D& ptStartNew, CFPoint3D& ptEndNew)
{
	BOOL bStartIn = FALSE, bEndIn = FALSE;
	if(rc.PtInRectangle(ptStart))
	{
		bStartIn = TRUE;
		ptStartNew	= ptStart;
	}

	if(rc.PtInRectangle(ptEnd))
	{
		bEndIn = TRUE;
		ptEndNew	= ptEnd;
	}

	if(bStartIn && bEndIn)
		return TRUE;

	CFPoint3D p0, p1;

	int nCount = 0;
	CFPoint3D ptIntersect[4]; // 2 at most
	for(int nEdgeIndex = 0; (nEdgeIndex < 4) && (nCount < 3); nEdgeIndex++)
	{
		rc.GetEdgeByIndex(nEdgeIndex, p0, p1);
		if(LineSeg_LineSeg_Intersect(ptStart, ptEnd, p0, p1, ptIntersect[nCount]))
			nCount++;
	}

	// 1 or 2
	if(1 == nCount)
	{
		if(bStartIn)
			ptEndNew = ptIntersect[0];
		else
			ptStartNew = ptIntersect[0];
	}
	else if(2 == nCount)
	{
		// which is the start, which is the end?
		ptStartNew	= ptIntersect[0];
		ptEndNew	= ptIntersect[1];
	}
	else
	{
		// ASSERT(0);
		//
		return FALSE;
	}

	return TRUE;
}

BOOL Rectangle_Rectangle_Intersect(const CRectangle& rc0, const CRectangle& rc1,
								   CFPoint3D& ptStart, CFPoint3D& ptEnd)
{
	BOOL bIntersect = FALSE; // 这两个矩形面片是否有交

	// debug
//	rc0.Dump(0);
//	rc1.Dump(1);

	// 如果两个矩形面片平行，则可定不交（重合情况以后再考虑）
	if( ForkMul(rc0.GetN(), rc1.GetN()).IsZeroVector() )
	{
		return bIntersect;
	}


	CFPoint3D ptInstersects[4]; // 2 at most
	int nCount = 0;
	CFPoint3D ptInstersect;
	CLineSeg3D LineSeg;

//	CFPoint3D ptStart, ptEnd;

	BOOL bFirstEdge = TRUE;
	for(int nEdgeIndex = 0; nEdgeIndex < 4; nEdgeIndex++)
	{
		rc0.GetEdgeByIndex(nEdgeIndex, ptStart, ptEnd);
		if( Intersect3D_LineSeg_Rectangle(ptStart, ptEnd, rc1, ptInstersect) )
		{
			if(bFirstEdge)
			{
				ptInstersects[nCount++] = ptInstersect;
			}
			else
			{
				if(0 == nCount)
					ptInstersects[nCount++] = ptInstersect;
				else if(ptInstersects[nCount-1] != ptInstersect)
					ptInstersects[nCount++] = ptInstersect;
			}
		}

		bFirstEdge = FALSE;
	}

	// <矩形面片0> 与 <矩形面片1所在平面> 的交线
	if(0 == nCount) // 没有交
	{
		// nop
	}
	else if(1 == nCount) // 角点接触
	{
		// nop
	}
	else if(2 == nCount) // 一条交线
	{
		// check further
		bIntersect = LineSeg_Rectangle_Intersect(ptInstersects[0], ptInstersects[1], rc1, ptStart, ptEnd);
		if(bIntersect)
		{
			if(! rc0.PtInRectangle(ptStart))
				rc0.PtInRectangle(ptStart);
			if(! rc0.PtInRectangle(ptEnd))
				rc0.PtInRectangle(ptEnd);

			if(! rc1.PtInRectangle(ptStart))
				rc1.PtInRectangle(ptStart);
			if(! rc1.PtInRectangle(ptEnd))
				rc1.PtInRectangle(ptEnd);
		}
	}
	else
	{
		ASSERT(0); // impossible
	}

	ASSERT(nCount < 3);

	return bIntersect;
}
