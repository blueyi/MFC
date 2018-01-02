实现的头文件combocolorpicker.h 

#if !defined(afx_combocolorpicker_h__b2348841_5541_11d1_8756_00a0c9181e86__included_)
#define afx_combocolorpicker_h__b2348841_5541_11d1_8756_00a0c9181e86__included_

#if _msc_ver >= 1000
#pragma once
#endif // _msc_ver >= 1000
// combocolorpicker.h : header file
// ? 1997 baldvin hansson

/////////////////////////////////////////////////////////////////////////////
// ccombocolorpicker window

class ccombocolorpicker : public ccombobox
{
// construction
public:
	ccombocolorpicker();

// attributes
private:
	bool m_binitialized;
	static colorref m_rgstandardcolors[];
public:

// operations
private:
	void initializedata();
public:
	colorref getselectedcolor();

// overrides
	// classwizard generated virtual function overrides
	//{{afx_virtual(ccombocolorpicker)
	protected:
	virtual void presubclasswindow();
	//}}afx_virtual
	virtual void drawitem(lpdrawitemstruct lpdrawitemstruct);

// implementation
public:
	virtual ~ccombocolorpicker();

	// generated message map functions
protected:
	//{{afx_msg(ccombocolorpicker)
	afx_msg int oncreate(lpcreatestruct lpcreatestruct);
	//}}afx_msg

	declare_message_map()
};

/////////////////////////////////////////////////////////////////////////////

//{{afx_insert_location}}
// microsoft developer studio will insert additional declarations immediately before the previous line.

#endif // !defined(afx_combocolorpicker_h__b2348841_5541_11d1_8756_00a0c9181e86__included_)


实现文件
combocolorpicker.cpp 


// combocolorpicker.cpp : implementation file
// ? 1997 baldvin hansson

#include "stdafx.h"
#include "combocolorpicker.h"

#ifdef _debug
#define new debug_new
#undef this_file
static char this_file[] = __file__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ccombocolorpicker

colorref ccombocolorpicker::m_rgstandardcolors[] = {
	rgb(0, 0, 0),			// black
	rgb(255, 255, 255),		// white
	rgb(128, 0, 0),			// dark red
	rgb(0, 128, 0),			// dark green
	rgb(128, 128, 0),		// dark yellow
	rgb(0, 0, 128),			// dark blue
	rgb(128, 0, 128),		// dark magenta
	rgb(0, 128, 128),		// dark cyan
	rgb(192, 192, 192),		// light grey
	rgb(128, 128, 128),		// dark grey
	rgb(255, 0, 0),			// red
	rgb(0, 255, 0),			// green
	rgb(255, 255, 0),		// yellow
	rgb(0, 0, 255),			// blue
	rgb(255, 0, 255),		// magenta
	rgb(0, 255, 255),		// cyan
	};

ccombocolorpicker::ccombocolorpicker()
{
	m_binitialized = false;
}

ccombocolorpicker::~ccombocolorpicker()
{
}


begin_message_map(ccombocolorpicker, ccombobox)
	//{{afx_msg_map(ccombocolorpicker)
	on_wm_create()
	//}}afx_msg_map
end_message_map()

/////////////////////////////////////////////////////////////////////////////
// ccombocolorpicker message handlers

int ccombocolorpicker::oncreate(lpcreatestruct lpcreatestruct) 
{
	if (ccombobox::oncreate(lpcreatestruct) == -1)
		return -1;
	
	initializedata();

	return 0;
}

void ccombocolorpicker::presubclasswindow() 
{
	initializedata();
	
	ccombobox::presubclasswindow();
}

void ccombocolorpicker::initializedata()
{
	int nitem;

	if (m_binitialized)
		return;

	for (int ncolor = 0; ncolor hdc))
		return;

	colorref rgbtextcolor = dc.gettextcolor();
	colorref rgbbkcolor = dc.getbkcolor();

	if (lpdrawitemstruct->itemaction & oda_focus)
	{
		dc.drawfocusrect(&lpdrawitemstruct->rcitem);
	}
	else if (lpdrawitemstruct->itemaction & oda_drawentire)
	{
		if (lpdrawitemstruct->itemstate & ods_focus)
			dc.drawfocusrect(&lpdrawitemstruct->rcitem);
		else
			dc.exttextout(0, 0, eto_opaque, &lpdrawitemstruct->rcitem, _t(""), 0, null);
	}

	if (0 <= (int)lpdrawitemstruct->itemid)	// any item selected?
	{
		::inflaterect(&lpdrawitemstruct->rcitem, -2, -2);
		
		dc.fillsolidrect(&lpdrawitemstruct->rcitem, (colorref)lpdrawitemstruct->itemdata);
		dc.framerect(&lpdrawitemstruct->rcitem, &brushblack);
	}

	// restore the dc state
	dc.settextcolor(rgbtextcolor);
	dc.setbkcolor(rgbbkcolor);
	dc.detach();
}

colorref ccombocolorpicker::getselectedcolor()
{
	int nitem = getcursel();
	if (cb_err == nitem)
		return rgb(0, 0, 0);	// default to black if nothing is selected

	return m_rgstandardcolors[nitem];
}

