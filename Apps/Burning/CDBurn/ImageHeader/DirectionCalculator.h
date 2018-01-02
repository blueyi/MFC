/********************************************************************
File Name:	DirectionCalculator.h
Written by: Yang Guang, Xie Haibin

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
	CDirectionCalculator

History:
	2002-6-23	Created.
*********************************************************************/

#if !defined(AFX_DIRECTIONCALCULATOR_H__3A429DF9_E6C2_47A3_B3C4_38FD0F91D00B__INCLUDED_)
#define AFX_DIRECTIONCALCULATOR_H__3A429DF9_E6C2_47A3_B3C4_38FD0F91D00B__INCLUDED_

#pragma warning (disable:4786)

#include "../Geometry/ThreeDim.h"

#include "BI_Constants.h"
#include "Scan.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

/*!
	\remarks Suppose the rotation is applied to the image before flip.
*/
class CLASS_DECL_IMAGEHEADER CTransformInfo
{	
public:
	bool m_bFlipVertical;
	bool m_bFlipHorizontal;
	int  m_nAngle;
	CTransformInfo() : 
		m_bFlipVertical(false), m_bFlipHorizontal(false), m_nAngle(0){};
};

typedef std::map<int, CTransformInfo> CTransformTable;
typedef CTransformTable::const_iterator CTransformTableConstIter;

typedef std::map<int, Geometry::CThreeDim> CPhysicalFromHBDTable;
typedef CPhysicalFromHBDTable::const_iterator CPhysicalFromHBDIter;

/*!
    This enumeration type is used to mark the direction of the image in the 
    human body coordination. Two variable in the scan field of the type are 
    used to record the read direction and phase direction of the image.
    We should save this information because the strategy used to determine
    the read/phase directions may change over time, so we cannot deduce the 
    read and phase directions from informations on body entry, body part, and
    body position when we are openning saved images. So it's always safe to 
    save these two directions. Slice direction is not saved in the same way
    since the offsets of each image already contain that information.
*/
enum EHumanBodyDirection
{
    hbdLeft,        //!< Points to the left of human body.
    hbdRight,       //!< Points to the right of human body.
    hbdAnterior,    //!< Points to the anterior.
    hbdPosterior,   //!< Points to the posterior.
    hbdSuperior,    //!< Points to the superior.
    hbdInferior,    //!< Points to the inferior.
};

enum ENUM_CODING_DIR_ON_2D_IMAGE
{
    fdLeftToRight,		// →
	fdTopToBottom,		// ↓
	fdRightToLeft,		// ←
	fdBottomToTop,		// ↑
};


/*! This class is implemented as a Singleton, which provides a convenient way
of global access and ensures there can be only one instance of the manager
in the application in the mean time. */
class CLASS_DECL_IMAGEHEADER CDirectionCalculator
{
protected:
	static CDirectionCalculator s_DirectionCalculator;
    //! Protected constructor.
	CDirectionCalculator();
public:
    //! Returns the handle to the only instance of the object.
	static CDirectionCalculator& GetHandle(){
		return s_DirectionCalculator;
	}
    //! Destructor.
	virtual ~CDirectionCalculator();
    //! Calculates the directions of the scan.
	void Calculate(CScan* pScan);
	void GetMIPActiveDirForDicom( CBIImageHeader oImageHeader,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY );
    //! Determines the main direction in the human body coordinates.
    EHumanBodyDirection GetMainDirection(EBodyPosition bodyPosition,
        EBodyEntry bodyEntry, Geometry::CThreeDim tdDiection);
    //! Determines the default orientation of an image of a given body part.
    void DefaultOrientation(EBodyPart bodyPart, EImagePlane imagePlane,
        EHumanBodyDirection& right,
        EHumanBodyDirection& top);

    bool GetPhysicalDirection(EBodyPosition bodyPosition, 
		EBodyEntry bodyEntry,
		EHumanBodyDirection hbd, 
		Geometry::CThreeDim& tdVector);

    bool GetPhysicalDirection_ALS(EBodyPosition bodyPosition, 
		EBodyEntry bodyEntry,
		Geometry::CThreeDim& tdAnterior, Geometry::CThreeDim& tdLeft, Geometry::CThreeDim& tdSuperior);

	bool GetDefaultTransform(
		EHumanBodyDirection hbdSrcTop, EHumanBodyDirection hbdSrcRight,
		EHumanBodyDirection hbdDestTop, EHumanBodyDirection hbdDestRight,
		CTransformInfo& ti);
	void Transform(char pchOrientation[4], ENUM_CODING_DIR_ON_2D_IMAGE& nCodingDir, const CTransformInfo& ti);
    EHumanBodyDirection Opposite(EHumanBodyDirection hbd);
    void CalcScanOffset(CScan* pScan);
    
	void UpdateSeriesRegion(CScan *pScan, 
		CPresaturationRegion *pHumanRegion,
		bool bUpdateSeriesField);
	EScancubeDirection GetScanDirection(CScan *pScan, EHumanBodyDirection bodyDirection);

	void ResetHumanRegion(CScan *pScan, CPresaturationRegion* pHumanRegion, 
		EHumanBodyDirection humanDirection);
	void SetDefaultforUncheck(CScan *pScan, CPresaturationRegion* pHumanRegion); 


    
protected:
	void CalculateNonOblique(CScan* pScan);
	void CalculateOblique(CScan* pScan);
	void AddItem(EHumanBodyDirection hbdSrcTop,
			   EHumanBodyDirection hbdSrcRight,
			   EHumanBodyDirection hbdDestTop, 
			   EHumanBodyDirection hbdDestRight,
			   int nAngle,
			   bool bVerticalFlip,
			   bool bHorizontalFlip);
	void AddPhysicalFromHBDItem(EBodyPosition bodyPosition, 
								EBodyEntry bodyEntry, 
								EHumanBodyDirection hbd, 
								Geometry::CThreeDim tdVector);
	void CalcPhysicalFromHBDTable();
	void CalcTransformTable();

	EHumanBodyDirection NegativeHumanDirection(EHumanBodyDirection hbd);

	CTransformTable m_TransformTable;
	CPhysicalFromHBDTable	m_PhysicalFromHBDTable;

	// ***************************** PROSPECT的img向DICOM的方位转换功能 *****************************
private:
	void GetBodyCoordinateAxisDir( 
		unsigned char nPatPosition, unsigned char nPatEntry,
		CThreeDim& vBodySuperior, CThreeDim& vBodyLeft, CThreeDim& vBodyPosterior );
public:
	void GetActiveDirForDicom( CBIImageHeader oImageHeader,double nAngleOffset,BOOL nVerFlip,BOOL nHorFlip,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY );
	void GetOrientationsForDicom( CBIImageHeader oImageHeader,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY );
	double ret[9];
	BOOL GetRotateMatrixFromAxis(CThreeDim axis,double radian);


	// ***************************** 预饱和带在设备坐标系中的方向 *****************************
public:
	EHumanBodyDirection Get_MIP_Series_MainDirection(EBodyPosition bodyPosition,
                                       EBodyEntry bodyEntry, 
                                       CThreeDim tdDirection);

	EPresaturationDirection GetPresatDirection( const CSeries* pSeries, EHumanBodyDirection hbdDir );
	CThreeDim VertorCrossMatrix(CThreeDim nSrc);
	//math::matrix<double> matrix_direction(3,3);
/*
	EEquipCoordinateAxisDirection GetEquipCoordinateAxisDirection( 
		StudyField oStudyField, EHumanBodyDirection hbdDir );
*/

public:
	CString GetDefaultFrequencyDir( StudyField oStudyParams, ScanField oScanParams );
	
};

#endif // !defined(AFX_DIRECTIONCALCULATOR_H__3A429DF9_E6C2_47A3_B3C4_38FD0F91D00B__INCLUDED_)
