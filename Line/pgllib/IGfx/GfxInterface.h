// GfxInterface.h: interface for the CGfxInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GFXINTERFACE_H__287E3BC9_0E37_4D0B_87B2_4EA1CEF0A76D__INCLUDED_)
#define AFX_GFXINTERFACE_H__287E3BC9_0E37_4D0B_87B2_4EA1CEF0A76D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef _GFXINTERFACE_LIB
#ifndef _GFXINTERFACE_LIB_LOADED
#define _GFXINTERFACE_LIB_LOADED
	#ifdef _MFC_7
		#ifdef _DEBUG
			#ifdef _UNICODE
				#pragma message("     _Adding library: IGfx7ud.lib: MFC7.0, Debug, UNICODE" ) 
				#pragma comment(lib, "IGfx7ud.lib")
			#else
				#pragma message("     _Adding library: IGfx7d.lib: MFC7.0, Debug, MBCS" ) 
				#pragma comment(lib, "IGfx7d.lib")
			#endif
		#else
			#ifdef _UNICODE
				#pragma message("     _Adding library: IGfx7u.lib: MFC7.0, Release, UNICODE" ) 
				#pragma comment(lib, "IGfx7u.lib")
			#else
				#pragma message("     _Adding library: IGfx7u.lib: MFC7.0, Release, UNICODE" ) 
				#pragma comment(lib, "IGfx7.lib")
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#ifdef _UNICODE
				#pragma message("     _Adding library: IGfxud.lib: MFC4.2, Debug, UNICODE" ) 
				#pragma comment(lib, "IGfxud.lib")
			#else
				#pragma message("     _Adding library: IGfxd.lib: MFC4.2, Debug, MBCS" ) 
				#pragma comment(lib, "IGfxd.lib")
			#endif
		#else
			#ifdef _UNICODE
				#pragma message("     _Adding library: IGfxu.lib: MFC4.2, Release, UNICODE" ) 
				#pragma comment(lib, "IGfxu.lib")
			#else
				#pragma message("     _Adding library: IGfxu.lib: MFC4.2, Release, UNICODE" ) 
				#pragma comment(lib, "IGfx.lib")
			#endif
		#endif
	#endif
#endif
#endif

#include "STLIGfx.h"
#include <math.h>
#include <wchar.h>

/*!
	\defgroup IGfxGroup Multiple Graphic Interface : IGfx
*/

/*! \namespace gfxinterface

  \ingroup IGfxGroup
  Namespace of the library.
*/
namespace gfxinterface
{

/*!
	\defgroup IGfxStruct Structures
*/
/*! \struct SRGBA 
	\ingroup IGfxStruct
A RGBA color structure. 
*/
typedef struct _sRGBA
{
	//! current red value
	double r;
	//! current green value
	double g;
	//! current blue value
	double b;
	//! current alpha value
	double a;
} SRGBA;

/* \struct SRectF

  \ingroup IGfxStruct
A rect (left, right, bottom, top) structure, double version
*/
typedef struct _sRectF
{
	double left;
	double top;
	double width;
	double height;
} SRectF;

/* \struct SRectI

  \ingroup IGfxStruct
A rect (left, right, bottom, top) structure, int version
*/
typedef struct _sRectI
{
	int left;
	int top;
	int width;
	int height;
} SRectI;

/* \struct SRectF

  \ingroup IGfxStruct
A point (x,y) (x,y are doubles)
*/
typedef struct _sPointF
{
	double x;
	double y;
} SPointF;

/* \struct RectFList

  \ingroup IGfxStruct
A list of SRectF structure
\sa std::list
*/
typedef std::stack<SRectF> SRectFStack;

//! \enum Text alignment
typedef enum _ETextAlignment
{
	TextAlignmentLeft=0,
	TextAlignmentRight=1,
	TextAlignmentCenter=2,
} ETextAlignment;



/*! \brief Virtual base class for graphic interfaces

  \ingroup IGfxGroup

This class contains the definitions of the functions that inherited classes must implement.
*/
class CGfxInterface
{
public:
	//! \name Construtors
	//@{
	//! Default constructor
	CGfxInterface();
	virtual ~CGfxInterface();
	//@}


	virtual void BeginPaint();
	virtual void EndPaint();

	//! \name Bounding box
	//@{
	//! Sets the main bounding box: (llx,lly) and (urx,ury) are respectively the lower-left and upper-right corner of the image.
	bool SetMainBoundingBox(int llx, int lly, int urx, int ury);

	//! Set the main bounding box
	bool SetMainBoundingBox(const CRect rect);

	//! Sets the current bounding box: (llx,lly) and (urx,ury) are respectively the lower-left and upper-right corner of the image.
	bool SetBoundingBox(int llx, int lly, int urx, int ury);

	//! Sets the bounding box: (llx,lly) and (urx,ury) are respectively the lower-left and upper-right corner of the image.
	bool SetWorldBoundingBox(double llx, double lly, double urx, double ury);

	double GetBBClipLeft() const			{	return m_rCurClip.left;};
	double GetBBClipRight() const		{	return m_rCurClip.left+m_rCurClip.width;};
	virtual double GetBBClipBottom() const		{	return m_rCurClip.top-m_rCurClip.height;};
	virtual double GetBBClipTop() const			{	return m_rCurClip.top;};
	double GetBBClipWidth() const		{	return m_rCurClip.width;};
	double GetBBClipHeight() const		{	return fabs(m_rCurClip.height);};

	double GetWorldClipLeft() const			{	return BBToWorldx(m_rCurClip.left);};
	virtual double GetWorldClipBottom() const		{	return BBToWorldy(m_rCurClip.top-m_rCurClip.height);};
	virtual double GetWorldClipTop() const			{	return BBToWorldy(m_rCurClip.top);};
	double GetWorldClipRight() const		{	return BBToWorldx(m_rCurClip.left+m_rCurClip.width);};
	double GetWorldClipWidth() const		{	return BBToWorldAbsx(m_rCurClip.width);};
	double GetWorldClipHeight() const		{	return BBToWorldAbsy(m_rCurClip.height);};

	double GetMainBBLeft() const		{	return m_rMainBoundingBox.left;};
	double GetMainBBBottom() const		{	return m_rMainBoundingBox.top-m_rMainBoundingBox.height;};
	double GetMainBBRight() const		{	return m_rMainBoundingBox.left+m_rMainBoundingBox.width;};
	double GetMainBBTop() const			{	return m_rMainBoundingBox.top;};
	double GetMainBBWidth() const		{	return m_rMainBoundingBox.width;};
	double GetMainBBHeight() const		{	return m_rMainBoundingBox.height;};

	double GetBBLeft() const		{	return m_rBoundingBox.left;};
	double GetBBBottom() const		{	return m_rBoundingBox.top-m_rBoundingBox.height;};
	double GetBBRight() const		{	return m_rBoundingBox.left+m_rBoundingBox.width;};
	double GetBBTop() const			{	return m_rBoundingBox.top;};
	double GetBBWidth() const		{	return m_rBoundingBox.width;};
	double GetBBHeight() const		{	return m_rBoundingBox.height;};

	double GetWorldLeft() const		{	return m_rWorldBoundingBox.left;};
	double GetWorldBottom() const	{	return m_rWorldBoundingBox.top-m_rWorldBoundingBox.height;};
	double GetWorldRight() const	{	return m_rWorldBoundingBox.left+m_rWorldBoundingBox.width;};
	double GetWorldTop() const		{	return m_rWorldBoundingBox.top;};
	double GetWorldWidth() const	{	return m_rWorldBoundingBox.width;};
	double GetWorldHeight() const	{	return m_rWorldBoundingBox.height;};
	//@}

	//! \name Clipping
	/*! \brief Sets a new clipping box and stores previous on a stack.

	\param llx Lower-left corner x coordinate (in World coornidates) 
	\param lly Lower-left corner y coordinate (in World coornidates) 
	\param urx Upper-right corner x coordinate (in World coornidates) 
	\param ury Upper-right corner y coordinate (in World coornidates) 

	A new clipping box is set. The previous is stored on a stack. All PushClipWorld call
	must be followed by a PopClipWorld cass.

	\sa PopClipWorld
	*/
	virtual void PushClipWorld(double llx, double lly, double urx, double ury)
	{	
		ASSERT(llx<urx); ASSERT(lly<ury);
		m_lClips.push(m_rCurClip);
		m_rCurClip.left = WorldToBBx(llx);	m_rCurClip.width = WorldToBBAbsx(urx-llx);
		m_rCurClip.top = WorldToBBy(ury);	m_rCurClip.height = WorldToBBAbsy(ury-lly); 
	};
	/*! \brief Restore previous Clip world.

	The previous clip box is set.

	\sa PushClipWorld
	*/
	virtual void PopClipWorld()
	{	ASSERT(!m_lClips.empty()); m_rCurClip=m_lClips.top(); m_lClips.pop();};
	//@}

	//! \name Graphic State
	//@{
	virtual void PushState()=0;
	virtual void PopState()=0;
	virtual void SetColor(double r, double g, double b, double a = 1) = 0;
	virtual void SetFillColor(double r, double g, double b, double a = 1) = 0;
	virtual void SetLineWidth(double width) = 0;	
	virtual void SetDash(const char* dash) = 0;
	//@}

	virtual void AddComment(const char* str)=0;

	//!\name Grids functions
	//@{
	virtual void DrawGridHor(double llx, double urx, double lly, double ury,double dy)=0;
	virtual void DrawGridVer(double llx, double urx, double lly, double ury,double dx)=0;
	//@}

	//!\name Lines, line strips, rectangle...
	//@{
	virtual void DrawRect(double llx, double lly, double urx, double ury, bool filled = false)=0;

	virtual void DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled =true)=0;
	virtual void DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled =true)=0;
	virtual void DrawLine(double x1, double y1, double x2, double y2)=0;
	virtual void DrawLineStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false)=0;
	virtual void DrawStepStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false)=0;
	virtual void DrawMultipleLineStrip(int n, int ns, double* pX, double* pY, bool open = true, bool filled  = false)=0;
	//@}

	//!\name Shapes
	//@{
	virtual void DrawBox(double llx, double lly, double dx, double dy, bool filled = false) = 0;
	virtual void DrawCircle(double cx, double cy, double radius, bool filled = false) = 0;
	virtual void DrawTriangle(double cx, double cy, double radius, bool filled = false) = 0;
	virtual void DrawSquare(double cx, double cy, double radius, bool filled = false) = 0;

	virtual void DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filed = false)=0;
	virtual void DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false)=0;
	virtual void DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false)=0;
	virtual void DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled = false)=0;
	//@}

	//!\name Text functions
	//@{
	static void GetDefaultLOGFONT(LOGFONT& lf);
	virtual void SetFont(long scale)=0;
	virtual void SetFont(const LOGFONT& logFont)=0;
	virtual void DrawTextLeft(double x, double y, const char* str, double angle = 0)=0;
	virtual void DrawTextRight(double x, double y, const char* str, double angle = 0)=0;
	virtual void DrawTextCenter(double x, double y, const char* str, double angle = 0)=0;

	virtual void DrawTextStrip(const std::vector<SPointF>& points, const std::vector<std::string>& lStrings, ETextAlignment ta = TextAlignmentCenter, double angle = 0)=0;
	double NormalizeAngle(double angle) const
	{		if (angle>=0) return angle - 360*((int)floor(angle)/360); else return angle + 360*((int)floor(angle)/360 +1); };
	//@}

	//!\name 3D functions
	//@{
	virtual void DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor)=0;
	virtual void DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double* pV, double lineWidth = 0)=0;
	//@}

	//!\name Coordinate transformations
	//@{
	virtual double BBToWorldx(double x) const=0;
	virtual double BBToWorldy(double y) const=0;
	virtual double BBToWorldAbsx(double x) const=0;
	virtual double BBToWorldAbsy(double y) const=0;

	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBx(double x) const=0;
	//! Transform world y coordinate to file coordinate y
	virtual double WorldToBBy(double y) const=0;
	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBAbsx(double x) const=0;	
	//! Transform absolute world y coordinate to file coordinate y
	virtual double WorldToBBAbsy(double y) const=0;
	//@}
protected:
	//! main bounding box llx lly width height
	SRectI m_rMainBoundingBox;
	//! current bonding box llx lly width height
	SRectI m_rBoundingBox;
	//! llx lly width height
	SRectF m_rWorldBoundingBox;
	//! Current clip coordinates
	SRectF	m_rCurClip;
	// Stack of clip coordinates
	SRectFStack m_lClips;
};

}

#endif // !defined(AFX_GFXINTERFACE_H__287E3BC9_0E37_4D0B_87B2_4EA1CEF0A76D__INCLUDED_)
