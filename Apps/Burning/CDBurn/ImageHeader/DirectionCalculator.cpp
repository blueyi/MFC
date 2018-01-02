/********************************************************************
File Name:	DirectionCalculator.h
Written by: Yang Guang, Xie Haibin

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
	CDirectionCalculator

History:
    2002/7/15  Added GetDefaultTransform(), Transform() -- YG, XHB
    2002/7/8   Added GetMainDirection(), DefaultOrientation() -- YG
	2002/6/23	Created.
*********************************************************************/

#include "stdafx.h"

#include <cmath>
#include <cassert>

#include "../Utilities/swap.h"
#include "../Geometry/Point.h"
#include "../ImageHeader/TransMatrix3D.h"

#include "Scan.h"
#include "Study.h"
#include "Series.h"
#include "Bi_constants.h"
#include "DirectionCalculator.h"
#include"fstream.h"


using namespace Geometry;

CDirectionCalculator CLASS_DECL_IMAGEHEADER CDirectionCalculator::s_DirectionCalculator;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#ifndef _CHEN_SHI_
#define _CHEN_SHI_

#endif
#ifdef _CHEN_SHI_
	
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectionCalculator::CDirectionCalculator()
{
	CalcTransformTable();
	CalcPhysicalFromHBDTable();
}

CDirectionCalculator::~CDirectionCalculator()
{

}

/*!
    This function determines the read/phase/slice directions and fills the 
    corresponding fields in the ScanField of the given scan.
*/
void CDirectionCalculator::Calculate(CScan* pScan)
{
	ASSERT(pScan != NULL);
	if (pScan->SeriesParams().Plane == ipOblique)
	{
		CalculateOblique(pScan);
	}
	else
	{
		CalculateNonOblique(pScan);
	}
	
}

/*!
	\remarks Factors influence the determination of the frequency direction
	include:
	<OL>
	<LI>Body part</LI>
	<LI>Body position</LI>
	<LI>Body entry</LI>
	<LI>Image plane</LI>
	</OL>
*/
void CDirectionCalculator::CalculateNonOblique(CScan* pScan)
{
	ASSERT(pScan != NULL);

	ScanField& scanParams = pScan->ScanParams();

	scanParams.FreqDirX = 0;
	scanParams.FreqDirY = 0;
	scanParams.FreqDirZ = 0;

	scanParams.PhaseDirX = 0;
	scanParams.PhaseDirY = 0;
	scanParams.PhaseDirZ = 0;

	scanParams.SliceDirX = 0;
	scanParams.SliceDirY = 0;
	scanParams.SliceDirZ = 0;

	switch(pScan->StudyParams().PatPosition)
	{
	case bpSupine:
	case bpProne:
		switch(pScan->SeriesParams().Plane)
		{
		case ipAxial:
			scanParams.SliceDirY = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
			case bpNeck:
			case bpCervicalSpine:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			case bpChest:
			case bpShoulder: 
			case bpLumberSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpBreast: 
			//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirX  = 1; 
				break;
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			default:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			}
			break;
		case ipCoronal:
			scanParams.SliceDirZ = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;
			case bpChest:
				//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirY = 1;
				scanParams.FreqDirX  = 1; 
				break;
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;
			default:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;
			}
			break;
		case ipSagittal:
			scanParams.SliceDirX = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
			case bpChest:
				//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirY  = 1; 
				break;
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
			default:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirY  = 1; 
				break;
			}
			break;
		default:
			ASSERT(0);
		}
		break;
	case bpDecubitusRight:
	case bpDecubitusLeft:
		switch(pScan->SeriesParams().Plane)
		{
		case ipAxial:
			scanParams.SliceDirY = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
			case bpNeck:
			case bpCervicalSpine:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirX  = 1; 
				break;
			case bpChest:
			case bpShoulder: 
			case bpSpine:
			case bpLumberSpine:
			case bpThoracicSpine: 
			case bpBreast: 
			//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral: 
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
			default:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirX  = 1; 
				break;
			}
			break;
		case ipCoronal:
			scanParams.SliceDirX = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
				scanParams.PhaseDirZ = 1;
				scanParams.FreqDirY  = 1; 
				break;
			case bpChest:
			//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirY = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
			default:
				scanParams.PhaseDirY = 1;
				scanParams.FreqDirZ  = 1; 
				break;
			}
			break;
		case ipSagittal:
			scanParams.SliceDirZ = 1;
			switch (pScan->StudyParams().PatBodyPart)
			{
			case bpHead:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;
			case bpChest:
			//Added by Tom, --2008.07.10
			case bpLung:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLiver:
			case bpKidney:
			default:
				scanParams.PhaseDirX = 1;
				scanParams.FreqDirY  = 1; 
				break;

			}
			break;
		default:
			ASSERT(0);
		}
		break;
	default:
		ASSERT(0);
	}

    bool bDefaultFreqDir = 
        ((pScan->SeriesParams().OtherOptions & cnstDefaultFrequencyDir) != 0);
    if (!bDefaultFreqDir)
	{
		swap(scanParams.PhaseDirX, scanParams.FreqDirX);
		swap(scanParams.PhaseDirY, scanParams.FreqDirY);
		swap(scanParams.PhaseDirZ, scanParams.FreqDirZ);
	}

}

void CDirectionCalculator::CalculateOblique(CScan* pScan)
{

}

//! Determines the main direction in the human body coordinates.
/*!
    \note Given a arbitrary vector, the main direction refers the direction
    in the human body coordinates on which the vector has the maximum projection.
*/
EHumanBodyDirection 
CDirectionCalculator::GetMainDirection(EBodyPosition bodyPosition,
                                       EBodyEntry bodyEntry, 
                                       CThreeDim tdDirection)
{
    EHumanBodyDirection hbd;
    // Firstly, we find the max projection direction. Then determines which
    // body direction that direction points to.

    if (fabs(tdDirection.x) >= fabs(tdDirection.y) && 
        fabs(tdDirection.x) >= fabs(tdDirection.z))
        // max projection is x.
    {
        if (bodyEntry == beHeadFirst)
        {
            switch(bodyPosition)
            {
            case bpProne:
                hbd = hbdRight;
                break;
            case bpSupine:
                hbd = hbdLeft;
                break;
            case bpDecubitusLeft:
                hbd = hbdAnterior;
                break;
            case bpDecubitusRight:
                hbd = hbdPosterior;
                break;
            default:
                ASSERT(0);
            }
        }
        else
        {
            switch(bodyPosition)
            {
            case bpProne:
                hbd = hbdLeft;
                break;
            case bpSupine:
                hbd = hbdRight;
                break;
            case bpDecubitusLeft:
                hbd = hbdPosterior;
                break;
            case bpDecubitusRight:
                hbd = hbdAnterior;
                break;
            default:
                ASSERT(0);
            }
        }
    }
    else if (fabs(tdDirection.y) >= fabs(tdDirection.z))
        // max projection is y.
    {
        if (bodyEntry == beHeadFirst)
        {
            hbd = hbdSuperior;
        }
        else
        {
            hbd = hbdInferior;
			//hbd = hbdPosterior;
        }
    }
    else // max projection is z.
    {
        switch(bodyPosition)
        {
        case bpProne:
            hbd = hbdPosterior;
            break;
        case bpSupine:
            hbd = hbdAnterior;
            break;
        case bpDecubitusLeft:
            hbd = hbdRight;
            break;
        case bpDecubitusRight:
            hbd = hbdLeft;
            break;
        default:
            ASSERT(0);
        }
    }

    return (hbd);
}

EHumanBodyDirection CDirectionCalculator::NegativeHumanDirection(EHumanBodyDirection hbd)
{
	EHumanBodyDirection hbdResult;
	switch(hbd)
	{
	case hbdLeft:
		hbdResult = hbdRight;
		break;
    case hbdRight:
		hbdResult = hbdLeft;
		break;
    case hbdAnterior:
		hbdResult = hbdPosterior;
		break;
    case hbdPosterior:
		hbdResult = hbdAnterior;
		break;
    case hbdSuperior:
		hbdResult = hbdInferior;
		break;
    case hbdInferior:
		hbdResult = hbdSuperior;
		break;
	default:
		break;
	}

	return hbdResult;
	
}

/*! 
    This funciton determines the default orientation of an image of a given 
    body part. 
    \remarks Doctors in the hospitals are used to watching the image in a 
    traditional orientation. For instance, for a axial image of the head, the 
    image is usually oriented so that the eyes of the patient are looking up
    and the left part of the head is put in the left part of image.
    \param bodyPart Part of the body scanned.
    \param imagePlane Plane of the image, one of \a axial, \a coronal, \a 
    sagittal, and \a oblique.
    \param right Output parameter, body direction of the right of image.
    \param top Output parameter, body direction of the upper of the image.
*/
void CDirectionCalculator::DefaultOrientation(EBodyPart bodyPart, 
                        EImagePlane imagePlane,
                        EHumanBodyDirection& right,
                        EHumanBodyDirection& top)
{
    switch (imagePlane)
    {
    case ipAxial:
        {
            switch (bodyPart)
            {
			case bpHead:
			case bpChest:
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLung:
			case bpLiver:
			case bpKidney:
				right = hbdLeft;
				top = hbdAnterior;  // facing top
				break;
			default:
				ASSERT(0);
            }
        }
        break;
    case ipCoronal:
        {
            switch (bodyPart)
            {
			case bpHead:
			case bpChest:
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLung:
			case bpLiver:
			case bpKidney:
				right = hbdLeft;
				top = hbdSuperior;
				break;
			default:
				ASSERT(0);
            }
        }
        break;
    case ipSagittal:
        {
            switch (bodyPart)
            {
			case bpHead:
			case bpChest:
			case bpNeck:
			case bpShoulder: 
			case bpCervicalSpine:
			case bpThoracicSpine: 
			case bpSpine:
			case bpLumberSpine:
			case bpBreast: 
			case bpAbdomen: 
			case bpPelvis: 
			case bpHip: 
			case bpElbow: 
			case bpWrist:
			case bpArm:
			case bpHand:
			case bpKnee:
			case bpLeg:
			case bpAnkle:
			case bpFoot:
			case bpHeart:
			case bpVascularHead:
			case bpVascularNeck:
			case bpVascularBody:
			case bpVascularPeripheral:
			//Added by Tom, --2008.07.10
			case bpLung:
			case bpLiver:
			case bpKidney:
				right = hbdPosterior;    // facing the left
				top = hbdSuperior;
				break;
			default:
				ASSERT(0);
            }
        }
        break;
    case ipOblique:
		// 对于Oblique成像平面，在调用本函数之前，已经作了相应的近似处理，不会走到该分支。
		//  参见: void CScanViewData::OnChangeImagePlane()
		//  Rodger, 20:36 2004-12-10

        // for oblique image, don't call this function.
        ASSERT(0); 
        break;
    default:
        ASSERT(0);
    }
}

bool CDirectionCalculator::GetDefaultTransform(EHumanBodyDirection hbdSrcTop, 
											   EHumanBodyDirection hbdSrcRight,
											   EHumanBodyDirection hbdDestTop, 
											   EHumanBodyDirection hbdDestRight,
											   CTransformInfo& ti)
{
	CTransformTableConstIter it = m_TransformTable.find(
		(hbdSrcTop << 24) + (hbdSrcRight << 16) + (hbdDestTop << 8) + hbdDestRight);

	if (it != m_TransformTable.end())
	{
		ti =  it->second;
		return true;
	}
	else
		return false;
}

void CDirectionCalculator::AddItem(EHumanBodyDirection hbdSrcTop,
								   EHumanBodyDirection hbdSrcRight,
								   EHumanBodyDirection hbdDestTop, 
								   EHumanBodyDirection hbdDestRight,
								   int nAngle,
								   bool bVerticalFlip,
								   bool bHorizontalFlip)
{
	CTransformInfo ti;
	ti.m_bFlipHorizontal = bHorizontalFlip;
	ti.m_bFlipVertical = bVerticalFlip;
	ti.m_nAngle = nAngle;

	m_TransformTable.insert(std::pair<int, CTransformInfo>(
		(hbdSrcTop << 24) + (hbdSrcRight << 16) + (hbdDestTop << 8) + hbdDestRight, ti));
}

/*!
	Since the physicians are used to watch the image in certain predefined
	orientation, we need to transform the image (rotate, vflip, hflip) before
	displaying it on the screen. Given the original image orientation and
	the destination (required) image orientation, we need to find out the 
	transform needed. To do this, we store a predefined lookup table in a 
	map. This function fills up that map.
*/
void CDirectionCalculator::CalcTransformTable()
{
	// axial
	AddItem(hbdAnterior, hbdRight, hbdAnterior, hbdLeft, 0, false, true);
	AddItem(hbdAnterior, hbdLeft, hbdAnterior, hbdLeft, 0, false, false);
	AddItem(hbdPosterior, hbdRight, hbdAnterior, hbdLeft, 0, true, true);
	AddItem(hbdPosterior, hbdLeft, hbdAnterior, hbdLeft, 0, true, false);
	AddItem(hbdRight, hbdAnterior, hbdAnterior, hbdLeft, 90, false, false);
	AddItem(hbdRight, hbdPosterior, hbdAnterior, hbdLeft, 270, false, true);
	AddItem(hbdLeft, hbdAnterior, hbdAnterior, hbdLeft, 270, true, false);
	AddItem(hbdLeft, hbdPosterior, hbdAnterior, hbdLeft, 270, false, false);

	// saggital
	AddItem(hbdSuperior, hbdAnterior, hbdSuperior, hbdPosterior, 0, false, true);
	AddItem(hbdSuperior, hbdPosterior, hbdSuperior, hbdPosterior, 0, false, false);
	AddItem(hbdInferior, hbdAnterior, hbdSuperior, hbdPosterior, 0, true, true);
	AddItem(hbdInferior, hbdPosterior, hbdSuperior, hbdPosterior, 0, true, false);
	AddItem(hbdAnterior, hbdSuperior, hbdSuperior, hbdPosterior, 90, false, false);
	AddItem(hbdAnterior, hbdInferior, hbdSuperior, hbdPosterior, 270, false, true);
	AddItem(hbdPosterior, hbdSuperior, hbdSuperior, hbdPosterior, 270, true, false);
	AddItem(hbdPosterior, hbdInferior, hbdSuperior, hbdPosterior, 270, false, false);

	// coronal
	AddItem(hbdSuperior, hbdRight, hbdSuperior, hbdLeft, 0, false, true);
	AddItem(hbdSuperior, hbdLeft, hbdSuperior, hbdLeft, 0, false, false);
	AddItem(hbdInferior, hbdRight, hbdSuperior, hbdLeft, 0, true, true);
	AddItem(hbdInferior, hbdLeft, hbdSuperior, hbdLeft, 0, true, false);
	AddItem(hbdRight, hbdSuperior, hbdSuperior, hbdLeft, 90, false, false);
	AddItem(hbdRight, hbdInferior, hbdSuperior, hbdLeft, 270, false, true);
	AddItem(hbdLeft, hbdSuperior, hbdSuperior, hbdLeft, 270, true, false);
	AddItem(hbdLeft, hbdInferior, hbdSuperior, hbdLeft, 270, false, false);

}

/*!
	\param pchOrientation Characters representing human body directions of 
	top, right, bottom, and, left of the image. This parameter is input/output
	parameter. The transformed directions will be stored in place.
	\param ti Transform applied to the image.
*/
void CDirectionCalculator::Transform(char pchOrientation[4], ENUM_CODING_DIR_ON_2D_IMAGE& nCodingDir,
									 const CTransformInfo& ti)
{
	char pchOrg[4];
	pchOrg[0] = pchOrientation[0];
	pchOrg[1] = pchOrientation[1];
	pchOrg[2] = pchOrientation[2];
	pchOrg[3] = pchOrientation[3];

	short nAnnotationCodingDirType = CConfigManager::GetHandle().m_nAnnotationCodingDirType;
	
	// rotate by ti.m_nAngle
	switch (ti.m_nAngle)
	{
		case 0:
			pchOrientation[0] = pchOrg[0];
			pchOrientation[1] = pchOrg[1];
			pchOrientation[2] = pchOrg[2];
			pchOrientation[3] = pchOrg[3];
			if ( nAnnotationCodingDirType == cdtFreqDirection )
			{
				nCodingDir = fdLeftToRight;
			}
			else if ( nAnnotationCodingDirType == cdtPhaseDirection )
			{
				nCodingDir = fdTopToBottom;				
			}
			break;
		case 90:
			pchOrientation[0] = pchOrg[1];
			pchOrientation[1] = pchOrg[2];
			pchOrientation[2] = pchOrg[3];
			pchOrientation[3] = pchOrg[0];
			if ( nAnnotationCodingDirType == cdtFreqDirection )
			{
				nCodingDir = fdBottomToTop;
			}
			else if ( nAnnotationCodingDirType == cdtPhaseDirection )
			{
				nCodingDir = fdLeftToRight;
			}
			break;
		case 180:
			pchOrientation[0] = pchOrg[2];
			pchOrientation[1] = pchOrg[3];
			pchOrientation[2] = pchOrg[0];
			pchOrientation[3] = pchOrg[1];
			if ( nAnnotationCodingDirType == cdtFreqDirection )
			{
				nCodingDir = fdRightToLeft;
			}
			else if ( nAnnotationCodingDirType == cdtPhaseDirection )
			{
				nCodingDir = fdBottomToTop;
			}
			break;
		case 270:
			pchOrientation[0] = pchOrg[3];
			pchOrientation[1] = pchOrg[0];
			pchOrientation[2] = pchOrg[1];
			pchOrientation[3] = pchOrg[2];
			if ( nAnnotationCodingDirType == cdtFreqDirection )
			{
				nCodingDir = fdTopToBottom;
			}
			else if ( nAnnotationCodingDirType == cdtPhaseDirection )
			{
				nCodingDir = fdRightToLeft;
			}
			break;
		default:
			assert(false);
	}
	
	
	// flip by ti.m_bFlipVertical or ti.m_bFlipHorizontal
	char ch;
	if (ti.m_bFlipVertical)
	{
		ch = pchOrientation[0];
		pchOrientation[0] = pchOrientation[2];
		pchOrientation[2] = ch;

		if ( nCodingDir == fdTopToBottom )
		{
			nCodingDir = fdBottomToTop;
		}
		else if ( nCodingDir == fdBottomToTop )
		{
			nCodingDir = fdTopToBottom;
		}		
	}

	if (ti.m_bFlipHorizontal)
	{
		ch = pchOrientation[1];
		pchOrientation[1] = pchOrientation[3];
		pchOrientation[3] = ch;

		if ( nCodingDir == fdLeftToRight )
		{
			nCodingDir = fdRightToLeft;
		}
		else if ( nCodingDir == fdRightToLeft )
		{
			nCodingDir = fdLeftToRight;
		}
	}
}

/*!
	Returns the opposite direction of the given direction in human body 
	coordinates.
	\param hbd Original direction in the human body coordinates.
	\return The opposite direction of the \a hbd.
*/
EHumanBodyDirection 
CDirectionCalculator::Opposite(EHumanBodyDirection hbd)
{
    if ((hbd % 2) == 0)
    {
        return (static_cast<EHumanBodyDirection>(hbd + 1));
    }
    else 
        return (static_cast<EHumanBodyDirection>(hbd - 1));
}

/*!
	Given a direction in the human body coordinates, this function returns
	the vector in the physical (magnet) coordinates.
	\param hbd Direction in the human body coordinates.
	\param bodyPosition Body position of the patient.
	\param bodyEntry Body entry of the patient.
	\param tdVector Three dimension vector representing the direction in the
	physical coordinates.
	\reuturn \a true if successful, \a false otherwise.
*/
bool
CDirectionCalculator::GetPhysicalDirection(EBodyPosition bodyPosition, 
										   EBodyEntry bodyEntry,
										   EHumanBodyDirection hbd, 
										   CThreeDim& tdVector)
{
	int nKey = 
		(static_cast<int>(bodyPosition) << 16) + 
		(static_cast<int>(bodyEntry) << 8) + 
		static_cast<int>(hbd);

	CPhysicalFromHBDIter it = m_PhysicalFromHBDTable.find(nKey);
	if (it != m_PhysicalFromHBDTable.end())
	{
		tdVector = it->second;
		return true;
	}
	else
	{
		tdVector = CThreeDim(0.0, 0.0, 0.0);
		return false;
	}
}

bool CDirectionCalculator::GetPhysicalDirection_ALS(EBodyPosition bodyPosition, 
													EBodyEntry bodyEntry,
													Geometry::CThreeDim& tdAnterior,
													Geometry::CThreeDim& tdLeft,
													Geometry::CThreeDim& tdSuperior)
{
    VERIFY(GetPhysicalDirection(bodyPosition, bodyEntry, hbdAnterior, tdAnterior));
	VERIFY(GetPhysicalDirection(bodyPosition, bodyEntry, hbdLeft, tdLeft));
	VERIFY(GetPhysicalDirection(bodyPosition, bodyEntry, hbdSuperior, tdSuperior));
	return true;
}

void 
CDirectionCalculator::AddPhysicalFromHBDItem(EBodyPosition bodyPosition, 
										  EBodyEntry bodyEntry, 
										  EHumanBodyDirection hbd, 
										  CThreeDim tdVector)
{
	int nKey = (bodyPosition << 16) + (bodyEntry << 8) + hbd;
	m_PhysicalFromHBDTable.insert(std::make_pair(nKey, tdVector));
}

void 
CDirectionCalculator::CalcPhysicalFromHBDTable()
{
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdAnterior, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdPosterior, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdLeft, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdRight, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdSuperior, CThreeDim(0, 1, 0));
	AddPhysicalFromHBDItem(bpSupine, beHeadFirst, hbdInferior, CThreeDim(0, -1, 0));

	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdAnterior, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdPosterior, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdLeft, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdRight, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdSuperior, CThreeDim(0, -1, 0));
	AddPhysicalFromHBDItem(bpSupine, beFootFirst, hbdInferior, CThreeDim(0, 1, 0));

	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdAnterior, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdPosterior, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdLeft, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdRight, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdSuperior, CThreeDim(0, 1, 0));
	AddPhysicalFromHBDItem(bpProne, beHeadFirst, hbdInferior, CThreeDim(0, -1, 0));

	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdAnterior, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdPosterior, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdLeft, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdRight, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdSuperior, CThreeDim(0, -1, 0));
	AddPhysicalFromHBDItem(bpProne, beFootFirst, hbdInferior, CThreeDim(0, 1, 0));

	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdAnterior, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdPosterior, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdLeft, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdRight, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdSuperior, CThreeDim(0, 1, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beHeadFirst, hbdInferior, CThreeDim(0, -1, 0));

	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdAnterior, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdPosterior, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdLeft, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdRight, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdSuperior, CThreeDim(0, -1, 0));
	AddPhysicalFromHBDItem(bpDecubitusRight, beFootFirst, hbdInferior, CThreeDim(0, 1, 0));

	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdAnterior, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdPosterior, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdLeft, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdRight, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdSuperior, CThreeDim(0, 1, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beHeadFirst, hbdInferior, CThreeDim(0, -1, 0));

	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdAnterior, CThreeDim(-1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdPosterior, CThreeDim(1, 0, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdLeft, CThreeDim(0, 0, -1));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdRight, CThreeDim(0, 0, 1));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdSuperior, CThreeDim(0, -1, 0));
	AddPhysicalFromHBDItem(bpDecubitusLeft, beFootFirst, hbdInferior, CThreeDim(0, 1, 0));
}

/*!
    This function calculates the ReadOffset, PhaseOffset, and SliceOffset
	of the scan according to the OffsetAP, OffsetLR, and OffsetSI of the scan.
    \param pScan Scan whose offsets are to be set.
	\pre The OffsetAP, OffsetLR, OffsetSI of the scan and BodyPos and BodyEntry
	of the study must be set properly.
	\post The ReadOffset, PhaseOffset, SliceOffset of the scan field is set.
*/
void 
CDirectionCalculator::CalcScanOffset(CScan* pScan)
{
    CThreeDim tdAP, tdLR, tdSI;

    StudyField& study = pScan->StudyParams();
    VERIFY(GetPhysicalDirection(
        static_cast<EBodyPosition>(study.PatPosition), 
		static_cast<EBodyEntry>(study.PatEntry), 
        hbdAnterior, tdAP));
    VERIFY(GetPhysicalDirection( 
        static_cast<EBodyPosition>(study.PatPosition),
		static_cast<EBodyEntry>(study.PatEntry), hbdLeft, tdLR));
    VERIFY(GetPhysicalDirection(
        static_cast<EBodyPosition>(study.PatPosition),
		static_cast<EBodyEntry>(study.PatEntry), hbdSuperior, tdSI));

    double dOffsetX = tdAP.x * pScan->m_dAPOffset + 
		tdLR.x * pScan->m_dLROffset + tdSI.x * pScan->m_dSIOffset;
    double dOffsetY = tdAP.y * pScan->m_dAPOffset + 
		tdLR.y * pScan->m_dLROffset + tdSI.y * pScan->m_dSIOffset;
    double dOffsetZ = tdAP.z * pScan->m_dAPOffset + 
		tdLR.z * pScan->m_dLROffset + tdSI.z * pScan->m_dSIOffset;

    ScanField& scanParams = pScan->ScanParams();
    CThreeDim td = CThreeDim(scanParams.FreqDirX, 
                             scanParams.FreqDirY, 
                             scanParams.FreqDirZ);
    td.Unify();
    scanParams.ReadOffset = dOffsetX * td.x + dOffsetY * td.y + dOffsetZ * td.z;

    td = CThreeDim(scanParams.PhaseDirX, scanParams.PhaseDirY, scanParams.PhaseDirZ);
    td.Unify();
    scanParams.PhaseOffset = dOffsetX * td.x + dOffsetY * td.y + dOffsetZ * td.z;

    td = CThreeDim(scanParams.SliceDirX, scanParams.SliceDirY, scanParams.SliceDirZ);
    td.Unify();
    scanParams.SliceOffset = dOffsetX * td.x + dOffsetY * td.y + dOffsetZ * td.z;
}
//! added by xhb.
EScancubeDirection CDirectionCalculator::GetScanDirection(CScan *pScan, EHumanBodyDirection bodyDirection)
{
	EHumanBodyDirection hbdPhaseDir, hbdReadDir, hbdSliceDir;

    CThreeDim tdReadDir(pScan->ScanParams().FreqDirX, 
                pScan->ScanParams().FreqDirY,
                pScan->ScanParams().FreqDirZ);

    CThreeDim tdPhaseDir(pScan->ScanParams().PhaseDirX, 
                pScan->ScanParams().PhaseDirY,
                pScan->ScanParams().PhaseDirZ);

	CThreeDim tdSliceDir(pScan->ScanParams().SliceDirX, 
                pScan->ScanParams().SliceDirY,
                pScan->ScanParams().SliceDirZ);

    hbdReadDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdReadDir);
    hbdPhaseDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdPhaseDir);

	hbdSliceDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdSliceDir);

	EScancubeDirection result;
	if(bodyDirection == hbdReadDir)
		result = sdPRead;
	else if(hbdReadDir == NegativeHumanDirection(bodyDirection))
		result = sdNRead;
	else if(hbdPhaseDir == bodyDirection)
		result = sdPPhase;
	else if(hbdPhaseDir == NegativeHumanDirection(bodyDirection))
		result = sdNPhase;
	else if(hbdSliceDir == bodyDirection)
		result = sdPSlice;
	else if(hbdSliceDir == NegativeHumanDirection(bodyDirection))
		result = sdNSlice;

	return result;

}
//! set pHumRegion to Defualt value.

void CDirectionCalculator::SetDefaultforUncheck(CScan *pScan, CPresaturationRegion* pHumanRegion)
{
	if( ! pHumanRegion[hbdLeft].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdLeft], hbdLeft);
	if( ! pHumanRegion[hbdRight].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdRight], hbdRight);
	if( ! pHumanRegion[hbdAnterior].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdAnterior], hbdAnterior);
	if( ! pHumanRegion[hbdPosterior].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdPosterior], hbdPosterior);
	if( ! pHumanRegion[hbdSuperior].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdSuperior], hbdSuperior);
	if( ! pHumanRegion[hbdInferior].m_bUse)
		ResetHumanRegion(pScan, &pHumanRegion[hbdInferior], hbdInferior);


}

void CDirectionCalculator::ResetHumanRegion(CScan *pScan, CPresaturationRegion *pHumanRegion, 
		EHumanBodyDirection humanDirection)
{
	EScancubeDirection bodyDirection;

	bodyDirection = GetScanDirection(pScan, humanDirection);

	switch( bodyDirection )
	{
	case sdPRead:
		pHumanRegion->m_sPos = pScan->ScanParams().ReadOffset + pScan->SeriesParams().FovX/2.0;
		break;
	case sdNRead:
		
		pHumanRegion->m_sPos = pScan->ScanParams().ReadOffset - pScan->SeriesParams().FovX/2.0;
		break;
	case sdPPhase:
		pHumanRegion->m_sPos = pScan->ScanParams().PhaseOffset + pScan->SeriesParams().FovY/2.0;
		
		break;
	case sdNPhase:
		pHumanRegion->m_sPos = pScan->ScanParams().PhaseOffset - pScan->SeriesParams().FovY/2.0;
		break;
	case sdPSlice:
		pHumanRegion->m_sPos = pScan->ScanParams().SliceOffset + 
			(pScan->SeriesParams().SliceThickness + pScan->SeriesParams().SliceGap) *
			pScan->SeriesParams().ResolutionZ/ 2.0;

		break;
	case sdNSlice:
		pHumanRegion->m_sPos = pScan->ScanParams().SliceOffset - 
			(pScan->SeriesParams().SliceThickness + pScan->SeriesParams().SliceGap) *
			pScan->SeriesParams().ResolutionZ/ 2.0;

		break;
	default:
		break;
	}


}

/*!
	\param bUpdateSeriesField If \a true, updates the presaturationRegion of series field,
	if \a false, updates HumenRegion with presaturationRegion in seriesField parameters.
*/
void CDirectionCalculator::UpdateSeriesRegion(CScan *pScan, 
		CPresaturationRegion *pHumanRegion,
		bool bUpdateSeriesField)
{
    // figure out the orginal orientation of the image.
    EHumanBodyDirection hbdPhaseDir, hbdReadDir, hbdSliceDir;
    CThreeDim tdReadDir(pScan->ScanParams().FreqDirX, 
                pScan->ScanParams().FreqDirY,
                pScan->ScanParams().FreqDirZ);

    CThreeDim tdPhaseDir(pScan->ScanParams().PhaseDirX, 
                pScan->ScanParams().PhaseDirY,
                pScan->ScanParams().PhaseDirZ);

	CThreeDim tdSliceDir(pScan->ScanParams().SliceDirX, 
                pScan->ScanParams().SliceDirY,
                pScan->ScanParams().SliceDirZ);

    hbdReadDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdReadDir);
    hbdPhaseDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdPhaseDir);

	hbdSliceDir = CDirectionCalculator::GetHandle().GetMainDirection(
            static_cast<EBodyPosition>(pScan->StudyParams().PatPosition), 
            static_cast<EBodyEntry>(pScan->StudyParams().PatEntry), 
            tdSliceDir);


	

	if(bUpdateSeriesField)
	{
		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdPRead],
			&pHumanRegion[hbdReadDir],
			sizeof(CPresaturationRegion));
		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdNRead],
			&pHumanRegion[NegativeHumanDirection(hbdReadDir)],
			sizeof(CPresaturationRegion));
		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdPPhase], 
			&pHumanRegion[hbdPhaseDir],
			sizeof(CPresaturationRegion));

		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdNPhase],
			&pHumanRegion[NegativeHumanDirection(hbdPhaseDir)],
			sizeof(CPresaturationRegion));
		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdPSlice],
			&pHumanRegion[hbdSliceDir],
			sizeof(CPresaturationRegion));
		memcpy(
			&pScan->SeriesParams().PresaturationRegions[sdNSlice],
			&pHumanRegion[NegativeHumanDirection(hbdSliceDir)],
			sizeof(CPresaturationRegion));

	}
	else
	{
		
		memcpy(
			&pHumanRegion[hbdReadDir],
			&pScan->SeriesParams().PresaturationRegions[sdPRead],
			sizeof(CPresaturationRegion));

		memcpy(
			&pHumanRegion[NegativeHumanDirection(hbdReadDir)],
			&pScan->SeriesParams().PresaturationRegions[sdNRead],
			sizeof(CPresaturationRegion));
		memcpy(
			&pHumanRegion[hbdPhaseDir],
			&pScan->SeriesParams().PresaturationRegions[sdPPhase],
			sizeof(CPresaturationRegion));
		memcpy(
			&pHumanRegion[NegativeHumanDirection(hbdPhaseDir)],
			&pScan->SeriesParams().PresaturationRegions[sdNPhase],
			sizeof(CPresaturationRegion));

		memcpy(
			&pHumanRegion[hbdSliceDir],
			&pScan->SeriesParams().PresaturationRegions[sdPSlice],
			sizeof(CPresaturationRegion));
		memcpy(
			&pHumanRegion[NegativeHumanDirection(hbdSliceDir)],
			&pScan->SeriesParams().PresaturationRegions[sdNSlice],
			sizeof(CPresaturationRegion));


	}


}


// ***************************** PROSPECT的img向DICOM的方位转换功能 *****************************
// S、L、P方向在设备坐标系中的方向(vBodySuperior,vBodyLeft,vBodyPosterior)；
void CDirectionCalculator::GetBodyCoordinateAxisDir( unsigned char nPatPosition, unsigned char nPatEntry,
							  CThreeDim& vBodySuperior, CThreeDim& vBodyLeft, CThreeDim& vBodyPosterior )
{
	CDirectionCalculator::GetHandle().GetPhysicalDirection(
		static_cast<EBodyPosition>(nPatPosition), 
		static_cast<EBodyEntry>(nPatEntry), 
		static_cast<EHumanBodyDirection>(hbdSuperior), 
		vBodySuperior );

	CDirectionCalculator::GetHandle().GetPhysicalDirection(
		static_cast<EBodyPosition>(nPatPosition), 
		static_cast<EBodyEntry>(nPatEntry), 
		static_cast<EHumanBodyDirection>(hbdLeft), 
		vBodyLeft );

	CDirectionCalculator::GetHandle().GetPhysicalDirection(
		static_cast<EBodyPosition>(nPatPosition), 
		static_cast<EBodyEntry>(nPatEntry), 
		static_cast<EHumanBodyDirection>(hbdPosterior), 
		vBodyPosterior );
}

// 分别求vImageReadDir、vImagePhaseDir与vBodySuperior,vBodyLeft,vBodyPosterior的夹角的余弦值
void CDirectionCalculator::GetOrientationsForDicom( CBIImageHeader oImageHeader,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY )
{
	// S、L、P的方向
	CThreeDim vBodySuperior, vBodyLeft, vBodyPosterior;
	GetBodyCoordinateAxisDir( oImageHeader.studyField.PatPosition, oImageHeader.studyField.PatEntry,
		vBodySuperior, vBodyLeft, vBodyPosterior );
	
	
	CThreeDim vImageReadDir, vImagePhaseDir;
	vImageReadDir.x = oImageHeader.imageField.fFreqDirX;
	vImageReadDir.y = oImageHeader.imageField.fFreqDirY;
	vImageReadDir.z = oImageHeader.imageField.fFreqDirZ;
	
	vImagePhaseDir.x = oImageHeader.imageField.fPhaseDirX;
	vImagePhaseDir.y = oImageHeader.imageField.fPhaseDirY;
	vImagePhaseDir.z = oImageHeader.imageField.fPhaseDirZ;
	
	// 方向是否有效
	double fReadDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	double fPhaseDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	if ( fReadDirModule < 1.0e-8 || fPhaseDirModule < 1.0e-8 )
	{
		fRowCosineWithZ = fRowCosineWithX = fRowCosineWithY = 0.0;
		fColCosineWithZ = fColCosineWithX = fColCosineWithY = 0.0;
		return;
	}

	// 左上角第一点的坐标
	fTopLeftX = oImageHeader.imageField.fCenterPointX 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.x
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.x;
	fTopLeftY = oImageHeader.imageField.fCenterPointY 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.y
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.y;
	fTopLeftZ = oImageHeader.imageField.fCenterPointZ 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.z
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.z;
	
	// 方向
	double fNumerator, fDenominator;
		// 行向量
	fNumerator = vImageReadDir.x*vBodySuperior.x + vImageReadDir.y*vBodySuperior.y + vImageReadDir.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fRowCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImageReadDir.x*vBodyLeft.x + vImageReadDir.y*vBodyLeft.y + vImageReadDir.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fRowCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImageReadDir.x*vBodyPosterior.x + vImageReadDir.y*vBodyPosterior.y + vImageReadDir.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fRowCosineWithY = fNumerator / fDenominator;
	
		// 列向量
	fNumerator = vImagePhaseDir.x*vBodySuperior.x + vImagePhaseDir.y*vBodySuperior.y + vImagePhaseDir.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImagePhaseDir.x,2) + pow(vImagePhaseDir.y,2) + pow(vImagePhaseDir.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fColCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDir.x*vBodyLeft.x + vImagePhaseDir.y*vBodyLeft.y + vImagePhaseDir.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImagePhaseDir.x,2) + pow(vImagePhaseDir.y,2) + pow(vImagePhaseDir.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fColCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDir.x*vBodyPosterior.x + vImagePhaseDir.y*vBodyPosterior.y + vImagePhaseDir.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImagePhaseDir.x,2) + pow(vImagePhaseDir.y,2) + pow(vImagePhaseDir.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fColCosineWithY = fNumerator / fDenominator;
}
void CDirectionCalculator::GetActiveDirForDicom( CBIImageHeader oImageHeader,double nAngleOffset,BOOL nVerFlip,BOOL nHorFlip,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY )
{
/*
	this->GetOrientationsForDicom(oImageHeader,fTopLeftX,fTopLeftY,fTopLeftZ,
		fRowCosineWithZ,fRowCosineWithX,fRowCosineWithY,
		fColCosineWithZ,fColCosineWithX,fColCosineWithY);
*/
/*
	fstream fW;
	fW.open("c:\\KPACS_Wrter.txt",ios::in|ios::out|ios::app);
	fW<<"nPlaneType="<<(int)oImageHeader.imageField.nPlaneType<<"\t"<<"Study ID="<<oImageHeader.studyField.Id<<"\t"<<"Series="<<(int)oImageHeader.seriesField.Id<<"\t"<<"Image ID="<<oImageHeader.imageField.Id<<"-----------------------------"<<endl;
	fW<<"nAngleOffset="<<nAngleOffset<<"\t"<<"nVerFlip="<<nVerFlip<<"\t"<<"nHorFlip="<<nHorFlip<<endl;
*/
	oImageHeader.imageField.fCenterPointX;
	oImageHeader.imageField.fCenterPointY;
	oImageHeader.imageField.fCenterPointZ;
	oImageHeader.seriesField.FovX;
	oImageHeader.seriesField.FovY;
	oImageHeader.seriesField.FovZ;

	CThreeDim vBodySuperior, vBodyLeft, vBodyPosterior;
	GetBodyCoordinateAxisDir( oImageHeader.studyField.PatPosition, oImageHeader.studyField.PatEntry,
		vBodySuperior, vBodyLeft, vBodyPosterior );
	//行向量和列向量
	CThreeDim vImageReadDir, vImagePhaseDir;
	vImageReadDir.x = oImageHeader.imageField.fFreqDirX;
	vImageReadDir.y = oImageHeader.imageField.fFreqDirY;
	vImageReadDir.z = oImageHeader.imageField.fFreqDirZ;
	
	vImagePhaseDir.x = oImageHeader.imageField.fPhaseDirX;
	vImagePhaseDir.y = oImageHeader.imageField.fPhaseDirY;
	vImagePhaseDir.z = oImageHeader.imageField.fPhaseDirZ;

	double fDirFlag = (vImageReadDir.x*1.0 + vImageReadDir.y*1.0 + vImageReadDir.z*1.0) 
		/ (sqrt( pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2)) * sqrt( 1.0 + 1.0 + 1.0 ));
	double fAngle = acos( fDirFlag ) * (360.0 / (2.0*PI));

	// swap direction
	if ( fDirFlag < 0.0 && fDirFlag >= -1.0)		// 90~180 degrees
	{
		vImageReadDir.x = -vImageReadDir.x;
		vImageReadDir.y = -vImageReadDir.y;
		vImageReadDir.z = -vImageReadDir.z;
	}
	else if ( fDirFlag > 0.0 && fDirFlag <= 1.0 )	// 0~90 degrees
	{
	}

	fDirFlag = (vImagePhaseDir.x*1.0 + vImagePhaseDir.y*1.0 + vImagePhaseDir.z*1.0) 
		/ (sqrt( pow(vImagePhaseDir.x,2) + pow(vImagePhaseDir.y,2) + pow(vImagePhaseDir.z,2)) * sqrt( 1.0 + 1.0 + 1.0 ));
	fAngle = acos( fDirFlag ) * (360.0 / (2.0*PI));
	
	// swap direction
	if ( fDirFlag < 0.0 && fDirFlag >= -1.0)		// 90~180 degrees
	{
		vImagePhaseDir.x = -vImagePhaseDir.x;
		vImagePhaseDir.y = -vImagePhaseDir.y;
		vImagePhaseDir.z = -vImagePhaseDir.z;
	}
	else if ( fDirFlag > 0.0 && fDirFlag <= 1.0 )	// 0~90 degrees
	{
	}
	
	
/*
	fW<<"vImageReadDir.x="<<vImageReadDir.x<<endl;
	fW<<"vImageReadDir.y="<<vImageReadDir.y<<endl;
	fW<<"vImageReadDir.z="<<vImageReadDir.z<<endl;
	fW<<"vImagePhaseDir.x="<<vImagePhaseDir.x<<endl;
	fW<<"vImagePhaseDir.y="<<vImagePhaseDir.y<<endl;
	fW<<"vImagePhaseDir.z="<<vImagePhaseDir.z<<endl;
*/
	//垂直向量
	CThreeDim pDimVer;
	pDimVer.x=vImageReadDir.y*vImagePhaseDir.z-vImageReadDir.z*vImagePhaseDir.y ;
	pDimVer.y=-vImageReadDir.x*vImagePhaseDir.z+vImageReadDir.z*vImagePhaseDir.x;
	pDimVer.z=vImageReadDir.x*vImagePhaseDir.y-vImageReadDir.y*vImagePhaseDir.x;
	double fReadDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	double fPhaseDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	double fDimVerModule=sqrt(pow(pDimVer.x,2) + pow(pDimVer.y,2) + pow(pDimVer.z,2));
	if ( fReadDirModule < 1.0e-8 || fPhaseDirModule < 1.0e-8 || fDimVerModule<1.0e-8)
	{
		fRowCosineWithZ = fRowCosineWithX = fRowCosineWithY = 0.0;
		fColCosineWithZ = fColCosineWithX = fColCosineWithY = 0.0;
		if ( oImageHeader.imageField.Id == 0  )
		{
			//CLang::GetHandle().ShowMessage( CLang::GetHandle().GetCharRes("MSG___INVALID_LOC_INFO") );
		}		
		return;
	}
	// 左上角第一点的坐标
	fTopLeftX = oImageHeader.imageField.fCenterPointX 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.x
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.x;
	fTopLeftY = oImageHeader.imageField.fCenterPointY 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.y
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.y;
	fTopLeftZ = oImageHeader.imageField.fCenterPointZ 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.z
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.z;
	//单位化
	pDimVer.x/=fDimVerModule;
	pDimVer.y/=fDimVerModule;
	pDimVer.z/=fDimVerModule;
	const double DPI=3.1415926535;
	//double pAngle=cos(/*DPI**/nAngleOffset);
	
	//根据推导公式的到旋转以后的行向量和列向量
	////////////////////////////////////////////////////////////////////////////////////
	CThreeDim vImageReadDirNew, vImagePhaseDirNew;
	//规定nAngleOffset>0向逆时针方向转动，反之逆时针方向转动
	//nAngleOffset=-nAngleOffset;
	GetRotateMatrixFromAxis(pDimVer,nAngleOffset);
	vImageReadDirNew=VertorCrossMatrix(vImageReadDir);
	vImagePhaseDirNew=VertorCrossMatrix(vImagePhaseDir);
	double n1=vImageReadDirNew.Modulus();
	double n2=vImagePhaseDirNew.Modulus();
////////////////////////////////////////////////////////////////////////////////////
	//jiang

	if(nVerFlip==TRUE)
	{
		vImagePhaseDirNew.x=-vImagePhaseDirNew.x;
		vImagePhaseDirNew.y=-vImagePhaseDirNew.y;
		vImagePhaseDirNew.z=-vImagePhaseDirNew.z;

	}
	if(nHorFlip==TRUE)
	{
		vImageReadDirNew.x=-vImageReadDirNew.x;
		vImageReadDirNew.y=-vImageReadDirNew.y;
		vImageReadDirNew.z=-vImageReadDirNew.z;
		
	}
	if(fabs(vImageReadDirNew.x)<1.0e-6)
	{
		vImageReadDirNew.x=0;

	}
	if(fabs(vImageReadDirNew.y)<1.0e-6)
	{
		vImageReadDirNew.y=0;

	}
	if(fabs(vImageReadDirNew.z)<1.0e-6)
	{
		vImageReadDirNew.z=0;

	}
	if(fabs(vImagePhaseDirNew.x)<1.0e-6)
	{
		vImagePhaseDirNew.x=0;

	}
	if(fabs(vImagePhaseDirNew.y)<1.0e-6)
	{
		vImagePhaseDirNew.y=0;

	}
	if(fabs(vImagePhaseDirNew.z)<1.0e-6)
	{
		vImagePhaseDirNew.z=0;

	}
/*
	fW<<"after calculate..."<<endl;
	fW<<"vImageReadDirNew.x="<<vImageReadDirNew.x<<endl;
	fW<<"vImageReadDirNew.y="<<vImageReadDirNew.y<<endl;
	fW<<"vImageReadDirNew.z="<<vImageReadDirNew.z<<endl;
	fW<<"vImagePhaseDirNew.x="<<vImagePhaseDirNew.x<<endl;
	fW<<"vImagePhaseDirNew.y="<<vImagePhaseDirNew.y<<endl;
	fW<<"vImagePhaseDirNew.z="<<vImagePhaseDirNew.z<<endl;
*/


//	CThreeDim p1,pdim,px;
//	pdim.x=0;
//	pdim.y=0;
//	pdim.z=1;
//	nAngleOffset=1.57;
//	GetRotateMatrixFromAxis(pdim,-nAngleOffset);
//	p1.x=1;
//	p1.y=0;
//	p1.z=0;
//	px=VertorCrossMatrix(p1);
	//////////////////////////////////////////////////////////////////////////////////
	//原来坐标系的旋转后的起始点坐标
	fTopLeftX = oImageHeader.imageField.fCenterPointX 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.x
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.x;
	fTopLeftY = oImageHeader.imageField.fCenterPointY 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.y
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.y;
	fTopLeftZ = oImageHeader.imageField.fCenterPointZ 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.z
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.z;
	//起始点矢量坐标变换
	CThreeDim pLeftTopStartPoint(fTopLeftX,fTopLeftY,fTopLeftZ);
	double fModuleStartPoint=pLeftTopStartPoint.Modulus();
	/*fModuleStartPoint*/

	



	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	double fNumerator, fDenominator;
		// 行向量
	fNumerator = vImageReadDirNew.x*vBodySuperior.x + vImageReadDirNew.y*vBodySuperior.y + vImageReadDirNew.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fRowCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImageReadDirNew.x*vBodyLeft.x + vImageReadDirNew.y*vBodyLeft.y + vImageReadDirNew.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fRowCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImageReadDirNew.x*vBodyPosterior.x + vImageReadDirNew.y*vBodyPosterior.y + vImageReadDirNew.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fRowCosineWithY = fNumerator / fDenominator;
	double p=fRowCosineWithX*fRowCosineWithX+fRowCosineWithY*fRowCosineWithY+fRowCosineWithZ*fRowCosineWithZ;
	
		// 列向量
	fNumerator = vImagePhaseDirNew.x*vBodySuperior.x + vImagePhaseDirNew.y*vBodySuperior.y + vImagePhaseDirNew.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fColCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDirNew.x*vBodyLeft.x + vImagePhaseDirNew.y*vBodyLeft.y + vImagePhaseDirNew.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fColCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDirNew.x*vBodyPosterior.x + vImagePhaseDirNew.y*vBodyPosterior.y + vImagePhaseDirNew.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fColCosineWithY = fNumerator / fDenominator;
	double p2=fColCosineWithX*fColCosineWithX+fColCosineWithY*fColCosineWithY+fColCosineWithZ*fColCosineWithZ;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//旋转的变量起始向量
	fNumerator = pLeftTopStartPoint.x*vBodySuperior.x + pLeftTopStartPoint.y*vBodySuperior.y + pLeftTopStartPoint.z*vBodySuperior.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fTopLeftZ =(float)(fNumerator / fDenominator*fModuleStartPoint) ;
	
	fNumerator = pLeftTopStartPoint.x*vBodyLeft.x + pLeftTopStartPoint.y*vBodyLeft.y + pLeftTopStartPoint.z*vBodyLeft.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fTopLeftX =(float) (fNumerator / fDenominator*fModuleStartPoint);
	
	fNumerator = pLeftTopStartPoint.x*vBodyPosterior.x + pLeftTopStartPoint.y*vBodyPosterior.y + pLeftTopStartPoint.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fTopLeftY =(float)(fNumerator / fDenominator*fModuleStartPoint) ;
//	fTopLeftX=fRowCosineWithX*fModuleStartPoint;
//	fTopLeftY=fRowCosineWithY*fModuleStartPoint;
//	fTopLeftZ=fRowCosineWithZ*fModuleStartPoint;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(fabs(fRowCosineWithX)<1.0e-6)
	{
		fRowCosineWithX=0;

	}	if(fabs(fRowCosineWithY)<1.0e-6)
	{
		fRowCosineWithY=0;

	}
	if(fabs(fRowCosineWithZ)<1.0e-6)
	{
		fRowCosineWithZ=0;

	}
	if(fabs(fColCosineWithX)<1.0e-6)
	{
		fColCosineWithX=0;

	}
	if(fabs(fColCosineWithY)<1.0e-6)
	{
		fColCosineWithY=0;

	}
	if(fabs(fColCosineWithZ)<1.0e-6)
	{
		fColCosineWithZ=0;

	}
/*
	fW<<"siz cosine values..."<<endl;
	fW<<"fRowCosineWithX="<<fRowCosineWithX<<endl;
	fW<<"fRowCosineWithY="<<fRowCosineWithY<<endl;
	fW<<"fRowCosineWithZ="<<fRowCosineWithZ<<endl;
	fW<<"fColCosineWithX="<<fColCosineWithX<<endl;
	fW<<"fColCosineWithY="<<fColCosineWithY<<endl;
	fW<<"fColCosineWithZ="<<fColCosineWithZ<<endl;
	fW.close();
*/

	return;
}
BOOL CDirectionCalculator::GetRotateMatrixFromAxis(CThreeDim axis,double radian)
{
	//MATRIX33 ret;
	for(int i=0;i<9;i++)
	{
		ret[i]=0.0;
	}
	CThreeDim axis_n = axis;
	axis_n.Unify();
	float c = (float)cos(radian);
	float s = (float)sin(radian);
	float omc = (1 - c);
							
	float x = axis_n.x;
	float y = axis_n.y;
	float z = axis_n.z;	
	float xs = x * s;
	float ys = y * s;
	float zs = z * s;
	float xyomc = x * y * omc;
	float xzomc = x * z * omc;
	float yzomc = y * z * omc;
	
	ret[0] = x*x*omc + c;
	ret[1] = xyomc + zs;
	ret[2] = xzomc - ys;
			
	ret[3] = xyomc - zs;
	ret[4] = y*y*omc + c;
	ret[5] = yzomc + xs;
			
	ret[6] = xzomc + ys;
	ret[7] = yzomc - xs;
	ret[8] = z*z*omc + c;

		return TRUE;
	
	
}


EPresaturationDirection CDirectionCalculator::GetPresatDirection( 
						const CSeries* pSeries, EHumanBodyDirection hbdDir )
{
	if ( !pSeries->GetCurrentScan() )
	{
		return pdNone;
	}
	
	// 求人体方位对应的设备坐标系方向
	CThreeDim vEquipCoordDir;
	CDirectionCalculator::GetHandle().GetPhysicalDirection(
		static_cast<EBodyPosition>(pSeries->StudyParams().PatPosition), 
		static_cast<EBodyEntry>(pSeries->StudyParams().PatEntry), 
		static_cast<EHumanBodyDirection>(hbdDir), 
		vEquipCoordDir );
	
	// 求人体方位对应的设备坐标轴表示
	EPresaturationDirection PresatDir = pdNone;
	ScanField scanField = pSeries->GetCurrentScan()->ScanParams();
	CThreeDim vReadDir ( scanField.FreqDirX, scanField.FreqDirY, scanField.FreqDirZ );
	CThreeDim vPhaseDir( scanField.PhaseDirX, scanField.PhaseDirY, scanField.PhaseDirZ );
	CThreeDim vSliceDir( scanField.SliceDirX, scanField.SliceDirY, scanField.SliceDirZ );
	double fNumerator, fDenominator;
	double fCosWithReadDir, fCosWithPhaseDir, fCosWithSliceDir;
	
	fNumerator = vEquipCoordDir.x*vReadDir.x + vEquipCoordDir.y*vReadDir.y + vEquipCoordDir.z*vReadDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vReadDir.x,2) + pow(vReadDir.y,2) + pow(vReadDir.z,2));
	fCosWithReadDir = fNumerator / fDenominator;
	fCosWithReadDir = fabs( fCosWithReadDir );
	
	fNumerator = vEquipCoordDir.x*vPhaseDir.x + vEquipCoordDir.y*vPhaseDir.y + vEquipCoordDir.z*vPhaseDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vPhaseDir.x,2) + pow(vPhaseDir.y,2) + pow(vPhaseDir.z,2));
	fCosWithPhaseDir = fNumerator / fDenominator;
	fCosWithPhaseDir = fabs( fCosWithPhaseDir );
	
	fNumerator = vEquipCoordDir.x*vSliceDir.x + vEquipCoordDir.y*vSliceDir.y + vEquipCoordDir.z*vSliceDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vSliceDir.x,2) + pow(vSliceDir.y,2) + pow(vSliceDir.z,2));
	fCosWithSliceDir = fNumerator / fDenominator;
	fCosWithSliceDir = fabs( fCosWithSliceDir );
	
	if ( fCosWithReadDir > 1.0/2 )
	{
		PresatDir = pdRead;
	}

	if ( fCosWithPhaseDir > 1.0/2 )
	{
		PresatDir = pdPhase;
	}

	if ( fCosWithSliceDir > 1.0/2 )
	{
		PresatDir = pdSlice;
	}
	
	return PresatDir;
}
/*
EEquipCoordinateAxisDirection CDirectionCalculator::GetEquipCoordinateAxisDirection( 
						StudyField oStudyField, EHumanBodyDirection hbdDir )
{
	// 求人体方位对应的设备坐标系方向
	CThreeDim vEquipCoordDir;
	CDirectionCalculator::GetHandle().GetPhysicalDirection(
		static_cast<EBodyPosition>(oStudyField.PatPosition), 
		static_cast<EBodyEntry>(oStudyField.PatEntry), 
		static_cast<EHumanBodyDirection>(hbdDir), 
		vEquipCoordDir );
	
	// 求人体方位对应的设备坐标轴表示
	EEquipCoordinateAxisDirection nECD = ecdNone;
	CThreeDim vXAxisDir( 1, 0, 0 );
	CThreeDim vYAxisDir( 0, 1, 0 );
	CThreeDim vZAxisDir( 0, 0, 1 );
	double fNumerator, fDenominator;
	double fCosineWithX, fCosineWithY, fCosineWithZ;
	
	fNumerator = vEquipCoordDir.x*vXAxisDir.x + vEquipCoordDir.y*vXAxisDir.y + vEquipCoordDir.z*vXAxisDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vXAxisDir.x,2) + pow(vXAxisDir.y,2) + pow(vXAxisDir.z,2));
	fCosineWithX = fNumerator / fDenominator;
	fCosineWithX = abs( fCosineWithX );
	
	fNumerator = vEquipCoordDir.x*vYAxisDir.x + vEquipCoordDir.y*vYAxisDir.y + vEquipCoordDir.z*vYAxisDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vYAxisDir.x,2) + pow(vYAxisDir.y,2) + pow(vYAxisDir.z,2));
	fCosineWithY = fNumerator / fDenominator;
	fCosineWithY = abs( fCosineWithY );
	
	fNumerator = vEquipCoordDir.x*vZAxisDir.x + vEquipCoordDir.y*vZAxisDir.y + vEquipCoordDir.z*vZAxisDir.z;
	fDenominator = sqrt(pow(vEquipCoordDir.x,2) + pow(vEquipCoordDir.y,2) + pow(vEquipCoordDir.z,2)) 
		* sqrt(pow(vZAxisDir.x,2) + pow(vZAxisDir.y,2) + pow(vZAxisDir.z,2));
	fCosineWithZ = fNumerator / fDenominator;
	fCosineWithZ = abs( fCosineWithZ );
	
	if ( fCosineWithX > 1.0/2 )
	{
		nECD = ecdX;
	}

	if ( fCosineWithY > 1.0/2 )
	{
		nECD = ecdY;
	}

	if ( fCosineWithZ > 1.0/2 )
	{
		nECD = ecdZ;
	}
	
	return nECD;
}*/

CThreeDim CDirectionCalculator::VertorCrossMatrix(CThreeDim nSrc)
{
	CThreeDim pDim;
	pDim.x=nSrc.x*ret[0]+nSrc.y*ret[3]+nSrc.z*ret[6];
	pDim.y=nSrc.x*ret[1]+nSrc.y*ret[4]+nSrc.z*ret[7];
	pDim.z=nSrc.x*ret[2]+nSrc.y*ret[5]+nSrc.z*ret[8];
	return pDim;


}
EHumanBodyDirection 
CDirectionCalculator::Get_MIP_Series_MainDirection(EBodyPosition bodyPosition,
                                       EBodyEntry bodyEntry, 
                                       CThreeDim tdDirection)
{
    EHumanBodyDirection hbd;
    // Firstly, we find the max projection direction. Then determines which
    // body direction that direction points to.

    if (fabs(tdDirection.x) >= fabs(tdDirection.y) && 
        fabs(tdDirection.x) >= fabs(tdDirection.z))
        // max projection is x.
    {
        if (bodyEntry == beHeadFirst)
        {
            switch(bodyPosition)
            {
            case bpProne:
				if(tdDirection.x>=0)
				{
					hbd = hbdRight;//
				}
				else
				{
					hbd = hbdLeft;
				
				}
                
                break;
            case bpSupine:
				if(tdDirection.x>=0)
				{
					hbd = hbdLeft;//
				}
				else
				{
					hbd = hbdRight;
				
				}
                //hbd = hbdLeft;
                break;
            case bpDecubitusLeft:
				if(tdDirection.x>=0)
				{
					hbd = hbdAnterior;//
				}
				else
				{
					hbd = hbdPosterior;
				
				}

                //hbd = hbdAnterior;
                break;
            case bpDecubitusRight:
				if(tdDirection.x>=0)
				{
					hbd = hbdPosterior;//
				}
				else
				{
					hbd = hbdAnterior;
				
				}
                //hbd = hbdPosterior;
                break;
            default:
                ASSERT(0);
            }
        }
        else
        {
            switch(bodyPosition)
            {
            case bpProne:
				if(tdDirection.x>=0)
				{
					hbd = hbdLeft;//
				}
				else
				{
					hbd = hbdRight;
				
				}
                //hbd = hbdLeft;
                break;
            case bpSupine:
				if(tdDirection.x>=0)
				{
					hbd = hbdRight;//
				}
				else
				{
					hbd = hbdLeft;
				
				}
                //hbd = hbdRight;
                break;
            case bpDecubitusLeft:
				if(tdDirection.x>=0)
				{
					hbd = hbdPosterior;//
				}
				else
				{
					hbd = hbdAnterior;
				
				}
                //hbd = hbdPosterior;
                break;
            case bpDecubitusRight:
				if(tdDirection.x>=0)
				{
					hbd = hbdAnterior;//
				}
				else
				{
					hbd = hbdPosterior;
				
				}
                //hbd = hbdAnterior;
                break;
            default:
                ASSERT(0);
            }
        }
    }
    else if (fabs(tdDirection.y) >= fabs(tdDirection.z))
        // max projection is y.
    {
        if (bodyEntry == beHeadFirst)
        {
			if(tdDirection.y>=0)
			{
				hbd = hbdSuperior;//
			}
			else
			{
				hbd = hbdInferior;
			
			}
            //hbd = hbdSuperior;
        }
        else
        {
			if(tdDirection.y>=0)
			{
				hbd = hbdInferior;//
			}
			else
			{
				hbd = hbdSuperior;
			
			}
            //hbd = hbdInferior;
			
        }
    }
    else // max projection is z.
    {
        switch(bodyPosition)
        {
        case bpProne:
			if(tdDirection.z>=0)
			{
				hbd = hbdPosterior;//
			}
			else
			{
				hbd = hbdAnterior;
			
			}
            //hbd = hbdPosterior;
            break;
        case bpSupine:
			if(tdDirection.z>=0)
			{
				hbd = hbdAnterior;//
			}
			else
			{
				hbd = hbdPosterior;
			
			}
            //hbd = hbdAnterior;
            break;
        case bpDecubitusLeft:
			if(tdDirection.z>=0)
			{
				hbd = hbdRight;//
			}
			else
			{
				hbd = hbdLeft;
			
			}
            //hbd = hbdRight;
            break;
        case bpDecubitusRight:
			if(tdDirection.z>=0)
			{
				hbd = hbdLeft;//
			}
			else
			{
				hbd = hbdRight;
			
			}
            hbd = hbdLeft;
            break;
        default:
            ASSERT(0);
        }
    }

    return (hbd);
}


CString CDirectionCalculator::GetDefaultFrequencyDir( StudyField oStudyParams, ScanField oScanParams )
{
	unsigned char nPatientPosition	= oStudyParams.PatPosition;
	unsigned char nPatientEntry		= oStudyParams.PatEntry;
	unsigned char PatientBodyPart	= oStudyParams.PatBodyPart;
	
	// figure out the orginal orientation of the image.
    EHumanBodyDirection  hbdReadDir ; //, hbdPhaseDir;   //Modified by Tom, --2008.07.10
    CThreeDim tdReadDir( oScanParams.FreqDirX, oScanParams.FreqDirY, oScanParams.FreqDirZ );	
    hbdReadDir = CDirectionCalculator::GetHandle().GetMainDirection(
		static_cast<EBodyPosition>(nPatientPosition), static_cast<EBodyEntry>(nPatientEntry),
		tdReadDir );
	
    // orientation array
    static achDirections[6] = {'L', 'R', 'A', 'P', 'S', 'I', };
	
	CString sDir = "";
    sDir = achDirections[hbdReadDir];
	sDir += "-";
    sDir += (hbdReadDir % 2 == 0) ? 
        achDirections[hbdReadDir + 1] : achDirections[hbdReadDir - 1];
	
	return sDir;
}
void CDirectionCalculator::GetMIPActiveDirForDicom( CBIImageHeader oImageHeader,
		float& fTopLeftX, float& fTopLeftY, float& fTopLeftZ,
		float& fRowCosineWithZ,float& fRowCosineWithX,float& fRowCosineWithY,
		float& fColCosineWithZ,float& fColCosineWithX,float& fColCosineWithY )
{
/*
	this->GetOrientationsForDicom(oImageHeader,fTopLeftX,fTopLeftY,fTopLeftZ,
		fRowCosineWithZ,fRowCosineWithX,fRowCosineWithY,
		fColCosineWithZ,fColCosineWithX,fColCosineWithY);
*/
/*
	fstream fW;
	fW.open("c:\\KPACS_Wrter.txt",ios::in|ios::out|ios::app);
	fW<<"nPlaneType="<<(int)oImageHeader.imageField.nPlaneType<<"\t"<<"Study ID="<<oImageHeader.studyField.Id<<"\t"<<"Series="<<(int)oImageHeader.seriesField.Id<<"\t"<<"Image ID="<<oImageHeader.imageField.Id<<"-----------------------------"<<endl;
	fW<<"nAngleOffset="<<nAngleOffset<<"\t"<<"nVerFlip="<<nVerFlip<<"\t"<<"nHorFlip="<<nHorFlip<<endl;
*/
	oImageHeader.imageField.fCenterPointX;
	oImageHeader.imageField.fCenterPointY;
	oImageHeader.imageField.fCenterPointZ;
	oImageHeader.seriesField.FovX;
	oImageHeader.seriesField.FovY;
	oImageHeader.seriesField.FovZ;

	CThreeDim vBodySuperior, vBodyLeft, vBodyPosterior;
	GetBodyCoordinateAxisDir( oImageHeader.studyField.PatPosition, oImageHeader.studyField.PatEntry,
		vBodySuperior, vBodyLeft, vBodyPosterior );

	//行向量和列向量
	CThreeDim vImageReadDir, vImagePhaseDir;
	vImageReadDir.x = oImageHeader.imageField.fFreqDirX;
	vImageReadDir.y = oImageHeader.imageField.fFreqDirY;
	vImageReadDir.z = oImageHeader.imageField.fFreqDirZ;
	
	vImagePhaseDir.x = oImageHeader.imageField.fPhaseDirX;
	vImagePhaseDir.y = oImageHeader.imageField.fPhaseDirY;
	vImagePhaseDir.z = oImageHeader.imageField.fPhaseDirZ;

	double fDirFlag = (vImageReadDir.x*1.0 + vImageReadDir.y*1.0 + vImageReadDir.z*1.0) 
		/ (sqrt( pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2)) * sqrt( 1.0 + 1.0 + 1.0 ));
	double fAngle = acos( fDirFlag ) * (360.0 / (2.0*PI));

	// swap direction
/*	if ( fDirFlag < 0.0 && fDirFlag >= -1.0)		// 90~180 degrees
	{
		vImageReadDir.x = -vImageReadDir.x;
		vImageReadDir.y = -vImageReadDir.y;
		vImageReadDir.z = -vImageReadDir.z;
	}
	else if ( fDirFlag > 0.0 && fDirFlag <= 1.0 )	// 0~90 degrees
	{
	}
*/
	fDirFlag = (vImagePhaseDir.x*1.0 + vImagePhaseDir.y*1.0 + vImagePhaseDir.z*1.0) 
		/ (sqrt( pow(vImagePhaseDir.x,2) + pow(vImagePhaseDir.y,2) + pow(vImagePhaseDir.z,2)) * sqrt( 1.0 + 1.0 + 1.0 ));
	fAngle = acos( fDirFlag ) * (360.0 / (2.0*PI));
	
	// swap direction
/*	if ( fDirFlag < 0.0 && fDirFlag >= -1.0)		// 90~180 degrees
	{
		vImagePhaseDir.x = -vImagePhaseDir.x;
		vImagePhaseDir.y = -vImagePhaseDir.y;
		vImagePhaseDir.z = -vImagePhaseDir.z;
	}
	else if ( fDirFlag > 0.0 && fDirFlag <= 1.0 )	// 0~90 degrees
	{
	}*/
	
	
/*
	fW<<"vImageReadDir.x="<<vImageReadDir.x<<endl;
	fW<<"vImageReadDir.y="<<vImageReadDir.y<<endl;
	fW<<"vImageReadDir.z="<<vImageReadDir.z<<endl;
	fW<<"vImagePhaseDir.x="<<vImagePhaseDir.x<<endl;
	fW<<"vImagePhaseDir.y="<<vImagePhaseDir.y<<endl;
	fW<<"vImagePhaseDir.z="<<vImagePhaseDir.z<<endl;
*/
	//垂直向量
	CThreeDim pDimVer;
	pDimVer.x=vImageReadDir.y*vImagePhaseDir.z-vImageReadDir.z*vImagePhaseDir.y ;
	pDimVer.y=-vImageReadDir.x*vImagePhaseDir.z+vImageReadDir.z*vImagePhaseDir.x;
	pDimVer.z=vImageReadDir.x*vImagePhaseDir.y-vImageReadDir.y*vImagePhaseDir.x;
	double fReadDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	double fPhaseDirModule = sqrt(pow(vImageReadDir.x,2) + pow(vImageReadDir.y,2) + pow(vImageReadDir.z,2));
	double fDimVerModule=sqrt(pow(pDimVer.x,2) + pow(pDimVer.y,2) + pow(pDimVer.z,2));
	if ( fReadDirModule < 1.0e-8 || fPhaseDirModule < 1.0e-8 || fDimVerModule<1.0e-8)
	{
		fRowCosineWithZ = fRowCosineWithX = fRowCosineWithY = 0.0;
		fColCosineWithZ = fColCosineWithX = fColCosineWithY = 0.0;
		if ( oImageHeader.imageField.Id == 0  )
		{
			//CLang::GetHandle().ShowMessage( CLang::GetHandle().GetCharRes("MSG___INVALID_LOC_INFO") );
		}		
		return;
	}
	// 左上角第一点的坐标
	fTopLeftX = oImageHeader.imageField.fCenterPointX 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.x
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.x;
	fTopLeftY = oImageHeader.imageField.fCenterPointY 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.y
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.y;
	fTopLeftZ = oImageHeader.imageField.fCenterPointZ 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDir.z
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDir.z;
	//单位化
	pDimVer.x/=fDimVerModule;
	pDimVer.y/=fDimVerModule;
	pDimVer.z/=fDimVerModule;
	const double DPI=3.1415926535;
	//double pAngle=cos(/*DPI**/nAngleOffset);
	
	//根据推导公式的到旋转以后的行向量和列向量
	////////////////////////////////////////////////////////////////////////////////////
	CThreeDim vImageReadDirNew=vImageReadDir;
	CThreeDim vImagePhaseDirNew=vImagePhaseDir;

////////////////////////////////////////////////////////////////////////////////////
	//jiang


	if(fabs(vImageReadDirNew.x)<1.0e-6)
	{
		vImageReadDirNew.x=0;

	}
	if(fabs(vImageReadDirNew.y)<1.0e-6)
	{
		vImageReadDirNew.y=0;

	}
	if(fabs(vImageReadDirNew.z)<1.0e-6)
	{
		vImageReadDirNew.z=0;

	}
	if(fabs(vImagePhaseDirNew.x)<1.0e-6)
	{
		vImagePhaseDirNew.x=0;

	}
	if(fabs(vImagePhaseDirNew.y)<1.0e-6)
	{
		vImagePhaseDirNew.y=0;

	}
	if(fabs(vImagePhaseDirNew.z)<1.0e-6)
	{
		vImagePhaseDirNew.z=0;

	}

	//////////////////////////////////////////////////////////////////////////////////
	//原来坐标系的旋转后的起始点坐标
	fTopLeftX = oImageHeader.imageField.fCenterPointX 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.x
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.x;
	fTopLeftY = oImageHeader.imageField.fCenterPointY 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.y
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.y;
	fTopLeftZ = oImageHeader.imageField.fCenterPointZ 
		- (float)(oImageHeader.seriesField.FovX / 2) * vImageReadDirNew.z
		- (float)(oImageHeader.seriesField.FovY / 2) * vImagePhaseDirNew.z;
	//起始点矢量坐标变换
	CThreeDim pLeftTopStartPoint(fTopLeftX,fTopLeftY,fTopLeftZ);
	double fModuleStartPoint=pLeftTopStartPoint.Modulus();
	/*fModuleStartPoint*/

	



	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	double fNumerator, fDenominator;
		// 行向量
	fNumerator = vImageReadDirNew.x*vBodySuperior.x + vImageReadDirNew.y*vBodySuperior.y + vImageReadDirNew.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fRowCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImageReadDirNew.x*vBodyLeft.x + vImageReadDirNew.y*vBodyLeft.y + vImageReadDirNew.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fRowCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImageReadDirNew.x*vBodyPosterior.x + vImageReadDirNew.y*vBodyPosterior.y + vImageReadDirNew.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImageReadDirNew.x,2) + pow(vImageReadDirNew.y,2) + pow(vImageReadDirNew.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fRowCosineWithY = fNumerator / fDenominator;
	double p=fRowCosineWithX*fRowCosineWithX+fRowCosineWithY*fRowCosineWithY+fRowCosineWithZ*fRowCosineWithZ;
	
		// 列向量
	fNumerator = vImagePhaseDirNew.x*vBodySuperior.x + vImagePhaseDirNew.y*vBodySuperior.y + vImagePhaseDirNew.z*vBodySuperior.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fColCosineWithZ = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDirNew.x*vBodyLeft.x + vImagePhaseDirNew.y*vBodyLeft.y + vImagePhaseDirNew.z*vBodyLeft.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fColCosineWithX = fNumerator / fDenominator;
	
	fNumerator = vImagePhaseDirNew.x*vBodyPosterior.x + vImagePhaseDirNew.y*vBodyPosterior.y + vImagePhaseDirNew.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(vImagePhaseDirNew.x,2) + pow(vImagePhaseDirNew.y,2) + pow(vImagePhaseDirNew.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fColCosineWithY = fNumerator / fDenominator;
	double p2=fColCosineWithX*fColCosineWithX+fColCosineWithY*fColCosineWithY+fColCosineWithZ*fColCosineWithZ;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//旋转的变量起始向量
	fNumerator = pLeftTopStartPoint.x*vBodySuperior.x + pLeftTopStartPoint.y*vBodySuperior.y + pLeftTopStartPoint.z*vBodySuperior.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodySuperior.x,2) + pow(vBodySuperior.y,2) + pow(vBodySuperior.z,2));
	fTopLeftZ =(float)(fNumerator / fDenominator*fModuleStartPoint) ;
	
	fNumerator = pLeftTopStartPoint.x*vBodyLeft.x + pLeftTopStartPoint.y*vBodyLeft.y + pLeftTopStartPoint.z*vBodyLeft.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodyLeft.x,2) + pow(vBodyLeft.y,2) + pow(vBodyLeft.z,2));
	fTopLeftX =(float) (fNumerator / fDenominator*fModuleStartPoint);
	
	fNumerator = pLeftTopStartPoint.x*vBodyPosterior.x + pLeftTopStartPoint.y*vBodyPosterior.y + pLeftTopStartPoint.z*vBodyPosterior.z;
	fDenominator = sqrt(pow(pLeftTopStartPoint.x,2) + pow(pLeftTopStartPoint.y,2) + pow(pLeftTopStartPoint.z,2)) 
		* sqrt(pow(vBodyPosterior.x,2) + pow(vBodyPosterior.y,2) + pow(vBodyPosterior.z,2));
	fTopLeftY =(float)(fNumerator / fDenominator*fModuleStartPoint) ;
//	fTopLeftX=fRowCosineWithX*fModuleStartPoint;
//	fTopLeftY=fRowCosineWithY*fModuleStartPoint;
//	fTopLeftZ=fRowCosineWithZ*fModuleStartPoint;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(fabs(fRowCosineWithX)<1.0e-6)
	{
		fRowCosineWithX=0;

	}	if(fabs(fRowCosineWithY)<1.0e-6)
	{
		fRowCosineWithY=0;

	}
	if(fabs(fRowCosineWithZ)<1.0e-6)
	{
		fRowCosineWithZ=0;

	}
	if(fabs(fColCosineWithX)<1.0e-6)
	{
		fColCosineWithX=0;

	}
	if(fabs(fColCosineWithY)<1.0e-6)
	{
		fColCosineWithY=0;

	}
	if(fabs(fColCosineWithZ)<1.0e-6)
	{
		fColCosineWithZ=0;

	}
/*
	fW<<"siz cosine values..."<<endl;
	fW<<"fRowCosineWithX="<<fRowCosineWithX<<endl;
	fW<<"fRowCosineWithY="<<fRowCosineWithY<<endl;
	fW<<"fRowCosineWithZ="<<fRowCosineWithZ<<endl;
	fW<<"fColCosineWithX="<<fColCosineWithX<<endl;
	fW<<"fColCosineWithY="<<fColCosineWithY<<endl;
	fW<<"fColCosineWithZ="<<fColCosineWithZ<<endl;
	fW.close();
*/

	return;
}
