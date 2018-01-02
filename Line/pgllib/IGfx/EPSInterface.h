// EPSInterface.h: interface for the CEPSInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPSINTERFACE_H__C35451D2_234F_4CA2_84C3_D860EA95D014__INCLUDED_)
#define AFX_EPSINTERFACE_H__C35451D2_234F_4CA2_84C3_D860EA95D014__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileGfxInterface.h"

namespace gfxinterface
{

/*! \brief Acutal eps state

  \ingroup IGfxGroup
This structure is used internaly in CEPSWriter to keep track of the current postscript graphic state.
The following states are tracked:
<ul>
<li>color components, RGB,
<li>line width,
<li>line dashing.
</ul>
*/
typedef struct _SEPSState
{
	//! current color
	SRGBA curcol;
	//! stroke color
	SRGBA strokecol;
	//! fill color
	SRGBA fillcol;
	//! current linewidth
	double linewidth;		
	//! current dash style
	std::string dash;
	//! current font
	LOGFONT m_font;
} SEPSState;

/*! \brief Pile of graphic states

  \ingroup IGfxGroup
*/
typedef std::list<SEPSState> EPSStatePile;

/*! \brief Class to create EPS files

  \ingroup IGfxGroup

	This class is designed to create your own eps files.

\sa CEPSState
*/
class CEPSInterface : public CFileGfxInterface  
{
public:
	//! Default constructor, sFileName is the name of the created EPS file.
	CEPSInterface(const char* sFileName = "untitled");
	//! Destrutor
	virtual ~CEPSInterface();

	//! Open EPS file and writes header
	virtual bool Open(const char* filename = NULL);
	//! Closes EPS and flushes all actions
	virtual void Close();
	virtual void AddComment(const char* str);

	virtual void PushClipWorld(double llx, double lly, double urx, double ury);
	virtual void PopClipWorld();
	virtual void PushState();
	virtual void PopState();
	void Fill();

	virtual void DrawGridHor(double llx, double urx, double lly, double ury,double dy);
	virtual void DrawGridVer(double llx, double urx, double lly, double ury,double dx);

	virtual void SetColor(double r, double g, double b, double a = 1);
	virtual void SetFillColor(double r, double g, double b, double a = 1);
	virtual void SetLineWidth(double width);	
	virtual void SetDash(const char* dash);

	virtual void DrawRect(double llx, double lly, double urx, double ury, bool filled = false);
	virtual void DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawLine(double x1, double y1, double x2, double y2);
	virtual void DrawLineStrip(int n, double* pX, double* pY, bool open = true, bool filled = false);
	virtual void DrawStepStrip(int n, double* pX, double* pY, bool open = true, bool filled = false);

	virtual void DrawMultipleLineStrip(int n, int ns, double* pX, double* pY, bool open = true, bool filled  = false){};

	virtual void DrawBox(double llx, double lly, double dx, double dy, bool filled = false);
	virtual void DrawCircle(double cx, double cy, double radius, bool filled = false);
	virtual void DrawTriangle(double cx, double cy, double radius, bool filled = false);
	virtual void DrawSquare(double cx, double cy, double radius, bool filled = false);

	virtual void DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filed = false);
	virtual void DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);

	virtual void SetFont(long scale);
	virtual void SetFont(const LOGFONT& logFont);
	virtual void DrawTextLeft(double x, double y, const char* str, double angle = 0);
	virtual void DrawTextRight(double x, double y, const char* str, double angle = 0);
	virtual void DrawTextCenter(double x, double y, const char* str, double angle = 0);

	virtual void DrawTextStrip(const std::vector<SPointF>& vPoints, const std::vector<std::string>& vStrings, ETextAlignment ta = TextAlignmentCenter, double angle = 0);

	virtual void DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor);
	virtual void DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double* pV, double lineWidth = 1);

	virtual double BBToWorldx(double x) const
	{	return GetWorldLeft()+(x-(double)GetBBLeft())/(double)(GetBBWidth())
			*(double)(GetWorldWidth());};
	virtual double BBToWorldy(double y) const
	{	return GetWorldBottom()+(y-(double)GetBBBottom())/(double)(GetBBHeight())
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
	{	return GetBBBottom()+(y-(double)GetWorldBottom())/(double)(GetWorldHeight())
			*(double)(GetBBHeight());};

	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBAbsx(double x) const
	{	return x/(double)(GetWorldWidth())*(double)(GetBBWidth());};
	//! Transform absolute world y coordinate to file coordinate y
	virtual double WorldToBBAbsy(double y) const
	{	return y/(double)(GetWorldHeight())*(double)(GetBBHeight());};

protected:
	void PutStrokeColorString();
	void PutFillColorString();
	void InitState();
	virtual void WriteHeader();
private:
	SEPSState m_state;
	EPSStatePile m_lStates;
};

}
#endif // !defined(AFX_EPSINTERFACE_H__C35451D2_234F_4CA2_84C3_D860EA95D014__INCLUDED_)
