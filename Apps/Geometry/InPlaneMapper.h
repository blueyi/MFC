// InPlaneMapper.h: interface for the CInPlaneMapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPLANEMAPPER_H__0BE9B1FE_D321_442C_8C12_347E3CE7F724__INCLUDED_)
#define AFX_INPLANEMAPPER_H__0BE9B1FE_D321_442C_8C12_347E3CE7F724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

namespace Geometry
{

class CPoint2D;

class CLASS_DECL_GEOMETRY CInPlaneMapper  
{
public:
	CInPlaneMapper();
	virtual ~CInPlaneMapper();

	/*!
		This function is used to update the parameters of Coordinate System
		Converter(CSC). After invoking this function, all parameters of CSC
		will be updated. Then we can transform all the coordinate from the 
		first coordinate system from the second one.
		\bug What's the meaning of these parameters?
	*/
	void Update(const CPoint2D& ptROI1, 
				const CPoint2D& ptPhysical1,
				 const CPoint2D& ptROI2, 
				 const CPoint2D& ptPhysical2,
				 const CPoint2D& ptROI3, 
				 const CPoint2D& ptPhysical3);
void Update(const CPoint2D& ptOrg, const CPoint2D& ptX, const CPoint2D& ptY);
void Update(const CPoint2D& ptOrg, double dAngleInArc);
	//! Transform the ROI coordinate to Physical coordinate.
	CPoint2D ROIToPhysical(const CPoint2D& ptROI) const;

	//! Transform the Physical coordinate to ROI coordinate.
	CPoint2D PhysicalToROI(const CPoint2D& ptPhysical) const;

protected:
	//! \name Variables used in coordinates conversion
	//@{
	double m_dA1RP, m_dB1RP, m_dC1RP;
	double m_dA2RP, m_dB2RP, m_dC2RP;
	double m_dA1PR, m_dB1PR, m_dC1PR;
	double m_dA2PR, m_dB2PR, m_dC2PR;
	//@}

	/*!
		This is a flag to indicate the state of CSC.
		\a true means the parameters of CSC are enabled, and the process of
		coordinate conversion can be executed.
		\a false means the parameters of CSC are disabled, and the process of
		coordinate conversion is prohibited.
	*/
	bool m_bUpdated;
};

}

#endif // !defined(AFX_INPLANEMAPPER_H__0BE9B1FE_D321_442C_8C12_347E3CE7F724__INCLUDED_)
