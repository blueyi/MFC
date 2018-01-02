// SCSI2.h: interface for the SCSI2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCSI2_H__1DEE4066_AFFF_4070_A647_1819791050E7__INCLUDED_)
#define AFX_SCSI2_H__1DEE4066_AFFF_4070_A647_1819791050E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WNASPI32.H"
#include "SCSIDEFS.H"
#include "scsireg.h"
#include "ecma_167.h"
#include "osta_udf.h"

#define block_size		2048

typedef struct{
	BYTE	m_HA;
	BYTE	m_ID;
	BYTE	m_LUN;
	CString m_name;
}DRIVEINFO;

class SCSI2  
{
public:
	SCSI2();
	virtual ~SCSI2();
	bool ASPIStart ();
	void ASPIStop ();
	void SCSISelectDevice(BYTE, BYTE, BYTE);
	bool ASPIReset();
	int SCSIBusScan (DRIVEINFO*,BYTE type=0xff,bool silent=true);
	bool WritePacket(long);
	bool WritePacket(unsigned char*,long);
	bool WritePacket(unsigned char*,long,long,bool packet=true);
	bool FormatDisc(const char*);
	bool WriteFiles(CString);
	CString ListFiles();
	bool SaveFileAs(int ID,CString path);
	bool CloseSession();
	bool ReserveTrack(int size);

	bool	SCSIRead(unsigned char*,long,long,bool header=false);
	bool	SCSISetSpeed(int,int);
	CString SCSIInquiry (bool multiline=true);
	CString SCSICDROMCapacity();
	CString SCSICDRScan();
	CString SCSICapabilities();
	CString TOC();
	CString ATIP();
	CString PMA();
	CString WriteParameters();
	CString ReadTrackInfo(int,track_info*result=NULL);
	CString ReadDiskInfo(disk_info* result=NULL);
	bool	SetWriteParameters(int,int,int,int);
	void	LoadUnload(bool);
	int		TestUnitReady ();
	CString checkError(BYTE);
	CString checkSense();
	static int toInt64(unsigned char input[8]);
	static int toInt32(unsigned char input[4]);		
	static int toInt16(unsigned char input[2]);
	void	setLBA(long);
	bool	m_silence;
	long	getLBA(){return m_lba;};
protected:
	BYTE	m_HA;
	BYTE	m_ID;
	BYTE	m_LUN;
	long	m_lba;
	scsi_sense	m_sense;

	CStringList* chopFileNames(CString s);
	tag		fillTag(int,BYTE*,int size,int);
	
	HINSTANCE		hinstWNASPI32;
	DWORD  (*pfnGetASPI32SupportInfo)( void );
	DWORD  (*pfnSendASPI32Command)( LPSRB );
	BOOL   (*pfnGetASPI32Buffer)( PASPI32BUFF );
	BOOL   (*pfnFreeASPI32Buffer)( PASPI32BUFF );
	BOOL   (*pfnTranslateASPI32Address)( PDWORD, PDWORD );
	void* hEventSRB;
};

#endif // !defined(AFX_SCSI2_H__1DEE4066_AFFF_4070_A647_1819791050E7__INCLUDED_)
