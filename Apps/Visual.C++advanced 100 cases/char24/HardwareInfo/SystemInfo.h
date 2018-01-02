// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__17BDCA90_50FA_11D2_8B77_000000000000__INCLUDED_)
#define AFX_SYSTEMINFO_H__17BDCA90_50FA_11D2_8B77_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _SYS_INFO
{
	UINT	m_stNumProcessors;
	UINT	m_OemId;
	UINT	m_PageSize;
	CString	m_stMaxAddress;
	
	CString	m_stMinAdress;
	
	CString	m_stProcessorLevel;
	CString	m_stMask;
	CString	m_stProRevision;
	CString	m_stProcessorType;
	CString	m_stArchitecture;
	CString	m_stMouse;
	CString	m_stButtonsSwapped;
	CString	m_stMouseSpeed;
} SYS_INFO, *LPSYS_INFO;

class CSystemInfo : public CObject  
{
public:
	CSystemInfo();
	virtual ~CSystemInfo();
protected:
	SYS_INFO m_SysInfo;

};

#endif // !defined(AFX_SYSTEMINFO_H__17BDCA90_50FA_11D2_8B77_000000000000__INCLUDED_)
