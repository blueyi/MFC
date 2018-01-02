#if !defined _TYPE_H_
#define _TYPE_H_

////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct tagFILETYPE				// 自定义的数据库文件格式
{
	char Flag[4];						// 标志,我的是"QDB\0"
    long rCount;						// 总记录数
	long rLen;							// 每个记录长度
	char rev[116];                      // 保留字节,作为以后扩展用
}FILETYPE;

typedef  struct  tagDATA
{
	char name[80];						// 公司名称                           
	char rev1;							// 保留字节,恒为零,作身份证号码的结尾
	char add[60];						// 公司地址
	char rev2;							// 保留字节,恒为零,作会员卡号码的结尾
	char industry[60];					// 行业
	char rev3;							// 保留字节,恒为零,作会员卡号码的结尾
	char scale[60];						// 规模
	char rev4;							// 保留字节,恒为零,作姓名的结尾
	char contact[60];				    // 联系方式
	char rev5;							// 保留字节,恒为零,作手机号码的结尾
	char attrib[40];				    // 性质
	char rev6;							// 保留字节,恒为零,作手机号码的结尾
	char source[60];                    // 信息来源     
	char rev7;							// 保留字节,恒为零,作手机号码的结尾
	char npost[40];                     // 职务名称     
	char rev8;							// 保留字节,恒为零,作手机号码的结尾
	char salary[40];                    // 薪水描述     
	char rev9;							// 保留字节,恒为零,作手机号码的结尾
	char stype;                         // 按月或者按年
    char x1;
	char x2;
	char x3;
	char c1;
	char c2;
	char c3;
 	char end;
	char date[14];
	char rev10;
	char introduction[800];             // 简单介绍     
	char rev11;							// 保留字节,恒为零,作手机号码的结尾
    char level[800];                    // 水平要求
	char rev12;
	char ls;                            //评价
	char lsinfo[800];
	char rev13;
	char rev[136];

}MYDATA;

typedef struct tagRECORD                // 数据记录双链表
{
	MYDATA    *Data;                    // 当前数据管家
    struct     tagRECORD *prev;         // 上一数据记录
	struct     tagRECORD *next;         // 下一数据记录
}RECORD;

////////////////////////////////////////////////////////////////////////////////////////////////
#endif 

