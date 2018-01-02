///////////////////////////////////////////////////////////////////
// 文件名 : FileInfoList.h
// 版本 : 1.00
// 目的及主要功 : 文件信息存储双向链表
// 创建日期 : 2008.08.29
// 修改日期 : 
// 作者 : alzq
// 修改者 : 
////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <magick++.h>
#include <gdiplus.h>
#include <io.h>
#include "91SeeDefineHead.h"
#include "afxcmn.h"
#include "MainFrm.h"
#include "MoveOrCopyToDlg.h"
using namespace Magick;
using namespace Gdiplus;
using namespace std;

struct itemInfo
{
	int nItem;			//所在ITEM编号
	CPoint printPos;	//相对ListView显示的位置 
	int photoWidth;		//图象宽度
	int photoHeight;	//图象高度
	int style;			//显示样式
	UINT state;			//item状态

	bool reDrawEnable;	//其他要求重画的操作对象
};

class FileInfoList
{
public:
	FileInfoList();
	~FileInfoList(void);
	//=====================================================================
	// 函 数 名：FileInfoList
	// 功能描述：根据输入的文件完整路径与是否文件夹初始化相关信息
	// 输入参数：string fileFullPath:文件全路径
	//			 bool isDirectory:是否文件夹
	//			 bool isPhoto:是否图象
	//			 LONG fileLength=0:文件长度，默认为0
	// 输出参数：
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	FileInfoList(string fileFullPath,UINT fileType,LONG fileLength=0);

// Attributes //属性, 品质, 特征, 加于, 归结
public:
	map<string,string> m_mssInfoMap;					//文件信息保存MAP

	int m_iFloderCode;									//文件所处路径编号，方便control类进行文件夹的添加删除

	int m_iPhotoWidth;									//图象宽度
	int m_iPhotoHeight;									//图象高度
	int m_iRealPhotoWidth;								//图象实际宽度
	int m_iRealPhotoHeight;								//图象实际高度
	int m_iNIcon;										//在系统中的系统图标编号
	int m_iGroupId;										//所属分组ID
	int m_iPhotoLevel;									//图片所属等级编号
	int m_iPhotoTypeCode;								//图片所属分类编号

	UINT m_uiState;										//存储文件状态变量
	UINT m_uiFileType;									//文件种类

	/**
	*	以下部分存储文件基本信息。	
	*	不使用MAP存储，主要是为了在排序时不消耗多余计算
	*/
	string m_sFileSize;									//文件大小
	string m_sFileType;									//文件类型
	string m_sFileCreateTime;							//文件创建时间
	string m_sFileEditTime;								//文件修改时间
	string m_sFileOpenTime;								//文件访问时间
	string m_sPhotoSize;								//图象大小
	string m_sTakePhotoTime;							//拍摄时间
	/**
	*	----文件基本信息部分完结----
	*/

	bool m_bNeedGetInfo;								//是否需要获取文件信息
	bool m_bNeedGetBaseInfo;							//是否需要获取文件基本信息
	bool m_bNeedGetSmallPhoto;							//是否需要获取缩略图
	bool m_bSmallPhotoEnable;							//缩略图是否有效
	bool m_bFileEnable;									//文件是否有效，文件在链表中是否有效

	itemInfo m_iiItemInfo;								//本对象在实际显示时的信息对比对象

	FileInfoList * m_filUpItem;							//链表中上一项的值
	FileInfoList * m_filNextItem;						//链表中下一项的值
protected:
	string m_sFileName;									//不包含扩展名的文件名
	string m_sFilePath;									//文件路径，包含"/"
	string m_sFileExtName;								//文件扩展名
	string m_sFileFullPath;								//文件完整路径，包括文件名什么的

	Gdiplus::Image * m_imgSmallPhotoImage;				//存放缩略图文件

// Operations //运转, 操作, 实施, 作用, 业务, 工作, 手术, 军事行动
public:
	//=====================================================================
	// 函 数 名：GetFileName
	// 功能描述：返回文件名
	// 输入参数：void
	// 输出参数：string
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	string GetFileName();
	//=====================================================================
	// 函 数 名：GetFilePath
	// 功能描述：返回文件路径
	// 输入参数：void
	// 输出参数：string
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	string GetFilePath();
	//=====================================================================
	// 函 数 名：GetFileExtName
	// 功能描述：返回文件扩展名
	// 输入参数：void
	// 输出参数：string
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	string GetFileExtName();
	//=====================================================================
	// 函 数 名：GetFileFullPath
	// 功能描述：返回文件完整路径
	// 输入参数：void
	// 输出参数：string
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	string GetFileFullPath();
	//=====================================================================
	// 函 数 名：GetFileBaseInfo
	// 功能描述：获取文件基本信息中的某一项
	// 输入参数：int INFO_TYPE:在本文件开头以宏定义
	// 输出参数：string
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	string GetFileBaseInfo(int INFO_TYPE);

	//=====================================================================
	// 函 数 名：SetFileType
	// 功能描述：设置文件种类
	// 输入参数：UINT
	// 输出参数：void
	// 创建日期：08.10.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void SetFileType(UINT type);
	//=====================================================================
	// 函 数 名：CheckFileType
	// 功能描述：判断文件种类
	// 输入参数：UINT
	// 输出参数：BOOL
	// 创建日期：08.10.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL CheckFileType(UINT type);
	//=====================================================================
	// 函 数 名：SetFileName
	// 功能描述：设置文件名
	// 输入参数：string
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void SetFileName(string fileName);

	//=====================================================================
	// 函 数 名：GetSmallPhotoImage
	// 功能描述：获取缩略图文件
	// 输入参数：void
	// 输出参数：Image *
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	Gdiplus::Image * GetSmallPhotoImage();
	//=====================================================================
	// 函 数 名：GetFileBaseInfo
	// 功能描述：获取文件基本信息
	// 输入参数：void
	// 输出参数：BOOL:返回读取是否成功
	// 创建日期：08.09.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL GetFileBaseInfo();
	//=====================================================================
	// 函 数 名：LoadExifInfo
	// 功能描述：载入Exif信息
	// 输入参数：void
	// 输出参数：void
	// 创建日期：08.09.16
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void LoadExifInfo();
	//=====================================================================
	// 函 数 名：CreateSmallImage
	// 功能描述：将image文件进行缩放
	// 输入参数：int width,int height
	// 输出参数：BOOL:返回是否成功
	// 创建日期：08.09.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL CreateSmallImage(int width,int height);

	//=====================================================================
	// 函 数 名：ISetFileName
	// 功能描述：设置文件名
	// 输入参数：string fileNewName:新的文件名，不包含路径
	// 输出参数：BOOL:返回是否设置成功
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL ISetFileName(string fileNewName);
	//=====================================================================
	// 函 数 名：ISetFileNameAndExtName
	// 功能描述：设置文件名与扩展名
	// 输入参数：string fileNewName:新的文件名，不包含路径
	// 输出参数：BOOL:返回是否设置成功
	// 创建日期：08.09.10
	// 修改日期：alzq 08.10.09
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL ISetFileNameAndExtName(string fileNewName);
	//=====================================================================
	// 函 数 名：ICopyFile
	// 功能描述：拷贝文件到路径
	// 输入参数：string fileNewPath:拷贝到的文件的路径，包含"/"
	// 输出参数：BOOL:返回是否设置成功
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL ICopyFile(string fileNewPath,UINT dealType);
	//=====================================================================
	// 函 数 名：ICutFile
	// 功能描述：剪切文件到某文件夹
	// 输入参数：string fileNewPath:剪切到的文件的路径，包含"/"
	// 输出参数：BOOL:返回是否设置成功
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL ICutFile(string fileNewPath,UINT dealType);

	//=====================================================================
	// 函 数 名：Dispose
	// 功能描述：释放本对象的资源
	// 输入参数：void
	// 输出参数：void
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void Dispose();

	//=====================================================================
	// 函 数 名：InsertNext
	// 功能描述：在本ITEM之后插入一个ITEM
	// 输入参数：FileInfoList * nextItem:需要插入的ITEM指针
	// 输出参数：BOOL
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	BOOL InsertNext(FileInfoList * nextItem);
	//=====================================================================
	// 函 数 名：InsertFront
	// 功能描述：在本ITEM之前插入一个ITEM
	// 输入参数：FileInfoList * nextItem:需要插入的ITEM指针
	// 输出参数：BOOL
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：返回TRUE表示成功在该项前添加ITEM并不影响链表头
	//			 返回FALSE表示成功添加ITEM但是链表头已经改变
	//=====================================================================
	BOOL InsertFront(FileInfoList * nextItem);
	//=====================================================================
	// 函 数 名：DeleteSelf
	// 功能描述：删除本项
	// 输入参数：void
	// 输出参数：FileInfoList * 返回删除自身后，下一项地址
	// 创建日期：08.09.12
	// 修改日期：
	// 作 者：alzq
	// 附加说明：返回TRUE表示成功
	//			 返回FALSE表示成功添加ITEM但是链表头已经改变
	//=====================================================================
	FileInfoList * DeleteSelf(bool disposeEnable);
	//=====================================================================
	// 函 数 名：SetState
	// 功能描述：删除本项
	// 输入参数：UINT newState:新的状态值
	//			 bool changeAll:是否完全替换状态值
	//			 UINT mask:遮罩
	// 输出参数：UINT 返回新的状态
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	UINT SetState(UINT newState,bool changeAll,UINT mask);
	//=====================================================================
	// 函 数 名：GetState
	// 功能描述：删除本项
	// 输入参数：UINT stateMask:获取状态的遮罩变量
	// 输出参数：UINT 返回状态
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	UINT GetState(UINT stateMask);

// Overridables //可重载的

// Implementation //实现

};

/**
*---------Exif信息描述-----------

("exif:ApertureValue","95/32")----------------------------光圈值
("exif:ColorSpace","1")------------------------------------色彩空间(1:"sRGB";2:"未知")
("exif:ComponentsConfiguration","...")--------------------分量配置("01020300":YCbCr;"04050600":RGB);
("exif:CompressedBitsPerPixel","3/1")--------------------图象压缩率
("exif:Compression","6")
("exif:CustomRendered","0")
("exif:DateTime","2008:08:06 09:24:10")--------------------时间戳
("exif:DateTimeDigitized","2008:08:06 09:24:10")--------数字化时间
("exif:DateTimeOriginal","2008:08:06 09:24:10")------------拍摄时间
("exif:DigitalZoomRatio","4000/4000")--------
("exif:ExifImageLength","1944")----------------------------Exif图象宽度
("exif:ExifImageWidth","2592")----------------------------Exif图象高度
("exif:ExifOffset","196")------------
("exif:ExifVersion","0220")--------------------------------Exif版本(/100)
("exif:ExposureBiasValue","0/3")------------------------曝光补偿值
("exif:ExposureMode","0")--------------------------------曝光模式(1:"手动";"自动")
("exif:ExposureTime","1/20")----------------------------快门速度值(/s)
("exif:FNumber","28/10")--------------------------------光圈值
("exif:FileSource",".")------------------------------------文件来源(0x03:"digital still camera":"unknown")
("exif:Flash","16")
("exif:FlashPixVersion","0100")----------------------------FlashPix版本(/100)
("exif:FocalLength","7400/1000")------------------------焦距mm
("exif:FocalPlaneResolutionUnit","2")--------------------焦平面分辨单位(0:"";1:"";2:"英寸";3:"厘米")
("exif:FocalPlaneXResolution","2592000/291")------------焦平面X分辨率
("exif:FocalPlaneYResolution","1944000/219")------------焦平面Y分辨率
("exif:ISOSpeedRatings","200")----------------------------ISO速率(ISO )
("exif:InteroperabilityIndex","R98")
("exif:InteroperabilityOffset","3362")
("exif:InteroperabilityVersion","0100")
("exif:JPEGInterchangeFormat","5108")
("exif:JPEGInterchangeFormatLength","5329")
("exif:Make","Canon")------------------------------------制造商
("exif:MakerNote",".")
("exif:MaxApertureValue","95/32")------------------------最大光圈值
("exif:MeteringMode","5")--------------------------------测光模式(0:"未知";1:"平均";2:"中央重点平均测光";3:"点测";4:"分区";5:"评估";6:"局部";255:"其他";)
("exif:Model","Canon PowerShot G9")------------------------型号
("exif:Orientation","1")--------------------------------方向(0:"";1:"左上";2:"右上";3:"右下";4:"左下";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)--------
("exif:RelatedImageLength","2592")------------------------象素X尺寸
("exif:RelatedImageWidth","1944")------------------------象素Y尺寸
("exif:ResolutionUnit","2")--------------------------------分辨单位(0:"";1:"";2:"英寸";3:"厘米")
("exif:SceneCaptureType","0")----------------------------场景类型(0x01:"A directly photographed image";"unknown")
("exif:SensingMethod","2")
("exif:ShutterSpeedValue","138/32")------------------------快门速度
("exif:WhiteBalance","0")--------------------------------白平衡(1:"手动";"自动")
("exif:XResolution","180/1")----------------------------X分辨率
("exif:YCbCrPositioning","1")----------------------------YCbCr位置(0:"";1:"居中";2:"the datum point";)
("exif:YResolution","180/1")----------------------------Y分辨率

*------------------------------
*/