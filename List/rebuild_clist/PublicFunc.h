/**
*	made by alzq,xpb
*	08-08-28
*
*
*/

#pragma once

#define	EXIF_NONE						0
#define	EXIF_MATCH						1
#define	EXIF_COLORSPACE					2
#define	EXIF_COMPONENTSCONFIGURATION	3
#define	EXIF_EXIFVERSION				4
#define	EXIF_EXPOSUREMODE				5
#define	EXIF_FILESOURCE					6
#define	EXIF_FLASHPIXVERSION			7
#define	EXIF_FOCALPLANERESOLUTIONUNIT	8
#define	EXIF_ISOSPEEDRATINGS			9
#define	EXIF_METERINGMODE				10
#define	EXIF_ORIENTATION				11
#define	EXIF_RESOLUTIONUNIT				12
#define	EXIF_SCENECAPTURETYPE			13
#define	EXIF_WHITEBALANCE				14
#define	EXIF_YCBCRPOSITIONING			15

#include <map>
#include "FileInfoList.h"
#include "ImgBaseFunc.h"
#include   <shlobj.h>  

/**
*	EXIF信息存储ITEM
*	DealMethod为读取时需要进行的处理，主要分为
*	0:不处理
*	1:计算
*/
typedef struct ExifInfoValueItem
{
	string ItemName;
	int DealMethod;
	string Value;
}ExifInfoValueItem;


typedef	map<string,ExifInfoValueItem>	T_mapStrStr;

class PublicFunc
{
public:
private:
	static T_mapStrStr ExifTitleMap;		//存放EXIF信息标题的MAP
	static HANDLE T_hMutex;					//GDI的Graphics创建时的互斥对象
public:

	PublicFunc(void);
	~PublicFunc(void);
	//=====================================================================
	// 函 数 名：InitPublicFuncs
	// 功能描述：初始化公共函数类中部分成员
	// 输入参数：void
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：08.10.07
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void InitPublicFuncs();


	//=====================================================================
	// 函 数 名：DoChangeImageSize
	// 功能描述：对image对象进行缩放
	// 输入参数：Image * image,				//图像对象指针
	//			 UINT nImageWidth,			//图像要设定的像素宽（最大）
	//			 UINT nImageHeight 			//图像要设定的像素高（最大）
	// 输出参数：BOOL:返回是否设置成功
	// 创建日期：
	// 修改日期：08.09.11
	// 作 者：edit:alzq
	// 附加说明：参数列表中的pImage已经指向一个有效的地址空间,图象按照最大宽高按原比例进行缩放
	//=====================================================================
	static BOOL DoChangeImageSize(Magick::Image * image,		//图像对象指针
						   UINT nImageWidth,				//图像要设定的像素宽（最大）
						   UINT nImageHeight );				//图像要设定的像素高（最大）


	/*
	返回值：TRUE表示图像数据拷贝入DC成功,FALSE表示图像数据拷贝入DC不成功
	参数表：Image &inImage				//图像数据对象
			CDC &SrcDC 					//图像拷贝进去的DC
	*/
	static BOOL  DoDCSelectObject( Magick::Image * inImage,				//图像数据对象
						CDC * SrcDC, 							//图像拷贝进去的DC
						CDC * pDC);	

	//=====================================================================
	// 函 数 名：ReadImage
	// 功能描述：将文件读取为指定大小的缩略图
	// 输入参数：FileInfoList * fileInfo
	//			 int width,int height
	// 输出参数：Gdiplus::Image *
	// 创建日期：08.08.29
	// 修改日期：08.08.29
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static Gdiplus::Image * ReadImage(FileInfoList * fileInfo,int width,int height);

	//=====================================================================
	// 函 数 名：Long2Str
	// 功能描述：将long型数据转化为string
	// 输入参数：LONG l:需要转化的数字
	//			 int minSize:最小长度
	// 输出参数：string
	// 创建日期：08.08.29
	// 修改日期：08.08.29
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static string Long2Str(LONG l,int minSize);

	//=====================================================================
	// 函 数 名：LockMutex
	// 功能描述：等待互斥对象并给互斥对象加锁
	// 输入参数：DWORD dwMilliseconds:等待的时间，单位-毫秒
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：08.10.07
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void LockMutex(DWORD dwMilliseconds);

	//=====================================================================
	// 函 数 名：UnLockMutex
	// 功能描述：给互斥对象解锁
	// 输入参数：void
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：08.10.07
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void UnLockMutex();
		

	//=====================================================================
	// 函 数 名：Time2Str
	// 功能描述：将时间类型转化为固定的字符串格式
	// 输入参数：LPSYSTEMTIME time
	// 输出参数：string
	// 创建日期：08.09.02
	// 修改日期：08.09.02
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static string Time2Str(LPSYSTEMTIME time);
		

	//=====================================================================
	// 函 数 名：GetFileType
	// 功能描述：根据文件扩展名得出文件类型
	// 输入参数：string exName:文件扩展名
	// 输出参数：string
	// 创建日期：08.09.02
	// 修改日期：08.09.02
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static string GetFileType(string exName);
		

	//=====================================================================
	// 函 数 名：InitExifMap
	// 功能描述：初始化EXIF信息相关存储对象
	// 输入参数：void
	// 输出参数：void
	// 创建日期：08.09.04
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void InitExifMes(void);
		

	//=====================================================================
	// 函 数 名：CreateExifInfoItem
	// 功能描述：生成一个ExifInfoValueItem对象
	// 输入参数：String itemName,int dealMethod,String value;
	// 输出参数：ExifInfoValueItem
	// 创建日期：08.09.04
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static ExifInfoValueItem CreateExifInfoItem(string itemName,int dealMethod,string value);
		

	//=====================================================================
	// 函 数 名：DealExifValue
	// 功能描述：根据EXIF的ITEM名称处理EXIF值
	// 输入参数：string itemName:ITEM名称
	//			 string value:ITEM值
	// 输出参数：ExifInfoValueItem
	// 创建日期：08.09.04
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static ExifInfoValueItem DealExifValue(string itemName,string value);
		

	//=====================================================================
	// 函 数 名：DealExifMatch
	// 功能描述：对EXIF信息中需要计算的字符串进行计算
	// 输入参数：string str
	// 输出参数：string
	// 创建日期：08.09.04
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static string DealExifMatch(string str);
		

	//=====================================================================
	// 函 数 名：Number2Str
	// 功能描述：将数字转化为String并保留规定小数位
	// 输入参数：double num,int maxS
	// 输出参数：string
	// 创建日期：08.09.04
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static string Number2Str(double num,int maxS);
		

	//=====================================================================
	// 函 数 名：DeleteThread
	// 功能描述：结束线程
	// 输入参数：HANDLE handle:需要结束的线程句柄
	// 输出参数：void
	// 创建日期：08.09.15
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void DeleteThread (HANDLE handle);

	//=====================================================================
	// 函 数 名：LowStr
	// 功能描述：将字符串全部转化为小写
	// 输入参数：string &str
	// 输出参数：void
	// 创建日期：08.09.24
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static void LowStr( string &str );

	//=====================================================================
	// 函 数 名：CreateShortcut
	// 功能描述：将字符串全部转化为小写
	// 输入参数：LPCSTR szPath:快捷方式绝对路径-必须以.lnk结尾
	//			 LPCSTR szLink:指向的文件路径
	// 输出参数：BOOL
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	static BOOL CreateLink(LPCSTR szPath,LPCSTR szLink);
	//=====================================================================
	// 函 数 名：CutOrCopyFiles
	// 功能描述：lpBuffer：文件名称列表，uBufLen:字符串长度，bCopy：是为复制，否为剪切
	// 输入参数：
	// 输出参数：void
	// 创建日期：2008.10.8
	// 修改日期:
	// 作 者：   jiangxh
	// 附加说明： 
	//=====================================================================
	static void PublicFunc::CutOrCopyFiles(char *lpBuffer,UINT uBufLen,BOOL bCopy);

	//=====================================================================
	// 函 数 名：ReadShortcut
	// 功能描述：
	// 输入参数：
	// 输出参数：void
	// 创建日期：2008.10.10
	// 修改日期:
	// 作 者：   jiangxh
	// 附加说明： 
	//=====================================================================
	static bool   ReadShortcut(LPWSTR   lpwLnkFile,   LPSTR   lpDescFile); 

	//=====================================================================
	// 函 数 名：ReadImageList
	// 功能描述：从指定路径读取CImageList
	// 输入参数：CString imgPath,CImageList * list,int width,int height,int count
	// 输出参数：void
	// 创建日期：2008.10.13
	// 修改日期:
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	static void   ReadImageList(CString imgPath,CImageList * list);

};

 
 


