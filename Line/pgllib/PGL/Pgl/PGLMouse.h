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
// mouse.h: interface for the CPGLMouse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLMOUSE_H__338966CD_1C93_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_PGLMOUSE_H__338966CD_1C93_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*!\brief A mouse.

  Takes care of handling the mouse moves or pressed buttons.
*/
class PGL_EXT_CLASS CPGLMouse  
{
public:
	/// default constructor
	CPGLMouse()
	{ m_bLDown=m_bRDown=m_bLMoving=m_bRMoving=FALSE;};
	/// destructor
	~CPGLMouse()
	{};
	
	/// the left button has been pressed at position x,y
	void LeftBtnPressed(int x,int y)
	{ m_iCLBx=m_iLBx=x; m_iCLBy=m_iLBy=y; m_bLDown=TRUE;};
	/// the right button has been pressed at position x,y
	void RightBtnPressed(int x,int y)
	{ m_iCRBx=m_iRBx=x; m_iCRBy=m_iRBy=y; m_bRDown=TRUE;};
	/// the left button has been released, returns x,y as the position of the mouse when clicked
	void LeftBtnReleased(int& x,int& y)
	{ m_bLDown=FALSE; x=m_iCLBx; y=m_iCLBy;};
	/// the left button has been released
	void RightBtnReleased(int& x,int& y)
	{ m_bRDown=FALSE; x=m_iCRBx; y=m_iCRBy;};

	/// returns true if left button down. In that case, _x,_y is the last mouse position
	BOOL IsLeftBtnDown(int& _x,int &_y)
	{ if (m_bLDown) {_x=m_iLBx; _y=m_iLBy;} return m_bLDown;};
	/// returns true if right button down. In that case, _x,_y is the last mouse position
	BOOL IsRightBtnDown(int& _x,int &_y)
	{ if (m_bRDown) {_x=m_iRBx; _y=m_iRBy;} return m_bRDown;};

	void GetLeftLastPos(int& _x, int& _y) const
	{ _x=m_iLBx; _y=m_iLBy;};
	void GetRightLastPos(int& _x, int& _y) const
	{ _x=m_iRBx; _y=m_iRBy;};
	void GetLeftFirstPos(int& _x, int& _y) const
	{ _x=m_iCLBx; _y=m_iCLBy;};
	void GetRightFirstPos(int& _x, int& _y) const
	{ _x=m_iCRBx; _y=m_iCRBy;};

	void UpdateLeftPos(int _x, int _y)
	{ m_iLBx=_x; m_iLBy=_y;};
	void UpdateRightPos(int _x, int _y)
	{ m_iRBx=_x; m_iRBy=_y;};

	void LeftMove() { m_bLMoving=TRUE;};
	void RightMove() { m_bLMoving=TRUE;};
	void Stop() { m_bLMoving=m_bRMoving=FALSE;};
	BOOL IsLeftMoving() const {return (m_bLMoving && m_bLDown);};
	BOOL IsRightMoving() const {return (m_bLMoving && m_bRDown);};

protected:
	/// position of the pointer when the left button was clicked
	int m_iCLBx,m_iCLBy;
	/// position of the pointer when the right button was clicked
	int m_iCRBx,m_iCRBy;
	/// last position of the pointer
	int m_iLBx,m_iLBy;
	/// position of the pointer
	int m_iRBx,m_iRBy;
	/// true if left button pressed
	BOOL m_bLDown;
	/// true if right button pressed
	BOOL m_bRDown;
	/// true if mouse moving with left button down
	BOOL m_bLMoving;
	/// true if mouse moving with left button down
	BOOL m_bRMoving;
};

#endif // !defined(AFX_MOUSECLASS_H__338966CD_1C93_11D4_8D89_00409503B978__INCLUDED_)
