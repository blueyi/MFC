#pragma once

#include <map>
#include <vector>
#include "FileInfoList.h"
#include "PublicFunc.h"

using namespace std;

//文件分组的分组信息存储结构
struct GroupInfo
{
	WCHAR groupName;
	int itemCount;
	int seledItemCount;
};

typedef map<string,bool>	MapStringBool;
typedef map<string,string>	MapStringString;
typedef map<string,int>		MapStringInt;
typedef map<int,GroupInfo *>	MapIntGInfo;
typedef map<string,HANDLE>		MapStringHandle;		//用于创建文件夹监控线程

typedef vector<int>			VectorInt;

//=====================================================================
// 函 数 名：MonitorFloder
// 功能描述：监控文件夹内文件修改的线程
// 输入参数：LPVOID lpParameter带入文件夹路径字符串的指向指针
// 输出参数：DWORD WINAPI
// 创建日期：08.10.10
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
DWORD WINAPI MonitorFloder(LPVOID lpParameter);

class FileInfoControl
{
public:
	FileInfoControl(void);
	~FileInfoControl(void);

// Attributes //属性, 品质, 特征, 加于, 归结
public:
	bool m_bFileChooseEnable;						//是否筛选文件的控制变量
	bool m_bLoadImagePosEnable;						//载入位置变量对载入Image对象是否有效
	bool m_bLoadBaseInfoEnable;						//载入位置变量对载入基本信息是否有效
	bool m_bOrderByGroup;							//是否进行文件分组

	int m_iTotalCount;								//所有文件的统计对象
	int m_iLastGetFilePos;							//最后获取的文件位置，主要用于加快搜索速度
	int m_iFilePathCount;							//选择的文件夹统计
	int m_iFilePathCode;							//选择的文件夹编号，累加不与之前重复
	int m_iMaxSearchDeep;							//最大搜索深度
	int m_iOrderType;								//已经进行的排序类型
	int m_iOrderItem;								//已经进行的排序属性对象编号
	int m_iLoadImagePos;							//载入Image对象的位置
	int m_iGroupType;								//分组方式	暂时只设文件名分组
	int m_iGroupCount;								//分组数量统计
	int m_iFoucFileCode;							//具有焦点的ITEM的编号
	
	int m_iSmallPhotoMaxWidth;						//缩略图的最大宽度
	int m_iSmallPhotoMaxHeight;						//缩略图的最大高度

	FileInfoList * m_filFoucFile;					//具有焦点的ITEM的FILE指针
	FileInfoList * m_filLastGetFileInfoP;			//最后获取的文件的指针，与位置配合使用加快搜索速度
	FileInfoList * m_filLoadImageBegin;				//载入Image对象的开始位置指针

	MapStringBool m_msbFileTypeControlMap;			//文件类型筛选的map
	MapStringString m_mssFileExtName2Type;			//文件扩展名对应文件类型的map
	MapStringInt m_msiFilePathMap;					//已经选取的文件夹集合map
	MapIntGInfo m_migiGroupMap;						//进行文件分组后分组信息存储位置

protected:
	FileInfoList * m_filFileListHeader;				//存储文件链表信息的头指针
	FileInfoList * m_filFileListEnder;				//存储文件链表信息的尾指针

// Operations //运转, 操作, 实施, 作用, 业务, 工作, 手术, 军事行动
public:
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
	FileInfoList * GetHeader();
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
	FileInfoList * GetEnder();
	//=====================================================================
	// 函 数 名：GetSmallPhotoMaxWidth
	// 功能描述：获取缩略图最大宽度
	// 输入参数：void
	// 输出参数：int
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int GetSmallPhotoMaxWidth();
	//=====================================================================
	// 函 数 名：GetIsPhoto
	// 功能描述：获取缩略图最大高度
	// 输入参数：void
	// 输出参数：int
	// 创建日期：08.09.10
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int GetSmallPhotoMaxHeight();
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
	void SetSmallPhotoMaxSize(int width,int height);

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
	void InitFileInfoControl();
	//=====================================================================
	// 函 数 名：SearchAddFile
	// 功能描述：查找的文件夹
	// 输入参数：string floderPath:文件夹的路径带"/"
	//			 int searchDeep:当前搜寻深度
	//			 int maxDeep:最大搜寻深度
	// 输出参数：void
	// 创建日期：08.09.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void SearchAddFile(string floderPath,int searchDeep,int maxDeep);
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
	FileInfoList * AddFile(string filePath,int floderCode);
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
	FileInfoList * AddFile(string filePath,string floderPath);
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
	FileInfoList * AddFile(string filePath);
	//=====================================================================
	// 函 数 名：SearchDelFloderCodes
	// 功能描述：查找文件夹下已经选择的文件夹编号集合
	// 输入参数：string floderPath:文件夹的路径带"/"
	//			 int searchDeep:当前搜寻深度
	//			 int maxDeep:最大搜寻深度
	//			 bool delMapIter:是否删除已选集合中的文件夹对象
	//			 VectorInt resVI:搜寻出的结果的集合
	// 输出参数：void
	// 创建日期：08.09.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：这个函数的主要应用在于删除选取的文件夹时使用的
	//=====================================================================
	void SearchDelFloderCodes(string floderPath,int searchDeep,int maxDeep,bool delMapIter,VectorInt * resVI);
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
	bool JudgeAllSelected(string floderPath,int searchDeep,int maxDeep);
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
	void OpenFloder(string floderPath,int maxDeep);
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
	void AddFloder(string  floderPath,int maxDeep);
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
	int AddSelectedFloder(string  floderPath);
	//=====================================================================
	// 函 数 名：SearchDelSelectedFloder
	// 功能描述：在已选文件夹MAP中查找一个文件夹，并根据参数选择是否删除文件夹与文件
	// 输入参数：string  floderPath:文件夹路径
	// 输出参数：int 返回该文件夹在已选集合中的编号，为-1则不存在
	//			 bool delSelectedFloder:是否在集合中删除该文件夹
	// 创建日期：08.09.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int SearchDelSelectedFloder(string floderPath,bool delSelectedFloder);
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
	void DisposeChoose();
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
	void DelFloder(string  floderPath,int maxDeep);

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
	FileInfoList * GetFile(int count);
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
	string GetFileType(string exName);
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
	void SortAttribute(int INFO_TYPE,int sortOrder);
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
	void InsertItemByOrder(FileInfoList * item,int INFO_TYPE,int sortOrder);
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
	void SortAsc(int INFO_TYPE);
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
	void InsertItemAsc(int INFO_TYPE,FileInfoList * item);
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
	void SortDes(int INFO_TYPE);
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
	void InsertItemDes(int INFO_TYPE,FileInfoList * item);
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
	void GroupByFileName();
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
	void DisGroup();
	//=====================================================================
	// 函 数 名：GetSelectedFileList
	// 功能描述：筛选被选中的文件
	// 输入参数：CStringList * resultList:存储被选中文件路径的集合
	//			,UINT selectType:筛选标志
	// 输出参数：int:返回被总体字符串的长度
	// 创建日期：08.10.06
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int GetSelectedFileList(CStringList * resultList,UINT selectType);
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
	UINT GetSelectedFileType();
	//=====================================================================
	// 函 数 名：DelSelectedFile
	// 功能描述：从链表中将选中文件设置到无效位置
	// 输入参数：
	// 输出参数：
	// 创建日期：08.10.06
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void DelSelectedFile();
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
	int CheckSelectedFile();
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
	void SetAllState(UINT state,bool changeAll,UINT mask);
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
	int GetFloderCode(string floderPath);
	//=====================================================================
	// 函 数 名：DealSelectedFile
	// 功能描述：拷贝或剪切已选择文件到目录
	// 输入参数：string newFloderPath,UINT dealType:dealType,UINT cutOrCopy为0：拷贝，1：剪切
	// 输出参数：
	// 创建日期：08.10.08
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int DealSelectedFile(string newFloderPath,UINT dealType,UINT cutOrCopy);
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
	int DealSelectedFile(UINT cutOrCopy);
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
	int GetFirstSelectedCode();
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
	int GetFirstSelectedPhotoCode();
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
	void SetSelectedLvOrType(int value,UINT dealTarget);
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
	void SetItemLvOrType(int nItem,int value,UINT dealTarget);
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
	void SetItemFouc(int nItem,FileInfoList * fileInfo=NULL);
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
	void SetFoucToItemState(int nItem);

protected:
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
	FileInfoList * _AddFile(string  fileFullPath,UINT fileType,int floderCode,LONG fileLength=0);
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
	FileInfoList * _DelFile(FileInfoList * fileIter,bool disposeEnable);
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
	void _ResetSearchItems();
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
	int _CompareFileInfo(FileInfoList * item1,FileInfoList * item2,int INFO_TYPE);
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
	int _CompareGroup(FileInfoList * item1,FileInfoList * item2);
// Overridables //可重载的

// Implementation //实现

};
/**
*	文件在详细信息列表中需要显示出来的属性值
*	1:文件大小
*	2:文件类型
*	3:文件创建时间
*	4:文件修改时间
*	5:文件访问时间
*	6:图象分辨率
*	7:拍照日期
*	8:
*/