// MRISeries.h: interface for the CMRISeries class.
// Created by Wei Wei [Mar.13, 2006]
// InterSmart Robotic System Co., Ltd.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRISERIES_H__8EF1F6DE_9D98_4CCA_A2B6_28C1F8B55773__INCLUDED_)
#define AFX_MRISERIES_H__8EF1F6DE_9D98_4CCA_A2B6_28C1F8B55773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MRIImage.h"
#include <afxtempl.h>
#include <afxcoll.h>
#include "LUT.h"

class __declspec(dllexport) CMRISeries  
{
public:
	float GetPTPos();
	void SetPTPos(float dPTPos);

	//////////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////////
	
	CMRISeries();
	virtual ~CMRISeries();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	//////////////////////////////////////////////////////////////////////////

	// Get series ID
	int GetSeriesID();
	// Get Scan ID
	int GetScanID();
	// Get Study ID
	CString GetStudyID();


	CString m_sFolder;  /*Í¼Ïñ´æ·ÅÂ·¾¶*/
	// Get Name
	CString GetName();

	// Get slice direction
	double* GetSliceDirection();

	// Get phase direction
	double* GetPhaseDirection();

	// Get freq direction
	double* GetFreqDirection();

	// Transformation
	// ppdTrans: 4*4
	void Transformation( double** ppdTrans );

	// Transform to new position and orientation
	void Transformation( double dNewCenter[3], double dNewPhaseDirection[3], double dNewFreqDirection[3] );

	// Translation by 3*1 vector
	void Translation( double dTranslation[3] );

	// Rotate by 3*3 matrix
	void Rotation( double** ppdRot );

	// Rotate dAngle degree about an axis
	void Rotation( double dAxis[3], double dAngle );

	
	
	// Set window width
	void ChangeWindowWidthAndLevel( int nWidthShift, int nLevelShift );
	void SetWindowWidthAndLevel(int nWindowWidth, int nWindowLevel);
	
	// Get all images from MRI workstation
	int Load( CString sFolder );

	// Get all images from buffer transfered by Internet
	int Load( char* pBuffer, int nLength, WORD nIMRIACPHiVer = 1, WORD nIMRIACPLoVer = 2);
	
	int Load(CArray<MR_STRUCT_IMAGE*, MR_STRUCT_IMAGE*> &caImgs);

	// Save image data
	int Save( CString sFolder );

	// Get the pointer to the i th image
	CMRIImage* GetImageAt( int nIndex );

	// Get the number of the images
	int GetNumOfImages();

	bool IsVisible();
	void SetVisible(bool bVisible);

	int  GetWindowWidth();
	int  GetWindowLevel();

	
	// Get new box orientation characters
	char* GetNewBoxOrientChar();

	// Set new box orientation characters
	void SetNewBoxOrientChar( char sOrient[6] );
		
	CLUT32 m_oClut32;

private:
	
	WORD GetIMRIACPVerHi() {return m_nIMRIACPHiVer;};
	WORD GetIMRIACPVerLo() {return m_nIMRIACPLoVer;};
	void UpdateOClut(int nWindowWidth, int nWindowLevel);

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	//////////////////////////////////////////////////////////////////////////
	// Scan ID
	int m_nScanID;
	// Series ID
	int m_nSeriesID;
	
	// Study ID
	CString m_sStudyID;

	// Series(Scan) name 
	CString m_sName;
	
	// Center of the series
	double m_dCenter[3];

	// Normal of the series
	double m_dSliceDirection[3];

	// X direction of the image
	double m_dPhaseDirection[3];

	// Y direction of the image
	double m_dFreqDirection[3];

	// Following used to store original position in scanner coordinates
	double m_dCenterInScanner[3];
	double m_dSliceDirectionInScanner[3];
	double m_dPhaseDirectionInScanner[3];
	double m_dFreqDirectionInScanner[3];

	
	// Pointer to the images of the series
	CMRIImage* m_pMRIImage;

	// Number of the images
	int m_nNumOfImages;

	int m_nWindowWidth;
	int m_nWindowLevel;

	int m_iVisibleCnt; // To identify whether it is display or not
	
	// Characters for box orientation
	// [0]: X+
	// [1]: X-
	// [2]: Y+
	// [3]: Y-
	// [4]: Z+
	// [5]: Z-
	// char m_sBoxOrientation[6];
	char* m_psNewBoxOrientation;
	
	void InitSeries();

	WORD m_nIMRIACPHiVer;
	WORD m_nIMRIACPLoVer;


};

#endif // !defined(AFX_MRISERIES_H__8EF1F6DE_9D98_4CCA_A2B6_28C1F8B55773__INCLUDED_)
