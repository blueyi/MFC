// Rectangle3D.h : header file
//
#ifndef __RECTANGLE3D_H__
#define __RECTANGLE3D_H__

#include "FPoint3D.h"
#include "TransMatrix3D.h"

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

// 矩形面片
/*
                       Edge3

    A -------------------^-m_Vector1--------- D
      |                  |                   |
      |                  |                   |
      |                  |         m_Vector0 |
Edge0 |                  +------------------->  Edge2
      |                 m_ptCenter           |
      |                                      |
      |                                      |
      |                                      |
    B ---------------------------------------- C
                      Edge1
*/
class CLASS_DECL_IMAGEHEADER CRectangle
{
public:
	CRectangle()
	{
		// m_ptCenter.Set(0.0, 0.0, 0.0);
		m_Vector0.Set(0.5, 0.0, 0.0);
		m_Vector1.Set(0.0, 0.5, 0.0);
	}

public:
	void SetCenter(const CFPoint3D& ptCenter) { m_ptCenter = ptCenter; }
	void SetVector0(const CFVector3D& Vector0) { m_Vector0 = Vector0; }
	void SetVector1(const CFVector3D& Vector1) { m_Vector1 = Vector1; }
	void SetVector(const CFVector3D& Vector0, const CFVector3D& Vector1) { m_Vector0 = Vector0; m_Vector1 = Vector1; }

	const CFPoint3D& GetCenter() const { return m_ptCenter; } 
	const CFVector3D& GetVector0() const { return m_Vector0; }
	const CFVector3D& GetVector1() const { return m_Vector1; }

	CFPoint3D& GetCenter() { return m_ptCenter; } 
	CFVector3D& GetVector0() { return m_Vector0; }
	CFVector3D& GetVector1() { return m_Vector1; }

	void GetEdge0(CFPoint3D& ptStart, CFPoint3D& ptEnd) const { GetA(ptStart); GetB(ptEnd); }
	void GetEdge1(CFPoint3D& ptStart, CFPoint3D& ptEnd) const { GetB(ptStart); GetC(ptEnd); }
	void GetEdge2(CFPoint3D& ptStart, CFPoint3D& ptEnd) const { GetC(ptStart); GetD(ptEnd); }
	void GetEdge3(CFPoint3D& ptStart, CFPoint3D& ptEnd) const { GetD(ptStart); GetA(ptEnd); }
	void GetEdgeByIndex(int nEdgeIndex, CFPoint3D& ptStart, CFPoint3D& ptEnd) const
	{
		switch(nEdgeIndex)
		{
		case 0:
			GetEdge0(ptStart, ptEnd);
			break;
		case 1:
			GetEdge1(ptStart, ptEnd);
			break;
		case 2:
			GetEdge2(ptStart, ptEnd);
			break;
		case 3:
			GetEdge3(ptStart, ptEnd);
			break;
		default:
			ASSERT(0);
		}
	}

	void GetABCD(CFPoint3D& A, CFPoint3D& B, CFPoint3D& C, CFPoint3D& D) const
	{
		GetA(A); GetB(B); GetC(C); GetD(D);
	}
	void GetVertexByIndex(int nVertexIndex, CFPoint3D& Vertex) const
	{
		switch(nVertexIndex)
		{
		case 0:
			GetA(Vertex);
			break;
		case 1:
			GetB(Vertex);
			break;
		case 2:
			GetC(Vertex);
			break;
		case 3:
			GetD(Vertex);
			break;
		default:
			ASSERT(0);
		}
	}

	CFVector3D GetN() const
	{
		CFVector3D FVector3D = ForkMul(m_Vector0, m_Vector1);
		FVector3D.Normalize();
		return FVector3D;
	}

// transform
public: // edit
	void Move(double dx, double dy, double dz)
	{
		m_ptCenter.Move(dx, dy, dz);
	}
	void Rotate(const CFPoint3D& p0, const CFPoint3D& p1, double theta) // theta in arc
	{
		CTransMatrix3D M;
		M.SetRotate(p0, p1, theta);
		Transform(M);
	}
	void Transform(const CTransMatrix3D& M)
	{
		CFPoint3D P0 = GetCenter() + GetVector0();
		CFPoint3D P1 = GetCenter() + GetVector1();

		GetCenter() = M.Transform(GetCenter());
		GetVector0() = M.Transform(P0) - GetCenter();
		GetVector1() = M.Transform(P1) - GetCenter();
	}

public:
	// 前提pt一定在本面片所在平面上
	BOOL PtInRectangle(const CFPoint3D& pt) const
	{
		CFPoint3D Vertex[4]; // verties & vectors
		for(int nVertexIndex = 0; nVertexIndex < 4; nVertexIndex++)
		{
			GetVertexByIndex(nVertexIndex, Vertex[nVertexIndex]);
			Vertex[nVertexIndex] -= pt;
		}

		CFVector3D ForkV0;
		BOOL bFirstExist = TRUE; // first NZ ForkVector exist already ?

		for(int i = 0; i < 4; i++)
		{
			int next = (i >= 3)? 0 : (i+1);
			CFVector3D ForkV1 = Vertex[i].ForkMulWith(Vertex[next]);
			ForkV1.Normalize();
			if(! ForkV1.IsZeroVector() )
			{
				if(bFirstExist)
				{
					bFirstExist = FALSE;
					ForkV0 = ForkV1;
				}
				else if(ForkV0 != ForkV1)
					return FALSE;
			}
		}
		return TRUE;
	}

private:
	void GetA(CFPoint3D& A) const { A = m_ptCenter - m_Vector0 + m_Vector1; }
	void GetB(CFPoint3D& B) const { B = m_ptCenter - m_Vector0 - m_Vector1; }
	void GetC(CFPoint3D& C) const { C = m_ptCenter + m_Vector0 - m_Vector1; }
	void GetD(CFPoint3D& D) const { D = m_ptCenter + m_Vector0 + m_Vector1; }

public:
#undef _RODGER_DBG // switch
#ifdef _RODGER_DBG
#define DUMP_POINT3D(pt3D)	TRACE("(%.2f, %.2f, %.2f)\n", pt3D.m_fx, pt3D.m_fy, pt3D.m_fz)
	void Dump(int i) const
	{
		TRACE("\n[Rectangle%d]\n", i);
		TRACE("  Center:"); DUMP_POINT3D(m_ptCenter);
		TRACE("  Vector0:"); DUMP_POINT3D(m_Vector0);
		TRACE("  Vector1:"); DUMP_POINT3D(m_Vector1);
	}
#else
	void Dump(int i) const {}
#endif // _RODGER_DBG

private:
	CFPoint3D m_ptCenter; // 矩形面片的中心点坐标

	// 两条边中点坐标
	CFPoint3D m_Vector0;
	CFPoint3D m_Vector1;
};


// 矩形面片集
class CRectVolume
{
public:
	CRectVolume()
	{
		// m_vcExt.Set(0.0, 0.0, 0.0);
	}

public:
	void SetRectangle(const CRectangle& MidRect) { m_MidRect = MidRect; }
	void SetExtVector(const CFVector3D& ExtVecor) { m_ExtVecor = ExtVecor; }

public:
	CFVector3D m_ExtVecor; // extention vector
	CRectangle m_MidRect; // middle rectangle
};


class CLineSeg3D
{
public:
	CFPoint3D m_Start;
	CFPoint3D m_End;
};


// public:
BOOL CLASS_DECL_IMAGEHEADER Rectangle_Rectangle_Intersect(const CRectangle& rc0, const CRectangle& rc1,
								   CFPoint3D& ptStart, CFPoint3D& ptEnd);

// 求空间任意直线与任意平面的交点
CFPoint3D Intersect3D_Line_Plane();


#endif // __RECTANGLE3D_H__
