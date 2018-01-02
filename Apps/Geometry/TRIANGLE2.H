/********************************************************************
File Name:	TRIANGLE2.H
Written by: 

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
	Vector3F-----Define a vector and some vector operators.
	CPolyTri-----Triangulate a polygon and calculate some parameters:
				 area, normal etc.
	CTriDC
	
History:
	2002/5/20	Modified by Li Peng.
				1. Add some comments, so this file becomes more readable.
				2. #include two indispensable files <cmath> and <cfloat>, so 
				this file can be compiled and linked in any C++ project.
				3. Rename two function Vector3F::Lenght() to Vector3F::Length()
				Vector3F::SquredLenght() to Vector3F::SquredLength().
				4. Add some function to calculate the area of a polygon.

	2002/5/20	Created.(This file is download from http://www.codeproject.com
				by Yang Guang.)
*********************************************************************/
/*
    \remarks
    http:// www.codeproject.com/useritems/polygon_tesselation.asp
    A more little explanation about my article. In order to tesselate the 
    polygon i use this tecnique:

    First compute the normal of polygon (i use the newell method see Graphic 
    Gems..). For each sequence of three vertex ( i, j, k ) in the polygon,
    compute the vector area (alias normal of triangle). If the normal go in the
    opposite direction of polygon normal the triangle is 'concave' and go 
    ahead. If the area il 0.0 the point j is alligned from i to k and 
    eliminated from the list of vertex. If the normal of triangle is in the 
    same direction of polygon normal the triangle is convex. In the last case 
    check if any other point is inside the triangle (the IsPointInside 
    function). This function test if the point is on solid angle ik ^ jk. If 
    this is true compute distance of intersection k->point to line ij and test
    distance. If all is good emit triangle, remove vertex j from list and go to
    the next triplet....

    The reason for wich i posted this article is that i don't find this 
    tecnique in any book or article and have a doubt about the mathematical 
    basic of my algoritm In other words is true that it work in any case? 
    (my experience says yes but is very far from a theorem...). The Delauney 
    algortim work fine but is 'computationally' more expensive than my 
    algorthm (using my Delauney implementation) for this reason I try this 
    way. 
   
*/
#ifndef _TRIANGLE_POLYTRY_
#define _TRIANGLE_POLYTRY_

#include <cmath>
#include <cfloat>

/*!
    This class is similar to CThreeDim written by Li Peng.
*/
class Vector3F
{
public:
	//! Constructor
	Vector3F(float x = 0.0f, float y = 0.0f, float z = 0.0f)   
	{  
		Set(x, y, z); 
	}

	//! Copy constructor
	Vector3F(const Vector3F& point)
	{  
		Set(point.m_v[0], point.m_v[1], point.m_v[2]); 
	}

	//! This function is used to assign.
	void Set(float x, float y, float z)                 
	{
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z; 
	}

	//! Overload [] operator, return the value of object.
	float operator[](int i) const
	{
		return m_v[i]; 
	}

	//! Overload [] operator, return the reference of object.
	float& operator[](int i)
	{  
		return m_v[i];
	}

	//! Overload += operator.
	Vector3F& operator+= (const Vector3F& v)         
	{
		m_v[0] += v.m_v[0];
		m_v[1] += v.m_v[1];
		m_v[2] += v.m_v[2];
		return *this;  
	}

	//! Overload -= operator.
	Vector3F& operator-= (const Vector3F& v)         
	{
		m_v[0] -= v.m_v[0];
		m_v[1] -= v.m_v[1];
		m_v[2] -= v.m_v[2];
		return *this;  
	}

	//! Overload *= operator.
	Vector3F& operator*= (const float d)             
	{
		m_v[0] *= d;
		m_v[1] *= d;
		m_v[2] *= d;
		return *this;  
	}

	//! Calculate the inner product of two Vector3Fs.
	float Dot(const Vector3F& v) const    
	{  
		return (m_v[0] * v.m_v[0] + m_v[1] * v.m_v[1] + m_v[2] * v.m_v[2]);   
	}

	//! Calculate the outer product of two Vector3Fs.
	void Vector(const Vector3F& b, Vector3F &c) const    
	{
		c.m_v[0]= m_v[1] * b.m_v[2] - m_v[2] * b.m_v[1];
		c.m_v[1]= m_v[2] * b.m_v[0] - m_v[0] * b.m_v[2];
		c.m_v[2]= m_v[0] * b.m_v[1] - m_v[1] * b.m_v[0]; 
	}

	//! Calculate the squared value of a Vector3F.
	float SquaredLength() const 
	{  
		return Dot(*this);
	}

	//! Calculate the length of a Vector3F.
	float Length() const
	{  
		return (float)sqrt(Dot(*this)); 
	}

	//! the attributes of Vector3F, an array of three float.
	float m_v[3];
};


class CPolyTri
{
public:
	//! Constructor
	CPolyTri()              
	{
		m_nIndex = NULL;
		m_nMaxPoints = 0;    
		m_fArea = 0.0f;
	}

	//! Destructor
	virtual  ~CPolyTri()    
	{
		if (m_nIndex)
			delete[] m_nIndex;  
	}

	//! Triangulate a polygon.
	/*!
		\param points Const point to Vector3F, it is an array of Vector3F, it
		represents the vertexes of the polygon.
		\param normal Reference to Vector3F, it is the result after invoking
		this function, it represents the normal of the polygon.
		\param nCount The count of the polygon's vertexes.
		\return The count of triangles after the polygon being triangulated.
	*/
	int Triangulate(const Vector3F* points, const Vector3F &normal, int nCount)
	{
		// Alloca un vettore di interi ...
		int nTriangle = 0;
		int nVertex = nCount;
		AllocIndex(nCount);

		bool bNoErrors = true;
		m_fArea = 0.0f;
		while (nVertex > 3 && bNoErrors)
		{
			// try to remove one vertex...
			bNoErrors   = false;
			for (int i = 0 , j = 1 , k = 2; k < nVertex; )
			{
				switch (TriangleArea(points,
					m_nIndex[i] ,
					m_nIndex[j] ,
					m_nIndex[k] ,
					normal))
				{
					// ok. flush face && remove vertex j
				case convex:
					// Testing containement
					if (IsAnyPointInside(points, i, j, k, nVertex))
					{
						// go ahead..
						i  = j;
						j  = k;
						k++;
					}
					else
					{
						nTriangle++;
//========	Commented out by Li Peng, 2002-5-21
//						AddFace(points, m_nIndex[i], m_nIndex[j], m_nIndex[k]);
//========	End Commented out by Li Peng, 2002-5-21
						
//========	Added by Li Peng, 2002-5-21
						m_fArea += CalcTriangleArea(points, m_nIndex[i], 
													m_nIndex[j], m_nIndex[k]);
//========	End added by Li Peng, 2002-5-21


						// remove vertex j
						nVertex  = RemoveVertex(j, nVertex);
						bNoErrors= true;
					}
					break;
				case concave:
					// go ahead..
					i  = j;
					j  = k;
					k++;
					break;
				case degenerate:
					// remove vertex j
					nVertex  = RemoveVertex(j, nVertex);
					bNoErrors= true;
					break;
				}
			}
		}
		return nTriangle;
	}

	//! Caculate the Normal of Polygon using "Newell" method.
	/*!
		\param points Const point to Vector3F, it is an array of Vector3F, it
		represents the vertexes of the polygon.
		\param nPoint The number of points of polygon.
		\param normal Reference to Vector3F, it is the result after invoking
		this function, it represents the normal of the polygon.
		\remarks Newell method is an algorithm to caculate the normal of 
		polygon. It provides a method of judging the direction of the sequence
		of polygon's vertex.

		//========	Added by Li Peng, 2002-5-20
		Accounting to my individual comprehension, the Newell method is 
		identical to the following algorithm:
			1) Put a polygon into an X-Y coordinate system;
			2) Define each vertex as P1, P2, ... , Pn in sequence with 
			clockwise or anticlockwise direction;
			3) Define a series of vector as V1, V2, ... , Vn;
			(Vi = Pi - Oxy, Oxy is the coordinate of original point)
			4) the normal of the polygon is:
			   Vnormal = Vzero;
			   for(int i = 0; i < n-1; i++)
			   {
					Vnormal += Out Product(Vi, Vi+1);
				}

		The method of Newell is:
			   Vnormal = Vzero;
			   for(int i = 0; i < n-1; i++)
			   {
				Vnormal += Out Product((Pi - Pi+1),(Pi + Pi+1));
				}
		Because
		  (Pi - Pi+1)*(Pi + Pi+1) 
		= Pi * Pi + Pi * Pi+1 - Pi+1 * Pi - Pi+1 * Pi+1
		= 2(Pi * Pi+1)
		(Here * is out product.)
		//========	End added by Li Peng, 2002-5-20
	*/
	static void ComputeNormal(const Vector3F* points, int nPoints, 
							  Vector3F &normal)
	{
		normal[0] = normal[1] = normal[2] = 0.0f;
//==================Newell======================//
//========	Commented out by Li Peng, 2002-5-27
//		for (register int i = 0 , j = 1; j < nPoints; i++ , j++)
//		{
//			normal[0] += (points[i][1] - points[j][1]) 
//				* (points[i][2] + points[j][2]);
//			normal[1] += (points[i][2] - points[j][2]) 
//				* (points[i][0] + points[j][0]);
//			normal[2] += (points[i][0] - points[j][0]) 
//				* (points[i][1] + points[j][1]);
//		}
//========	End Commented out by Li Peng, 2002-5-27
		Vector3F* edge = new Vector3F[nPoints];
		for(register int i = 0; i < nPoints; i++)
		{
			edge[i] = points[(i + 1) % nPoints];
			edge[i] -= points[i];
		}
		for(i = 0; i < nPoints; i++)
		{
			normal[0] += edge[i][1] * edge[(i + 1) % nPoints][2] 
				- edge[i][2] * edge[(i + 1) % nPoints][1];
			normal[1] += edge[i][2] * edge[(i + 1) % nPoints][0]
				- edge[i][0] * edge[(i + 1) % nPoints][2];
			normal[2] += edge[i][0] * edge[(i + 1) % nPoints][1]
				- edge[i][1] * edge[(i + 1) % nPoints][0];
		}
		delete []edge;
	}

	//! To predicate whether a polygon is convex or not.
	/*!
		\param points Const point to Vector3F, it an array of Vector3F, it
		represents the vertexes of the polygon.
		\param nPoint The number of points of polygon.
		\param normal Reference to Vector3F, it is the normal of the polygon.
		\return \a true if the polygon is convex, \a false otherwise.
		\remarks 
		The process of algorithm is that:
		1) Calculate all the edges of the polygon in sequence.
		Attention: the direction of edges in sequence must be identical to the
		direction of points in sequence, and the normal of the polygon is 
		obtained by the later.
		2) Calculate all the normals of the continuous two edges in sequence.
		if all the direction of normals is same as the normal of the polygon,
		the polygon is convex. Otherwise, the polygon is concave.
	*/
	static bool IsConvex(const Vector3F* points, int nPoints, 
						 const Vector3F& normal)
	{
		Vector3F vi(points[1]);
		vi -= points[0];
		Vector3F vj, n;
		int      nP = nPoints - 1;
		for (register int i = 0 , j = 1 , k; j < nPoints; i++ , j++)
		{
			// when (j == nPoints - 1), k = 0, vj = point[0]
			k  = (j + 1) % nP;
			vj = points[k];
			vj-= points[j];
			vi.Vector(vj, n);
			if ((n[0]*normal[0]) < 0.0f ||
				(n[1]*normal[1]) < 0.0f ||
				(n[2]*normal[2]) < 0.0f)
				break;
			vi = vj;
		}
		return (j == nPoints ? true : false);
	}
	
//========	Added by Li Peng, 2002-5-21
	//! Get the area of the polygon.
	float GetArea()
	{
		return m_fArea;
	}
//========	End added by Li Peng, 2002-5-21

protected:
    //! Index of point, it will be used to allocate new array.
    int         *m_nIndex; //!< index of point
    Vector3F    m_e0; //!< the first edge, k->i
    Vector3F    m_e1; //!< the second edge, k->j
    Vector3F    m_N;  //!< the out product of (m_e0, m_e1).
    float       m_A;  //!< the inner product of (m_N, m_N).
	float       m_fArea; //!< the area of the polygon.



    /*!
		\remarks This enum represents three status of the triangle which is 
		defined by the three point (i, j, k).
		\a convex If the direction of the normal is same as the one of polygon.
		\a degenerate If the three points are in one line.
		\a concave If the direction of the normal is opposite to the normal of
		polygon.
	*/
    enum  
    {
        convex      =  1,  
        degenerate  =  0,
        concave     = -1
    };

    //! Remove point[nVertex] from the array of point.
	/*!
		\param j It is the point index that should be remove from the array of
		point.
		\param nVertex It is the index of the last point in the array of point.
		\return the index of the last point after remove point[j].
	*/
    int RemoveVertex(int j, int nVertex)
    {
        while (++j < nVertex)
            m_nIndex[j - 1] = m_nIndex[j];
        return (nVertex - 1);
    }
	
    //! To judeg if the series of point is in the region of triangle(i, j, k).
	/*!
		\param points Const point to Vector3F, it an array of Vector3F, it
		represents the vertexes of the polygon.
		\param i the index of the array of points, the first point.
		\param j the index of the array of points, the second point.
		\param k the index of the array of points, the third point.
		\param nVertex The count of vertexes.
		\return \a true if there are at least one point in the region, \a false
		if there are no points in the region.
	*/
    bool IsAnyPointInside(const Vector3F* points, int i, int j, int k, 
						  int nVertex) const
    {
        int   ik = m_nIndex[k];
        for (register int ip = 0; ip < nVertex; ip++)
            if ((ip < i || ip > k) &&
                IsPointInside(points[m_nIndex[ip]], points[ik]))
            {
                return true;
            }
            return false;
    }

	//! To judge if point is in the region of triangle(i,j,k)
    /*!
		\param point Const reference to Vector3F, it is the point to be judged.
		\param q2 Const reference of Vector3F, it is the vertex(k) of the 
		triangle.
		\return \a true if the point is in the region of the triangle, \a false
		otherwise.
	*/
    bool IsPointInside(const Vector3F& point, const Vector3F& q2) const
    {
		// pmq2 is the vector from point[k] to point.
        Vector3F pmq2  = point;
        pmq2 -= q2;
        
		// To judge if the point is in the angle of k->i and k->j.
        Vector3F ntmp;
        float B0, B1;
        pmq2.Vector(m_e1, ntmp);
		if ((B0 = m_N.Dot(ntmp)) <= 0.0)
            return false;
        m_e0.Vector(pmq2, ntmp);
		if ((B1 = m_N.Dot(ntmp)) <= 0.0)
            return false;
		// To judge if the point is in the region of triangle(i, j, k).
        return ((m_A - B0 - B1) > 0.0 ? true : false);
    }

    //! Calculate the area of the triangle which is determined by three points.
	/*!
		\param points Const point to Vector3F, it an array of Vector3F, it
		represents the vertexes of the polygon.
		\param i the index of the array of points, the first point.
		\param j the index of the array of points, the second point.
		\param k the index of the array of points, the third point.
		\param normal Reference to Vector3F, it is the normal of the polygon.
		\return \a 1 if the triangle is convex, \a -1 if the triangle is 
		concave, \a 0 if the triangle is degenerate.
		\remarks After invoke this function, the area of the triangle will be
		calculated and be assigned to m_N;
	*/
    int TriangleArea(const Vector3F* points, int i, int j, int k, 
					 const Vector3F& normal)
    {
		// m_e0 is the edge which is defined by point[i] and point[k].
        m_e0 = points[i];
        m_e0 -= points[k];

		// m_e1 is the edge which is defined by point[j] and point[k].
        m_e1 = points[j];
        m_e1 -= points[k];

        // the area of the triangle will be calculated and assigned to m_N.
        m_e0.Vector(m_e1, m_N);

        m_A = m_N.SquaredLength();
        // j is alligned from i to k ?
        if ((-FLT_EPSILON) < m_A && m_A < FLT_EPSILON)
            return degenerate;

        // test convexity
        return (m_N.Dot(normal) < 0.0 ? concave : convex);
    }

    //! This function is used to get the convex triangle.
	/*!
		\param points Const point to Vector3F, it an array of Vector3F, it
		represents the vertexes of a triangle.
		\param i the index of the array of points, the first point.
		\param j the index of the array of points, the second point.
		\param k the index of the array of points, the third point.
	*/
    virtual void AddFace(const Vector3F* points, int i, int j, int k){}


//========	Added by Li Peng, 2002-5-21
	//! Calculate the area of a triangle.
	/*!
		\param points Const point to Vector3F, it an array of Vector3F, it
		represents the vertexes of a triangle.
		\param i the index of the array of points, the first point.
		\param j the index of the array of points, the second point.
		\param k the index of the array of points, the third point.
	*/
	float CalcTriangleArea(const Vector3F* points, int i, int j, int k)
	{
		// m_e0 is the edge which is defined by point[i] and point[k].
        m_e0 = points[i];
        m_e0 -= points[k];

		// m_e1 is the edge which is defined by point[j] and point[k].
        m_e1 = points[j];
        m_e1 -= points[k];

        // the normal of the triangle will be calculated and assigned to m_N.
        m_e0.Vector(m_e1, m_N);
		
		return m_N.Length() / 2.0f;
	}
//========	End added by Li Peng, 2002-5-21


private:
	
    int	m_nMaxPoints;

    void  AllocIndex(int nCount)
    {
        if (nCount > m_nMaxPoints)
        {
            if (m_nIndex)
			{
                delete[] m_nIndex;
			}
            m_nMaxPoints = nCount + 2;
            m_nIndex     = new int[m_nMaxPoints];
        }
		
        for (register int i = 0; i < nCount; i++)
            m_nIndex[i] = i;
    }
};


/*
class CTriDC : public CPolyTri
{
public:
    CTriDC(CDC* pDC)
    {
        m_pDC = pDC;
    }
    CDC*  m_pDC;
protected:
    //
    CPoint   m_points[4];
    //
    virtual  void  AddFace(const Vector3F* points, int i, int j, int k)
    {
        m_points[0].x  = (int)points[i][0];
        m_points[0].y  = (int)points[i][1];
        m_points[1].x  = (int)points[j][0];
        m_points[1].y  = (int)points[j][1];
        m_points[2].x  = (int)points[k][0];
        m_points[2].y  = (int)points[k][1];
        m_points[3]    = m_points[0];
        m_pDC->Polygon(m_points, 4);
    }
};
*/

#define _TRIANGLE_POLYTRY_
#endif
