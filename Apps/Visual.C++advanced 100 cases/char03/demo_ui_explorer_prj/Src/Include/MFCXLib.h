//
// Copyright © 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", without WARRANTY OF ANY KIND, and the user
// holds Kirk Stowell blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#if !defined(MFCXLIB_H_INCLUDED)
#define MFCXLIB_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#if defined(MFCXLIB_STATIC) 
  #if defined (_DEBUG) 
    #pragma comment(lib,"MFCXStaticLib_d.lib") 
    #pragma message("Automatically linking with MFCXStaticLib_d.lib") 
  #else 
    #pragma comment(lib,"MFCXStaticLib_r.lib") 
    #pragma message("Automatically linking with MFCXStaticLib_r.lib") 
  #endif 
#elif defined(_DEBUG) 
  #pragma comment(lib,"mfcxlib_d.lib") 
  #pragma message("Automatically linking with mfcxlib_d.dll") 
#else 
  #pragma comment(lib,"mfcxlib_r.lib") 
  #pragma message("Automatically linking with mfcxlib_r.dll") 
#endif 

#if defined(MFCXLIB_STATIC) 
  #define CLASS_EXPORT 
#elif defined(MFCX_PROJ) 
  #define CLASS_EXPORT AFX_CLASS_IMPORT 
#else 
  #define CLASS_EXPORT AFX_CLASS_EXPORT 
#endif 

#include <ControlBarEx.h>
#include <CoolBar.h>
#include <CoolMenu.h>
#include <DockBarEx.h>
#include <FlatBar.h>
#include <FlatButton.h>
#include <FrameWndEx.h>
#include <HyperLink.h>
#include <MDIFrameWndEx.h>
#include <ModulVer.h>
#include <OutlookBar.h>
#include <SizeCBar.h>
#include <SubClass.h>
#include <TabCtrlBar.h>
#include <ToolBarEx.h>

#if defined(AUTO_SUBCLASS)
#define CMenuMgr	 CCoolMenuManager
#define CControlBar  CControlBarEx
#define CDockBar     CDockBarEx
#define CFrameWnd    CFrameWndEx
#define CMDIFrameWnd CMDIFrameWndEx
#define CToolBar     CToolBarEx
#endif

#endif // MFCXLIB_H_INCLUDED