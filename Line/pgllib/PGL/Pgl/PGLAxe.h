/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/

// PGLAxe.h: interface for the CPGLAxe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLAXE2D_H__4DACBB7A_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_PGLAXE2D_H__4DACBB7A_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#include "PGLObject.h"
#include "PGLText.h"
#include "PGLView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! \brief Axis.

\ingroup PGLTextGroup

Draws the axis, grids, labels and title. 
The user can switch on/off the grids, turn on auto-updated of axis labelling.

Not working yet : logarithmic scales.

\sa CPGLText
\sa CPGLGraph
*/
class PGL_EXT_CLASS CPGLAxe2D  : public CPGLObject
{
public:
	DECLARE_SERIAL(CPGLAxe2D);

	//! \name Constructors
	//@{
	//! default constructor
	CPGLAxe2D(CPGLView2D* pView=NULL);
	//! copy constructor
	CPGLAxe2D(const CPGLAxe2D& a);
	//! assignement constructor
	CPGLAxe2D& operator=(const CPGLAxe2D& a);
	//! returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLAxe2D(*this); return pCopy; };
	virtual ~CPGLAxe2D();
	//@}


	void SetView(CPGLView2D* pView)
	{	ASSERT_VALID(pView); m_pView=pView; UpdateLabels();};
	CPGLView2D* GetView()
	{	return m_pView;};
	void SetLimits(int iaxe, double _start,double _end);
	void GetLimits(int iaxe, double* pLimits);

	void Delete();
	void UpdateLabels();

	//! Grows the extents in pExt to show axe.
	void GrowExtent(double* pExt);

	CPGLText* GetLabel(int iLabel) {	ASSERT(iLabel>=0 && iLabel<4); return &m_pLabels[iLabel];};
	CPGLText* GetBottomLabel() {	return &m_pLabels[0];}	
	CPGLText* GetLeftLabel() {	return &m_pLabels[1];}	
	CPGLText* GetRightLabel() {	return &m_pLabels[2];}	
	CPGLText* GetTopLabel() {	return &m_pLabels[3];}	
	CPGLText* GetTitle() {	return &m_pLabels[3];}	

	CPGLText* GetNumber(int i) {	ASSERT(i>=0 && i<4); return &m_pNumbers[i];};
	CPGLText* GetBottomNumber() {	return &m_pNumbers[0];}	
	CPGLText* GetLeftNumber() {	return &m_pNumbers[1];}	
	CPGLText* GetRightNumber() {	return &m_pNumbers[2];}	
	CPGLText* GetTopNumber() {	return &m_pNumbers[3];}	

	void SetLabel(int iLabel, const CPGLText& newLabel);
	void SetLabel(int iLabel, const CString& newLabel);

	void SetBottomLabel(const CPGLText& newLabel)	{ SetLabel(0,newLabel); };
	void SetBottomLabel(const CString& newLabel)	{ SetLabel(0,newLabel); };
	void SetLeftLabel(const CPGLText& newLabel)		{ SetLabel(1,newLabel); };
	void SetLeftLabel(const CString& newLabel)		{ SetLabel(1,newLabel); };
	void SetRightLabel(const CPGLText& newLabel)	{ SetLabel(2,newLabel); };
	void SetRightLabel(const CString& newLabel)		{ SetLabel(2,newLabel); };
	void SetTopLabel(const CPGLText& newLabel)		{ SetLabel(3,newLabel); };
	void SetTopLabel(const CString& newLabel)		{ SetLabel(3,newLabel); };
	void SetTitle(const CPGLText& tTitle)			{ SetLabel(3,tTitle); };
	void SetTitle(const CString& tTitle)			{ SetLabel(3,tTitle); };

	void SetNumber(int i, const CPGLText& textType) { ASSERT(i>=0 || i<4); m_pNumbers[i] = textType;};
	void SetBottomNumber(const CPGLText& textType)	{ SetNumber(0,textType); };
	void SetLeftNumber(const CPGLText& textType)	{ SetNumber(1,textType); };
	void SetRightNumber(const CPGLText& textType)	{ SetNumber(2,textType); };
	void SetTopNumber(const CPGLText& textType)		{ SetNumber(3,textType); };

	BOOL IsTimeLabel() const							{	return m_bTimeLabel;};
	const CTime& GetTimeLabelOrig() const				{	return m_tTimeLabelOrig;};
	const CTimeSpan& GetTimeLabelStep() const			{	return m_tsDt;};
	const CString& GetTimeLabelString() const			{	return m_sTimeLabel;};
	void SetTimeLabel(BOOL yes = TRUE)					{	m_bTimeLabel=yes;};
	void SetTimeLabelFormat(const CTime& _tOrig, const CTimeSpan& _tsDt, LPCSTR _szTimeLabel)		
	{	m_tTimeLabelOrig = _tOrig; m_tsDt = _tsDt; m_sTimeLabel = _szTimeLabel;};
	void SetTimeLabelFormat(const COleDateTime& _tOrig, const COleDateTimeSpan& _tsDt, LPCSTR _szTimeLabel);


	BOOL IsShowGrid(int i) const {	ASSERT(i==0 || i==1); return m_pGridVisible[i];};
	void SetShowGrid(int i,BOOL on=TRUE) {	ASSERT(i==0 || i==1); m_pGridVisible[i]=on;};
	BOOL IsAutoSteps(int i) const {	ASSERT(i==0 || i==1); return m_pAutoSteps[i];};
	void SetAutoSteps(int i, BOOL on=TRUE) {	ASSERT(i==0 || i==1); m_pAutoSteps[i]=on;};
	double GetGridStep(int i) const {	ASSERT(i>=0 && i<2); return m_pSteps[i];};
	void SetGridStep(int i, double step) {	ASSERT(i>=0 && i<2); ASSERT(step > 0); m_pSteps[i]=step;};

	BOOL IsShowLabel(int i) const {	ASSERT(i>=0 && i<4); return m_pLabels[i].IsVisible();};
	void SetShowLabel(int i,BOOL on=TRUE) {	ASSERT(i>=0 && i<4); m_pLabels[i].Show(on);};

	BOOL IsShowNumbers(int i) const {	ASSERT(i>=0 && i<4); return m_pNumbers[i].IsVisible();};
	void SetShowNumbers(int i,BOOL on=TRUE) {	ASSERT(i>=0 && i<4); m_pNumbers[i].Show(on);};

	//! \name Numbering position
	//@{
	double GetNumberPos(int i) const	{	ASSERT(i>=0 && i<4); return m_pNumberPos[i]; };
	double GetBottomNumberPos() const	{	return m_pNumberPos[0]; };
	double GetLeftNumberPos() const		{	return m_pNumberPos[1]; };
	double GetRightNumberPos() const	{	return m_pNumberPos[2]; };
	double GetTopNumberPos() const		{	return m_pNumberPos[3]; };

	void SetNumberPos(int i, double pos)	{	ASSERT(i>=0 && i<4); m_pNumberPos[i] = __max(0, __min(1, pos));};
	void SetBottomNumberPos(double pos)		{	SetNumberPos(0,pos);};
	void SetLeftNumberPos(double pos)		{	SetNumberPos(1,pos);};
	void SetRightNumberPos(double pos)		{	SetNumberPos(2,pos);};
	void SetTopNumberPos(double pos)		{	SetNumberPos(3,pos);};
	//@}

	//! \name Main ticks
	//@{
	void SetMainTicksSize(int i, double pixels)		{ ASSERT(i>=0 && i<4); m_pMainTicksSize[i] = pixels;};
	void SetBottomMainTicksSize(double pixels)		{	m_pMainTicksSize[0] = pixels;};
	void SetLeftMainTicksSize(double pixels)		{	m_pMainTicksSize[1] = pixels;};
	void SetRightMainTicksSize(double pixels)		{	m_pMainTicksSize[2] = pixels;};
	void SetTopMainTicksSize(double pixels)			{	m_pMainTicksSize[3] = pixels;};

	double GetMainTicksSize(int i) const		{	ASSERT(i>=0 && i<4); return m_pMainTicksSize[i]; };
	double GetBottomMainTicksSize()const		{	return m_pMainTicksSize[0];};
	double GetLeftMainTicksSize()const			{	return m_pMainTicksSize[1];};
	double GetRightMainTicksSize()const	{	return m_pMainTicksSize[2];};
	double GetTopMainTicksSize()const		{	return m_pMainTicksSize[3];};
	//@}

	//! \name Secondary ticks (size and number)
	//@{
	void SetSecondTicksSize(int i, double pixels)		{ ASSERT(i>=0 && i<4); m_pSecondTicksSize[i] = pixels;};
	void SetBottomSecondTicksSize(double pixels)		{	m_pSecondTicksSize[0] = pixels;};
	void SetLeftSecondTicksSize(double pixels)		{	m_pSecondTicksSize[1] = pixels;};
	void SetRightSecondTicksSize(double pixels)		{	m_pSecondTicksSize[2] = pixels;};
	void SetTopSecondTicksSize(double pixels)			{	m_pSecondTicksSize[3] = pixels;};

	double GetSecondTicksSize(int i) const		{	ASSERT(i>=0 && i<4); return m_pSecondTicksSize[i]; };
	double GetBottomSecondTicksSize()const		{	return m_pSecondTicksSize[0];};
	double GetLeftSecondTicksSize()const			{	return m_pSecondTicksSize[1];};
	double GetRightSecondTicksSizeBottom()const	{	return m_pSecondTicksSize[2];};
	double GetTopSecondTicksSizeBottom()const		{	return m_pSecondTicksSize[3];};

	void SetSecondTicksNb(int i, UINT nb)		{ ASSERT(i>=0 && i<4); m_pSecondTicksNb[i] = __max(0,nb);};
	void SetBottomSecondTicksNb(UINT nb)		{	m_pSecondTicksNb[0] = __max(0,nb);};
	void SetLeftSecondTicksNb(UINT nb)			{	m_pSecondTicksNb[1] = __max(0,nb);};
	void SetRightSecondTicksNb(UINT nb)			{	m_pSecondTicksNb[2] = __max(0,nb);};
	void SetTopSecondTicksNb(UINT nb)			{	m_pSecondTicksNb[3] = __max(0,nb);};

	double GetSecondTicksNb(int i) const		{	ASSERT(i>=0 && i<4); return m_pSecondTicksNb[i]; };
	double GetBottomSecondTicksNb()const		{	return m_pSecondTicksNb[0];};
	double GetLeftSecondTicksNb()const			{	return m_pSecondTicksNb[1];};
	double GetRightSecondTicksNb()const			{	return m_pSecondTicksNb[2];};
	double GetTopSecondTicksNb()const			{	return m_pSecondTicksNb[3];};
	//@}
	
	BOOL IsLogAxis(int i) const {	ASSERT(i==0 || i==1); return m_pLogAxis[i];};
	void SetLogAxis(int i, BOOL logstate) {	ASSERT(i==0 || i==1); m_pLogAxis[i]=logstate;};

	CPGLObject* FindObject(UINT ID);
	void AddPropertyPage(CPropertySheet* pPropSheet);
	HTREEITEM AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent);

	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);
	void DrawGridGfx(int iaxe,gfxinterface::CGfxInterface& gfx);
	void DrawNumbersGfx(gfxinterface::CGfxInterface& gfx);
	void DrawLinesGfx(gfxinterface::CGfxInterface& gfx);

	void GenerateSteps(int iaxe);

	void UnClipGfx(gfxinterface::CGfxInterface& gfx);
	void ClipGfx(gfxinterface::CGfxInterface& gfx);
	void Pan(double dx, double dy);

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif

protected:
	//! a pointer to the associated view
	CPGLView2D* m_pView;
	//! axes labels: [bottom, left, right, top], ...
	CPGLText m_pLabels[4];
	//! axes numbering
	CPGLText m_pNumbers[4];
	//! axes numbering position
	double m_pNumberPos[4];
	//! beginning value of axes
	double m_pStarts[2];
	//! Main ticks size
	double m_pMainTicksSize[4];
	//! Secondary Ticks size
	double m_pSecondTicksSize[4];
	//! number of secondary ticks
	UINT m_pSecondTicksNb[4];
	//! end value of axes
	double m_pEnds[2];
	//! length of steps for numbering
	double m_pSteps[2];
	//! true if step is computed automaticaly
	BOOL m_pAutoSteps[2];
	//! log axis
	BOOL m_pLogAxis[2];
	//! Time labels
	BOOL m_bTimeLabel;
	//! Time step : 1 in coordinate = 1 time step
	CTimeSpan m_tsDt;
	//! Time at 0.
	CTime m_tTimeLabelOrig;
	//! String describing time label
	CString m_sTimeLabel;
	//! visibility of grids
	BOOL m_pGridVisible[2];
	//! Width of respective borders
	RECT m_rBorders;
};

#endif // !defined(AFX_PGLAXE2D_H__4DACBB7A_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
