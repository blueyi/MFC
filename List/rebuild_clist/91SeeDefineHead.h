//获取文件基本信息的宏对应值
#define	FILE_NAME				0
#define	FILE_SIZE				1
#define FILE_TYPE				2
#define	FILE_CREATE_TIME		3
#define	FILE_CHANGE_TIME		4
#define	FILE_EDIT_TIME			5
#define	FILE_PHOTO_SIZE			6
#define	FILE_TAKE_PHOTO_TIME	7

#define ORDER_NONE				0x0000
#define ORDER_ASC				0x0001					//升序排列
#define ORDER_DES				0x0002					//降序排列

//鼠标位置信息
#define POSITION_OUT						0x0000		//在窗口外
#define POSITION_HEAD_ITEM					0x0001		//在栏目头的列标题上
#define POSITION_HEAD_MID					0x0002		//在栏目头的列间隔间
#define POSITION_SCROLL_BAR_V_DRAG_SPACE	0x0004		//在垂直拖动条的拖拽空白区域上
#define POSITION_SCROLL_BAR_V_UP_BT			0x0008		//在垂直拖动条向上按钮上
#define POSITION_SCROLL_BAR_V_MID_BT		0x0010		//在垂直拖动条拖动划块上
#define POSITION_SCROLL_BAR_V_DOWN_BT		0x0020		//在垂直拖动条向下按钮上
#define POSITION_SCROLL_BAR_H_DRAG_SPACE	0x0040		//在水平拖动条的拖拽空白区域上
#define POSITION_SCROLL_BAR_H_LEFT_BT		0x0080		//在水平拖动条向左按钮上
#define POSITION_SCROLL_BAR_H_MID_BT		0x0100		//在水平拖动条拖动划块上
#define POSITION_SCROLL_BAR_H_RIGHT_BT		0x0200		//在水平拖动条向右按钮上
#define POSITION_ITEM						0x0400		//在显示区域中的ITEM上
#define POSITION_WORKAREA_NONE				0x0800		//在显示区域中的空白区域上

//鼠标操作信息
#define MOUSE_NONE				0x0000					//无状态
#define MOUSE_LBT_DOWN			0x0001					//鼠标左键按下
#define MOUSE_RBT_DOWN			0x0002					//鼠标右键按下
#define MOUSE_MBT_DOWN			0x0004					//鼠标中键按下
#define MOUSE_DRAG_FILE			0x0008					//拖拽文件
#define MOUSE_DRAG_SELECT		0x0010					//拖拽选择
#define MOUSE_DRAG_SCROLL_V		0x0020					//拖拽纵向滑动条划块
#define MOUSE_DRAG_SCROLL_H		0x0040					//拖拽横向滑动条划块
#define MOUSE_SCROLL_V_UP		0x0080					//按住纵向向上按钮
#define MOUSE_SCROLL_V_DOWN		0x0100					//按住纵向向下按钮
#define MOUSE_SCROLL_H_LEFT		0x0200					//按住横向向左按钮
#define MOUSE_SCROLL_H_RIGHT	0x0400					//按住横向向右按钮
#define MOUSE_SCROLL_V_AREA		0x0800					//按住纵向滑动条的空白区域
#define MOUSE_SCROLL_H_AREA		0x1000					//按住横向滑动条的空白区域
#define MOUSE_DRAG_HEAD_ITEM	0x2000					//拖动表头栏目
#define MOUSE_DRAG_HEAD_MID		0x4000					//修改表头栏目宽度

#define FILE_UNDEF				0x0000
#define FILE_DISK				0x0001
#define FILE_FLODER				0x0002
#define FILE_PHOTO				0x0004
#define FILE_OHTER				0x0008
#define FILE_ALL				0xffff

#define STYLE_REPORT			0x0001					//详细列表形式
#define STYLE_ICON				0x0002					//图标形式
#define STYLE_LIST				0x0004					//列表形式
#define STYLE_SMALL_PHOTO		0x0008					//缩略图形式
#define STYLE_PPT				0x0010					//幻灯片形式
#define STYLE_PICASA			0x0011					//PICASA形式

#define HEAD_ALI_LEFT			0x0001					//内容左对齐
#define HEAD_ALI_RIGHT			0x0002					//内容右对齐
#define HEAD_ALI_CENTER			0x0004					//内容居中

#define DEAL_FILE_COPY			0						//文件拷贝
#define DEAL_FILE_CUT			1						//剪切
#define DEAL_ASK				0						//询问
#define DEAL_RENAME				1						//重命名
#define DEAL_RECOVER			2						//覆盖
#define DEAL_PASS				3						//忽略
#define DEAL_DRAG_LV			0						//拖拽评级
#define DEAL_DRAG_TYPE			1						//拖拽类型

#define PHOTO_MAX_WIDTH			320						//缩略图最大宽度
#define PHOTO_MAX_HEIGHT		240						//缩略图最大高度
#define REPORT_ITEM_HEIGHT		20						//REPORT样式时ITEM的高度
#define REPORT_HEAD_HEIGHT		20						//REPORT样式表头的高度

#define STATE_NONE				0x0000					//正常状态
#define STATE_MOUSE_OVER		0x0001					//鼠标在范围内
#define STATE_MOUSE_LDOWN		0x0002					//鼠标左键按下
#define STATE_MOUSE_RDOWN		0x0004					//鼠标右键按下
#define STATE_MOUSE_MDOWN		0x0008					//鼠标中键按下		

#define SCROLL_BAR_NONE					0x0000			//无拖动条
#define SCROLL_BAR_H					0x0001			//横向拖动条
#define SCROLL_BAR_V					0x0002			//竖向拖动条
#define SCROLL_BAR_WIDTH_HEIGHT			20				//拖动条的宽度或高度
#define SCROLL_DRAG_ENABLE_DISTANCE		100				//拖动划块时有效距离
#define SMALL_PHOTO_ITEM_BORDER			5				//缩略图显示方式时，ITEM与周围的间隔
#define PHOTO_BORDER_WIDTH				5				//缩略图绘制图象时与周围间隔
#define PHOTO_SMALL_TARGET_HEIGHT		10				//缩略图绘制时的标志绘制需要高度
#define PHOTO_SMALL_WORD_HEIGHT			20				//缩略图绘制时文字高度
#define PHOTO_SHADOW_WIDTH				3				//缩略图阴影宽度
#define PHOTO_SHADOW_MOVE				3				//缩略图阴影与原图差距

#define MES_ALZQ_OPEN_FLODER (WM_USER+100)				//双击文件夹时向父窗口发送消息
#define MES_ALZQ_SHOW_PHOTO (WM_USER+101)				//悬浮窗口显示图象的消息
#define MES_ALZQ_VIEW_PHOTO (WM_USER+200)				//双击图象文件时向父窗口发送的消息

#define MES_ALZQ_BEGIN_DRAG_LV (WM_USER+201)			//开始拖拽等级时，发送的消息
#define MES_ALZQ_BEGIN_DRAG_TYPE (WM_USER+202)			//开始拖拽文件分类时，发送的消息
#define MES_ALZQ_END_DRAG_LV (WM_USER+203)				//结束拖拽等级时，发送的消息
#define MES_ALZQ_END_DRAG_TYPE (WM_USER+204)			//结束拖拽文件分类时，发送的消息
#define MES_ALZQ_REFRESH_ALL (WM_USER+300)				//刷新LIST控件所有图象
#define MES_ALZQ_REFRESH_ITEM (WM_USER+301)				//刷新LIST控件中一个ITEM，带入第一个参数为ITEM开始编号，第2个参数为ITEM结束编号