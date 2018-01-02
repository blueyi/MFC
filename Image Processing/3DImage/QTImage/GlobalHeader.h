#if !defined(_GLOBAL_HEADER_H)
#define _GLOBAL_HEADER_H

#include "ImageViewer.h"

#define WM_SHOW_SERIES        WM_USER+200
#define WM_CALL_COMMAND       WM_USER+201
#define WM_IMAGEPROCESS_END   WM_USER+202
#define	WM_INTIME_SEGMENTED	  WM_USER+203

#define VRCTRL_PIXELMAXRANGE 1024
#define VRCTRL_GRADIENTRANGE 550
struct SERIES
{
	vtkImageData* Data;
	vtkImageData* SegmentedData;
	char          Name[256];
	double base1[4][4],base2[4][4],base3[4][4]; //1 normal; 2 sag; 3 cor
	SERIES()
	{
		memset(this,0,sizeof(SERIES));
	}
};

struct IA_PIXEL_ITEM
{
	unsigned short pixel;  //像素值
	float opacity; //像素值对应的透明度
	COLORREF color; //像素值对应的颜色
	int count;  //像素值对应的像素个数，画直方图使用
	
};

struct ROI_POINT
{
	unsigned short x,y,z;
};

struct ROI
{
	ROI_POINT *pnts;
	int pntNum;
	COLORREF color;
	int iImageIndex; //位于那一图像层上
	int iImageType; //1 normal; 2 sag; 3 cor
	double alpha;  
	int bounds[6];  //基于base1的边界

	ROI()
	{
		pnts=NULL;
		pntNum=0;
		color=RGB(0,0,255);
		alpha=0.5;
	}
};

struct MESH_OPTIONS
{
	BOOL bUsePatented;
	// Begin render switches
	BOOL bUseGaussianSmoothing;
	BOOL bUseDecimation;
	BOOL bUseMeshSmoothing;
	// Begin gsmooth params
	float fGaussianStandardDeviation;
	float fGaussianError;
	
	// Begin decimate parameters
	float fDecimateTargetReduction;
	float fDecimateInitialError;
	float fDecimateAspectRatio;
	float fDecimateFeatureAngle;
	float fDecimateErrorIncrement;
	unsigned int iDecimateMaximumIterations;
	BOOL bDecimatePreserveTopology;
	
	// Begin msmooth params
	float fMeshSmoothingRelaxationFactor;
	unsigned int iMeshSmoothingIterations;
	float fMeshSmoothingConvergence;
	float fMeshSmoothingFeatureAngle;
	BOOL bMeshSmoothingFeatureEdgeSmoothing;
	BOOL bMeshSmoothingBoundarySmoothing;

	COLORREF color;
	float opacity;
	short label;

	MESH_OPTIONS()
	{
		bUsePatented=TRUE;

		color=RGB(255,0,255);
		opacity=1.0;
		label=255;

		bUseGaussianSmoothing = TRUE;
		bUseDecimation = TRUE;
		bUseMeshSmoothing = TRUE;

		// Begin gsmooth params
		fGaussianStandardDeviation = 0.8f;
		fGaussianError = 0.03f;

		// Begin decimate params
		fDecimateTargetReduction = 0.95f;
		fDecimateInitialError = 0.002f;
		fDecimateAspectRatio = 20.0f;
		fDecimateErrorIncrement = 0.002f;
		iDecimateMaximumIterations = 1;
		fDecimateFeatureAngle = 45;
		bDecimatePreserveTopology = TRUE;
   
		// Begin msmooth params
		iMeshSmoothingIterations = 1;
		fMeshSmoothingRelaxationFactor = 0.01f;
		fMeshSmoothingFeatureAngle = 45;
		fMeshSmoothingConvergence = 0;
		bMeshSmoothingFeatureEdgeSmoothing = FALSE;
		bMeshSmoothingBoundarySmoothing = FALSE;
	}
};

struct vvPluginProperty
{
	char sVVP_ERROR[255];
	char sVVP_NAME[255];
	char sVVP_TERSE_DOCUMENTATION[255];
	char sVVP_FULL_DOCUMENTATION[255];
	char sVVP_NUMBER_OF_GUI_ITEMS[255];
	char sVVP_ABORT_PROCESSING[255];
	char sVVP_REPORT_TEXT[255];
};

enum ENUM_SEGMENT_METHOD
{	
	SEGMENT_SIMPLE_THRESHOLD,
	SEGMENT_CONNECTED_THRESHOLD,
	SEGMENT_CONFIDENCE_CONNECTED,
	SEGMENT_ISOLATED_CONNECTED
};

enum ENUM_VOLRENDER_MODE
{
	VOLRENDER_MIP,
	VOLRENDER_VOLUME
};

enum ENUM_VOLRENDER_METHOD
{
	VOLRENDER_HARDWARE,
	VOLRENDER_FIXPOINT,
	VOLRENDER_SOFTWARE
};



struct VOLRENDER_CONFIG
{
	BOOL bShade;
	BOOL bGradient;
	ENUM_VOLRENDER_MODE renderMode;
	ENUM_VOLRENDER_METHOD method;

	CList<IA_PIXEL_ITEM,IA_PIXEL_ITEM&> pixelOpacityColorList;
	CList<IA_PIXEL_ITEM,IA_PIXEL_ITEM&> gradOpacityList;

	float LOD;
	short sampleDistance;
	float lowResLODFactor;
	float lodRange[2];
	
	short WindowWidth,WindowLevel;  //窗宽窗位

	VOLRENDER_CONFIG()
	{
		LOD=1;
		sampleDistance=1;
		lowResLODFactor=1.5;

		lodRange[0]=1.0;
		lodRange[1]=4.0;

		WindowWidth=4096;
		WindowLevel=2048;
	}
};

struct LABEL_COLOR
{
	COLORREF color;
	short label;
};

#endif