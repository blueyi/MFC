// Image.cpp : CImage  Wraps an MRI image.
//
#include "stdafx.h"
#include "Image.h"
#include "BI_Constants.h"

#pragma warning (disable:4786)
#include <fstream>
#include <exception>
#include <iostream>
#include <cassert>

#include "DirectionCalculator.h"

/*!
	\param pScan Scan to which the image belongs.
	\param nID Image id, useful when loading the image from file.
*/
CImage::CImage(CScan* pScan, int nID)
{
	//Added by Tom, --2008.07.10
    memset(&m_sImageHeader, 0, sizeof(CBIImageHeader));

	memset(&m_ImageParams, 0, sizeof(m_ImageParams));
    if (nID != -1)
	{
		m_ImageParams.Id = nID;
	}
    assert(pScan != NULL);
	m_pBuffer = NULL;

//Added by jhzhang 2004/09/03 init 
	m_pFilterBuffer = NULL;

    m_pRawData = NULL;
    m_bOwnRawData = false;
    //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

    m_pScan = pScan;
    pScan->AddImage(this);
	m_bImageWndSel=FALSE;
}

CImage::~CImage()
{
	if(m_pBuffer)
		delete m_pBuffer;

    if (m_bOwnRawData)
        delete m_pRawData;

	if(m_pFilterBuffer)
		delete m_pFilterBuffer;
}


/*!
    This function save the image data together with all of the parameters to a 
    given file.
    \todo support data types other than IMGDATA_RAW and IMGDAT_IMGDAT_MAG.
*/
bool CImage::SaveToFile(const std::string& strFilename)
{
    ASSERT(m_pBuffer != NULL);

    std::ofstream outFile(strFilename.c_str(), 
        std::ios::out | std::ios::binary);
    
    if (!outFile)
        return false;

	// read Version of image

    HeaderInfo fileHeader;
    memset(&fileHeader, 0, sizeof(fileHeader));

    // file signature: "BIMRI"
    fileHeader.BITitle[0] = 'B';
    fileHeader.BITitle[1] = 'I';
    fileHeader.BITitle[2] = 'M';
    fileHeader.BITitle[3] = 'R';
    fileHeader.BITitle[4] = 'I';

	// {xuzhl,2005.12.09} change data type from U2 to F4, 	
    // major version 1, minor version 0	
	
	/** [zhlxu 2008.2.3] [] 解决在添加DefaultSliceOrder选项功能后软件的向前兼容问题 **/
//    fileHeader.Version = int (1) << 16 + 0;	// Support short SliceGap
//    fileHeader.Version = int (1) << 16 + 1;	// Support float SliceGap
    fileHeader.Version = int (1) << 16 + 2;		// Support DefaultSliceOrder
	/** [zhlxu 2008.2.3] **/
	
    
	// image header info structr size.
    fileHeader.Size = sizeof(HeaderInfo);
    // number of header fields in the header.
    fileHeader.NumHdrFields = 6; 
    // size of the entire header
    fileHeader.HeaderSize = sizeof(HeaderInfo) + sizeof(SiteField) +
        sizeof(PatientField) + sizeof(StudyField) + sizeof(SeriesField)
        + sizeof(ScanField) + sizeof(ImageField);

    // for the time being, only these two types are supported.
    ASSERT (((SeriesParams().DataType & cnstRaw) != 0) ||
            ((SeriesParams().DataType & cnstMagnitudeImage) != 0));
  
    // size of the data matrixs that follows the header, in bytes.
    int nPixelSize = 0;
    if (SeriesParams().DataType & cnstRaw)
        nPixelSize = 2 * sizeof(float);
    else if (SeriesParams().DataType & cnstMagnitudeImage)
        nPixelSize = sizeof(unsigned short);
    fileHeader.DataMatrixSize = GetWidth() * GetHeight() * nPixelSize;

    // write out the image header
    outFile.write((char*)(&fileHeader), sizeof(fileHeader));
    outFile.write((char*)(&SiteParams()), sizeof(SiteField));
    outFile.write((char*)(&PatientParams()), sizeof(PatientField));
    outFile.write((char*)(&StudyParams()), sizeof(StudyField));
    outFile.write((char*)(&SeriesParams()), sizeof(SeriesField));
    outFile.write((char*)(&ScanParams()), sizeof(ScanField));
    outFile.write((char*)(&ImageParams()), sizeof(ImageField));

    // write image data to the file
    outFile.write((char*)(m_pBuffer), fileHeader.DataMatrixSize);

    return true;
}

void CImage::ReadLocInfoFile(const std::string& strFilename, CSeries* pSeries)
{
	char sBuf[50], sKey[50];
    CFileFind FileFinder;
	BOOL bFileExist = FileFinder.FindFile( strFilename.c_str() );
	if ( !bFileExist ) return;

		
	// reference series info
	GetPrivateProfileString( "REF_SERIES_INFO", "SeriesIdInLocWin1", "0", sBuf, 255, strFilename.c_str() );
	pSeries->SeriesParams().RefSeries1 = atoi( sBuf );
	GetPrivateProfileString( "REF_SERIES_INFO", "SeriesIdInLocWin2", "0", sBuf, 255, strFilename.c_str() );
	pSeries->SeriesParams().RefSeries2 = atoi( sBuf );
	
	// FOV of setup series
	GetPrivateProfileString( "SERIES_FOV_INFO", "FovX", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().FovX = atoi( sBuf );
	GetPrivateProfileString( "SERIES_FOV_INFO", "FovY", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().FovY = atoi( sBuf );
	GetPrivateProfileString( "SERIES_FOV_INFO", "FovZ", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().FovZ = atoi( sBuf );
	
	// slice info of a cluster in setup series
	GetPrivateProfileString( "SLICE_INFO", "SlicesNum", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().ResolutionZ = atoi( sBuf );
	GetPrivateProfileString( "SLICE_INFO", "SliceThickness", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().SliceThickness = atof( sBuf );
	GetPrivateProfileString( "SLICE_INFO", "SliceGap", "0", sBuf, 255, strFilename.c_str() );
//	pSeries->SeriesParams().SliceGap = atoi( sBuf );
	
	// cluster info
	GetPrivateProfileString( "CLUSTER_INFO", "ClusterNum", "0", sBuf, 255, strFilename.c_str() );
	pSeries->m_ClusterSet.clear();
	int nClusterNum = atoi( sBuf );
	for ( int i=0; i< nClusterNum; i++ )
	{
		CCluster oCluster;
		double x,y,z;
		
		sprintf( sKey, "Center_Point_X_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		x = atof( sBuf );
		sprintf( sKey, "Center_Point_Y_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		y = atof( sBuf );
		sprintf( sKey, "Center_Point_Z_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		z = atof( sBuf );
		CThreeDim pCenter(x,y,z);
		oCluster.SetCenter( pCenter );
		
		sprintf( sKey, "READ_Dir_X_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		x = atof( sBuf );
		sprintf( sKey, "READ_Dir_Y_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		y = atof( sBuf );
		sprintf( sKey, "READ_Dir_Z_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		z = atof( sBuf );
		CThreeDim V0(x,y,z);
		oCluster.SetV0( V0 );
		
		sprintf( sKey, "PHASE_Dir_X_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		x = atof( sBuf );
		sprintf( sKey, "PHASE_Dir_Y_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		y = atof( sBuf );
		sprintf( sKey, "PHASE_Dir_Z_%d", i );
		GetPrivateProfileString( "CLUSTER_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		z = atof( sBuf );
		CThreeDim V1(x,y,z);
		oCluster.SetV1( V1 );
		
		pSeries->m_ClusterSet.push_back( oCluster );
	}
}

void CImage::ReadPosInfoFile(const std::string& strFilename, CSeries* pSeries)
{
	char sBuf[50], sKey[50];
    CFileFind FileFinder;
	BOOL bFileExist = FileFinder.FindFile( strFilename.c_str() );
	if ( !bFileExist ) return;
	
	// pos info of all slabs
	pSeries->vPosInfo.clear();
	GetPrivateProfileString( "POSITION_INFO", "ClusterNum", "0", sBuf, 255, strFilename.c_str() );
	int nClusterNum = atoi( sBuf );
	for ( int i=0; i< nClusterNum; i++ )
	{
		STRUCT_POSITION_INFO oPosInfo;
		
		// PLANE type
		sprintf( sKey, "PLANE_TYPE_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "3", sBuf, 255, strFilename.c_str() );
		oPosInfo.nPlaneType = atoi( sBuf );
		
		// center point OFFSET
		sprintf( sKey, "READ_OFFSET_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.ReadOffset = atof( sBuf );
		sprintf( sKey, "PHASE_OFFSET_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.PhaseOffset = atof( sBuf );
		sprintf( sKey, "SLICE_OFFSET_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.SliceOffset = atof( sBuf );
		
		// READ_Dir				 
		sprintf( sKey, "FREQ_DIR_X_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.FreqDirX = atof( sBuf );
		sprintf( sKey, "FREQ_DIR_Y_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.FreqDirY = atof( sBuf );
		sprintf( sKey, "FREQ_DIR_Z_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.FreqDirZ = atof( sBuf );
		
		// PHASE_Dir				 		
		sprintf( sKey, "PHASE_DIR_X_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.PhaseDirX = atof( sBuf );
		sprintf( sKey, "PHASE_DIR_Y_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.PhaseDirY = atof( sBuf );
		sprintf( sKey, "PHASE_DIR_Z_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.PhaseDirZ = atof( sBuf );
		
		// SLICE_Dir				 
		sprintf( sKey, "SLICE_DIR_X_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.SliceDirX = atof( sBuf );
		sprintf( sKey, "SLICE_DIR_Y_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.SliceDirY = atof( sBuf );
		sprintf( sKey, "SLICE_DIR_Z_%d", i );
		GetPrivateProfileString( "POSITION_INFO", sKey, "0.0", sBuf, 255, strFilename.c_str() );
		oPosInfo.SliceDirZ = atof( sBuf );
		
		pSeries->vPosInfo.push_back( oPosInfo );
	}
}

bool CImage::ReadImageFileHeader( std::ifstream& inFile, CBIImageHeader& imageHeader )
{
	int nn = sizeof(imageHeader.seriesField);

	// read whole header
	inFile.seekg( 0, std::ios::seekdir::beg);
    inFile.read((char*)(&imageHeader.headInfo), sizeof(imageHeader.headInfo));
    inFile.read((char*)(&imageHeader.siteField), sizeof(imageHeader.siteField));
    inFile.read((char*)(&imageHeader.patientField), sizeof(imageHeader.patientField));
    inFile.read((char*)(&imageHeader.studyField), sizeof(imageHeader.studyField));

	//
	LONG nHeahAddr, nGapAddr, nOffsetAddr;
	CString sHeadAddr, sGapAddr;
	sHeadAddr.Format( "%ld", &imageHeader.seriesField );
	nHeahAddr = atoi( sHeadAddr );

	sGapAddr.Format( "%ld", &imageHeader.seriesField.SliceGap );
	nGapAddr = atoi( sGapAddr );
	nOffsetAddr = nGapAddr - nHeahAddr;

    inFile.read( (char*)(&imageHeader.seriesField), nOffsetAddr );
	
	// read SliceGap by image's Version {BEGIN}
	int nGapLen = 0;
	if ( imageHeader.headInfo.Version == (int(1) << 16 + 0) )
	{
		U2 SliceGap;
		inFile.read((char*)(&SliceGap), sizeof(U2));
		imageHeader.seriesField.SliceGap = SliceGap;
		nGapLen = sizeof(U2);
	}
	else if ( imageHeader.headInfo.Version >= (int(1) << 16 + 1) )
	{
		F4 SliceGap;
		inFile.read((char*)(&SliceGap), sizeof(F4));
		imageHeader.seriesField.SliceGap = SliceGap;
		nGapLen = sizeof(F4);
	}
	else
	{
		AfxMessageBox( "Unknown image version !" );
		return false;
	}
	// read SliceGap by image's Version {END}
	
	if ( imageHeader.headInfo.Version == (int(1) << 16 + 0) )
	{
		inFile.seekg( 2, std::ios::seekdir::cur );
	}
	
    inFile.read( (char*)(&imageHeader.seriesField.EchoTime), 
		  sizeof(imageHeader.seriesField) - nOffsetAddr - 1/* - nGapLen*/ 
		+ sizeof(imageHeader.scanField)
		+ sizeof(imageHeader.imageField) );

	/** [zhlxu 2008.2.3] [] 解决在添加DefaultSliceOrder选项功能后软件的向前兼容问题 **/
	if ( imageHeader.headInfo.Version < (int(1) << 16 + 2) )
	{
		imageHeader.seriesField.bDefaultSliceOrder = true;
	}
	else if ( imageHeader.headInfo.Version >= (int(1) << 16 + 2) )
	{
		if ( imageHeader.seriesField.SliceGap < 0.0 )
		{
			imageHeader.seriesField.bDefaultSliceOrder = false;
		}
		else
		{
			imageHeader.seriesField.bDefaultSliceOrder = true;
		}
	}
	/** [zhlxu 2008.2.3] **/
	
	return true;
}

/*!
    This function read an image file and stores the image header in the output
    parameter imageHeader, and allocate a buffer for the image data and then 
    returns the pointer to the buffer. The size of buffer be calculated from 
    the imageHeader.
    \param strFilename File name of the image file to read.
    \param imageHeader Image heade structure used to store the image header
    information.
    \return Pointer to the buffer used to store the image data. This buffer is 
    allocated by this function and should be released by the caller once it
    finishes with the buffer. \a NULL if fails to open the file.
*/
short* CImage::ReadImageFile(const std::string& strFilename, 
                             CBIImageHeader& imageHeader)
{	
	std::ifstream inFile(strFilename.c_str(), std::ios::in | std::ios::binary);	
    if (!inFile)
	{
        return NULL;
	}
    
	// {xuzhl,2005.12.09} read image's header
	ReadImageFileHeader( inFile, imageHeader );	
//    inFile.read((char*)(&imageHeader), sizeof(CBIImageHeader));

    // an image file should store valid resolution values in it.    
    int nNumOfPoints = 
        imageHeader.seriesField.ResolutionX * imageHeader.seriesField.ResolutionY;
    short* pBuffer = NULL;
    try
    {
        pBuffer = new short[nNumOfPoints];
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

	inFile.seekg( -sizeof(short) * nNumOfPoints, std::ios::seekdir::end );
	long nPos = inFile.tellg();
	inFile.read( (char*)(pBuffer), sizeof(short) * nNumOfPoints );    
    
    if ( inFile.gcount() < sizeof(short) * nNumOfPoints)
    {
        // not enough data has been read
        // release the buffer and return NULL to indicate error.
        delete []pBuffer;
		inFile.close();
        return NULL;
    }

	inFile.close();
	return (pBuffer);
}

//! Read in image data from a binary file that contains only image data.
short* CImage::ReadThirdPartyImageFile(const std::string& strFilename,
								int nResolutionX, 
								int nResolutionY, 
								int nResolutionZ,
								int nOffset)
{
    std::ifstream inFile(strFilename.c_str(), 
        std::ios::in | std::ios::binary);

    if (!inFile)
        return NULL;


    int nNumOfPoints = nResolutionX * nResolutionY * nResolutionZ;

    // an image file should store valid resolution values in it.
    ASSERT(nNumOfPoints > 0);
    
    short* pBuffer = NULL;
    try
    {
        pBuffer = new short[nNumOfPoints];
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

	inFile.seekg(nOffset, std::ios::seekdir::beg);
    inFile.read((char*)(pBuffer), 
        sizeof(short) * nNumOfPoints);    
    
    if ( inFile.gcount() < sizeof(short) * nNumOfPoints)
    {

        // not enough data has been read
        // release the buffer and return NULL to indicate error.
        delete []pBuffer;
        return NULL;
    }
    else
        return (pBuffer);

}

/*!
    This function determines the offsets of the image in three directions (AP, 
    LR, SI) and fills the corresponding fields in the ImageFields.
*/
Geometry::CThreeDim CImage::CalculateHBCOffset()
{
    Geometry::CThreeDim offset = GetHBCOffset(SeriesParams().ResolutionX /2, 
        SeriesParams().ResolutionY / 2 );
    ImageParams().OffsetAP = offset.x;
    ImageParams().OffsetLR = offset.y;
    ImageParams().OffsetSI = offset.z;

    return offset;
}

Geometry::CThreeDim CImage::CalculateHBCOffsetForAnnotation()
{
    Geometry::CThreeDim offset = GetHBCOffsetForAnntation(SeriesParams().ResolutionX /2, 
        SeriesParams().ResolutionY / 2 );	
    return offset;
}

/*!
	This function calculates the offset of a given voxel in the human body 
	coordinates.
	\param x X coordinate of the voxel in the voxel coordinates.
	\param y Y coordinate of the voxel in the voxel coordinates.
	\return Offset in three directions of the human body coordinates. \a x 
	stands for offset in AP direction, \a y stands for offset in LR direction, 
	and \a z stands for offset in SI direction. Note these three directions 
	forms a right-hand Cartesian system of coordinates.
*/

// {ZLX,2005.08.24} add this function for annotation of image
Geometry::CThreeDim CImage::GetHBCOffsetForAnntation(int x, int y)
{
    // Calculate the offset of the point in scan coordinates whose bases are
    // ReadDir, PhaseDir, and SliceDir.
	float nPointReadOffset, nPointPhaseOffset, nPointSliceOffset;
	float FreqDirX, FreqDirY, FreqDirZ, PhaseDirX, PhaseDirY, PhaseDirZ, SliceDirX, SliceDirY, SliceDirZ;
	
	int nClusterIndex = ImageParams().Id / m_pScan->GetSeries()->SeriesParams().ResolutionZ;
	if ( m_pScan->GetSeries()->vPosInfo.size() > 0 
		&& (nClusterIndex >=0 && nClusterIndex < m_pScan->GetSeries()->vPosInfo.size()) )
	{
		// according to saved pos info read from pos.txt file
		nPointReadOffset  = m_pScan->GetSeries()->vPosInfo[nClusterIndex].ReadOffset;		
		nPointPhaseOffset = m_pScan->GetSeries()->vPosInfo[nClusterIndex].PhaseOffset;
		
//		float fff = m_pScan->GetSeries()->vPosInfo[nClusterIndex].SliceOffset;
		int nImageId_1;
		if ( nClusterIndex == 0 )
		{
			nImageId_1 = ImageParams().Id;
		} 
		else
		{
			nImageId_1 = ImageParams().Id - m_pScan->GetSeries()->SeriesParams().ResolutionZ * nClusterIndex;
		}
		nPointSliceOffset =  m_pScan->GetSeries()->vPosInfo[nClusterIndex].SliceOffset + 
			((float)SeriesParams().SliceGap + SeriesParams().SliceThickness) * 
			(-(float)(SeriesParams().ResolutionZ - 1)/ 2.0 + (float)nImageId_1);

		FreqDirX = m_pScan->GetSeries()->vPosInfo[nClusterIndex].FreqDirX; 
		FreqDirY = m_pScan->GetSeries()->vPosInfo[nClusterIndex].FreqDirY;
		FreqDirZ = m_pScan->GetSeries()->vPosInfo[nClusterIndex].FreqDirZ;

		PhaseDirX = m_pScan->GetSeries()->vPosInfo[nClusterIndex].PhaseDirX; 
		PhaseDirY = m_pScan->GetSeries()->vPosInfo[nClusterIndex].PhaseDirY; 
		PhaseDirZ = m_pScan->GetSeries()->vPosInfo[nClusterIndex].PhaseDirZ; 

		SliceDirX = m_pScan->GetSeries()->vPosInfo[nClusterIndex].SliceDirX; 
		SliceDirY = m_pScan->GetSeries()->vPosInfo[nClusterIndex].SliceDirY; 
		SliceDirZ = m_pScan->GetSeries()->vPosInfo[nClusterIndex].SliceDirZ; 
	}
	else
	{
		// according to default pos info in scan object read from image file
		nPointReadOffset  = ScanParams().ReadOffset;
		nPointPhaseOffset = ScanParams().PhaseOffset;
		nPointSliceOffset = ScanParams().SliceOffset + 
			((float)SeriesParams().SliceGap + SeriesParams().SliceThickness) * 
			(-(float)(SeriesParams().ResolutionZ - 1)/ 2.0 + (float)ImageParams().Id);		

		FreqDirX = ScanParams().FreqDirX; 
		FreqDirY = ScanParams().FreqDirY;
		FreqDirZ = ScanParams().FreqDirZ;

		PhaseDirX = ScanParams().PhaseDirX; 
		PhaseDirY = ScanParams().PhaseDirY; 
		PhaseDirZ = ScanParams().PhaseDirZ; 

		SliceDirX = ScanParams().SliceDirX; 
		SliceDirY = ScanParams().SliceDirY; 
		SliceDirZ = ScanParams().SliceDirZ; 
	}

    // Calculate the human body coordinates bases (in physical coordinates).
    Geometry::CThreeDim vA, vL, vS;

    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdAnterior), vA);
    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdLeft), vL);
    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdSuperior), vS);

    // Map the offset to human body coordinates.
    Geometry::CThreeDim offset;
    // note: vA, vL, vS are all unit vectors.
    offset.x = (FreqDirX * vA.x + 
                FreqDirY * vA.y + 
                FreqDirZ * vA.z) * nPointReadOffset +
               (PhaseDirX * vA.x + 
                PhaseDirY * vA.y +
                PhaseDirZ * vA.z) * nPointPhaseOffset +
               (SliceDirX * vA.x + 
                SliceDirY * vA.y +
                SliceDirZ * vA.z ) * nPointSliceOffset;

    offset.y = (FreqDirX * vL.x + 
                FreqDirY * vL.y + 
                FreqDirZ * vL.z) * nPointReadOffset +
               (PhaseDirX * vL.x + 
                PhaseDirY * vL.y +
                PhaseDirZ * vL.z) * nPointPhaseOffset +
               (SliceDirX * vL.x + 
                SliceDirY * vL.y +
                SliceDirZ * vL.z ) * nPointSliceOffset;

    offset.z = (FreqDirX * vS.x + 
                FreqDirY * vS.y + 
                FreqDirZ * vS.z) * nPointReadOffset +
               (PhaseDirX * vS.x + 
                PhaseDirY * vS.y +
                PhaseDirZ * vS.z) * nPointPhaseOffset +
               (SliceDirX * vS.x + 
                SliceDirY * vS.y +
                SliceDirZ * vS.z ) * nPointSliceOffset;

	return offset;
}

int CImage::GetPlaneTypeForAnnotation()
{
	int nPlaneType;
	int nClusterIndex = ImageParams().Id / m_pScan->GetSeries()->SeriesParams().ResolutionZ;
	if ( m_pScan->GetSeries()->vPosInfo.size() > 0 
		&& (nClusterIndex >=0 && nClusterIndex < m_pScan->GetSeries()->vPosInfo.size()) )
	{
		// according to saved pos info read from pos.txt file
		nPlaneType  = m_pScan->GetSeries()->vPosInfo[nClusterIndex].nPlaneType;		
	}
	else
	{
		// according to default pos info in scan object read from image file
		nPlaneType  = SeriesParams().Plane;
	}
	return nPlaneType;
}

Geometry::CThreeDim CImage::GetHBCOffset(int x, int y)
{
    // Calculate the offset of the point in scan coordinates whose bases are
    // ReadDir, PhaseDir, and SliceDir.

	// {ZLX,2005.08.24}

/*
    int nPointReadOffset = (x - (SeriesParams().ResolutionX - 1) / 2.0) * 
        GetFOVX() / SeriesParams().ResolutionX + ScanParams().ReadOffset;

    int nPointPhaseOffset = (y - (SeriesParams().ResolutionY - 1) / 2.0) * 
        GetFOVY() / SeriesParams().ResolutionY + ScanParams().PhaseOffset;

    int nPointSliceOffset =  ScanParams().SliceOffset + 
        (SeriesParams().SliceGap + SeriesParams().SliceThickness) * 
        (-(SeriesParams().ResolutionZ - 1)/ 2.0 + ImageParams().Id);
*/

    float nPointReadOffset = ((float)x - (float)(SeriesParams().ResolutionX - 1) / 2.0) * 
        (float)GetFOVX() / (float)SeriesParams().ResolutionX + ScanParams().ReadOffset;

    float nPointPhaseOffset = ((float)y - (float)(SeriesParams().ResolutionY - 1) / 2.0) * 
        (float)GetFOVY() / (float)SeriesParams().ResolutionY + ScanParams().PhaseOffset;

    float nPointSliceOffset =  ScanParams().SliceOffset + 
        ((float)SeriesParams().SliceGap + SeriesParams().SliceThickness) * 
        (-(float)(SeriesParams().ResolutionZ - 1)/ 2.0 + (float)ImageParams().Id);
		

    // Calculate the human body coordinates bases (in physical coordinates).
    Geometry::CThreeDim vA, vL, vS;

    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdAnterior), vA);
    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdLeft), vL);
    CDirectionCalculator::GetHandle().GetPhysicalDirection(
        static_cast<EBodyPosition>(StudyParams().PatPosition), 
        static_cast<EBodyEntry>(StudyParams().PatEntry), 
        static_cast<EHumanBodyDirection>(hbdSuperior), vS);

    // Map the offset to human body coordinates.
    Geometry::CThreeDim offset;
    // note: vA, vL, vS are all unit vectors.
    offset.x = (ScanParams().FreqDirX * vA.x + 
                ScanParams().FreqDirY * vA.y + 
                ScanParams().FreqDirZ * vA.z) * nPointReadOffset +
               (ScanParams().PhaseDirX * vA.x + 
                ScanParams().PhaseDirY * vA.y +
                ScanParams().PhaseDirZ * vA.z) * nPointPhaseOffset +
               (ScanParams().SliceDirX * vA.x + 
                ScanParams().SliceDirY * vA.y +
                ScanParams().SliceDirZ * vA.z ) * nPointSliceOffset;

    offset.y = (ScanParams().FreqDirX * vL.x + 
                ScanParams().FreqDirY * vL.y + 
                ScanParams().FreqDirZ * vL.z) * nPointReadOffset +
               (ScanParams().PhaseDirX * vL.x + 
                ScanParams().PhaseDirY * vL.y +
                ScanParams().PhaseDirZ * vL.z) * nPointPhaseOffset +
               (ScanParams().SliceDirX * vL.x + 
                ScanParams().SliceDirY * vL.y +
                ScanParams().SliceDirZ * vL.z ) * nPointSliceOffset;

    offset.z = (ScanParams().FreqDirX * vS.x + 
                ScanParams().FreqDirY * vS.y + 
                ScanParams().FreqDirZ * vS.z) * nPointReadOffset +
               (ScanParams().PhaseDirX * vS.x + 
                ScanParams().PhaseDirY * vS.y +
                ScanParams().PhaseDirZ * vS.z) * nPointPhaseOffset +
               (ScanParams().SliceDirX * vS.x + 
                ScanParams().SliceDirY * vS.y +
                ScanParams().SliceDirZ * vS.z ) * nPointSliceOffset;

	return offset;
}

// by Rodger, 2005.02.23
void SetCurrentDateTime(BIDateTime& dt)
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	dt.year		= (unsigned short) sysTime.wYear;
	dt.month	= (char) sysTime.wMonth;
	dt.day		= (char) sysTime.wDay;
	dt.hour		= (char) sysTime.wHour;
	dt.minute	= (char) sysTime.wMinute;
	dt.second	= (char) sysTime.wSecond;
}

bool CImage::ReadFileHeader(CString csFileName, CBIImageHeader &imageHeader)
{
    CFile file;
	if (!file.Open(csFileName,CFile::modeRead))
	{
		return false;
	}
	file.Read((void*)&imageHeader,sizeof(CBIImageHeader));
	file.Close();
	return true;
}
