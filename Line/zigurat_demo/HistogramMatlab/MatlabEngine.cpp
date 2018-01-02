// MatlabEngine.cpp: implementation of the CMatlabEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MatlabEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMatlabEngine::CMatlabEngine()
: m_bInitialized(false), m_sWorkspace(_T("base"))
{
#ifndef _UNICODE
	m_pBuffer=new WCHAR[1024];
	m_uBufferSize=1024;
#endif

	m_dpNoArgs.cArgs=0;
	m_dpNoArgs.cNamedArgs=0;
	m_dpNoArgs.rgdispidNamedArgs=NULL;
	m_dpNoArgs.rgvarg=NULL;

	// Get the Class Identifier for Matlab Application Object,
	// which is a globally unique identifier (GUID)
	OLECHAR FAR* szFunction;

	CLSID clsid;
	::CLSIDFromProgID(OLESTR("Matlab.Application"), &clsid);
	
	
	// Create an instance of the Matlab application and obtain the pointer
	// to the application's IUnknown interface
	
	IUnknown* pUnk;
	m_hr = ::CoCreateInstance(clsid, NULL, CLSCTX_SERVER,IID_IUnknown,(void**) &pUnk);
	if (FAILED(m_hr))
		return;

	// Query IUnknown to retrieve a pointer to the application IDispatch
	// interface
	m_hr = pUnk ->QueryInterface(IID_IDispatch, (void**)&m_pMtlbDispApp);
	if (FAILED(m_hr))
		return;

	// Get the Dispatch Identifiers
	szFunction = OLESTR("GetFullMatrix");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_GetFullMatrix);
	if (FAILED(m_hr))
		return;
	
	
	szFunction = OLESTR("PutFullMatrix");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_PutFullMatrix);
	if (FAILED(m_hr))
		return;
	
	
	szFunction = OLESTR("Execute");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_Execute);
	if (FAILED(m_hr))
		return;

	
	szFunction = OLESTR("MinimizeCommandWindow");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_MinimizeCommandWindow);
	if (FAILED(m_hr))
		return;

	szFunction = OLESTR("MaximizeCommandWindow");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_MaximizeCommandWindow);
	if (FAILED(m_hr))
		return;
	
	szFunction = OLESTR("GetCharArray");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_GetCharArray);
	if (FAILED(m_hr))
		return;
	
	szFunction = OLESTR("PutCharArray");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_PutCharArray);
	if (FAILED(m_hr))
		return;
	
	szFunction = OLESTR("Visible");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_Visible);
	if (FAILED(m_hr))
		return;

	szFunction = OLESTR("Quit");
	m_hr = m_pMtlbDispApp ->GetIDsOfNames(IID_NULL, &szFunction, 1, LOCALE_USER_DEFAULT, &m_dispid_Quit);
	if (FAILED(m_hr))
		return;

	m_bInitialized = true;
}

CMatlabEngine::~CMatlabEngine()
{
	if (m_pMtlbDispApp)
		m_pMtlbDispApp->Release();

#ifndef _UNICODE
	if (m_pBuffer)
		delete[] m_pBuffer;
#endif
}


void CMatlabEngine::ErrHandler(HRESULT hr, EXCEPINFO excep, UINT uArgErr)
{
  if (hr == DISP_E_EXCEPTION)
  {
    TCHAR errDesc[512];
    TCHAR errMsg[512];
    ::_tprintf(errMsg, TEXT("Run-time error %d:\n\n %s"),
            excep.scode & 0x0000FFFF,  //Lower 16-bits of SCODE
            errDesc);                  //Text error description
    ::MessageBox(NULL, errMsg, TEXT("Automation Server Error"),
                MB_SETFOREGROUND | MB_OK);
  }
  else
  {
    LPVOID lpMsgBuf;
    ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hr,
                    MAKELANGID(LANG_NEUTRAL,
                    SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,
                    0, NULL);
    if ((hr == DISP_E_TYPEMISMATCH ) ||
        (hr == DISP_E_PARAMNOTFOUND))
    {
      TCHAR extMess[512];
      ::_tprintf(extMess, TEXT("%s Position of incorrect argument is %u.\n"), (LPCTSTR) lpMsgBuf, uArgErr);
      ::MessageBox(NULL, extMess, TEXT("COM Error"), MB_OK | MB_SETFOREGROUND);
    }
    else
    {
      ::MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("COM Error"),MB_OK | MB_SETFOREGROUND);
    }
    ::LocalFree(lpMsgBuf);
  }
}

HRESULT CMatlabEngine::Execute(LPCTSTR szCode)
{
	VARIANT vArgsTypeText[1];
	DISPPARAMS dpTypeText;
	BSTR bstrName=NULL;

	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	ProcessString(szCode, bstrName);
	
	vArgsTypeText [0].vt = VT_BSTR;
	vArgsTypeText [0].bstrVal = bstrName;	
	
	dpTypeText.cArgs = 1;
	dpTypeText.cNamedArgs = 0;
	dpTypeText.rgvarg = vArgsTypeText;
		
	m_hr = m_pMtlbDispApp ->Invoke(m_dispid_Execute, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dpTypeText, &m_vResult, &m_excep, &m_uArgErr);

	if (FAILED(m_hr))
		goto Exit;

// Cleaning memory...		
Exit:
	if (bstrName)
	::SysFreeString(bstrName);

	return m_hr;
}

HRESULT CMatlabEngine::Show(bool bShow)
{
	VARIANT vArgsTypeLong[1];

	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	::VariantInit(vArgsTypeLong);
	
	vArgsTypeLong[0].vt = VT_I4;
	vArgsTypeLong[0].lVal = (bShow) ? 1 : 0; // Visible = 1; Invisible = 0
	
	DISPID dispidNamed = DISPID_PROPERTYPUT;
		
	DISPPARAMS dpVisible;
	dpVisible.cArgs = 1;
	dpVisible.cNamedArgs = 1;
	dpVisible.rgvarg = vArgsTypeLong;
	dpVisible.rgdispidNamedArgs = &dispidNamed;
		
	return m_hr = m_pMtlbDispApp ->Invoke(m_dispid_Visible, IID_NULL,LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &dpVisible, NULL, &m_excep, &m_uArgErr);
}

void CMatlabEngine::GetLastErrorMessage() const
{
	if(FAILED(m_hr))
		ErrHandler(m_hr, m_excep, m_uArgErr);
}

bool CMatlabEngine::IsVisible()
{
	VARIANT vArgsTypeLong[1];
	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	::VariantInit(vArgsTypeLong);
	
	vArgsTypeLong[0].vt = VT_I4;
	vArgsTypeLong[0].lVal = 0; // Visible = 1; Invisible = 0
	
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	
	DISPPARAMS dpVisible;
	dpVisible.cArgs = 1;
	dpVisible.cNamedArgs = 1;
	dpVisible.rgvarg = vArgsTypeLong;
	dpVisible.rgdispidNamedArgs = &dispidNamed;


	m_hr = m_pMtlbDispApp ->Invoke(m_dispid_Visible, IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_PROPERTYGET, &m_dpNoArgs, &m_vResult, &m_excep, &m_uArgErr);

	return m_vResult.lVal != 0;
}

HRESULT CMatlabEngine::MaximiseWidow()
{
	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	return m_hr = m_pMtlbDispApp->Invoke(m_dispid_MaximizeCommandWindow,
		IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_METHOD, &m_dpNoArgs, NULL,
		&m_excep, &m_uArgErr);
}

HRESULT CMatlabEngine::MinimizeWindow()
{
	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	return m_hr = m_pMtlbDispApp ->Invoke(m_dispid_MinimizeCommandWindow,
		IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_METHOD, &m_dpNoArgs, NULL,
		&m_excep, &m_uArgErr);
}


HRESULT CMatlabEngine::PutMatrix( LPCTSTR szName, const std::vector<double>& vRealArray, const std::vector<double>& vImgArray, UINT nRows, UINT nCols)
{
	BSTR bstrName=NULL;
	BSTR bstrWorkspace=NULL;

	if (!m_bInitialized || !m_pMtlbDispApp || (vRealArray.size() != vImgArray.size()) || (nRows*nCols > vRealArray.size()) )
		return S_FALSE;

	ProcessString(szName, bstrName);
	ProcessString(m_sWorkspace, bstrWorkspace);

	SAFEARRAYBOUND realPartDims[2];
	realPartDims[0].lLbound = 1;     // Lower bound of the first dimension
	realPartDims[0].cElements = nRows;
	realPartDims[1].lLbound = 1;     // Lower bound of the second dimension
	realPartDims[1].cElements = nCols;


	SAFEARRAY *realPart = ::SafeArrayCreate(VT_R8, 2, realPartDims);
	SAFEARRAY *imgPart = ::SafeArrayCreate(VT_R8, 2, realPartDims);

	long lIndex[2];
	UINT k;
	double val;

	for (int i = 1; i <= nRows; i++)
	{
		lIndex[0] = i;

		for (int j = 1; j <= nCols; j++)
		{
			lIndex[1] = j;
			
			k=(i-1)*nCols+j-1;
			val=vRealArray[k];
			m_hr = ::SafeArrayPutElement(realPart, lIndex, &val);
			if (FAILED(m_hr))
				goto Exit;

			val=vImgArray[k];
			m_hr = ::SafeArrayPutElement(imgPart, lIndex, &val);
			if (FAILED(m_hr))
				goto Exit;
		}
	}


	VARIANT vArgPutFullMatrix[4];
	for (i = 0; i < 4; ++i)
		::VariantInit(&vArgPutFullMatrix[i]);


	vArgPutFullMatrix[0].vt = VT_ARRAY | VT_R8;
	vArgPutFullMatrix[0].parray = imgPart; // do set to NULL when not complex
	vArgPutFullMatrix[1].vt = VT_ARRAY | VT_R8;
	vArgPutFullMatrix[1].parray = realPart;
	vArgPutFullMatrix[2].vt = VT_BSTR;
	vArgPutFullMatrix[2].bstrVal = bstrWorkspace;
	vArgPutFullMatrix[3].vt = VT_BSTR;
	vArgPutFullMatrix[3].bstrVal = bstrName;


	DISPPARAMS dpPutFullMatrix;
	dpPutFullMatrix.cArgs = 4;
	dpPutFullMatrix.cNamedArgs = 0;
	dpPutFullMatrix.rgvarg = vArgPutFullMatrix;


	m_hr = m_pMtlbDispApp ->Invoke(m_dispid_PutFullMatrix, IID_NULL,
    LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dpPutFullMatrix, NULL, &m_excep, &m_uArgErr);

	if (FAILED(m_hr))
		goto Exit;

Exit:
	if (bstrName)	
		::SysFreeString(bstrName);
	if (bstrWorkspace)
		::SysFreeString(bstrWorkspace);
	m_hr = ::SafeArrayDestroy(realPart);
	m_hr = ::SafeArrayDestroy(imgPart);

	return m_hr;
}

HRESULT CMatlabEngine::PutMatrix( LPCTSTR szName, const std::vector<double>& vArray, UINT nRows, UINT nCols)
{
	BSTR bstrName=NULL;
	BSTR bstrWorkspace=NULL;

	if (!m_bInitialized || !m_pMtlbDispApp || (nRows*nCols > vArray.size()) )
		return S_FALSE;

	ProcessString(szName, bstrName);
	ProcessString(m_sWorkspace, bstrWorkspace);

	SAFEARRAYBOUND realPartDims[2];
	realPartDims[0].lLbound = 1;     // Lower bound of the first dimension
	realPartDims[0].cElements = nRows;
	realPartDims[1].lLbound = 1;     // Lower bound of the second dimension
	realPartDims[1].cElements = nCols;


	SAFEARRAY *realPart = ::SafeArrayCreate(VT_R8, 2, realPartDims);

	long lIndex[2];
	double val;

	for (int i = 1; i <= nRows; i++)
	{
		lIndex[0] = i;

		for (int j = 1; j <= nCols; j++)
		{
			lIndex[1] = j;

			val=vArray[(i-1)*nCols+j-1];
			m_hr = ::SafeArrayPutElement(realPart, lIndex, &val);
			if (FAILED(m_hr))
				goto Exit;
		}
	}


	VARIANT vArgPutFullMatrix[4];
	for (i = 0; i < 4; ++i)
		::VariantInit(&vArgPutFullMatrix[i]);


	vArgPutFullMatrix[0].vt = VT_ARRAY | VT_R8;
	vArgPutFullMatrix[0].parray = NULL; // do set to NULL when not complex
	vArgPutFullMatrix[1].vt = VT_ARRAY | VT_R8;
	vArgPutFullMatrix[1].parray = realPart;
	vArgPutFullMatrix[2].vt = VT_BSTR;
	vArgPutFullMatrix[2].bstrVal = bstrWorkspace;
	vArgPutFullMatrix[3].vt = VT_BSTR;
	vArgPutFullMatrix[3].bstrVal = bstrName;


	DISPPARAMS dpPutFullMatrix;
	dpPutFullMatrix.cArgs = 4;
	dpPutFullMatrix.cNamedArgs = 0;
	dpPutFullMatrix.rgvarg = vArgPutFullMatrix;

	m_hr = m_pMtlbDispApp ->Invoke(m_dispid_PutFullMatrix, IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dpPutFullMatrix, NULL, &m_excep, &m_uArgErr);

	if (FAILED(m_hr))
		goto Exit;

Exit:
	if (bstrName)
		::SysFreeString(bstrName);
	if (bstrWorkspace)
		::SysFreeString(bstrWorkspace);
	m_hr = ::SafeArrayDestroy(realPart);

	return m_hr;
}

HRESULT CMatlabEngine::GetMatrix( LPCTSTR szName, std::vector<double>& vArray, UINT& nRows, UINT& nCols)
{
	if (!m_bInitialized || !m_pMtlbDispApp)
		return S_FALSE;

	TCHAR szBuffer[512];
	BSTR bstrName=NULL;
	BSTR bstrWorkspace=NULL;
	UINT i;
	SAFEARRAY *realPart;

	ProcessString(szName, bstrName);
	ProcessString(m_sWorkspace, bstrWorkspace);

	// getting size
	_stprintf( szBuffer, _T("size(%s,1)"), szName);
	m_hr = Execute(szBuffer);
	if (FAILED(m_hr))
		goto Exit;
	swscanf( m_vResult.bstrVal, L"%u", &nRows); 
	ASSERT(m_vResult.vt == VT_BSTR);

	_stprintf( szBuffer, _T("size(%s,2)"), szName);
	m_hr = Execute(szBuffer);
	if (FAILED(m_hr))
		goto Exit;
	swscanf( m_vResult.bstrVal, L"%u", &nCols); 

	SAFEARRAYBOUND realPartDims[2];
	realPartDims[0].lLbound = 1;     // Lower bound of the first dimension
	realPartDims[0].cElements = 1;
	realPartDims[1].lLbound = 1;     // Lower bound of the second dimension
	realPartDims[1].cElements = 1;
	realPart=::SafeArrayCreate(VT_R8, 2, realPartDims);

	//loading data...
	VARIANT vArgGetFullMatrix[4];
	for (i = 0; i < 4; ++i)
		::VariantInit(&vArgGetFullMatrix[i]);

	vArgGetFullMatrix[0].vt = VT_ARRAY | VT_R8;
	vArgGetFullMatrix[0].parray = NULL; // do set to NULL when not complex
	vArgGetFullMatrix[1].vt = VT_ARRAY | VT_R8;
	vArgGetFullMatrix[1].parray = realPart;
	vArgGetFullMatrix[2].vt = VT_BSTR;
	vArgGetFullMatrix[2].bstrVal = bstrWorkspace;
	vArgGetFullMatrix[3].vt = VT_BSTR;
	vArgGetFullMatrix[3].bstrVal = bstrName;

	DISPPARAMS dpGetFullMatrix;
	dpGetFullMatrix.cArgs = 4;
	dpGetFullMatrix.cNamedArgs = 0;
	dpGetFullMatrix.rgvarg = vArgGetFullMatrix;

	m_hr = m_pMtlbDispApp ->Invoke(m_dispid_GetFullMatrix, IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dpGetFullMatrix, NULL, &m_excep, &m_uArgErr);

	if (FAILED(m_hr))
		goto Exit;

	// copying to vector...

Exit:
	if (bstrName)
		::SysFreeString(bstrName);
	if (bstrWorkspace)
		::SysFreeString(bstrWorkspace);

	m_hr = ::SafeArrayDestroy(realPart);

	return m_hr;
}

HRESULT CMatlabEngine::Quit()
{
	if (!m_bInitialized || !m_pMtlbDispApp)
	{
		
		m_bInitialized = false;
		return S_FALSE;
	}

	return m_hr = m_pMtlbDispApp ->Invoke(m_dispid_Quit, IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_METHOD, &m_dpNoArgs, NULL, &m_excep, &m_uArgErr);
}

void CMatlabEngine::ProcessString( LPCTSTR szName, BSTR& bstrName)
{
	LPCTSTR szName = szName;
#ifndef _UNICODE
	int nChar;
	AllocateBuffer(_tcslen(szName));
	nChar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,szName,-1,m_pBuffer,m_uBufferSize);
	bstrName = ::SysAllocString(m_pBuffer);
#else
	bstrName = ::SysAllocString(OLESTR(szName));
#endif
}

SAFEARRAY* CMatlabEngine::CreateCell(UINT nRows, UINT nCols)
{
	SAFEARRAYBOUND sabCellArray[2];
	sabCellArray[0].lLbound = 1;
	sabCellArray[0].cElements = nRows;
	sabCellArray[1].lLbound = 1;
	sabCellArray[1].cElements = nCols;

	return ::SafeArrayCreate(VT_VARIANT, 2, sabCellArray);	
}

HRESULT CMatlabEngine::PutElem(SAFEARRAY *saCellArray, UINT i, UINT j, LPCTSTR szString)
{
	VARIANT vCell[1];
	BSTR bstrCell;
	long lIndex[2];

	ProcessString( szString, bstrCell );

	::VariantInit(vCell);
	vCell[1].vt = VT_BSTR;
	vCell[1].bstrVal = bstrCell;
	lIndex[0] = i;
	lIndex[1] = j;
	return m_hr = ::SafeArrayPutElement(saCellArray, lIndex, vCell);
}

HRESULT CMatlabEngine::PutElem(SAFEARRAY *saCellArray, UINT i, UINT j, double d)
{
	VARIANT vCell[1];
	long lIndex[2];

	::VariantInit(vCell);
	vCell[1].vt = VT_R8;
	vCell[1].dblVal = d;
	lIndex[0] = i;
	lIndex[1] = j;
	return m_hr = ::SafeArrayPutElement(saCellArray, lIndex, vCell);
}


HRESULT CMatlabEngine::PutElem(SAFEARRAY *saCellArray, UINT i, UINT j, float f)
{
	VARIANT vCell[1];
	long lIndex[2];

	::VariantInit(vCell);
	vCell[1].vt = VT_R8;
	vCell[1].dblVal = (double)f;
	lIndex[0] = i;
	lIndex[1] = j;
	return m_hr = ::SafeArrayPutElement(saCellArray, lIndex, vCell);
}

HRESULT CMatlabEngine::DestroyCell(SAFEARRAY *saCellArray)
{
	return m_hr = ::SafeArrayDestroy(saCellArray);
}
