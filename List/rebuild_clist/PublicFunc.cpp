/**
*	made by alzq,dpb
*	08-08-28
*	edit alzq 08-29
*
*/

#include "StdAfx.h"
#include "PublicFunc.h"
#include <sstream>
#include <map>

T_mapStrStr PublicFunc::ExifTitleMap;
HANDLE PublicFunc::T_hMutex;

PublicFunc::PublicFunc(void)
{
}

PublicFunc::~PublicFunc(void)
{
}
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
void PublicFunc::InitPublicFuncs()
{
	T_hMutex=CreateMutex(NULL,FALSE,NULL);
}

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
void PublicFunc::LockMutex(DWORD dwMilliseconds)
{
	WaitForSingleObject(T_hMutex,dwMilliseconds);
}

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
void PublicFunc::UnLockMutex()
{
	ReleaseMutex(T_hMutex);
}

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
BOOL PublicFunc::DoChangeImageSize(Magick::Image * image,		//图像对象指针
					   UINT nImageWidth,				//图像要设定的像素宽（最大）
					   UINT nImageHeight )				//图像要设定的像素高（最大）
{
	try
	{
		/*--alzq edit 08-29--*/
		LONG pWidth=image->columns();	//图象宽度
		LONG pHeight=image->rows();	//图象高度
		LONG realWidth=pWidth;									//显示图象宽度
		LONG realHeight=pHeight;								//显示图象高度
		double scaleW=(double)(pWidth)/nImageWidth;
		double scaleH=(double)(pHeight)/nImageHeight;
		double scale=scaleW>scaleH?scaleW:scaleH;
		if(scale>1)
		{
			realWidth=(LONG)(pWidth/scale);
			realHeight=(LONG)(pHeight/scale);
		}

		//创建Magick中代表区域的数据对象：Geometry类型的对象
		Magick::Geometry geometry;
		geometry.width(realWidth);		//设定宽度
		geometry.height(realHeight);	//设定高度
		geometry.aspect( true );		//打开任意修改图像宽高比例的开关
		/*--edit end --*/

		//更改图像的宽高比例
		image->resize(geometry);
		geometry.~Geometry();
	}
	catch (Magick::Error & e)
	{
		AfxMessageBox(_T(e.what()));
		return FALSE;
	}

	return TRUE;
}


/*
返回值：TRUE表示图像数据拷贝入DC成功,FALSE表示图像数据拷贝入DC不成功
参数表：Image &inImage				//图像数据对象
		CDC &SrcDC 					//图像拷贝进去的DC	在传入SrcDC时需要对SrcDC的上下文初始化
		CDC *pDC					//图象需要显示的DC
*/
BOOL  PublicFunc::DoDCSelectObject( Magick::Image * inImage,			//图像数据对象
						CDC * SrcDC ,							//图像拷贝进去的DC
						CDC * pDC)								//图象需要显示的DC
{
	HBITMAP hBitmap;
	RGBQUAD *prgbaDIB = 0;
	BITMAPINFOHEADER bmi;
	//CDC * pDC=new CDC();

	// make sure we're getting a valid image!
	if (!inImage->isValid())
	{
		return FALSE;
	}

	// make sure we have a valid destination DC
	if (&pDC != NULL)
	{
		//
		// Set up the Windows bitmap header
		//
		//BITMAPINFOHEADER bmi;
		bmi.biSize = sizeof(BITMAPINFOHEADER);	// Size of structure
		bmi.biWidth = inImage->columns();	// Bitmaps width in pixels
		bmi.biHeight = (-1)*inImage->rows();	// Bitmaps height n pixels
		bmi.biPlanes = 1;				// Number of planes in the image
		bmi.biBitCount = 32;			// The number of bits per pixel
		bmi.biCompression = BI_RGB;		// The type of compression used
		bmi.biSizeImage = 0;			// The size of the image in bytes
		bmi.biXPelsPerMeter = 0;			// Horizontal resolution
		bmi.biYPelsPerMeter = 0;			// Veritical resolution
		bmi.biClrUsed = 0;			// Number of colors actually used
		bmi.biClrImportant = 0;			// Colors most important
		//			mBMI = bmi;	// keep it for clipboard use...

		hBitmap = CreateDIBSection
			(
			pDC->m_hDC,            // handle to device context
			(BITMAPINFO *)&bmi,    // pointer to structure containing bitmap size, format, and color data
			DIB_RGB_COLORS,        // color data type indicator: RGB values or palette indices
			(void**)&prgbaDIB,     // pointer to variable to receive a pointer to the bitmap's bit values
			NULL,                  // optional handle to a file mapping object
			0                      // offset to the bitmap bit values within the file mapping object
			);

		if ( !hBitmap )
		{
			return FALSE;
		}

		//
		// If image is non-opaque, create overlay the image on top of
		// a pattern background so non-opaque regions become evident.
		//

		Magick::Image * image=inImage;
		if (image->matte())
		{
			Magick::Image matteImage;
			matteImage.size(Magick::Geometry(image->columns(), image->rows()));
			matteImage.read("pattern:checkerboard");
			matteImage.composite(*image,0,0,AtopCompositeOp);
			image->~Image();
			image=&matteImage;
			//image->replaceImage(&matteImage);
		}

		//
		// Extract the pixels from Magick++ image object and convert to a DIB section
		//

		const unsigned int columns = image->columns();
		const unsigned int rows = image->rows();

		RGBQUAD *pDestPixel = prgbaDIB;

		for( unsigned int row = 0 ; row < rows ; row++ )
		{
			const PixelPacket *pPixels = image->getConstPixels(0,row,columns,1);
#if QuantumDepth == 8
			// Form of PixelPacket is identical to RGBQUAD when QuantumDepth==8
			memcpy((void*)pDestPixel,(const void*)pPixels,sizeof(PixelPacket)*columns);
			pDestPixel += columns;

#else	    // 16 or 32 bit Quantum
			// Transfer pixels, scaling to Quantum
			for( unsigned long nPixelCount = columns; nPixelCount ; nPixelCount-- )
			{
				pDestPixel->rgbRed = (BYTE)pPixels->red;//ScaleQuantumToChar(pPixels->red);
				pDestPixel->rgbGreen = (BYTE)pPixels->green;//ScaleQuantumToChar(pPixels->green);
				pDestPixel->rgbBlue = (BYTE)pPixels->blue;//ScaleQuantumToChar(pPixels->blue);
				pDestPixel->rgbReserved = 0;
				++pDestPixel;
				++pPixels;
			}
#endif
		}

		// Now copy the bitmap to device
		SrcDC->SelectObject( hBitmap );
		DeleteObject( hBitmap );
		DeleteObject(pDestPixel);

		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("DoDCSelectObject Error..."));
		return FALSE;
	}
}

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
Gdiplus::Image * PublicFunc::ReadImage(FileInfoList * fileInfo,int width,int height)
{
	USES_CONVERSION;
	Gdiplus::Image * image=Gdiplus::Image::FromFile(A2W(fileInfo->GetFileFullPath().c_str()));
	Bitmap * bmp=new Bitmap(width,height,image->GetPixelFormat());
	Gdiplus::Image * tmpImg=bmp;
	
	Gdiplus::Graphics * graph=Gdiplus::Graphics::FromImage(tmpImg);
	graph->SetInterpolationMode(InterpolationModeHighQualityBicubic);
	graph->DrawImage(image,0,0,width,height);
	delete image;
	delete graph;

	return tmpImg;
}


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
string PublicFunc::Long2Str(LONG l,int minSize)
{
	stringstream stream; 
	string str;
	stream<<l;
	stream>>str;
	if(str.length()<minSize)
	{
		string str_head="";
		for(int n=0;n<minSize-str.length();n++)
		{
			str_head.append("0");
		}
		str_head.append(str);
		return str_head;
	}
	else
	{
		return str;
	}
}
	

//=====================================================================
// 函 数 名：Time2Str
// 功能描述：将时间类型转化为固定的字符串格式
// 输入参数：LPSYSTEMTIME time
// 输出参数：string
// 创建日期：08.08.29
// 修改日期：08.08.29
// 作 者：alzq
// 附加说明：
//=====================================================================
string PublicFunc::Time2Str(LPSYSTEMTIME time)
{
	string timeStr="";
	timeStr.append(Long2Str(time->wYear,4));
	timeStr.append("-");
	timeStr.append(Long2Str(time->wMonth,2));
	timeStr.append("-");
	timeStr.append(Long2Str(time->wDay,2));
	timeStr.append(" ");
	timeStr.append(Long2Str(time->wHour,2));
	timeStr.append(":");
	timeStr.append(Long2Str(time->wMinute,2));
	timeStr.append(":");
	timeStr.append(Long2Str(time->wSecond,2));
	return timeStr;
}
		

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
string PublicFunc::GetFileType(string exName)
{
	if(exName.compare("exe")==0){return "应用程序";}
	if(exName.compare("")==0){return "未知文件";}
	return exName+"文件";

}
		

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
void PublicFunc::InitExifMes(void)
{
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
	("exif:FNumber","28/10")--------------------------------F-值
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
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ApertureValue",CreateExifInfoItem("光圈值",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ColorSpace",CreateExifInfoItem("色彩空间",EXIF_COLORSPACE,"")));								//(1:"sRGB";2:"未知")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ComponentsConfiguration",CreateExifInfoItem("分量配置",EXIF_COMPONENTSCONFIGURATION,"")));	//("01020300":YCbCr;"04050600":RGB);
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:CompressedBitsPerPixel",CreateExifInfoItem("图象压缩率",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Compression",CreateExifInfoItem("Compression",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:CustomRendered",CreateExifInfoItem("CustomRendered",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTime",CreateExifInfoItem("时间戳",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTimeDigitized",CreateExifInfoItem("数字化时间",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTimeOriginal",CreateExifInfoItem("拍摄时间",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DigitalZoomRatio",CreateExifInfoItem("DigitalZoomRatio",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifImageLength",CreateExifInfoItem("Exif图象宽度",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifImageWidth",CreateExifInfoItem("Exif图象高度",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifOffset",CreateExifInfoItem("ExifOffset",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifVersion",CreateExifInfoItem("Exif版本",EXIF_EXIFVERSION,"")));					//(/100)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureBiasValue",CreateExifInfoItem("曝光补偿值",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureMode",CreateExifInfoItem("曝光模式",EXIF_EXPOSUREMODE,"")));					//(1:"手动";"自动")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureTime",CreateExifInfoItem("快门速度值",EXIF_MATCH,"")));						//(/s)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FNumber",CreateExifInfoItem("光圈",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FileSource",CreateExifInfoItem("FileSource",EXIF_FILESOURCE,"")));					//文件来源(0x03:"digital still camera":"unknown")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Flash",CreateExifInfoItem("Flash",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FlashPixVersion",CreateExifInfoItem("FlashPix版本",EXIF_FLASHPIXVERSION,"")));		//(/100)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalLength",CreateExifInfoItem("焦距",EXIF_MATCH,"")));								//mm
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneResolutionUnit",CreateExifInfoItem("焦平面分辨单位",EXIF_FOCALPLANERESOLUTIONUNIT,"")));	//(0:"";1:"";2:"英寸";3:"厘米")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneXResolution",CreateExifInfoItem("焦平面X分辨率",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneYResolution",CreateExifInfoItem("焦平面Y分辨率",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ISOSpeedRatings",CreateExifInfoItem("ISO速率",EXIF_ISOSPEEDRATINGS,"")));				//(ISO )
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityIndex",CreateExifInfoItem("InteroperabilityIndex",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityOffset",CreateExifInfoItem("InteroperabilityOffset",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityVersion",CreateExifInfoItem("InteroperabilityVersion",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:JPEGInterchangeFormat",CreateExifInfoItem("JPEGInterchangeFormat",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:JPEGInterchangeFormatLength",CreateExifInfoItem("JPEGInterchangeFormatLength",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Make",CreateExifInfoItem("制造商",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MakerNote",CreateExifInfoItem("MakerNote",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MaxApertureValue",CreateExifInfoItem("最大光圈值",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MeteringMode",CreateExifInfoItem("测光模式",EXIF_METERINGMODE,"")));					//(0:"未知";1:"平均";2:"中央重点平均测光";3:"点测";4:"分区";5:"评估";6:"局部";255:"其他";)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Model",CreateExifInfoItem("型号",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Orientation",CreateExifInfoItem("方向",EXIF_ORIENTATION,"")));						//(0:"";1:"左上";2:"右上";3:"右下";4:"左下";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)--------
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:RelatedImageLength",CreateExifInfoItem("象素X尺寸",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:RelatedImageWidth",CreateExifInfoItem("象素Y尺寸",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ResolutionUnit",CreateExifInfoItem("分辨单位",EXIF_RESOLUTIONUNIT,"")));				//(0:"";1:"";2:"英寸";3:"厘米")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:SceneCaptureType",CreateExifInfoItem("场景类型",EXIF_SCENECAPTURETYPE,"")));			//(0x01:"A directly photographed image";"unknown")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:SensingMethod",CreateExifInfoItem("SensingMethod",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ShutterSpeedValue",CreateExifInfoItem("快门速度",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:WhiteBalance",CreateExifInfoItem("白平衡",EXIF_WHITEBALANCE,"")));					//(1:"手动";"自动")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:XResolution",CreateExifInfoItem("X分辨率",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:YCbCrPositioning",CreateExifInfoItem("YCbCr位置",EXIF_YCBCRPOSITIONING,"")));			//(0:"";1:"居中";2:"the datum point";)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:YResolution",CreateExifInfoItem("Y分辨率",EXIF_MATCH,"")));
}
		

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
ExifInfoValueItem PublicFunc::CreateExifInfoItem(string itemName,int dealMethod,string value)
{
	ExifInfoValueItem item;
	item.ItemName=itemName;
	item.DealMethod=dealMethod;
	item.Value=value;
	return item;
}
		

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
ExifInfoValueItem PublicFunc::DealExifValue(string itemName,string value)
{
	//获取名称对应的预存储的对象
	ExifInfoValueItem methodItem=ExifTitleMap[itemName];
	ExifInfoValueItem item;
	item.ItemName=methodItem.ItemName;

	if(value.compare("")==0)
	{
		item.Value="";
		return item;
	}

	//根据预存储对象中的处理方法进行不同处理
	switch(methodItem.DealMethod)
	{
		case EXIF_NONE:							//不处理直接返回值
			item.Value=value;
			break;
		case EXIF_MATCH:						//进行计算处理
			item.Value=DealExifMatch(value);
			break;
		case EXIF_COLORSPACE:					//色彩空间处理(1:"sRGB";2:"未知")
			item.Value=value.compare("1")==0?"sRGB":"未知";
			break;
		case EXIF_COMPONENTSCONFIGURATION:		//分量配置处理("01020300":YCbCr;"04050600":RGB);
			item.Value=value.compare("01020300")==0?"YCbCr":
				value.compare("04050600")==0?"RGB":"未知";
			break;
		case EXIF_EXIFVERSION:					//Exif版本处理(/100)
			item.Value=Number2Str((double)(StrToInt(value.c_str()))/(double)(100),2);
			break;
		case EXIF_EXPOSUREMODE:					//曝光模式处理(1:"手动";"自动")
			item.Value=value.compare("1")==0?"手动":"自动";
			break;
		case EXIF_FILESOURCE:					//文件来源处理(0x03:"digital still camera":"unknown")
			item.Value=value.compare("0x03")==0?"digital still camera":"unknown";
			break;
		case EXIF_FLASHPIXVERSION:				//FlashPix版本处理(/100)
			item.Value=Number2Str((double)(StrToInt(value.c_str()))/(double)(100),2);
			break;
		case EXIF_FOCALPLANERESOLUTIONUNIT:		//焦平面分辨单位处理(0:"";1:"";2:"英寸";3:"厘米")
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"":
				value.compare("2")==0?"英寸":
				value.compare("3")==0?"厘米":"未知";
			break;
		case EXIF_ISOSPEEDRATINGS:				//ISO速率处理(ISO +)
			item.Value="ISO "+value;
			break;
		case EXIF_METERINGMODE:					//测光模式处理(0:"未知";1:"平均";2:"中央重点平均测光";3:"点测";4:"分区";5:"评估";6:"局部";255:"其他";)
			item.Value=value.compare("0")==0?"未知":
				value.compare("1")==0?"平均":
				value.compare("2")==0?"中央重点平均测光":
				value.compare("3")==0?"点测":
				value.compare("4")==0?"分区":
				value.compare("5")==0?"评估":
				value.compare("6")==0?"局部":
				value.compare("255")==0?"其他":"未知";
			break;
		case EXIF_ORIENTATION:					//方向处理(0:"";1:"左上";2:"右上";3:"右下";4:"左下";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"左上":
				value.compare("2")==0?"右上":
				value.compare("3")==0?"右下":
				value.compare("4")==0?"左下":
				value.compare("5")==0?"left side top":
				value.compare("6")==0?"right side top":
				value.compare("7")==0?"right side bottom":
				value.compare("8")==0?"left side bottom":"未知";
			break;
		case EXIF_RESOLUTIONUNIT:				//分辨单位处理(0:"";1:"";2:"英寸";3:"厘米")
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"":
				value.compare("2")==0?"英寸":
				value.compare("4")==0?"厘米":"未知";
			break;
		case EXIF_SCENECAPTURETYPE:				//场景类型处理(1:"A directly photographed image";"unknown")
			item.Value=value.compare("1")==0?"A directly photographed image":"未知";
			break;
		case EXIF_WHITEBALANCE:					//白平衡处理(1:"手动";"自动")
			item.Value=value.compare("1")==0?"手动":"自动";
			break;
		case EXIF_YCBCRPOSITIONING:				//YCbCr位置处理(0:"";1:"居中";2:"the datum point";)
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"居中":
				value.compare("2")==0?"the datum point":"未知";
			break;
		default:
			item.Value=value;
			break;
	}

	return item;
}
		

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
string PublicFunc::DealExifMatch(string str)
{
	int s=(int)str.find_first_of("/");
	double d1=(double)(StrToInt(string(str,0,s).c_str()));
	double d2=(double)(StrToInt(string(str,s+1).c_str()));
	return Number2Str(d1/d2,2);
}
		

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
string PublicFunc::Number2Str(double num,int maxS)
{
	stringstream stream; 
	string str;
	stream<<num;
	stream>>str;
	int pointS=(int)str.find_first_of(".");
	if(maxS==0)
	{
		return string(str,0,pointS);
	}
	else
	{
		if(pointS==-1)
		{
			//当不存在小数点时
			return str;
		}
		else
		{
			return string(str,0,pointS+maxS+1);
		}
	}
}
	

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
void PublicFunc::DeleteThread (HANDLE handle)
{
	DWORD exitCode;			//线程状态码
	if(handle!=NULL)
	{
		GetExitCodeThread(handle,&exitCode);	//获取线程状态码
		if(exitCode==STILL_ACTIVE)
		{
			//当运行状态为运行状态时，关闭线程
			//TerminateThread(m_hLoadImageDC,0);
			TerminateThread(handle,0);
			CloseHandle(handle);
		}
	}
}
	

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
void PublicFunc::LowStr( string &str )
{
	int i;
	int nlen;

	char *ps = (char *)str.c_str();

	int d='A' - 'a';

	nlen = (int)str.length();
	for( i=0;i<nlen;i++ )
	{
		if( ps[i]<='Z' && ps[i]>='A' )
			ps[i] =  ps[i] - d;
	}
}
	

//=====================================================================
// 函 数 名：CreateShortcut
// 功能描述：将字符串全部转化为小写
// 输入参数：LPCSTR szPath:快捷方式绝对路径-必须以.lnk结尾
//			 LPCSTR szLink:指向的文件路径
// 输出参数：BOOL
// 创建日期：08.10.07
// 修改日期：
// 作 者：alzq   
// 附加说明：jiangxh changed 2008.10.9
//=====================================================================
BOOL PublicFunc::CreateLink(LPCSTR szPath,LPCSTR szLink)
{	
	CoInitialize(NULL);
	HRESULT hres;
	IShellLink * psl;
	IPersistFile * ppf;
	WORD wsz[MAX_PATH];
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,IID_IShellLink, (void**)&psl);

	if(FAILED(hres))
		return FALSE;

	psl-> SetPath((LPCTSTR)szPath);
	hres = psl-> QueryInterface(IID_IPersistFile, (void**)&ppf);

	if(FAILED(hres))
		return FALSE;

	MultiByteToWideChar(CP_ACP, 0, szLink, -1, (LPWSTR)wsz, MAX_PATH);
	hres = ppf-> Save((LPCOLESTR)wsz, STGM_READWRITE);

	ppf-> Release();
	psl-> Release();
	//jxh 删除 2008.10.9
	//delete psl;
	//delete ppf;
	CoUninitialize();

	return TRUE; 
}


	

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
void PublicFunc::CutOrCopyFiles(char *lpBuffer,UINT uBufLen,BOOL bCopy)
{
	UINT uDropEffect;
	DROPFILES dropFiles;
	UINT uGblLen,uDropFilesLen;
	HGLOBAL hGblFiles,hGblEffect;
	char *szData,*szFileList;

	DWORD *dwDropEffect;

	uDropEffect=RegisterClipboardFormat("Preferred DropEffect");
	hGblEffect=GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE,sizeof(DWORD));
	dwDropEffect=(DWORD*)GlobalLock(hGblEffect);
	if(bCopy)
		*dwDropEffect=DROPEFFECT_COPY;
	else 
		*dwDropEffect=DROPEFFECT_MOVE;
	GlobalUnlock(hGblEffect);

	uDropFilesLen=sizeof(DROPFILES);
	dropFiles.pFiles =uDropFilesLen;
	dropFiles.pt.x=0;
	dropFiles.pt.y=0;
	dropFiles.fNC =FALSE;
	dropFiles.fWide =TRUE;

	uGblLen=uDropFilesLen+uBufLen*2+8;
	hGblFiles= GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, uGblLen);
	szData=(char*)GlobalLock(hGblFiles);
	memcpy(szData,(LPVOID)(&dropFiles),uDropFilesLen);
	szFileList=szData+uDropFilesLen;

	MultiByteToWideChar(CP_ACP,MB_COMPOSITE,
		lpBuffer,uBufLen,(WCHAR *)szFileList,uBufLen);

	GlobalUnlock(hGblFiles);

	if( OpenClipboard(NULL) )
	{
		EmptyClipboard();
		SetClipboardData( CF_HDROP, hGblFiles );
		SetClipboardData(uDropEffect,hGblEffect);
		CloseClipboard();
	}
} 

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
bool   PublicFunc::ReadShortcut(LPWSTR   lpwLnkFile,   LPSTR   lpDescFile)
{
	bool   bReturn   =   true;   
	IShellLink   *pShellLink;   

	if(bReturn)   
	{   
		bReturn   =   (CoInitialize(NULL)   !=   S_OK);   
		if(bReturn)   
		{   
			bReturn   =   CoCreateInstance   (CLSID_ShellLink,   NULL,   CLSCTX_INPROC_SERVER,   
				IID_IShellLink,   (void   **)&pShellLink)   >=   0;   
			if(bReturn)   
			{   
				IPersistFile   *ppf;   
				bReturn   =   pShellLink->QueryInterface(IID_IPersistFile,   (void   **)&ppf)   >=   0;   
				if(bReturn)   
				{   
					bReturn   =   ppf->Load(lpwLnkFile,   TRUE)   >=   0;   
					if(bReturn)   
					{   
						pShellLink->GetPath(lpDescFile,   MAX_PATH,   NULL,   0);   
					}   
					ppf->Release   ();   
				}   
				pShellLink->Release   ();   
			}   
			CoUninitialize();   
		}   
	}   
	return   bReturn;   
}
	

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
void   PublicFunc::ReadImageList(CString imgPath,CImageList * list)
{
	HBITMAP hBitmap;
	CBitmap pBitmap;

	hBitmap = (HBITMAP)LoadImage(NULL,imgPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	pBitmap.Attach(hBitmap); 

	list->Add(&pBitmap,RGB(255,255,255));
}

