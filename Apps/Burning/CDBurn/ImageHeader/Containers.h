// Containers.h
//
#ifndef __CONTAINERS_H__
#define __CONTAINERS_H__

#pragma warning (disable:4786)

#include <vector>
class CSeries;
class CStudy;
class CScan;
class CImage;

typedef std::vector<CStudy*> CStudyContainer;
typedef CStudyContainer::iterator CStudyIter;
typedef CStudyContainer::const_iterator CStudyConstIter;

typedef std::vector<const CStudy*> CConstStudyContainer;
typedef CConstStudyContainer::iterator CConstStudyIter;

typedef std::vector<CSeries*> CSeriesContainer;
typedef CSeriesContainer::iterator CSeriesIter;
typedef CSeriesContainer::const_iterator CSeriesConstIter;

typedef std::vector<CScan*> CScanContainer;
typedef CScanContainer::iterator CScanIter;
typedef CScanContainer::const_iterator CScanConstIter;

typedef std::vector<CImage*> CImageContainer;
typedef CImageContainer::iterator CImageIter;
typedef CImageContainer::const_iterator CImageConstIter;

#endif // __CONTAINERS_H__
