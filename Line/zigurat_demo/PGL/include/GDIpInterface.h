// GDIpInterface.h: interface for the CGDIpInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIPINTERFACE_H__61081227_2FA9_4B5E_9293_7BA16162781F__INCLUDED_)
#define AFX_GDIPINTERFACE_H__61081227_2FA9_4B5E_9293_7BA16162781F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "GfxInterface.h"
#include <objbase.h>
#include <gdiplus.h>
#include "GdiRect.h"

namespace gfxinterface
{


/*! \struct SGDIpState 
	\ingroup IGfxStruct
GDI+ state
*/
typedef struct _SGDIpState
{
	Gdiplus::GraphicsState m_gState;
	Gdiplus::Color m_curColor;
	Gdiplus::Color m_fillColor;
	LOGFONT m_font;
	Gdiplus::REAL m_lineWidth;
	std::list<Gdiplus::REAL> m_dash;
} SGDIpState;

typedef std::stack<SGDIpState> SGdipStateStack;
typedef std::list<Gdiplus::RectF> CRectFList;

/* \brief GDI+ interface

  \ingroup IGfxGroup

*/
class CGDIpInterface : public CGfxInterface  
{
public:
	CGDIpInterface();
	virtual ~CGDIpInterface();

	void SetGraphics(Gdiplus::Graphics* pGraphics) {	ASSERT(pGraphics); m_pGraphics = pGraphics;};
	virtual void BeginPaint();
	virtual void EndPaint();

	virtual void PushClipWorld(double llx, double lly, double urx, double ury)
	{
		CGfxInterface::PushClipWorld(llx,lly,urx,ury);
		Gdiplus::RectF clipRectF(GetBBClipLeft(),GetBBClipTop(),GetBBClipWidth(),GetBBClipHeight());  
		m_pGraphics->SetClip(clipRectF);	
	};
	virtual void PopClipWorld()
	{	
		CGfxInterface::PopClipWorld();
		m_pGraphics->ResetClip();
	};

	virtual void PushState();
	virtual void PopState();

	Gdiplus::RectF MeasureString(LPCSTR str);
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	virtual void AddComment(const char* str){};

	virtual void SetColor(double r, double g, double b, double a = 1)
	{	m_curState.m_curColor = Gdiplus::Color((BYTE)floor(a*255),(BYTE)floor(r*255),(BYTE)floor(g*255),(BYTE)floor(b*255));};
	virtual void SetFillColor(double r, double g, double b, double a = 1)
	{	m_curState.m_fillColor = Gdiplus::Color((BYTE)floor(a*255),(BYTE)floor(r*255),(BYTE)floor(g*255),(BYTE)floor(b*255));};
	virtual void SetLineWidth(double width)
	{	m_curState.m_lineWidth = (Gdiplus::REAL)__max(0,width);};	
	virtual void SetDash(const char* dash);

	virtual void DrawGridHor(double llx, double urx, double lly, double ury,double dy);
	virtual void DrawGridVer(double llx, double urx, double lly, double ury,double dx);

	virtual void DrawRect(double llx, double lly, double urx, double ury, bool filled = false);

	virtual void DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawLine(double x1, double y1, double x2, double y2);
	virtual void DrawLineStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false);
	virtual void DrawStepStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false);
	virtual void DrawMultipleLineStrip(int n, int ns, double* pX, double* pY, bool open = true, bool filled  = false);

	virtual void DrawBox(double llx, double lly, double dx, double dy, bool filled = false);
	virtual void DrawCircle(double cx, double cy, double radius, bool filled = false);
	virtual void DrawTriangle(double cx, double cy, double radius, bool filled = false);
	virtual void DrawSquare(double cx, double cy, double radius, bool filled = false);

	virtual void DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filed = false);
	virtual void DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);

	virtual void SetFont(long scale){	m_curState.m_font.lfHeight=scale;};
	virtual void SetFont(const LOGFONT& logFont){ m_curState.m_font=logFont;};
	virtual void DrawTextLeft(double x, double y, const char* str, double angle = 0);
	virtual void DrawTextRight(double x, double y, const char* str, double angle = 0);
	virtual void DrawTextCenter(double x, double y, const char* str, double angle = 0);

	virtual void DrawTextStrip(const std::vector<SPointF>& vPoints, const std::vector<std::string>& lStrings, ETextAlignment ta = TextAlignmentCenter, double angle = 0);

	virtual void DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor);
	virtual void DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double* pV, double lineWidth = 0){};

	virtual double BBToWorldx(double x) const
	{	return GetWorldLeft()+(x-(double)GetBBLeft())/(double)(GetBBWidth())
			*(double)(GetWorldWidth());};
	virtual double BBToWorldy(double y) const
	{	return GetWorldTop()+(y-(double)GetBBTop())/(double)(GetBBHeight())
			*(double)(GetWorldHeight());};
	virtual double BBToWorldAbsx(double x) const
	{	return x/(double)(GetBBWidth())*(double)(GetWorldWidth());};
	virtual double BBToWorldAbsy(double y) const
	{	return y/(double)(GetBBHeight())*(double)(GetWorldHeight());};

	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBx(double x) const
	{	return GetBBLeft()+(x-(double)GetWorldLeft())/(double)(GetWorldWidth())
			*(double)(GetBBWidth());};
	//! Transform world y coordinate to file coordinate y
	virtual double WorldToBBy(double y) const
	{	return GetMainBBBottom() + GetMainBBHeight() 
		- ((y-(double)GetWorldBottom())/(double)(GetWorldHeight())
			*(double)(GetBBHeight()) + GetBBBottom());};
	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBAbsx(double x) const
	{	return x/(double)(GetWorldWidth())*(double)(GetBBWidth());};
	//! Transform absolute world y coordinate to file coordinate y
	virtual double WorldToBBAbsy(double y) const
	{	return y/(double)(GetWorldHeight())*(double)(GetBBHeight());};

	virtual double GetWorldClipBottom() const		{	return BBToWorldy(m_rCurClip.top);};
	virtual double GetWorldClipTop() const			{	return BBToWorldy(m_rCurClip.top+m_rCurClip.height);};

	virtual double GetBBClipBottom() const		{	return m_rCurClip.top+m_rCurClip.height;};
	virtual double GetBBClipTop() const			{	return m_rCurClip.top;};

protected:
	void SetCurPenState(Gdiplus::Pen& pen);
	Gdiplus::Graphics* m_pGraphics;
	SGDIpState m_curState;
	SGdipStateStack	m_lStates;
private:
	Gdiplus::REAL* m_pDash;
	WCHAR m_wBuffer[2048];
};

}
#endif // !defined(AFX_GDIPINTERFACE_H__61081227_2FA9_4B5E_9293_7BA16162781F__INCLUDED_)
