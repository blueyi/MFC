// TransMatrix3D.h : header file
//

#ifndef __TRANSMATRIX3D_H__
#define __TRANSMATRIX3D_H__

#include "FPoint3D.h"

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif


class CGMatrix
{
public:
	CGMatrix();
	CGMatrix(const CGMatrix& m);

	void SetIdentity();
	void Set(double e[4][4]);
	BOOL IsIdentity();

public:
	double e[4][4];

public:
};

/*
  P' = M x P
     ©³               ©·
     ©§a00 a01 a02 a03©§
     ©§a10 a11 a12 a13©§
  M =©§a20 a21 a22 a23©§
     ©§  0   0   0   1©§
     ©»               ©¿
*/
class CLASS_DECL_IMAGEHEADER CTransMatrix3D
{
public:
	CTransMatrix3D()
	{
		Normalize();
	}

public:
	CTransMatrix3D& Normalize()
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 4; j++)
			a[i][j] = (j==i)? 1.0 : 0.0;
		return *this;
	}

	// ×ªÖÃ
	CTransMatrix3D& Transpose()
	{
		double temp = 0.0;
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < i; j++) // let 'a03, a13, a23' be
		{
			if(j != i)
			{
				temp = a[i][j];
				a[i][j] = a[j][i];
				a[j][i] = temp;
			}
		}
		return *this;
	}

	CTransMatrix3D GetInverse()
	{
		ASSERT(0);
		return *this;
	}


	CTransMatrix3D& Concat(const CTransMatrix3D& M)
	{
		CTransMatrix3D tmpM = *this;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				a[i][j] = tmpM.a[i][0] * M.a[0][j] +
						  tmpM.a[i][1] * M.a[1][j] +
						  tmpM.a[i][2] * M.a[2][j];
			}

			a[i][3] = tmpM.a[i][0] * M.a[0][3] +
					  tmpM.a[i][1] * M.a[1][3] +
					  tmpM.a[i][2] * M.a[2][3] +
					  tmpM.a[i][3];
		}
		return *this;
	}

	CTransMatrix3D& SetTranslate(double dx, double dy, double dz)
	{
		Normalize();
		a03 = dx, a13 = dy, a23 = dz;
		return *this;
	}
	CTransMatrix3D& SetTranslate(const CFVector3D& V)
	{
		return SetTranslate(V.m_fx, V.m_fy, V.m_fz);
	}


	// in arc
	CTransMatrix3D& SetRotateZ(double theta)
	{
		Normalize();
		a00 = a11 = cos(theta);
		a10 = sin(theta), a01 = -a10;
		return *this;
	}
	CTransMatrix3D& SetRotateY(double theta)
	{
		Normalize();
		a00 = a22 = cos(theta);
		a02 = sin(theta), a20 = -a02;
		return *this;
	}
	CTransMatrix3D& SetRotateX(double theta)
	{
		Normalize();
		a11 = a22 = cos(theta);
		a21 = sin(theta), a12 = -a21;
		return *this;
	}
	CTransMatrix3D& SetRotate(const CFPoint3D& p0, const CFPoint3D& p1, double theta);

	void SetRow(int nRowIndex, CFVector3D& V)
	{
		if(0 > nRowIndex || nRowIndex > 3)
			return;

		a[nRowIndex][0] = V.m_fx;
		a[nRowIndex][1] = V.m_fy;
		a[nRowIndex][2] = V.m_fz;
	}

// operators
	CFPoint3D Transform(const CFPoint3D& pt3D) const
	{
		return CFPoint3D(a00*pt3D.m_fx + a01*pt3D.m_fy + a02*pt3D.m_fz + a03,
						 a10*pt3D.m_fx + a11*pt3D.m_fy + a12*pt3D.m_fz + a13,
						 a20*pt3D.m_fx + a21*pt3D.m_fy + a22*pt3D.m_fz + a23);
	}


public:
	union
	{
		double a[3][4];
		struct
		{
			double a00, a01, a02, a03;
			double a10, a11, a12, a13;
			double a20, a21, a22, a23;
		};
	};
};


class CMatrix_4x4
{
public:
	CMatrix_4x4()
	{
		Zero();
	}

	CMatrix_4x4(const CTransMatrix3D& TM3D)
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 4; j++)
			a[i][j] = TM3D.a[i][j];

		a[3][0] = a[3][1] = a[3][2] = 0.0;
		a[3][3] = 1.0;
	}

public:
	CMatrix_4x4& Concat(const CMatrix_4x4& M)
	{
		CMatrix_4x4 tmpM = *this;
		for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			a[i][j] = tmpM.a[i][0] * M.a[0][j] +
					  tmpM.a[i][1] * M.a[1][j] +
					  tmpM.a[i][2] * M.a[2][j] +
					  tmpM.a[i][3] * M.a[3][j];
		}

		return *this;
	}

	CMatrix_4x4& Normalize()
	{
		for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			a[i][j] = (j==i)? 1.0 : 0.0;
		}

		return *this;
	}

	CMatrix_4x4& Zero()
	{
		for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			a[i][j] = 0.0;
		return *this;
	}

public:
	union
	{
		double a[4][4];
		struct
		{
			double a00, a01, a02, a03;
			double a10, a11, a12, a13;
			double a20, a21, a22, a23;
			double a30, a31, a32, a33;
		};
	};
};

#endif // __TRANSMATRIX3D_H__
