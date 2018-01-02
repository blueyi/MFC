// TransMatrix3D.cpp : implementation file
//
#include "StdAfx.h"
#include "TransMatrix3D.h"

CFVector3D operator -(const CFVector3D& V)
{
	return CFVector3D(-V.m_fx, -V.m_fy, -V.m_fz);
}

void swap(double& a, double& b )
{
    double c = a;
    a = b;
	b = c;
}

#if 0
CTransMatrix3D& CTransMatrix3D::SetRotate_2(const CFPoint3D& p0, const CFPoint3D& p1, double theta)
{
	CFVector3D V = p1 - p0;
	if(! V.IsZeroVector())
	{
		CTransMatrix3D T, rT;
		T.SetTranslate(V);
		rT.SetTranslate(-V);

		// x_alpha, y_beta
		CTransMatrix3D R_xa_yb;

		CFVector3D U = V;
		U.Normalize();

		CFVector3D Ux(1.0, 0, 0);

		CFVector3D Uzp = U;

		CFVector3D Uyp = U.ForkMulWith(Ux);
		ASSERT(! Uyp.IsZeroVector());

		CFVector3D Uxp = Uyp.ForkMulWith(Uyp);
		ASSERT(! Uxp.IsZeroVector());

		R_xa_yb.SetRow(0, Uxp);
		R_xa_yb.SetRow(1, Uyp);
		R_xa_yb.SetRow(2, Uzp);


		// z_theta
		CTransMatrix3D R_z0;
		R_z0.SetRotateZ(theta);

		Concat(rT).Concat(R_xa_yb).Concat(R_z0).Concat(T);
	}

	return *this;
}
#endif


CGMatrix::CGMatrix()
{
	SetIdentity();
}

CGMatrix::CGMatrix(const CGMatrix& m)
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	{
		e[i][j] = m.e[i][j];
	}
}

void CGMatrix::SetIdentity()
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	{
		e[i][j] = (i == j)? 1.0 : 0.0;
	}
}

BOOL CGMatrix::IsIdentity()
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	{
		double r = (i == j)? 1.0 : 0.0;
		if(! IsEqual(e[i][j], r))
			return FALSE;
	}

	return TRUE;
}


double GetTranspose(CGMatrix& mOut, const CGMatrix& rhs)
{
	CGMatrix m(rhs);
	DWORD is[4];
	DWORD js[4];
	double fDet = 1.0f;
	int f = 1;

	for (int k = 0; k < 4; k ++)
	{
		double fMax = 0.0f;
		for (DWORD i = k; i < 4; i ++)
		{
			for (DWORD j = k; j < 4; j ++)
			{
				const double f = fabs(m.e[i][j]);
				if (f > fMax)
				{
					fMax = f;
					is[k] = i;
					js[k] = j;
				}
			}
		}

		if (fabs(fMax) < 0.0001f)
			return 0;

		if (is[k] != k)
		{
			f = -f;
			swap(m.e[k][0], m.e[is[k]][0]);
			swap(m.e[k][1], m.e[is[k]][1]);
			swap(m.e[k][2], m.e[is[k]][2]);
			swap(m.e[k][3], m.e[is[k]][3]);
		}
		
		if (js[k] != k)
		{
			f = -f;
			swap(m.e[0][k], m.e[0][js[k]]);
			swap(m.e[1][k], m.e[1][js[k]]);
			swap(m.e[2][k], m.e[2][js[k]]);
			swap(m.e[3][k], m.e[3][js[k]]);
		}

		fDet *= m.e[k][k];


		m.e[k][k] = 1.0f / m.e[k][k]; 
		for (DWORD j = 0; j < 4; j ++)
		{
			if (j != k)
				m.e[k][j] *= m.e[k][k];
		}

		for (/*DWORD */i = 0; i < 4; i ++)
		{
			if (i != k)
			{
				for (j = 0; j < 4; j ++)
				{
					if (j != k)
						m.e[i][j] = m.e[i][j] - m.e[i][k] * m.e[k][j];
				}
			}
		}

		for (i = 0; i < 4; i ++)
		{
			if (i != k)
				m.e[i][k] *= -m.e[k][k];
		}
	}

	for (k = 3; k >= 0; k --)
	{
		if (js[k] != k)
		{
			swap(m.e[k][0], m.e[js[k]][0]);
			swap(m.e[k][1], m.e[js[k]][1]);
			swap(m.e[k][2], m.e[js[k]][2]);
			swap(m.e[k][3], m.e[js[k]][3]);
		}
		if (is[k] != k)
		{
			swap(m.e[0][k], m.e[0][is[k]]);
			swap(m.e[1][k], m.e[1][is[k]]);
			swap(m.e[2][k], m.e[2][is[k]]);
			swap(m.e[3][k], m.e[3][is[k]]);
		}
	}

	mOut = m;
	return fDet * f;
}


CTransMatrix3D& CTransMatrix3D::SetRotate(const CFPoint3D& p0, const CFPoint3D& p1, double theta)
{
	CFVector3D V = p1 - p0;
	if(! V.IsZeroVector())
	{
		CFVector3D U = V;
		U.Normalize();

		CFVector3D Ux(1.0, 0.0, 0.0);
		CFVector3D Uy(0.0, 1.0, 0.0);
		CFVector3D Uz(0.0, 0.0, 1.0);

		CTransMatrix3D T; // rT;
		T.SetTranslate(V); // T is set to this Matrix
		SetTranslate(-V);

		CTransMatrix3D R;

		if(U.ForkMulWith(Ux).IsZeroVector())
		{
			if(U.m_fx < 0.0)
				theta = -theta;
			R.SetRotateX(theta);
		}
		else if(U.ForkMulWith(Uy).IsZeroVector())
		{
			if(U.m_fy < 0.0)
				theta = -theta;
			R.SetRotateY(theta);
		}
		else if(U.ForkMulWith(Uz).IsZeroVector())
		{
			if(U.m_fz < 0.0)
				theta = -theta;
			R.SetRotateZ(theta);
		}
		else 
		{
			// x_alpha, y_beta
			CTransMatrix3D R_xa_yb;

			//
			CFVector3D Uxp = Ux;
			CFVector3D Uyp = Uy;
			CFVector3D Uzp = Uz;
			Uzp = U;

			Uyp = U.ForkMulWith(Ux);
			ASSERT(! Uyp.IsZeroVector());

			Uxp = Uyp.ForkMulWith(Uzp);
			ASSERT(! Uxp.IsZeroVector());

			//
			R_xa_yb.SetRow(0, Uxp);
			R_xa_yb.SetRow(1, Uyp);
			R_xa_yb.SetRow(2, Uzp);

			//
			CTransMatrix3D rR_xa_yb = R_xa_yb;
			//rR_xa_yb.Transpose();
			CGMatrix GM, rGM;
			int i = 0, j = 0;
			for(i = 0; i < 3; i++)
			for(j = 0; j < 4; j++)
				GM.e[i][j] = R_xa_yb.a[i][j];
			GetTranspose(rGM, GM);
			for(i = 0; i < 3; i++)
			for(j = 0; j < 4; j++)
				rR_xa_yb.a[i][j] = rGM.e[i][j];

			// z_theta
			CTransMatrix3D R_z0;
			R_z0.SetRotateZ(theta);

			// composte rotation matrix
			R.Concat(rR_xa_yb).Concat(R_z0).Concat(R_xa_yb);
		}

		Concat(R).Concat(T);
	}

	return *this;
}
