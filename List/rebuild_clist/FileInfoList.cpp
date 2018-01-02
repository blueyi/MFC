#include "StdAfx.h"
#include "FileInfoList.h"
#include "PublicFunc.h"
#include "ImgBaseFunc.h"

FileInfoList::FileInfoList(void)
{
	m_filUpItem=NULL;								//链表中上一项的值
	m_filNextItem=NULL;								//链表中下一项的值
	m_imgSmallPhotoImage=NULL;						//存放缩略图文件
}

FileInfoList::~FileInfoList(void)
{
	//if(m_imgSmallPhotoImage!=NULL)
	//	{delete m_imgSmallPhotoImage;}		//存放缩略图文件

}
	

//=====================================================================
// 函 数 名：FileInfoList
// 功能描述：根据输入的文件完整路径与是否文件夹初始化相关信息
// 输入参数：string fileFullPath:文件全路径
//			 bool isDirectory:是否文件夹
//			 bool isPhoto:是否图象
//			 LONG fileLength:文件长度
// 输出参数：
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList::FileInfoList(string fileFullPath,UINT fileType,LONG fileLength)
{
	int mark_1;					//文件完整路径中最后一个'/'或'\'位置
	int fileNameLen;			//文件扩展名长度
	mark_1=(int)fileFullPath.find_last_of("\\/");

	m_uiFileType=fileType;

	m_sFileFullPath=fileFullPath;
	m_sFileName=string(fileFullPath,mark_1+1);
	m_sFilePath=string(fileFullPath,0,mark_1+1);
	if(!CheckFileType(FILE_FLODER))
	{
		//当不是文件夹时，获取扩展名等
		fileNameLen=(int)m_sFileName.find_last_of(".");
		if(fileNameLen>=0)
		{
			m_sFileExtName=string(m_sFileName,fileNameLen+1);
			PublicFunc::LowStr(m_sFileExtName);
		}
		else
		{
			fileNameLen=(int)(m_sFileName.length());
			m_sFileExtName="";
		}
	}
	else
	{
		m_sFileExtName="";
	}

	m_iFloderCode=0;

	m_sFileSize="";									//文件大小
	m_sFileType="";									//文件类型
	m_sFileCreateTime="";							//文件创建时间
	m_sFileEditTime="";								//文件修改时间
	m_sFileOpenTime="";								//文件访问时间
	//图象大小
	if(fileLength==0)
	{
		m_sFileSize="";
	}
	else
	{
		m_sFileSize=PublicFunc::Long2Str(fileLength/1024,0)+"KB";
	}
	m_sTakePhotoTime="";							//拍摄时间

	//其余变量的初始化
	m_bNeedGetInfo=true;							//是否需要获取文件信息
	m_bNeedGetBaseInfo=true;						//是否需要获取文件基本信息
	m_bNeedGetSmallPhoto=true;						//是否需要获取缩略图
	m_bSmallPhotoEnable=false;						//缩略图是否有效
	m_bFileEnable=true;								//文件是否有效，文件在链表中是否有效
	m_uiState=0;									//item状态

	m_filUpItem=NULL;								//链表中上一项的值
	m_filNextItem=NULL;								//链表中下一项的值
	m_imgSmallPhotoImage=NULL;						//存放缩略图文件
	m_iPhotoWidth=0;								//图象宽度
	m_iPhotoHeight=0;								//图象高度
	m_iRealPhotoWidth=0;							//图象实际宽度
	m_iRealPhotoHeight=0;							//图象实际高度
	m_iNIcon=-1;									//在系统图标中的位置编号
	m_iGroupId=-1;									//所属分组ID
	m_iPhotoLevel=0;								//图片所属等级编号
	m_iPhotoTypeCode=0;								//图片所属分类编号

	//设置显示项的初始化
	m_iiItemInfo.nItem=-1;
	m_iiItemInfo.photoHeight=0;
	m_iiItemInfo.photoWidth=0;
	m_iiItemInfo.printPos=CPoint(0,0);
	m_iiItemInfo.reDrawEnable=true;
	m_iiItemInfo.state=0;
	m_iiItemInfo.style=-1;
}
	

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
string FileInfoList::GetFileName()
{
	return m_sFileName;
}
	

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
string FileInfoList::GetFilePath()
{
	return m_sFilePath;
}
	

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
string FileInfoList::GetFileExtName()
{
	return m_sFileExtName;
}
	

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
string FileInfoList::GetFileFullPath()
{
	return m_sFileFullPath;
}
	

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
string FileInfoList::GetFileBaseInfo(int INFO_TYPE)
{
	switch(INFO_TYPE)
	{
	case FILE_NAME:
		return m_sFileName;
	case FILE_SIZE:
		return m_sFileSize;
	case FILE_TYPE:
		return m_sFileType;
	case FILE_CREATE_TIME:
		return m_sFileCreateTime;
	case FILE_EDIT_TIME:
		return m_sFileEditTime;
	case FILE_CHANGE_TIME:
		return m_sFileEditTime;
	case FILE_PHOTO_SIZE:
		return m_sPhotoSize;
	case FILE_TAKE_PHOTO_TIME:
		return m_sTakePhotoTime;
	default:
		return "";
	}
}
	

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
void FileInfoList::SetFileType(UINT type)
{
	m_uiFileType=type;
}
	

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
BOOL FileInfoList::CheckFileType(UINT type)
{
	return m_uiFileType & type;
}
	

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
void FileInfoList::SetFileName(string fileName)
{
	m_sFileName=fileName;
}
	

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
Gdiplus::Image * FileInfoList::GetSmallPhotoImage()
{
	return m_imgSmallPhotoImage;
}
	

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
BOOL FileInfoList::GetFileBaseInfo()
{
	try
	{
		/**
		*	读取文件基本信息
		*/
		//获取文件大小

		//获取文件创建，修改，最后访问时间
		WIN32_FILE_ATTRIBUTE_DATA fileTimeData;
		SYSTEMTIME ftCreationTime;
		SYSTEMTIME ftLastWriteTime;
		SYSTEMTIME ftLastAccessTime;
		GetFileAttributesEx(m_sFileFullPath.c_str(),GetFileExInfoStandard,&fileTimeData);	//获取三个时间
		FileTimeToSystemTime(&fileTimeData.ftCreationTime,&ftCreationTime);					//转换创建时间
		FileTimeToSystemTime(&fileTimeData.ftLastWriteTime,&ftLastWriteTime);				//转换修改时间
		FileTimeToSystemTime(&fileTimeData.ftLastAccessTime,&ftLastAccessTime);				//转换最后访问时间

		//将三个时间存入基本属性MAP中
		m_sFileCreateTime=PublicFunc::Time2Str(&ftCreationTime);
		m_sFileEditTime=PublicFunc::Time2Str(&ftLastWriteTime);
		m_sFileEditTime=PublicFunc::Time2Str(&ftLastAccessTime);
		
		if(m_iNIcon==-1)
		{
			SHFILEINFO shfi;
			SHGetFileInfo((m_sFileFullPath.c_str()),
			        0,
			        &shfi,
			        sizeof(SHFILEINFO),
					SHGFI_DISPLAYNAME | SHGFI_TYPENAME | SHGFI_LARGEICON | SHGFI_ICON);
			m_iNIcon=shfi.iIcon;
		}

		m_bNeedGetBaseInfo=false;

		return TRUE;
	}
	catch(Error e)
	{
		AfxMessageBox(e.what());
		return FALSE;
	}
}
	

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
void FileInfoList::LoadExifInfo()
{
	Magick::Image image(m_sFileFullPath);
	CImgBaseFunc cimgbasefunc;
	m_mssInfoMap=cimgbasefunc.GetImgExifDatas(image);

	m_bNeedGetInfo=false;
}
	

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
BOOL FileInfoList::CreateSmallImage(int width,int height)
{
	try
	{
		//搜索数据库，查询是否存在同路径，同文件名的缩略图

		USES_CONVERSION;
		Gdiplus::Image * image=new Gdiplus::Image(A2W(m_sFileFullPath.c_str()));

		if(image==NULL)
		{
			delete image;
			return FALSE;
		}

		m_iRealPhotoWidth=image->GetWidth();		//图象实际宽度
		m_iRealPhotoHeight=image->GetHeight();	//图象实际高度
		double scaleW=(double)(m_iRealPhotoWidth)/width;
		double scaleH=(double)(m_iRealPhotoHeight)/height;
		double scale=scaleW>scaleH?scaleW:scaleH;
		if(scale>1)
		{
			m_iPhotoWidth=(LONG)(m_iRealPhotoWidth/scale);
			m_iPhotoHeight=(LONG)(m_iRealPhotoHeight/scale);
		}
		else
		{
			m_iPhotoWidth=m_iRealPhotoWidth;
			m_iPhotoHeight=m_iRealPhotoHeight;
		}

		Gdiplus::Image * tmpImg=image->GetThumbnailImage(m_iPhotoWidth,m_iPhotoHeight);
		//Gdiplus::Image * tmpImg=PublicFunc::ReadImage(this,200,160);

		if(tmpImg==NULL)
		{
			delete image;
			return FALSE;
		}

		m_imgSmallPhotoImage=tmpImg;

		delete image;
		return TRUE;
	}
	catch(Exception ex)
	{
		AfxMessageBox(_T(ex.what()));
		return FALSE;
	}
	catch (Magick::Error & e)
	{
		AfxMessageBox(_T(e.what()));
		return FALSE;
	}
}
	

//=====================================================================
// 函 数 名：ISetFileName
// 功能描述：设置文件名
// 输入参数：string fileNewName:新的文件名，不包含路径
// 输出参数：BOOL:返回是否设置成功
// 创建日期：08.09.10
// 修改日期：alzq 08.10.09
// 作 者：alzq
// 附加说明：
//=====================================================================
BOOL FileInfoList::ISetFileName(string fileNewName)
{
	//实现函数
	//获取原文件路径
	string newFullPath=m_sFilePath;
	//生成新文件绝对路径
	newFullPath.append(fileNewName);
	//重命名文件
	int i=rename(m_sFileFullPath.c_str(),newFullPath.c_str());
	//设置新的文件信息
	m_sFileFullPath=newFullPath;
	m_sFileName=fileNewName;

	//重新设置扩展名
	if(!CheckFileType(FILE_FLODER))
	{
		//当不是文件夹时，获取扩展名等
		int fileNameLen=(int)m_sFileName.find_last_of(".");
		if(fileNameLen>=0)
		{
			m_sFileExtName=string(m_sFileName,fileNameLen+1);
			PublicFunc::LowStr(m_sFileExtName);
		}
		else
		{
			m_sFileExtName="";
		}
	}
	else
	{
		m_sFileExtName="";
	}

	return TRUE;
}
	

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
BOOL FileInfoList::ISetFileNameAndExtName(string fileNewName)
{
	if(ISetFileName(fileNewName))
	{
		//修改成功时重新设置扩展名
		if(!CheckFileType(FILE_FLODER))
		{
			//当不是文件夹时，获取扩展名等
			int fileNameLen=(int)m_sFileName.find_last_of(".");
			if(fileNameLen>=0)
			{
				m_sFileExtName=string(m_sFileName,fileNameLen+1);
				PublicFunc::LowStr(m_sFileExtName);
			}
			else
			{
				m_sFileExtName="";
			}
		}
		else
		{
			m_sFileExtName="";
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
	

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
BOOL FileInfoList::ICopyFile(string fileNewPath,UINT dealType)
{
	//实现函数
	string newFullPath=fileNewPath+m_sFileName;

	if(access(newFullPath.c_str(),0)==0)
	{
		//当文件存在时，根据操作方式对文件进行操作
		if(dealType==DEAL_ASK)
		{
			int res=AfxMessageBox(("文件："+newFullPath+" 已经存在，请问是否覆盖？").c_str(),MB_ICONQUESTION|MB_YESNO);
			if(res==IDNO)
			{
				//当选择否时
				return FALSE;
			}
		}
		else if(dealType==DEAL_RENAME)
		{
			int n=0;
			do
			{
				n++;
				string s="91拷贝"+n;
				newFullPath=fileNewPath+s+m_sFileName;
			}while(access(newFullPath.c_str(),0)==0);
		}
		else if(dealType==DEAL_PASS)
		{
			//当忽略时，直接返回
			return FALSE;
		}
		//当覆盖时不需要执行任何操作
	}

	//对文件进行操作，将文件从原文件夹剪切到当前文件夹
	CopyFile(m_sFileFullPath.c_str(),newFullPath.c_str(),FALSE);

	return TRUE;
}
	

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
BOOL FileInfoList::ICutFile(string fileNewPath,UINT dealType)
{
	//实现函数
	string newFullPath=fileNewPath+m_sFileName;

	if(access(newFullPath.c_str(),0)==0)
	{
		//当文件存在时，根据操作方式对文件进行操作
		if(dealType==DEAL_ASK)
		{
			int res=AfxMessageBox(("文件："+newFullPath+" 已经存在，请问是否覆盖？").c_str(),MB_ICONQUESTION|MB_YESNO);
			if(res!=IDYES)
			{
				//当选择否时
				return FALSE;
			}
		}
		else if(dealType==DEAL_RENAME)
		{
			int n=0;
			do
			{
				n++;
				string s="91剪切"+n;
				newFullPath=fileNewPath+s+m_sFileName;
			}while(access(newFullPath.c_str(),0)==0);
		}
		else if(dealType==DEAL_PASS)
		{
			//当忽略时，直接返回
			return FALSE;
		}
		//当覆盖时不需要执行任何操作
	}

	//对文件进行操作，将文件从原文件夹剪切到当前文件夹
	MoveFileEx(m_sFileFullPath.c_str(),newFullPath.c_str(),MOVEFILE_REPLACE_EXISTING);

	return TRUE;
}
	

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
void FileInfoList::Dispose()
{
 	try
 	{
 		m_mssInfoMap.clear();					//文件信息保存MAP
 
 		m_filUpItem=NULL;						//链表中上一项的值
 		m_filNextItem=NULL;						//链表中下一项的值
 
 		m_sFileSize.~basic_string();			//文件大小
 		m_sFileType.~basic_string();			//文件类型
 		m_sFileCreateTime.~basic_string();		//文件创建时间
 		m_sFileEditTime.~basic_string();		//文件修改时间
 		m_sFileOpenTime.~basic_string();		//文件访问时间
 		m_sPhotoSize.~basic_string();			//图象大小
 		m_sTakePhotoTime.~basic_string();		//拍摄时间
 
 		m_sFileName.~basic_string();			//不包含扩展名的文件名
 		m_sFilePath.~basic_string();			//文件路径，包含"/"
 		m_sFileExtName.~basic_string();			//文件扩展名
 		m_sFileFullPath.~basic_string();		//文件完整路径，包括文件名什么的
 
 		if(m_imgSmallPhotoImage!=NULL){delete m_imgSmallPhotoImage;}		//存放缩略图文件
 	}
 	catch(Exception e)
 	{
 		AfxMessageBox(e.what());
 	}
}
	

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
BOOL FileInfoList::InsertNext(FileInfoList * nextItem)
{
	if(this->m_filNextItem!=NULL)
	{
		//当下一项不为空是需要设置下一项的回调指针
		this->m_filNextItem->m_filUpItem=nextItem;
	}
	nextItem->m_filNextItem=this->m_filNextItem;
	nextItem->m_filUpItem=this;
	this->m_filNextItem=nextItem;

	return TRUE;
}
	

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
BOOL FileInfoList::InsertFront(FileInfoList * nextItem)
{
	if(this->m_filUpItem==NULL)
	{
		//上一项为空时，只设置三项，此时头指针改变为nextItem
		nextItem->m_filUpItem=NULL;
		nextItem->m_filNextItem=this;
		this->m_filUpItem=nextItem;
		return FALSE;
	}
	else
	{
		//上一项不为空时，需要设置四项
		this->m_filUpItem->m_filNextItem=nextItem;
		nextItem->m_filUpItem=this->m_filUpItem;
		nextItem->m_filNextItem=this;
		this->m_filUpItem=nextItem;
		return TRUE;
	}
}
	

//=====================================================================
// 函 数 名：DeleteSelf
// 功能描述：删除本项
// 输入参数：bool disposeEnable
// 输出参数：FileInfoList * 返回删除自身后，下一项地址
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：返回TRUE表示成功
//			 返回FALSE表示成功添加ITEM但是链表头已经改变
//=====================================================================
FileInfoList * FileInfoList::DeleteSelf(bool disposeEnable)
{
	FileInfoList * res=m_filNextItem;
	if(m_filUpItem==NULL)
	{
		if(m_filNextItem!=NULL)
		{
			m_filNextItem->m_filUpItem=NULL;
		}
	}
	else
	{
		m_filUpItem->m_filNextItem=m_filNextItem;
		if(m_filNextItem!=NULL)
		{
			m_filNextItem->m_filUpItem=m_filUpItem;
		}
	}

	if(disposeEnable)
	{
		Dispose();
	}
	else
	{
		SetState(0,true,0);			//将状态归0
		m_bFileEnable=false;		//设置文件为无效文件
	}

	return res;
}
	

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
UINT FileInfoList::SetState(UINT newState,bool changeAll,UINT mask)
{
	if(changeAll)
	{
		m_uiState=newState;
	}
	else
	{
		//将位置遮罩变量的位置设为0
		m_uiState&=~mask;
		m_uiState|=(newState & mask);
	}

	return m_uiState;
}
	

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
UINT FileInfoList::GetState(UINT stateMask)
{
	UINT tmpState=m_uiState & stateMask;
	return tmpState;
}
