// GLInterface.h: interface for the CGLInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLINTERFACE_H__F364B9EA_20B9_49C0_8DD0_18C5231A331A__INCLUDED_)
#define AFX_GLINTERFACE_H__F364B9EA_20B9_49C0_8DD0_18C5231A331A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GfxInterface.h"

namespace gfxinterface
{
class CGLInterface : public CGfxInterface  
{
public:
	CGLInterface();
	virtual ~CGLInterface();

};

}
#endif // !defined(AFX_GLINTERFACE_H__F364B9EA_20B9_49C0_8DD0_18C5231A331A__INCLUDED_)
