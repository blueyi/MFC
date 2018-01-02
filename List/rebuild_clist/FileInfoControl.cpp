#include "StdAfx.h"
#include "FileInfoControl.h"

FileInfoControl::FileInfoControl(void)
{
	m_filFileListHeader = NULL;
	m_filFileListEnder = NULL;
	m_filLastGetFileInfoP = NULL;			//最后获取的文件的指针，与位置配合使用加快搜索速度
	m_filLoadImageBegin = NULL;				//载入Image对象的开始位置指针
	InitFileInfoControl();
}

FileInfoControl::~FileInfoControl(void)
{
	DisposeChoose();
	if(m_filFileListHeader)
		delete m_filFileListHeader;
	if(m_filFileListEnder)
		delete m_filFileListEnder;

}
	

//=====================================================================
// 函 数 名：GetHeader
// 功能描述：获取头指针
// 输入参数：void
// 输出参数：FileInfoList *
// 创建日期：08.09.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::GetHeader()
{
	return m_filFileListHeader;
}
	

//=====================================================================
// 函 数 名：GetEnder
// 功能描述：获取尾指针
// 输入参数：void
// 输出参数：FileInfoList *
// 创建日期：08.09.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::GetEnder()
{
	return m_filFileListEnder;
}
	

//=====================================================================
// 函 数 名：GetSmallPhotoMaxWidth
// 功能描述：获取缩略图最大宽度
// 输入参数：void
// 输出参数：bool
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetSmallPhotoMaxWidth()
{
	return m_iSmallPhotoMaxWidth;
}
	

//=====================================================================
// 函 数 名：GetIsPhoto
// 功能描述：获取缩略图最大高度
// 输入参数：void
// 输出参数：bool
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetSmallPhotoMaxHeight()
{
	return m_iSmallPhotoMaxHeight;
}
	

//=====================================================================
// 函 数 名：SetSmallPhotoMaxSize
// 功能描述：设置缩略图最大尺寸
// 输入参数：int width,int height
// 输出参数：void
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetSmallPhotoMaxSize(int width,int height)
{
	m_iSmallPhotoMaxWidth=width;
	m_iSmallPhotoMaxHeight=height;
}
	

//=====================================================================
// 函 数 名：InitFileInfoControl
// 功能描述：初始化文件信息链表控制对象
// 输入参数：void
// 输出参数：void
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：在这里初始化基本变量与结构，例如文件筛选的MAP，或文件类型对应MAP等
//=====================================================================
void FileInfoControl::InitFileInfoControl()
{
	m_filFileListHeader=new FileInfoList();								//存储文件链表信息的头指针
	m_filFileListHeader->InsertNext(new FileInfoList());				//在头指针后添加一个空指针做为尾指针
	m_filFileListEnder=m_filFileListHeader->m_filNextItem;				//存储文件链表信息的尾指针

	m_bFileChooseEnable=false;											//是否筛选文件的控制变量
	m_bLoadImagePosEnable=false;										//载入Image对象的位置是否有效
	m_bLoadBaseInfoEnable=false;										//载入位置变量对载入基本信息是否有效
	m_bOrderByGroup=false;												//是否进行文件分组

	m_iTotalCount=0;													//所有文件的统计对象
	m_iFilePathCount=0;													//选择的文件夹统计
	m_iFilePathCode=0;													//选择的文件夹编号，累加不与之前重复
	m_iMaxSearchDeep=0;													//最大搜索深度
	m_iOrderType=1;														//已经进行的排序类型
	m_iOrderItem=0;														//已经进行的排序属性对象编号
	m_iGroupType=0;														//分组方式
	m_iGroupCount=0;													//分组数量统计

	m_iSmallPhotoMaxWidth=0;											//缩略图的最大宽度
	m_iSmallPhotoMaxHeight=0;											//缩略图的最大高度

	m_iFoucFileCode=-1;													//具有焦点的ITEM的编号
	m_filFoucFile=m_filFileListHeader;									//具有焦点的ITEM的FILE指针

	//将为加快访问速度的变量初始化
	_ResetSearchItems();

	m_iLoadImagePos=0;
	m_filLoadImageBegin=m_filFileListHeader->m_filNextItem;

	//文件类型筛选的map初始化
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("jpg",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("gif",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("bmp",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("tif",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("tiff",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("png",true));
	m_msbFileTypeControlMap.insert(MapStringBool::value_type("ico",true));

	//文件扩展名对应文件类型的map初始化
	m_mssFileExtName2Type.insert(MapStringString::value_type("exe","可执行文件"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("bmp","windows 位图"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("jpg","jpg图象"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("gif","gif图象"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("tiff","tiff图象"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("png","png图象"));
	m_mssFileExtName2Type.insert(MapStringString::value_type("ico","ico图标"));

	//已经选取的文件夹集合map初始化
	m_msiFilePathMap.clear();
}
	

//=====================================================================
// 函 数 名：SearchAddFile
// 功能描述：查找并添加文件夹
// 输入参数：string floderPath:文件夹的路径带"/"
//			 int searchDeep:当前搜寻深度
//			 int maxDeep:最大搜寻深度
// 输出参数：void
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：当maxDeep为-1时为无限深度的遍历，当searchDeep与maxDeep都为0时只搜索当前文件夹下
//=====================================================================
void FileInfoControl::SearchAddFile(string floderPath,int searchDeep,int maxDeep)
{
	//根据文件夹是否在被选择集合中判断文件夹下文件是否应该被添加
	bool AddFileEnable=m_msiFilePathMap[floderPath]==NULL?true:false;
	//检索对象
	CFileFind findfile;
	//将为加快访问速度的变量初始化
	_ResetSearchItems();
	//将文件夹加入已选择队列
	int floderCode=0;							//文件夹编号
	if(AddFileEnable)
	{
		floderCode=AddSelectedFloder(floderPath);
	}

	if(floderPath.compare("我的电脑\\")==0)
	{
		//当选择我的电脑时，搜索文件方式与其他文件不同
		size_t szAllDriveStrings = GetLogicalDriveStrings(0,NULL);
		char * pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];
		char * head=pDriveStrings;
		GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);
		size_t szDriveString = strlen(pDriveStrings);
		while(szDriveString > 0)
		{
			if(AddFileEnable)
			{
				//当允许添加文件时
				FileInfoList * file=_AddFile(string(pDriveStrings,strlen(pDriveStrings)-1),FILE_DISK,floderCode,0);
				file->SetFileName("本地磁盘 "+file->GetFileName());
			}
			
			pDriveStrings += szDriveString + 1;
			szDriveString = strlen(pDriveStrings);
		}
		delete head;
	}
	else
	{
		//判断是否有文件
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return ;}		//文件夹下没有文件则返回

		BOOL fileEnd=1;						//是否到达搜索文件的末尾
		
		while(fileEnd)
		{
			fileEnd=findfile.FindNextFileA();
			//当查询下一个文件成功时
			if(findfile.IsDots())
			{
				//为上级目录或本目录
				//当文件名为.或者..时不操作
			}
			else if(findfile.IsDirectory())
			{
				//当为文件夹时添加进文件链表，然后判断是否需要递归
				if(AddFileEnable)
				{
					_AddFile(findfile.GetFilePath().GetBuffer(0),FILE_FLODER,floderCode,0);
				}
				
				//当未到达最深搜索深度时
				if(searchDeep<maxDeep || maxDeep==-1)
				{
					//当需要查询子文件夹时,开始递归
					SearchAddFile(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep);
				}
			}
			//else，说明是文件
			else
			{
				if(AddFileEnable)
				{
					//当为文件时添加进文件链表,在函数中整合了文件扩展名的筛选，所以不在此进行筛选
					_AddFile(findfile.GetFilePath().GetBuffer(0),FILE_OHTER,floderCode,(LONG)(findfile.GetLength()));
				}
			}
		}
	}
}
	

//=====================================================================
// 函 数 名：AddFile
// 功能描述：添加文件
// 输入参数：string filePath:文件的路径带"/"
//			 int floderCode:所在文件夹在文件夹集合中的编号
// 输出参数：void
// 创建日期：08.10.06
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath,int floderCode)
{
	
	DWORD type=GetFileAttributes(filePath.c_str());
	type &= FILE_ATTRIBUTE_DIRECTORY;

	long fileLen=0;
	if(!type)
	{
		CFileFind ff;
		ff.FindFile(filePath.c_str());
		ff.FindNextFileA();
		fileLen=ff.GetLength();
		ff.Close();
	}

	//当为文件时添加进文件链表,在函数中整合了文件扩展名的筛选，所以不在此进行筛选
	return _AddFile(filePath,type,floderCode,fileLen);
}
	

//=====================================================================
// 函 数 名：AddFile
// 功能描述：添加文件
// 输入参数：string filePath,string floderPath
// 输出参数：
// 创建日期：08.10.07
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath,string floderPath)
{
	int floderCode=m_msiFilePathMap[floderPath];
	if(floderCode)
	{
		return AddFile(filePath,floderCode);
	}
	
	return NULL;
}
	

//=====================================================================
// 函 数 名：AddFile
// 功能描述：添加文件
// 输入参数：string filePath
// 输出参数：
// 创建日期：08.10.07
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::AddFile(string filePath)
{
	_ResetSearchItems();
	int mark=(int)filePath.find_last_of("\\/");

	string floderPath=string(filePath,0,mark+1);
	return AddFile(filePath,floderPath);
}
	

//=====================================================================
// 函 数 名：SearchDelFloderCodes
// 功能描述：查找文件夹下已经选择的文件夹编号集合
// 输入参数：string floderPath:文件夹的路径带"/"
//			 int searchDeep:当前搜寻深度
//			 int maxDeep:最大搜寻深度
//			 bool delMapIter:是否删除已选集合中的文件夹与文件对象
//			 VectorInt resVI:搜寻出的结果的集合
// 输出参数：void
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：这个函数的主要应用在于删除选取的文件夹时使用的
//=====================================================================
void FileInfoControl::SearchDelFloderCodes(string floderPath,int searchDeep,int maxDeep,bool delMapIter,VectorInt * resVI)
{
	int code=SearchDelSelectedFloder(floderPath,delMapIter);
	if(code!=-1)
	{
		//当已选择文件夹集合中有查询到的文件夹
		if(resVI!=NULL)
			resVI->push_back(code);
	}

	if(searchDeep<maxDeep || maxDeep==-1)
	{
		//当未到达最大深度时检索其子对象
		CFileFind findfile;
		//判断是否有文件
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return ;}		//文件夹下没有文件则返回
		
		while(findfile.FindNextFileA())
		{
			//当查询下一个文件成功时
			if(findfile.IsDirectory())
			{
				//当需要查询子文件夹时,开始递归
				SearchDelFloderCodes(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep,delMapIter,resVI);
			}
		}
	}
}
	

//=====================================================================
// 函 数 名：JudgeAllSelected
// 功能描述：判断文件夹下，规定深度内，是否完全被选中
// 输入参数：string floderPath:文件夹的路径带"/"
//			 int searchDeep:当前搜寻深度
//			 int maxDeep:最大搜寻深度
// 输出参数：bool 返回某文件夹下，在深度范围内，是否有未被选中项
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：返回true表示全被选中，返回false表示有未选中项
//=====================================================================
bool FileInfoControl::JudgeAllSelected(string floderPath,int searchDeep,int maxDeep)
{
	if(!m_msiFilePathMap[floderPath])
	{
		//当已选择文件夹集合中无查询到的文件夹
		return false;
	}

	if(searchDeep<maxDeep || maxDeep==-1)
	{
		//当未到达最大深度时检索其子对象
		CFileFind findfile;
		//判断是否有文件
		floderPath=floderPath+"*.*";
		BOOL bfind=findfile.FindFile(floderPath.c_str());
		if(!bfind){return true;}		//文件夹下没有文件则返回
		
		while(findfile.FindNextFileA())
		{
			//当查询下一个文件成功时
			if(findfile.IsDirectory())
			{
				//当需要查询子文件夹时,开始递归
				if(!JudgeAllSelected(findfile.GetFilePath().GetBuffer(0),searchDeep+1,maxDeep))
				{
					return false;
				}
			}
		}
	}

	return true;
}
	

//=====================================================================
// 函 数 名：OpenFloder
// 功能描述：打开一个文件夹
// 输入参数：string  floderPath:文件夹的路径带"/"
//			 int maxDeep:最大搜寻深度
// 输出参数：void
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::OpenFloder(string  floderPath,int maxDeep)
{
	//关于终止读取线程等方面的操作


	//清空已经获取的文件链表
	DisposeChoose();

	//根据文件夹路径获取文件并添加进文件链表
	SearchAddFile(floderPath,0,maxDeep);
	if(m_iTotalCount>0)
	{
		m_iFoucFileCode=0;
		m_filFoucFile=m_filFileListHeader->m_filNextItem;
	}
	else
	{
		m_iFoucFileCode=-1;
		m_filFoucFile=m_filFileListHeader;
	}

	//开启相关线程


}
	

//=====================================================================
// 函 数 名：AddFloder
// 功能描述：添加一个文件夹中的文件到链表中
// 输入参数：string  floderPath:文件夹的路径带"/"
//			 int maxDeep:最大搜寻深度
// 输出参数：void
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::AddFloder(string  floderPath,int maxDeep)
{
	//关于终止读取线程等方面的操作


	//根据文件夹路径获取文件并添加进文件链表
	SearchAddFile(floderPath,0,maxDeep);

	//开启相关线程


}
	

//=====================================================================
// 函 数 名：AddSelectedFloder
// 功能描述：添加一个文件夹到已选文件夹MAP中
// 输入参数：string  floderPath:文件夹路径
// 输出参数：int:返回文件夹的编号
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::AddSelectedFloder(string floderPath)
{
	m_iFilePathCount++;
	m_iFilePathCode++;
	m_msiFilePathMap[floderPath]=m_iFilePathCode;

	return m_iFilePathCode;
}
	

//=====================================================================
// 函 数 名：SearchDelSelectedFloder
// 功能描述：在已选文件夹MAP中查找一个文件夹，并根据参数选择是否删除文件夹与文件
// 输入参数：string  floderPath:文件夹路径
// 输出参数：int 返回该文件夹在已选集合中的编号，为-1则不存在
//			 bool delSelectedFloder:是否在集合中删除该文件夹，以及文件夹内文件
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::SearchDelSelectedFloder(string floderPath,bool delSelectedFloder)
{
	if(m_msiFilePathMap[floderPath])
	{
		int code=m_msiFilePathMap[floderPath];
		if(delSelectedFloder)
		{
			//当需要删除文件与文件夹时
			m_iFilePathCount--;
			m_msiFilePathMap.erase(m_msiFilePathMap.find(floderPath));
			m_migiGroupMap.erase(m_migiGroupMap.find(code));

			//将迭代对象设置为头指针后一个对象，即实际的开始对象
			FileInfoList * iter=m_filFileListHeader->m_filNextItem;
			//开始循环删除有效数据
			while(iter!=m_filFileListEnder)
			{
				//当迭代未到达链表结尾时
				if(iter->m_iFloderCode==code)
				{
					iter=_DelFile(iter,true);
				}
				else
				{
					iter=iter->m_filNextItem;
				}
			}
			//开始循环删除无效数据
			iter=m_filFileListEnder->m_filNextItem;
			while(!iter)
			{
				//当迭代未到达链表结尾时
				if(iter->m_iFloderCode==code)
				{
					iter=_DelFile(iter,true);
				}
				else
				{
					iter=iter->m_filNextItem;
				}
			}
		}
		return code;
	}
	else
	{
		return -1;
	}
}
	

//=====================================================================
// 函 数 名：DisposeChoose
// 功能描述：设置为无选择项
// 输入参数：void
// 输出参数：void
// 创建日期：08.09.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::DisposeChoose()
{
	//将迭代对象设置为头指针后一个对象，即实际的开始对象
	if(m_filFileListHeader == NULL)
		return;
 	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	FileInfoList * tmpIter=NULL;
	//开始循环删除数据

	//删除链表中有效数据
	while(iter!=NULL && iter!=m_filFileListEnder)
	{
		//当迭代未到达链表结尾时
		tmpIter=iter->m_filNextItem;
		iter->Dispose();
		delete iter;
		iter=tmpIter;
	}
	//删除链表中无效数据
	iter=m_filFileListEnder->m_filNextItem;
	while(iter)
	{
		//当迭代未到达链表结尾时
		tmpIter=iter->m_filNextItem;
		iter->Dispose();
		delete iter;
		iter=tmpIter;
	}

	//将链表头连到尾，将中间连接数据清除
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;
	m_filFileListEnder->m_filNextItem=NULL;

	m_iTotalCount=0;								//所有文件选择的统计
	m_iFilePathCount=0;								//选择的文件夹统计
	m_msiFilePathMap.clear();						//已经选择的文件夹的集合MAP

	//将为加快访问速度的变量初始化
	_ResetSearchItems();
}
	

//=====================================================================
// 函 数 名：DelFloder
// 功能描述：删除文件链表中一个文件夹的文件
// 输入参数：string  floderPath:文件夹的路径带"/"
//			 int maxDeep:最大搜寻深度
// 输出参数：void
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::DelFloder(string  floderPath,int maxDeep)
{
	//将为加快访问速度的变量初始化
	_ResetSearchItems();

	//搜索深度范围内的所有被选择文件夹，并在集合中删除该文件夹项
	SearchDelFloderCodes(floderPath,0,maxDeep,true,NULL);
}
	

//=====================================================================
// 函 数 名：DelFile
// 功能描述：在链表中删除一个文件
// 输入参数：FileInfoList * fileIter:文件在链表中对象
//			 ,bool disposeEnable:是否释放资源
// 输出参数：FileInfoList * 返回删除自身后，下一项地址
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::_DelFile(FileInfoList * fileIter,bool disposeEnable)
{
	if(fileIter->m_bFileEnable)
	{
		m_iTotalCount--;
	}

	FileInfoList * res=fileIter->DeleteSelf(disposeEnable);

	if(!disposeEnable)
	{
		//如果只是放到无效位置，则需要将指针放置到ENDER后
		m_filFileListEnder->InsertNext(fileIter);
	}
	return res;
}

//=====================================================================
// 函 数 名：GetFile
// 功能描述：在链表中获取count位置的文件
// 输入参数：int count:文件在链表中的位置，从0开始
// 输出参数：FileInfoList *
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
FileInfoList * FileInfoControl::GetFile(int count)
{
	if(count<0){return NULL;}

	FileInfoList * res=NULL;								//最后返回的指针存储对象
	int iterCnt;											//当前指针所在位置

	//计算需要获取的位置与链表结尾与最近取值位置的距离
	int distance=abs(m_iTotalCount-count);					//计算距离尾部距离
	distance=distance>count?count:distance;					//计算距离头尾距离的最短值
	int distanceLast=abs(m_iLastGetFilePos-count);			//计算与最近取值位置的距离

	if(distance<distanceLast)
	{
		//当距离头或尾位置更短时
		if(count<m_iTotalCount/2)
		{
			//当位置处于链表前部时，从头指针开始
			res=m_filFileListHeader->m_filNextItem;
			iterCnt=0;

			while(iterCnt<count)
			{
				res=res->m_filNextItem;
				iterCnt++;
			}
		}
		else
		{
			//当位置处于链表后半部时，从尾指针开始
			res=m_filFileListEnder->m_filUpItem;
			iterCnt=m_iTotalCount-1;						//位置从0开始，是全部文件数量-1

			while(iterCnt>count)
			{
				res=res->m_filUpItem;
				iterCnt--;
			}
		}
	}
	else
	{
		//当距离最近取值位置最短时，从最近取值位置开始
		res=m_filLastGetFileInfoP;
		iterCnt=m_iLastGetFilePos;

		if(count<m_iLastGetFilePos)
		{
			//当位置在前时，向前滚动
			while(iterCnt>count)
			{
				res=res->m_filUpItem;
				iterCnt--;
			}
		}
		else if(count>m_iLastGetFilePos)
		{
			//当位置在后时，向后滚动
			while(iterCnt<count)
			{
				res=res->m_filNextItem;
				iterCnt++;
			}
		}
		else
		{
			//当位置相同时，直接返回
			return m_filLastGetFileInfoP;
		}
	}

	m_iLastGetFilePos=iterCnt;
	m_filLastGetFileInfoP=res;
	return res;
}
	

//=====================================================================
// 函 数 名：GetFileType
// 功能描述：根据文件扩展名得出文件类型
// 输入参数：string exName:文件扩展名
// 输出参数：string
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
string FileInfoControl::GetFileType(string exName)
{
	string name=m_mssFileExtName2Type[exName];
	if(name.compare("")==0)
	{
		return exName+"文件";
	}

	return name;
}
	

//=====================================================================
// 函 数 名：SortAttribute
// 功能描述：对链表进行排序
// 输入参数：int INFO_TYPE:在FileInfoList.h中定义的宏
//			 int sortOrder:排序方式--0：升序-1：降序
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SortAttribute(int INFO_TYPE,int sortOrder)
{
	if(sortOrder==0)
	{
		//升序排列
		SortAsc(INFO_TYPE);
	}
	else if(sortOrder==1)
	{
		//降序排列
		SortDes(INFO_TYPE);
	}
	else
	{
	}
}
	

//=====================================================================
// 函 数 名：InsertItemByOrder
// 功能描述：按顺序插入新的文件对象
// 输入参数：FileInfoList * item:需要插入的文件对象
//			 int INFO_TYPE:在FileInfoList.h中定义的宏
//			 int sortOrder:排序方式--0：升序-1：降序
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::InsertItemByOrder(FileInfoList * item,int INFO_TYPE,int sortOrder)
{
	if(sortOrder==0)
	{
		//升序排列
		InsertItemAsc(INFO_TYPE,item);
	}
	else if(sortOrder==1)
	{
		//降序排列
		InsertItemDes(INFO_TYPE,item);
	}
	else
	{
		if(item->CheckFileType(FILE_FLODER))
		{
			m_filFileListHeader->InsertNext(item);
		}
		else
		{
			m_filFileListEnder->InsertFront(item);
		}
	}
}
	

//=====================================================================
// 函 数 名：SortAsc
// 功能描述：升序排列
// 输入参数：int INFO_TYPE:在FileInfoList.h中定义的宏
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SortAsc(int INFO_TYPE)
{
	//将为加快访问速度的变量初始化
	_ResetSearchItems();

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	//将链表头尾相连，排序时直接插入
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;

	while(iter!=m_filFileListEnder)
	{
		FileInfoList * tmp=iter;
		iter=iter->m_filNextItem;

		InsertItemAsc(INFO_TYPE,tmp);
	}

	m_iOrderType=0;					//设置链表排序方式
	m_iOrderItem=INFO_TYPE;			//设置排序所使用的属性列
}
	

//=====================================================================
// 函 数 名：InsertItemAsc
// 功能描述：升序插入对象
// 输入参数：int INFO_TYPE:在FileInfoList.h中定义的宏
//			 FileInfoList * item:需要插入的对象
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::InsertItemAsc(int INFO_TYPE,FileInfoList * item)
{
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;

	while(tmpIter!=m_filFileListEnder)
	{
		if(m_bOrderByGroup)
		{
			//当进行了分组时，分组顺序优先
			int comRes=_CompareGroup(tmpIter,item);
			if(comRes>0)
			{
				break;
			}
			if(comRes<0)
			{
				tmpIter=tmpIter->m_filNextItem;
				continue;
			}
		}

		if(_CompareFileInfo(tmpIter,item,INFO_TYPE)<=0)
		{
			tmpIter=tmpIter->m_filNextItem;
		}
		else
		{
			break;
		}
	}
	tmpIter->InsertFront(item);
}
	

//=====================================================================
// 函 数 名：SortDes
// 功能描述：降序排列
// 输入参数：int INFO_TYPE:在FileInfoList.h中定义的宏
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SortDes(int INFO_TYPE)
{
	//将为加快访问速度的变量初始化
	_ResetSearchItems();

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	//将链表头尾相连，排序时直接插入
	m_filFileListHeader->m_filNextItem=m_filFileListEnder;
	m_filFileListEnder->m_filUpItem=m_filFileListHeader;

	while(iter!=m_filFileListEnder)
	{
		FileInfoList * tmp=iter;
		iter=iter->m_filNextItem;

		InsertItemDes(INFO_TYPE,tmp);
	}

	m_iOrderType=1;					//设置链表排序方式
	m_iOrderItem=INFO_TYPE;			//设置排序所使用的属性列
}
	


//=====================================================================
// 函 数 名：InsertItemDes
// 功能描述：降序插入对象
// 输入参数：int INFO_TYPE:在FileInfoList.h中定义的宏
//			 FileInfoList * item:需要插入的对象
// 输出参数：void
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::InsertItemDes(int INFO_TYPE,FileInfoList * item)
{
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;

	while(tmpIter!=m_filFileListEnder)
	{
		if(m_bOrderByGroup)
		{
			//当进行了分组时，分组顺序优先
			int comRes=_CompareGroup(tmpIter,item);
			if(comRes>0)
			{
				break;
			}
			if(comRes<0)
			{
				tmpIter=tmpIter->m_filNextItem;
				continue;
			}
		}

		if(_CompareFileInfo(tmpIter,item,INFO_TYPE)>=0)
		{
			tmpIter=tmpIter->m_filNextItem;
		}
		else
		{
			break;
		}
	}
	tmpIter->InsertFront(item);
}
	

//=====================================================================
// 函 数 名：GroupByFileName
// 功能描述：按文件名进行分组排列
// 输入参数：
// 输出参数：void
// 创建日期：08.09.28
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::GroupByFileName()
{
	//循环检查，建立分组，之后根据分组进行排序
	FileInfoList * tmpIter=m_filFileListHeader->m_filNextItem;
	map<WCHAR,int> GroupExistMap;			//已经存在的分组信息MAP
	m_iGroupCount=0;						//分组数量统计变量
	m_migiGroupMap.clear();

	while(tmpIter!=m_filFileListEnder)
	{
		//获取文件名第一个字符，因为可能要判断中文的问题，所以将其转化为w_char
		USES_CONVERSION;
		LPWSTR tmpS=A2W(tmpIter->GetFileName().c_str());
		WCHAR wc=tmpS[0];

		if(!GroupExistMap[wc])
		{
			//当存在的分组信息表中不存在该分组时建立新的分组
			GroupExistMap[wc]=m_iGroupCount+1;		//存储时将INT+1，则INT必大于0
			GroupInfo * info=new GroupInfo();
			info->groupName=wc;
			info->itemCount=0;
			info->seledItemCount=0;
			m_migiGroupMap.insert(MapIntGInfo::value_type(m_iGroupCount,info));
			//分组统计增加
			m_iGroupCount++;
		}

		//获取分组信息，并处理
		int n=GroupExistMap[wc]-1;		//获取编号时需要-1还原
		GroupInfo * info=m_migiGroupMap[n];
		info->itemCount++;
		if(tmpIter->GetState(LVIS_SELECTED))
		{
			//当ITEM被选中则相关分组信息中被选中ITEM统计+1
			info->seledItemCount++;
		}
		tmpIter->m_iGroupId=n;

		//滚动至下一条
		tmpIter=tmpIter->m_filNextItem;
	}

	//设置分组为真
	m_bOrderByGroup=true;


	if(m_iOrderType)
	{
		//当m_iOrderType==1时，原本列表是降序排序方式
		SortDes(m_iOrderItem);
	}
	else
	{
		SortAsc(m_iOrderItem);
	}
}
	

//=====================================================================
// 函 数 名：DisGroup
// 功能描述：不进行分组
// 输入参数：
// 输出参数：void
// 创建日期：08.09.28
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::DisGroup()
{
	m_bOrderByGroup=false;
}
	

//=====================================================================
// 函 数 名：GetSelectedFileList
// 功能描述：筛选被选中的文件
// 输入参数：CStringList * resultList:
//			,UINT selectType:筛选标志
// 输出参数：int:返回被总体字符串的长度
// 创建日期：08.10.06
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetSelectedFileList(CStringList * resultList,UINT selectType)
{
	int len=0;			//存储总文件长度（每个文件名需要+1长度）

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED) && iter->CheckFileType(selectType))
		{
			//当文件被选择时
			CString s=iter->GetFileFullPath().c_str();
			resultList->AddTail(s);
			len+=strlen(s)+1;			//字符串结尾存在"\0"所以+1
		}

		iter=iter->m_filNextItem;
	}

	return len;
}
	

//=====================================================================
// 函 数 名：GetSelectedFileType
// 功能描述：获取所有被选中文件类型的表示符
// 输入参数：
// 输出参数：UINT:类型表示符号
// 创建日期：08.10.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
UINT FileInfoControl::GetSelectedFileType()
{
	UINT type=0;

	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//当文件被选择时
			type|=iter->m_uiFileType;
		}

		iter=iter->m_filNextItem;
	}

	return type;
}
	

//=====================================================================
// 函 数 名：DelSelectedFile
// 功能描述：从链表中将选中文件设置到无效位置
// 输入参数：
// 输出参数：
// 创建日期：08.10.06
// 修改日期：08.10.09
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::DelSelectedFile()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//当文件被选择时
			iter=_DelFile(iter,false);
		}
		else
		{
			iter=iter->m_filNextItem;
		}
	}
}
	

//=====================================================================
// 函 数 名：CheckSelectedFile
// 功能描述：检查已选择文件，当文件未选择时从链表删除文件
// 输入参数：
// 输出参数：
// 创建日期：08.10.06
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::CheckSelectedFile()
{
	int count=0;
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			//当文件被选择时
			if(access(iter->GetFileFullPath().c_str(),0)!=0)
			{
				//当文件不存在时
				iter=_DelFile(iter,true);
				count++;
				continue;
			}
		}

		iter=iter->m_filNextItem;
	}

	if(!count)
	{
		_ResetSearchItems();
	}

	return count;
}
	

//=====================================================================
// 函 数 名：SetAllState
// 功能描述：设置所有项的状态
// 输入参数：UINT state,bool changeAll,UINT mask
// 输出参数：
// 创建日期：08.10.07
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetAllState(UINT state,bool changeAll,UINT mask)
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	while(iter!=m_filFileListEnder)
	{
		iter->SetState(state,changeAll,mask);

		iter=iter->m_filNextItem;
	}
}
	

//=====================================================================
// 函 数 名：GetFloderCode
// 功能描述：设置所有项的状态
// 输入参数：UINT state,bool changeAll,UINT mask
// 输出参数：
// 创建日期：08.10.07
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetFloderCode(string floderPath)
{
	int floderCode=m_msiFilePathMap[floderPath];
	
	return floderCode;
}
	

//=====================================================================
// 函 数 名：DealSelectedFile
// 功能描述：从链表中删除被选中的文件
// 输入参数：string newFloderPath,UINT dealType:dealType为0：拷贝，1：剪切
// 输出参数：
// 创建日期：08.10.08
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::DealSelectedFile(string newFloderPath,UINT dealType,UINT cutOrCopy)
{
	int count=0;
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	if(cutOrCopy==DEAL_FILE_CUT)
	{
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//当文件被选择时
				iter->ICutFile(newFloderPath,dealType);
			}

			iter=iter->m_filNextItem;
		}
	}
	else if(cutOrCopy==DEAL_FILE_COPY)
	{
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//当文件被选择时
				iter->ICopyFile(newFloderPath,dealType);
			}

			iter=iter->m_filNextItem;
		}
	}

	return count;
}
	

//=====================================================================
// 函 数 名：DealSelectedFile
// 功能描述：拷贝或剪切已选择文件到剪切板
// 输入参数：UINT cutOrCopy为0：拷贝，1：剪切
// 输出参数：
// 创建日期：08.10.08
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::DealSelectedFile(UINT cutOrCopy)
{
	int count=0;
	
	//选中的文件列表
	CStringList csList;
	//获得选中的文件列表CStringList
	int len=GetSelectedFileList(&csList,FILE_ALL);

	//申请内存
	HGLOBAL hMemData = GlobalAlloc(GPTR,len);
	ASSERT(hMemData != NULL);   

	//锁定分配的内存，内存的值为char*类型   
	char * lpDropFiles = (char *)GlobalLock(hMemData);  
	//CStringList的起始位置
	POSITION pItemPos = csList.GetHeadPosition();
	char * pszStart = lpDropFiles;   
	while(pItemPos != NULL)     
	{   
		lstrcpy(pszStart, (LPCTSTR)csList.GetNext(pItemPos));   
		pszStart = strchr(pszStart,'\0')   +   1;   //下次的起始位置是上一次结尾+1   
	} 
	//把选中的文件放入剪贴板
	if(cutOrCopy==DEAL_FILE_COPY)
	{
		//拷贝
		PublicFunc::CutOrCopyFiles(lpDropFiles,len,TRUE);
	}
	else
	{
		//剪切
		PublicFunc::CutOrCopyFiles(lpDropFiles,len,FALSE);
	}
	//解锁内存
	GlobalUnlock(hMemData);

	return count;
}
	

//=====================================================================
// 函 数 名：GetFirstSelectedCode
// 功能描述：获取第一个被选择的ITEM的编号
// 输入参数：
// 输出参数：
// 创建日期：08.10.08
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetFirstSelectedCode()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	int i=0;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED))
		{
			return i;
		}

		i++;
		iter=iter->m_filNextItem;
	}

	return -1;
}
	

//=====================================================================
// 函 数 名：GetFirstSelectedPhotoCode
// 功能描述：获取第一个被选择的图象的编号
// 输入参数：
// 输出参数：
// 创建日期：08.10.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::GetFirstSelectedPhotoCode()
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	int i=0;
	while(iter!=m_filFileListEnder)
	{
		if(iter->GetState(LVIS_SELECTED) && iter->CheckFileType(FILE_PHOTO))
		{
			return i;
		}

		i++;
		iter=iter->m_filNextItem;
	}

	return -1;
}
		

//=====================================================================
// 函 数 名：SetSelectedLvOrType
// 功能描述：获取第一个被选择的ITEM的编号
// 输入参数：int value:设置的值
//			 UINT dealTarget:设置的类型，根据DEAL_DRAG_LV或DEAL_DRAG_TYPE判断
// 输出参数：
// 创建日期：08.10.09
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetSelectedLvOrType(int value,UINT dealTarget)
{
	FileInfoList * iter=m_filFileListHeader->m_filNextItem;
	if(dealTarget==DEAL_DRAG_LV)
	{
		//修改评级信息时
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//当ITEM被选中时
				iter->m_iPhotoLevel=value;
			}
	
			iter=iter->m_filNextItem;
		}
	}
	else if(dealTarget==DEAL_DRAG_TYPE)
	{
		//修改类型信息时
		while(iter!=m_filFileListEnder)
		{
			if(iter->GetState(LVIS_SELECTED))
			{
				//当ITEM被选中时
				iter->m_iPhotoTypeCode=value;
			}
	
			iter=iter->m_filNextItem;
		}
	}

}
//=====================================================================
// 函 数 名：SetItemLvOrType
// 功能描述：获取第一个被选择的ITEM的编号
// 输入参数：int nItem:设置的对象编号
//			 int value:设置的值
//			 UINT dealTarget:设置的类型，根据DEAL_DRAG_LV或DEAL_DRAG_TYPE判断
// 输出参数：
// 创建日期：08.10.09
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetItemLvOrType(int nItem,int value,UINT dealTarget)
{
	FileInfoList * file=GetFile(nItem);

	if(dealTarget==DEAL_DRAG_LV)
	{
		//修改评级信息时
		file->m_iPhotoLevel=value;
	}
	else if(dealTarget==DEAL_DRAG_TYPE)
	{
		//修改类型信息时
		file->m_iPhotoTypeCode=value;
	}
}
	

//=====================================================================
// 函 数 名：SetItemFouc
// 功能描述：设置编号位置的ITEM为具有焦点的ITEM
// 输入参数：int nItem:设置的对象编号,FileInfoList * fileInfo=NULL
// 输出参数：
// 创建日期：08.10.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetItemFouc(int nItem,FileInfoList * fileInfo)
{
	FileInfoList * file=fileInfo?fileInfo:GetFile(nItem);
	m_filFoucFile->SetState(~LVIS_FOCUSED,false,LVIS_FOCUSED);
	file->SetState(LVIS_FOCUSED,false,LVIS_FOCUSED);
	m_iFoucFileCode=nItem;
	m_filFoucFile=file;
}
	

//=====================================================================
// 函 数 名：SetFoucToItemState
// 功能描述：设置从焦点ITEM开始到指定编号的ITEM的状态
// 输入参数：int nItem
// 输出参数：
// 创建日期：08.10.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::SetFoucToItemState(int nItem)
{
	if(m_iFoucFileCode<0)
	{
		return ;
	}

	if(nItem>m_iFoucFileCode)
	{
		FileInfoList * iter=m_filFoucFile;
		int i=m_iFoucFileCode;
		while(i<=nItem)
		{
			iter->SetState(LVIS_SELECTED,false,LVIS_SELECTED);
			i++;
			iter=iter->m_filNextItem;
		}
	}
	else
	{
		FileInfoList * iter=m_filFoucFile;
		int i=m_iFoucFileCode;
		while(i>=nItem)
		{
			iter->SetState(LVIS_SELECTED,false,LVIS_SELECTED);
			i--;
			iter=iter->m_filUpItem;
		}
	}
}
	

//=====================================================================
// 函 数 名：AddFile
// 功能描述：添加一个文件到链表中
// 输入参数：string  fileFullPath:文件的完整路径
//			 bool isDirectory:是否文件夹
//			 int floderCode:所在文件夹在已经选择文件夹集合中的编号
//			 LONG fileLength:文件长度
// 输出参数：FileInfoList *
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：在本函数中包含了对文件扩展名的筛选
//=====================================================================
FileInfoList * FileInfoControl::_AddFile(string  fileFullPath,UINT fileType,int floderCode,LONG fileLength)
{
	FileInfoList * item=new FileInfoList(fileFullPath,fileType,fileLength);
	item->m_iFloderCode=floderCode;

	if(item->CheckFileType(FILE_FLODER))
	{
		//当为文件夹时
		item->m_sFileType="文件夹";
	}
	else
	{
		//当为文件时
 		if(m_msbFileTypeControlMap[item->GetFileExtName()])
		{
			//当筛选项为true时，添加进文件链表，并设置为图象
			item->SetFileType(FILE_PHOTO);
			item->m_sFileType=GetFileType(item->GetFileExtName());
		}
		else
		{
			if(!m_bFileChooseEnable)
			{
				//当不需要通过筛选时
				if(m_msbFileTypeControlMap[item->GetFileExtName()])
				{
					//当文件扩展名在筛选表中存在，则表示文件为图象
					item->SetFileType(FILE_PHOTO);
				}
				item->m_sFileType=GetFileType(item->GetFileExtName());
			}
			else
			{
				item->m_bFileEnable=false;		//设置文件无效
			}
		}
	}

	if(item->m_bFileEnable)
	{
		//当文件有效时，正常插入，当文件无效时插入到末尾节点后
		//按排序方式与排序属性插入文件
		m_iTotalCount++;
		InsertItemByOrder(item,m_iOrderItem,m_iOrderType);
	}
	else
	{
		m_filFileListEnder->InsertNext(item);
	}

	return item;
}
	

//=====================================================================
// 函 数 名：ResetSearchItems
// 功能描述：重新设置查询相关对象
// 输入参数：void
// 输出参数：void
// 创建日期：08.09.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void FileInfoControl::_ResetSearchItems()
{
	m_iLastGetFilePos=-1;								//最后获取的文件位置，主要用于加快搜索速度
	m_filLastGetFileInfoP=m_filFileListHeader;			//最后获取的文件的指针，与位置配合使用加快搜索速度
}
	

//=====================================================================
// 函 数 名：CompareFileInfo
// 功能描述：对两个文件对象进行比较
// 输入参数：FileInfoList * item1,FileInfoList * item2
//			 int INFO_TYPE:在FileInfoList.h中定义的宏
// 输出参数：int:-1则前者小，0相等，1后者小
// 创建日期：08.09.12
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::_CompareFileInfo(FileInfoList * item1,FileInfoList * item2,int INFO_TYPE)
{
	if(item1->CheckFileType(FILE_FLODER) && !item2->CheckFileType(FILE_FLODER))
	{
		return 1;
	}
	else if(!item1->CheckFileType(FILE_FLODER) && item2->CheckFileType(FILE_FLODER))
	{
		return -1;
	}
	else
	{
		return item1->GetFileBaseInfo(INFO_TYPE).compare(item2->GetFileBaseInfo(INFO_TYPE));
	}
}
	

//=====================================================================
// 函 数 名：_CompareGroup
// 功能描述：对两个文件对象进行比较
// 输入参数：FileInfoList * item1,FileInfoList * item2
// 输出参数：int:-1则前者小，0相等，1后者小
// 创建日期：08.09.28
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
int FileInfoControl::_CompareGroup(FileInfoList * item1,FileInfoList * item2)
{
	if(item1->m_iGroupId<item2->m_iGroupId)
	{
		return -1;
	}
	else if(item1->m_iGroupId>item2->m_iGroupId)
	{
		return 1;
	}
	return 0;
}