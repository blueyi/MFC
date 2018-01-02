/******************************************************************************
*
* DirectSoundErr.cpp : This class gives a static method related to the differents
*						error messages returned by different DirectSound methods. 
*
*/

#include "DirectSoundErr.h"
#include "dsound.h"

CComBSTR DirectSoundErr::GetErrDesc(HRESULT hres)
	{
	switch(hres)
		{
		case DSERR_ALLOCATED : 
				return _T("The request failed because resources, such as a priority level, were already in use by another caller.");				
		case DSERR_ALREADYINITIALIZED : 
				return _T("The object is already initialized.");				
		case DSERR_BADFORMAT :
				return _T("The specified wave format is not supported.");				
		case DSERR_BUFFERLOST :
				return _T("The buffer memory has been lost and must be restored.");				
		case DSERR_CONTROLUNAVAIL :
				return _T("The buffer control (volume, pan, and so on) requested by the caller is not available. Controls must be specified when the buffer is created, using the dwFlags member of DSBUFFERDESC.");				
		case DSERR_GENERIC :
				return _T("An undetermined error occurred inside the DirectSound subsystem.");
				
		case DSERR_INVALIDCALL :
				return _T("This function is not valid for the current state of this object.");
			
		case DSERR_INVALIDPARAM :
				return _T("An invalid parameter was passed to the returning function.");
			
		case DSERR_NOAGGREGATION :
				return _T("The object does not support aggregation.");
					
		case DSERR_NODRIVER :
				return _T("No sound driver is available for use, or the given GUID is not a valid DirectSound device ID.");
			
		case DSERR_NOINTERFACE :
				return _T("The requested COM interface is not available.");
			
		case DSERR_OTHERAPPHASPRIO :
				return _T("Another application has a higher priority level, preventing this call from succeeding.");
			
		case DSERR_OUTOFMEMORY :
				return _T("The DirectSound subsystem could not allocate sufficient memory to complete the caller's request.");
			
		case DSERR_PRIOLEVELNEEDED :
				return _T("A cooperative level of DSSCL_PRIORITY or higher is required.");
			
		case DSERR_UNINITIALIZED :
				return _T("The IDirectSound8::Initialize method has not been called or has not been called successfully before other methods were called.");
			
		case DSERR_UNSUPPORTED :
				return _T("The function called is not supported at this time.");
			
		default : return _T("Unknown error");
		}
	}

