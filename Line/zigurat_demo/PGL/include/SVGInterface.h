// SVGInterface.h: interface for the CSVGInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGINTERFACE_H__AE98E121_D266_4F12_9036_B592D8F5EB02__INCLUDED_)
#define AFX_SVGINTERFACE_H__AE98E121_D266_4F12_9036_B592D8F5EB02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileGfxInterface.h"

namespace gfxinterface
{

/*! \struct SSVGState 
	\ingroup IGfxStruct
SVG state
*/
typedef struct _SSVGState
{
	//! font structure
	LOGFONT m_font;
	//! current stroke color
	SRGBA strokecol;
	//! current fill color
	SRGBA fillcol;
	//! current linewidth
	double linewidth;		
	//! current dash style
	std::string dash;
} SSVGState;


/* \brief SVG interface

  \ingroup IGfxGroup

*/
class CSVGInterface : public CFileGfxInterface  
{
public:
	CSVGInterface(const char* sFileName = "untitled", bool bZipped = true);
	virtual ~CSVGInterface();

	virtual bool Open(const char* filename = NULL);
	virtual void Close();
	virtual void AddComment(const char* str){};

	virtual void PushClipWorld(double llx, double lly, double urx, double ury);
	virtual void PopClipWorld();
	virtual void PushState(){};
	virtual void PopState(){};

	virtual void SetDash(const char* dash);
	virtual void SetLineWidth(double width);
	virtual void SetFont(long scale);
	virtual void SetFont(const LOGFONT& logFont);
	virtual void SetColor(double r, double g, double b, double a = 1);
	virtual void SetFillColor(double r, double g, double b, double a = 1);

	virtual void DrawGridHor(double llx, double urx, double lly, double ury,double dy);
	virtual void DrawGridVer(double llx, double urx, double lly, double ury,double dx);

	virtual void DrawRect(double llx, double lly, double urx, double ury, bool filled = false);

	virtual void DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled =true);
	virtual void DrawLine(double x1, double y1, double x2, double y2);
	virtual void DrawLineStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false);
	virtual void DrawStepStrip(int n, double* pX, double* pY, bool open = true, bool filled  = false);

	virtual void DrawMultipleLineStrip(int n, int ns, double* pX, double* pY, bool open = true, bool filled  = false){};

	virtual void DrawBox(double llx, double lly, double dx, double dy, bool filled = false) ;
	virtual void DrawCircle(double cx, double cy, double radius, bool filled = false) ;
	virtual void DrawTriangle(double cx, double cy, double radius, bool filled = false) ;
	virtual void DrawSquare(double cx, double cy, double radius, bool filled = false) ;

	virtual void DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filled = false);
	virtual void DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);
	virtual void DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled = false);


	virtual void DrawTextLeft(double x, double y, const char* str, double angle = 0) ;
	virtual void DrawTextRight(double x, double y, const char* str, double angle = 0) ;
	virtual void DrawTextCenter(double x, double y, const char* str, double angle = 0) ;

	virtual void DrawTextStrip(const std::vector<SPointF>& points, const std::vector<std::string>& lStrings, ETextAlignment ta = TextAlignmentCenter, double angle = 0);

	virtual void DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor);
	virtual void DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double* pV, double lineWidth = 0);

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
	{	return GetMainBBBottom() + GetMainBBHeight() 
		- ((y-(double)GetWorldBottom())/(double)(GetWorldHeight())
			*(double)(GetBBHeight()) + GetBBBottom());};
	//! Transform world x coordinate to file coordinate x
	virtual double WorldToBBAbsx(double x) const
	{	return x/(double)(GetWorldWidth())*(double)(GetBBWidth());};
	//! Transform absolute world y coordinate to file coordinate y
	virtual double WorldToBBAbsy(double y) const
	{	return -y/(double)(GetWorldHeight())*(double)(GetBBHeight());};

protected:
	void InitState();
	void PutFillAlphaString(std::ostrstream& ssout);
	void PutStrokeAlphaString(std::ostrstream& ssout);
	void PutStrokeColorString(std::ostrstream& ssout);
	void PutFillColorString(std::ostrstream& ssout,bool filled);
	//! Write
	virtual void WriteHeader();
private:
	SSVGState m_state;
	bool m_bZipped;
	std::ostrstream* m_pssFile;
	std::ostrstream* m_pssDefs;
	std::ostrstream* m_pssMain;
	long m_liCurDef;
};

}
#endif // !defined(AFX_SVGINTERFACE_H__AE98E121_D266_4F12_9036_B592D8F5EB02__INCLUDED_)
