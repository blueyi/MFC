// PathHull.h: interface for the CPathHull class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_)
#define AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef NULL
	#define NULL 0
#endif

#define DP_PUSH_OP 0		/* Operation names saved in history stack */
#define DP_TOP_OP 1
#define DP_BOT_OP 2

#ifndef FALSE
	#define FALSE 0
#endif
#ifndef TRUE
	#define TRUE 1
#endif

typedef double DP_POINT[2];	/* Most data is cartesian points */
typedef double DP_HOMOG[3];	/* Some partial calculations are homogeneous */

#define DP_XX 0
#define DP_YY 1
#define DP_WW 2

#define DP_CROSSPROD_2CCH(p, q, r) /* 2-d cartesian to homog cross product */\
 (r)[DP_WW] = (p)[DP_XX] * (q)[DP_YY] - (p)[DP_YY] * (q)[DP_XX];\
 (r)[DP_XX] = - (q)[DP_YY] + (p)[DP_YY];\
 (r)[DP_YY] =   (q)[DP_XX] - (p)[DP_XX];

#define DP_DOTPROD_2CH(p, q)	/* 2-d cartesian to homog dot product */\
 (q)[DP_WW] + (p)[DP_XX]*(q)[DP_XX] + (p)[DP_YY]*(q)[DP_YY]


#define DP_DOTPROD_2C(p, q)	/* 2-d cartesian  dot product */\
 (p)[DP_XX]*(q)[DP_XX] + (p)[DP_YY]*(q)[DP_YY]

#define DP_LINCOMB_2C(a, p, b, q, r) /* 2-d cartesian linear combination */\
 (r)[DP_XX] = (a) * (p)[DP_XX] + (b) * (q)[DP_XX];\
 (r)[DP_YY] = (a) * (p)[DP_YY] + (b) * (q)[DP_YY];



#define DP_SGN(a) (a >= 0)


#define DP_MIN(a,b) ( a < b ? a : b)
#define DP_MAX(a,b) ( a > b ? a : b)

class CPathHull  
{
public:
	CPathHull();
	virtual ~CPathHull();

	void SetMaxSize(int iHullMax);

	int GetHp() const
	{	return m_iHp;};
	int GetBot() const
	{	return m_iBot;};
	int GetTop() const
	{	return m_iTop;};
	DP_POINT* GetpElt(int i)
	{	return m_ppElt[i];};
	DP_POINT* GetpHelt(int i)
	{	return m_ppHelt[i];};
	int* GetpOp()
	{	return m_pOp;};

	void SetHp(int hp)
	{	m_iHp=hp;};

	void UpHp()		{	m_iHp++;};
	void UpTop()	{	m_iTop++;};
	void UpBot()	{	m_iBot++;};
	void DownHp()	{	m_iHp--;};
	void DownTop()	{	m_iTop--;};
	void DownBot()	{	m_iBot--;};

	void SetTopElt(DP_POINT* p)
	{	m_ppElt[m_iTop]=p;};
	void SetBotElt(DP_POINT* p)
	{	m_ppElt[m_iBot]=p;};

	void Split(DP_POINT *e);
	void FindExtreme(DP_HOMOG  line, DP_POINT ** e, double * dist);

	void Init(DP_POINT* e1, DP_POINT* e2)
	{
		/* Initialize path hull and history  */
		m_ppElt[m_iHullMax] = e1;
		m_ppElt[m_iTop = m_iHullMax + 1] = 
			m_ppElt[m_iBot = m_iHullMax - 1] = 
			m_ppHelt[m_iHp = 0] = e2;
		m_pOp[0] = DP_PUSH_OP;
	}

	void Push(DP_POINT* e)
	{
		/* Push element $e$ onto path hull $h$ */
		m_ppElt[++m_iTop] = m_ppElt[--m_iBot] = m_ppHelt[++m_iHp] = e;
		m_pOp[m_iHp] = DP_PUSH_OP;
	}

	void PopTop()
	{	/* Pop from top */
		m_ppHelt[++m_iHp] = m_ppElt[m_iTop--];
		m_pOp[m_iHp] = DP_TOP_OP;
	}

	void PopBot()
	{
		/* Pop from bottom */
		m_ppHelt[++m_iHp] = m_ppElt[m_iBot++];
		m_pOp[m_iHp] = DP_BOT_OP;
	}
	
	void Add(DP_POINT* p);

	int LeftOfTop(DP_POINT* c)
	{
		/* Determine if point c is left of line a to b */
		return (((*m_ppElt[m_iTop])[DP_XX] - (*c)[DP_XX])*((*m_ppElt[m_iTop-1])[DP_YY] - (*c)[DP_YY]) 
			>= ((*m_ppElt[m_iTop-1])[DP_XX] - (*c)[DP_XX])*((*m_ppElt[m_iTop])[DP_YY] - (*c)[DP_YY]));
	}

	int LeftOfBot(DP_POINT* c)
	{
		/* Determine if point c is left of line a to b */
		return (((*m_ppElt[m_iBot+1])[DP_XX] - (*c)[DP_XX])*((*m_ppElt[m_iBot])[DP_YY] - (*c)[DP_YY]) 
			>= ((*m_ppElt[m_iBot])[DP_XX] - (*c)[DP_XX])*((*m_ppElt[m_iBot+1])[DP_YY] - (*c)[DP_YY]));
	}


	int SlopeSign(int p, int q, DP_HOMOG l)
	{
		/* Return the sign of the projection 
				   of $h[q] - h[p]$ onto the normal 
				   to line $l$ */ 
		return (int)(DP_SGN((l[DP_XX])*((*m_ppElt[q])[DP_XX] - (*m_ppElt[p])[DP_XX]) 
			+ (l[DP_YY])*((*m_ppElt[q])[DP_YY] - (*m_ppElt[p])[DP_YY]))) ;
	};

protected:
	/// Maxium number of elements in hull
	int m_iHullMax;
	
	/// internal values
	int m_iTop;
	int m_iBot; 
	int m_iHp;
	int *m_pOp;	
	DP_POINT **m_ppElt; 
	DP_POINT **m_ppHelt;
};

#endif // !defined(AFX_PATHHULL_H__50C639BA_585B_4272_9AF4_4632128D8938__INCLUDED_)
