/******************************************************************************
*
* DirectSoundErr.h : This class gives a static method related to the differents
*						error messages returned by different DirectSound methods. 
*
*/

#include <windows.h>
#include <atlbase.h>


class DirectSoundErr
{
	
public:
	
	static CComBSTR GetErrDesc(HRESULT hres);

};