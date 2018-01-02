#ifndef __BIMESSAGES_H__
#define __BIMESSAGES_H__

//=============================================================================
// Message sent whenever state of a series has been chnaged.
/*
	\remarks WPARAM contains pointer to the changed series, LPARAM is ignored.
*/
#define WM_SERIESSTATECHANGE				(WM_USER + 100)



//=============================================================================
//Active shimming task finished
#define WM_SHIM_FINISHED					(WM_USER + 101)
#define WM_SHIMMING_UNIFORMITY				(WM_USER + 102)



//=============================================================================
// Message sent to window when the recon manager has reconed one image.
//	WPARAM : pointer to a CReconResult object.
//	LPARAM : pointer to the CReconTask object.
#define WM_RECON_ONEIMAGE					(WM_USER + 200)

// Message sent to window when the recon manager has reconed the whole task.
//	WPARAM : pointer to a CReconResult object.
//	LPARAM : pointer to the CReconTask object.
#define WM_RECON_FINISHED					(WM_USER + 201)

// Message sent to window when the recon failed due to lack of memory.
#define WM_RECON_NOMEMORY					(WM_USER + 202)

//=============================================================================
//Added by jhzhang 2004/09/06
#define WM_FILTER_UPDATE					(WM_USER + 300)




//=============================================================================
#define WM_SLAB_MODIFY						(WM_USER + 400)
#define WM_SLAB_ADD							(WM_USER + 401)
#define WM_SLAB_DELETE						(WM_USER + 402)

#define WM_SORT_CLUSTER						(WM_USER + 405)




//=============================================================================
/*
	When a scan is finished, the scan manager will send a WM_SCANFINISHED 
	message to the window specified in the CScanTask. WPARAM of the message
	holds a pointer to the buffer while LPARAM of the message holds a pointer
	to a CImageDimensions struct. After the window has finished with these
	data, it should delete both pointers.
*/
#define WM_SCANFINISHED						(WM_USER + 500)
#define WM_SCANPROGRESS						(WM_USER + 501)
#define WM_SCANPAUSED						(WM_USER + 502)
#define WM_SCANSTOPPED						(WM_USER + 503)
#define WM_SCANCONTINUED					(WM_USER + 504)
/*
	When a scan fails, the buddy window will receive a WM_SCANFAIL message.
	WPARAM of the message holds an error code that explains why the scan 
	failed.
*/
#define WM_SCANFAIL							(WM_USER + 505)
const int cnstScanFailUnknown		= 0;
const int cnstScanFailCanceled		= 1;
const int cnstScanFailPrescan		= 2;
const int cnstScanFailSpectrometer	= 3;
const int cnstScanFailO1			= 4;

#define WM_PRESCANFINISHED					(WM_USER + 506)

#define WM_STARTPRESCAN						(WM_USER + 507) // not used

#define WM_PRESCAN_EPIIMAGE					(WM_USER + 508)
#define WM_PRESCAN_ANALYZE_DATA				(WM_USER + 509)

#define WM_SCANSTARTED						(WM_USER + 510)

#define SIUCMD_READ							0
#define SIUCMD_WRITE						1
#define WM_SIUCMD   						(WM_USER + 511)
#define WM_GATINGCMD						(WM_USER + 512)

//=============================================================================
#define WM_SCANPARAM_CHANGED				(WM_USER + 600)
// 关于扫描时间的参数发生了改变，通知主框架，及时调整与该series关联的button
#define WM_SCANPARAM_TIMING_CHANGED			(WM_USER + 601)


//=============================================================================

// 关闭当前Study
#define WM_CLOSE_STUDY						(WM_USER + 610)

// 发送给主窗口，设置scout series.
#define WM_SET_SCOUT_SERIES					(WM_USER + 1001)
#define WM_ACTIVATE_MRIVIEW					(WM_USER + 1002)

//当没有信号,显示no valid bmap!时
#define  WM_INVALID_BMAP					(WM_USER + 1003) //dolphin

//==============================================================================
#define  WM_LIST_KEYDOWN					(WM_USER + 1100)
#define  WM_PROGRESS_BEGIN					(WM_USER + 1110)
#define  WM_PROGRESS_END					(WM_USER + 1114)
#define  WM_PROGRESS_STEPIT					(WM_USER + 1118)
#define  WM_PROGRESS_SET_TITLE				(WM_USER + 1120)
//响应进度条取消的消息
#define  WM_PROGRESS_CANCEL_STUDY           (WM_USER + 1122)
#define  WM_PROGRESS_CANCEL_SERIES          (WM_USER + 1125)
#define	 WM_FILMING_WND_PRINT_CANCEL        (WM_USER + 1130)
#define  WM_FILMING_PRINT_SUCCESS			(WM_USER + 1135)
#define  WM_FILMING_PRINT_FAIL				(WM_USER + 1140)
#define  VK_CTRL_A_CTRL						2186
#define  VK_CTRL_B_CTRL						2188
#define  WM_UPDATE_ALL_SERIES_WIN			(WM_USER + 1145)
#define	 WM_WIN_REFRESH_MSG					(WM_USER + 1146)
#define  WM_USER_CANCEL_CLOSED_SERIES		(WM_USER + 1148)
//切换刷新
#define  WM_MRI_VIEW_SWITCH_REFRESH			(WM_USER + 1149)

#define _DEFAULT_SHEET_LAYOUT_ "DEFAULT_SHEET_LAYOUT"
#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif
#ifdef _CHEN_SHI_
#define _MAX_STUDY_ID_LEN_ 16
typedef struct 
{
	char pStudyID[_MAX_STUDY_ID_LEN_];
	int nSeriesID;

}_SEL_SERIES_INFO_BLOCK_;


#endif

//系统故障诊断定义消息
#define  WM_SYS_DIAGNOSIS_TIME_EVENT		(WM_USER + 1135)
#define  WM_SYS_DIAGNOSIS_USER_SCAN_START	(WM_USER + 1139)
#define  WM_SYS_DIAGNOSIS_USER_SCAN_END		(WM_USER + 1140)
#define _END_OF_COMM_COMMAND_  "\n"
#define _CMD_ES_ "$ES "
#define _CMD_BS_ "$BS "
#define _CMD_DT_ "$DT"
#define _CMD_TC_ "$TC"
#define _MAX_LAYOUT_ROW_ 6 
#define _MAX_LAYOUT_COLOMN_ 6
//For pacs
/**  [SHCH 2007114 For pacs] **/
#define  WM_PROGRESS_BEGIN_PACS_TRAN					(WM_USER + 1150)
#define  WM_PROGRESS_END_PACS_TRAN						(WM_USER + 1151)
#define  WM_PROGRESS_STEPIT_PACS_TRAN					(WM_USER + 1153)
#define  WM_PROGRESS_SET_TITLE_PACS_TRAN				(WM_USER + 1156)
#define  WM_PROGRESS_CANCEL_FILM_PRINT				(WM_USER + 1158)
/** [SHCH:4-1-2008 TITLE:XABW/CX-31-11-0143/PUR:将更新移出] **/
#define  WM_NOTIFIED_BACKUP				(WM_USER + 1162)
/** [SHCH:4-1-2008 TITLE:XABW/CX-31-11-0143/PUR:将更新移出] **/


/**  [SHCH 2007114 For pacs] **/

/*********zyh add 2008.2.26*********/
#define WM_SETBTNSTATUS				WM_USER + 1888
/**********************************************/



/** [zhlxu 2008.3.10] [] 增加温控功能 **/
#define WM_EXECUTE_WATER_TEMP_CTRL_FUNCTION (WM_USER+ 1170)	// 获取温控参数命令信息
/** [zhlxu 2008.3.10] **/



#endif // __BIMESSAGES_H__
