// Image.h : CImage Wraps an MRI image, including parameters and data.
//
#if !defined(AFX_IMAGE_H__47D279CF_B4C9_412B_B40A_ED2F43A67E53__INCLUDED_)
#define AFX_IMAGE_H__47D279CF_B4C9_412B_B40A_ED2F43A67E53__INCLUDED_


#include "../BIGlobals/BI_ImageHeader.h"
#include "scan.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif


class CLASS_DECL_IMAGEHEADER CImage  
{
public:
	CImage(CScan* pScan, int nID = -1);
	virtual ~CImage();

// Parameter Field Access Function
public:
	BOOL GetImageHeader(const std::string& strFilename,CBIImageHeader& imageHeader)
	{
		//这个逻辑是对的
		short*pData=ReadImageFile( strFilename,imageHeader);
		if(!pData)
		{
			return FALSE;
		}
		imageHeader.imageField=this->ImageParams();
		imageHeader.patientField=this->PatientParams();
		imageHeader.scanField=this->ScanParams();
		imageHeader.seriesField=this->SeriesParams();
		imageHeader.siteField=this->SiteParams();
		imageHeader.studyField=this->StudyParams();
		return TRUE;
		//m_sImageHeader.headInfo=
		
	}
	const ImageField& ImageParams() const { return m_ImageParams; }
    ImageField& ImageParams() { return m_ImageParams; }

	const ScanField& ScanParams() const { return m_pScan->ScanParams(); }
    ScanField& ScanParams() { return m_pScan->ScanParams(); }

	const SeriesField& SeriesParams() const { return m_pScan->SeriesParams(); }
    SeriesField& SeriesParams() { return m_pScan->SeriesParams(); }

	const StudyField& StudyParams() const { return m_pScan->StudyParams(); }
    StudyField& StudyParams() { return m_pScan->StudyParams(); }

	const PatientField& PatientParams() const { return m_pScan->PatientParams(); }
    PatientField& PatientParams() { return m_pScan->PatientParams(); }

	const SiteField& SiteParams() const { return m_pScan->SiteParams(); }
    SiteField& SiteParams() { return m_pScan->SiteParams(); }	

public:
	CBIImageHeader m_sImageHeader;
	// unsigned int* GetRawImageData(); // Returns pointer to the buffer holding raw image data. 

	//Added by Tom, --2008.07.10
	// image size in voxel
	int GetWidth() const 
	{ 
		int nW ;
		nW = m_sImageHeader.seriesField.ResolutionX ;
		if (nW > 0)
		{
			return nW ;
		}
		else
		{
			return SeriesParams().ResolutionX; 
		}
	};
	int GetHeight() const 
	{
		int nH ;
		nH = m_sImageHeader.seriesField.ResolutionY ;
		if (nH > 0)
		{
			return nH ;
		}
		else
		{
			return SeriesParams().ResolutionY; 
		}
	};

	// data buffer
	const short* GetBuffer() const { return m_pBuffer; }
	short* GetBuffer() { return m_pBuffer; }
    void SetBuffer(short* pBuffer) { m_pBuffer = pBuffer; }

	//Added by jhzhang 2004/09/03
	//! Get the pointer to the image data filter buffer.
	short* GetFilterBuffer()
	{
		return m_pFilterBuffer;
	}
    void SetFilterBuffer(short* pFilterBuffer)
    {
        m_pFilterBuffer = pFilterBuffer;
    }

	//! Returns the FovX of the image.
    /*!
        \note This function returns the FOV that is effective in the displayed
        image, not the FOV in scan setup.
    */
	int GetFOVX() const
	{
		//Modified by Tom, --2008.07.10
		return (int)(SeriesParams().ResolutionX * 
                     max(SeriesParams().FovX / static_cast<float>(SeriesParams().ResolutionX),
                     SeriesParams().FovY / static_cast<float>(SeriesParams().ResolutionY)));
            
	}
	//! Returns the FovY of the image.
    /*!
        \note This function returns the FOV that is effective in the displayed
        image, not the FOV in scan setup.
    */
	int GetFOVY() const
	{
		//Modified by Tom, --2008.07.10
		return (int)(SeriesParams().ResolutionY * 
                     max(SeriesParams().FovX / static_cast<float>(SeriesParams().ResolutionX),
                     SeriesParams().FovY / static_cast<float>(SeriesParams().ResolutionY)));
	}

	CSize GetSize() const { return CSize(GetWidth(), GetHeight()); }

	//Added by Sun Shang for database function at 2002/09/19
	//! Set or Get the saved to record number.
	inline long& GetSavedRecordNum()
	{
		return m_lUniqueRecNoSaveed;
	}

    bool SaveToFile(const std::string& strFilename);
    
    static short* ReadImageFile(const std::string& strFilename, 
        CBIImageHeader& imageHeader);
	// {xuzhl,2005.12.09} read image header by image's version
	static bool ReadImageFileHeader( std::ifstream& inFile, CBIImageHeader& imageHeader );

    static void ReadLocInfoFile(const std::string& strFilename, 
        CSeries* pSeries);
	static void ReadPosInfoFile(const std::string& strFilename, CSeries* pSeries);
	
	//! Read in image data from a binary file that contains only image data.
	static short* ReadThirdPartyImageFile(const std::string& strFilename,
		int nResolutionX, int nResolutionY, int nResolutionZ, int nOffset = 0);

    CScan* GetScan(){return m_pScan;}

    void SetRawData(float* pRawData, bool bOwnRawData) { m_pRawData = pRawData; m_bOwnRawData = bOwnRawData; }
    float* GetRawData() { return m_pRawData; }

public:
	BOOL m_bImageWndSel;
	bool ReadFileHeader(CString csFileName, CBIImageHeader &imageHeader);
    bool CalculateOffsets(); // calculate offset of the images.
    Geometry::CThreeDim CalculateHBCOffset(); // Calculates offsets of the image in human body coordinates.
	Geometry::CThreeDim CalculateHBCOffsetForAnnotation();
	Geometry::CThreeDim GetHBCOffset(int x, int y); // Calculates offset in human body coordinates of a given voxel in the image.
	Geometry::CThreeDim GetHBCOffsetForAnntation(int x, int y);
	int GetPlaneTypeForAnnotation();

protected:
	ImageField	m_ImageParams;	//!< Parameters specific to the image.
	CScan*		m_pScan;		//!< Pointer to the hosting scan.
	short*      m_pBuffer;	    //!< Pointer to the image data.

//This is added by jhzhang 2004/09/03 put filter data
	short*		m_pFilterBuffer; //!< Pointer to the filter image data. 

    float*      m_pRawData;     //!< Pointer to the raw data.
    bool        m_bOwnRawData;  //!< Should we delete the raw data in destructor?
	//Added by Sun Shang for database function at 2002/09/19
	long		m_lUniqueRecNoSaveed;//!< If the image be saved then set to record number.
	
	//End.

};

// by Rodger, 2005.02.23
void CLASS_DECL_IMAGEHEADER SetCurrentDateTime(BIDateTime& dt);

#endif // !defined(AFX_IMAGE_H__47D279CF_B4C9_412B_B40A_ED2F43A67E53__INCLUDED_)
