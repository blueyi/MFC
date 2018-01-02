#pragma once

//simple in-line GDI wrapper classes for proper GDI resources de-allocation and release
struct MChGDIObj : private MChNonCopyableConcept
{
	MChGDIObj(HGDIOBJ hObj, bool bOwns = true) : 
		m_hObj(hObj)
	,	m_hOldObj(NULL)
	, m_hDC(NULL)
	,	m_bOwnsObject(bOwns)
	,	m_bSelected(false)
	{}
	virtual ~MChGDIObj() 
	{
		Deselect();
		if( m_bOwnsObject )
			::DeleteObject( m_hObj );
	}

	operator HGDIOBJ () const { return m_hObj; }
	bool operator ! () const { return m_hObj == NULL; }

	void SelectIn(HDC hDC)
	{
		M_ASSERT(hDC);
		if( !m_bSelected )
		{
			m_hDC = hDC;
			m_hOldObj = ::SelectObject(m_hDC, m_hObj);
			m_bSelected = true;
		}
	}
	virtual void Deselect()
	{
		if( m_bSelected )
		{
			::SelectObject(m_hDC, m_hOldObj);	

			m_bSelected = false;
		}
	}

protected:
	HDC m_hDC;
	HGDIOBJ m_hObj;
	HGDIOBJ m_hOldObj;
	bool m_bSelected;
	bool m_bOwnsObject;
};

//special case for pattern brush
struct MChGDIPattBrush : public MChGDIObj
{
	MChGDIPattBrush(HGDIOBJ hObj, bool bOwns = true) : MChGDIObj(hObj, bOwns), m_bAdjustBrushOrg(false) {}

	void Select(HDC hDC, bool bAdjustBrushOrg = false, int iX = 0, int iY = 0 )
	{
		M_ASSERT(hDC);
		if( !m_bSelected )
		{
			m_hDC = hDC;
			m_bAdjustBrushOrg = bAdjustBrushOrg;

			//do brush origin adjustment as neccessary
			if( m_bAdjustBrushOrg )
			{
#if !defined(UNDER_CE) && defined(_WIN32_WINDOWS) && (_WIN32_WINDOWS >= 0x0400)
				//automatic brush tracking not supported in Win9x
				UnrealizeObject( m_hObj );
#endif
				SetBrushOrgEx( m_hDC, iX, iY, &m_pntOldOrg );
			}

			m_hOldObj = ::SelectObject(m_hDC, m_hObj);
			m_bSelected = true;
		}
	}

	virtual void Deselect()
	{
		if( m_bSelected )
		{
			::SelectObject(m_hDC, m_hOldObj);		

			//reset brush origin
			if( m_bAdjustBrushOrg )
			{
#if !defined(UNDER_CE) && defined(_WIN32_WINDOWS) && (_WIN32_WINDOWS >= 0x0400)
				//automatic brush tracking not supported in Win9x
				UnrealizeObject( m_hObj );
#endif
				SetBrushOrgEx( m_hDC, m_pntOldOrg.x, m_pntOldOrg.y, NULL );
			}

			m_bSelected = false;
		}
	}

protected:
	POINT m_pntOldOrg;
	bool m_bAdjustBrushOrg;
};

//dc de-allocator
struct MChDC : private MChNonCopyableConcept
{
	MChDC() : m_hDC(NULL), m_hWnd(NULL), m_bNeedDelete(false) {}
	~MChDC() { Cleanup(); }

	inline void GetDC( HWND hWnd = NULL ) { m_hDC = ::GetDC(hWnd); m_hWnd = hWnd; }
	inline void GetWindowDC( HWND hWnd = NULL ) { m_hDC = ::GetWindowDC(hWnd); m_hWnd = hWnd; }
	inline void CreateCompatibleDC( HDC hDC = NULL ) { m_hDC = ::CreateCompatibleDC( hDC ); m_bNeedDelete = true; }

	inline bool operator ! () const { return (m_hDC == NULL); }
	inline operator HDC () const { return m_hDC; }

	inline void Cleanup() 
	{ 
		if( m_hDC ) 
		{
			if( m_bNeedDelete ) 
				::DeleteDC( m_hDC );
			else
				::ReleaseDC( m_hWnd, m_hDC ); 
		}

		m_bNeedDelete = false;
		m_hDC = NULL;
		m_hWnd = NULL;
	}

protected:
	HDC m_hDC;
	HWND m_hWnd;
	bool m_bNeedDelete;
};

//simple clip region wrapper
struct MChGDIClipRgn : private MChNonCopyableConcept
{
	MChGDIClipRgn( HDC hDC, HRGN hRgn ) : m_hDC(hDC), m_hRgn(hRgn)
	{
		int iResult = ::SelectClipRgn(m_hDC, m_hRgn);
		m_bClipped = (iResult != ERROR);
	}
	inline void UnClip() const 
	{ 
		if( m_bClipped )
		{
			int iResult = ::SelectClipRgn(m_hDC, NULL); 
			if(iResult != ERROR)
				m_bClipped = false;
		}
	}
	~MChGDIClipRgn()
	{
		UnClip();
		::DeleteObject(m_hRgn);
	}

protected:
	HDC m_hDC;
	mutable bool m_bClipped;
	HRGN m_hRgn;
};

//simple GDI value setter helper macro
#define MCH_GDI_VALUE( GDIValName, GDIValType )						\
struct MChGDI ## GDIValName : private MChNonCopyableConcept	\
{																													\
	MChGDI ## GDIValName( HDC hDC, GDIValType tNewVal ) :		\
	m_hDC(hDC)																							\
	{	m_tOldVal = ::Set ## GDIValName(m_hDC, tNewVal);	}		\
																													\
	~MChGDI ## GDIValName()																	\
	{ ::Set ## GDIValName(m_hDC, m_tOldVal); }							\
																													\
protected:																								\
	HDC m_hDC;																							\
	GDIValType m_tOldVal;																		\
};																												\

//predefined GDI value setters
MCH_GDI_VALUE( BkMode, int )
MCH_GDI_VALUE( TextColor, COLORREF )
MCH_GDI_VALUE( TextAlign, UINT )
MCH_GDI_VALUE( BkColor, COLORREF )
#ifndef UNDER_CE
MCH_GDI_VALUE( StretchBltMode, int )
#endif //UNDER_CE

//GDI point helper
struct MChPoint : public POINT
{
	MChPoint() { Reset(); }
	MChPoint(int iX, int iY) { x = iX; y = iY; }
	MChPoint( const POINT& crefOther ) { x = crefOther.x; y = crefOther.y; }
	MChPoint( const SIZE& crefOther ) { x = crefOther.cx; y = crefOther.cy; }

	inline void Reset() { memset(this, 0, sizeof(POINT)); }

	operator const POINT& () const { return *this; }
	operator POINT& () { return *this; }

	inline bool operator == ( const POINT& crefOther ) const { return (x == crefOther.x) && (y == crefOther.y); }
	inline bool operator != ( const POINT& crefOther ) const { return ! operator==(crefOther); }
	inline const POINT& operator = ( const POINT& crefOther ) { x = crefOther.x; y = crefOther.y; return *this; }
	inline void operator += ( const POINT& crefOther ) { x += crefOther.x; y += crefOther.y; }
	inline bool operator > ( const POINT& crefOther ) const { return (x > crefOther.x) || ((x == crefOther.x) && (y > crefOther.y)); }
	inline bool operator < ( const POINT& crefOther ) const { return !(*this > crefOther) && !(*this == crefOther); }

	inline MChPoint operator + ( const POINT& crefOther ) const
	{ return MChPoint(x + crefOther.x, y + crefOther.y); }
	inline MChPoint operator - ( const POINT& crefOther ) const	
	{ return MChPoint(x - crefOther.x, y - crefOther.y); }

	inline MChPoint operator - () const
	{ return MChPoint(-x, -y); }

	//distance
	inline int DistFrom(const MChPoint& crefOther) const
	{
		int iDX = x - crefOther.x;
		int iDY = y - crefOther.y;
		return static_cast<int>(sqrt( static_cast<double>(iDX * iDX + iDY * iDY) ));
	}

	//if MChUtils were included in precompile
#ifdef _MChUtils_H_
	//rotation
	MChPoint Rotate(double dAngle, bool bClockwise, bool bAngleInDeg, bool bXIsRight, bool bYIsUp) const
	{
		MChPoint pntResult(*this);
		if( dAngle )
		{
			double dRadAngle = bAngleInDeg ? MChDegToRad(dAngle) : dAngle;

			if( !bXIsRight )
				dRadAngle = MCH_PI-dRadAngle;

			if( !bYIsUp )
				dRadAngle = -dRadAngle;

			dRadAngle = bClockwise ? -dRadAngle : dRadAngle;
			double dSin = sin(dRadAngle);
			double dCos = cos(dRadAngle);

			pntResult.x = static_cast<int>(x * dCos - y * dSin);
			pntResult.y = static_cast<int>(x * dSin + y * dCos);
		}

		return pntResult;
	}
#endif //_MChUtils_H_

};
typedef std::vector<MChPoint> MChPoints;

//GDI rect wrapper
struct MChRect : public RECT
{
	MChRect() 
		{ Reset(); }
	MChRect(const POINT& crefExtent) 
		{ Set(0, 0, crefExtent.x, crefExtent.y); }
	MChRect(const RECT& crefOther) 
		{ ::CopyRect(this, &crefOther); Normalize(); }
	MChRect(const POINT& crefTopLeft, const POINT& crefBottomRight) 
		{ Set(crefTopLeft, crefBottomRight); }
	MChRect(int iLeft, int iTop, int iRight, int iBottom) 
		{ Set(iLeft, iTop, iRight, iBottom); }

	inline void Reset() { ::SetRectEmpty(this); }

	inline void Set( const POINT& crefTopLeft, const POINT& crefBottomRight )
	{ ::SetRect(this, crefTopLeft.x, crefTopLeft.y, crefBottomRight.x, crefBottomRight.y); Normalize(); }
	inline void Set( int iLeft, int iTop, int iRight, int iBottom )
	{ ::SetRect(this, iLeft, iTop, iRight, iBottom); Normalize(); }

	inline int GetWidth() const { return abs(right-left); }
	inline int GetHeight() const { return abs(bottom-top); }
	inline bool IsTall() const { return GetHeight() > GetWidth(); }
	inline bool IsSquare() const { return GetHeight() == GetWidth(); }

	inline MChPoint GetExtent() const { return MChPoint(GetWidth(), GetHeight()); }
	inline void SetExtent(int iCX, int iCY) { right = left + iCX; bottom = top + iCY; }
	inline void SetExtent(const POINT& crefExt) { SetExtent(crefExt.x, crefExt.y); }

	inline int GetXCenter() const { return left + GetWidth()/2; }
	inline int GetYCenter() const { return top + GetHeight()/2; }
	inline MChPoint GetCenter() const {	return MChPoint(GetXCenter(), GetYCenter()); }
	inline void SetCenter(int iX, int iY) { Offset(iX-GetXCenter(), iY-GetYCenter()); }
	inline void SetCenter(const POINT& crefNewCenter) { Offset(crefNewCenter.x-GetXCenter(), crefNewCenter.y-GetYCenter()); }

	inline const POINT& TopLeft() const {	return *((POINT*)this);	}
	inline POINT TopRight() const { return MChPoint(right, top); }
	inline const POINT& BottomRight() const { return *(((POINT*)this)+1); }
	inline POINT& TopLeft() {	return *((POINT*)this); }
	inline POINT& BottomRight() {	return *(((POINT*)this)+1);	}
	inline POINT BottomLeft() const { return MChPoint(left, bottom); }

	inline void Inflate(int iDeltaX, int iDeltaY) { ::InflateRect(this, iDeltaX, iDeltaY); Normalize(); }
	inline void Inflate(const POINT& crefDelta) { Inflate(crefDelta.x, crefDelta.y); }

	inline void Offset(int iOffsX, int iOffsY) { Normalize(); ::OffsetRect(this, iOffsX, iOffsY); }
	inline void Offset(const POINT& crefOffs) { Offset(crefOffs.x, crefOffs.y); }

	inline operator const RECT& () const { return *this; }
	inline operator RECT& () { return *this; }

	inline bool operator == (const RECT& crefOther) const { return ::EqualRect(this, &crefOther) != 0; }
	inline bool operator != (const RECT& crefOther) const { return ::EqualRect(this, &crefOther) == 0; }
	inline const RECT& operator = (const RECT& crefOther) { ::CopyRect(this, &crefOther); Normalize(); return *this; }

	inline bool operator ! () const { return ::IsRectEmpty(this) != 0; }

	inline bool HasPoint(const POINT& crefPoint) const { return ::PtInRect( this, crefPoint ) != 0; }
	inline MChRect IntersectRect(const MChRect& crefOther) const 
		{	MChRect rResult; ::IntersectRect(&rResult, this, &crefOther); return rResult;	}

	inline HRGN CreateRgn() const { return ::CreateRectRgn(left, top, right, bottom); }

	inline void Normalize()
	{
		int iTmp;
		if( left > right )
		{
			iTmp = right;
			right = left;
			left = iTmp;
		}

		if( top > bottom )
		{
			iTmp = bottom;
			bottom = top;
			top = iTmp;
		}
	}
};