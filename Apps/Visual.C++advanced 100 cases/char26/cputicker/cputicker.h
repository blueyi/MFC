// TITLE:
// High-Resolution Counter Class.
//
// VERSION:
// 1.0
//
// AUTHORS:
// Created by J.M.McGuiness, CompuServe ID 100627,630.
//            PJ Naughter,   Email: pjn@indigo.ie Web: http://indigo.ie/~pjn
//
// DESCRIPTION:
// This file declares a class the wraps the Pentium-specific time stamp counter.
// This counter has a resolution in terms of PCLKS (processor clocks) so it can
// be used for direct instruction timings.
//
// VERSION HISTORY:
// 26/3/96 Creation of version 1.0
// 16/7/97 PJ Naughter,
//         A number of additions including:
//         Support for running on Windows NT
//         now uses the build-in 64 bit data type "__int64"
//         Improved diagnostic info thanks to the above
//         Usage of static variables to improve efficiency
//         Addition of a function which will convert from CPU ticks to seconds
//         Improved adhereance to the MFC coding style and standards
//
// LEGALITIES:
// Copyright © 1996-1997 by J.M.McGuiness and PJ Naughter, all rights reserved.
//
// This file must not be distributed without the authors prior
// consent.
//
/////////////////////////////////////////////////////////////////////////////


////////////////////////////////// Macros ///////////////////////////////////

#ifndef __CPUTICKER_H__
#define __CPUTICKER_H__





////////////////////////// Classes //////////////////////////////////////////
class CCPUTicker : public CObject
{
public:
//constructors / Destructors
	inline CCPUTicker();
	inline CCPUTicker(const CCPUTicker& ticker);

//copy constructor
	inline CCPUTicker& operator=(const CCPUTicker& ticker);

//perform the actual measurement
  void Measure();

//accessors to the actual measurement value
  double GetTickCountAsSeconds() const;  
  inline __int64 GetTickCount() const { return m_TickCount; };  

//static methods
	static BOOL GetCPUFrequency(double& frequency, double& target_ave_dev, 
                              const unsigned long interval = 1000,
                              const unsigned int max_loops =20);

//Is high resolution available on this CPU
	BOOL IsAvailable();

//Standard MFC diagnostics
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  __int64 m_TickCount;

 	static BOOL m_bHasRDTSC;
  static BOOL m_bRunningOnNT;
  static BOOL m_bStaticsCalculated;

  static double m_deviation;
  static double m_freq;
  static BOOL m_bFrequencyCalculated;

  static BOOL CheckHasRDTSC();
  static BOOL RunningOnNT();

	DECLARE_DYNAMIC(CCPUTicker)
};


#endif //__CPUTICKER_H__