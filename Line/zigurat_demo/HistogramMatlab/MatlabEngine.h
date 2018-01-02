// MatlabEngine.h: interface for the CMatlabEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATLABENGINE_H__68399C4F_F2D7_4111_B685_0B4778EE6F16__INCLUDED_)
#define AFX_MATLABENGINE_H__68399C4F_F2D7_4111_B685_0B4778EE6F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! \brief A class wrapper for the Matlab COM interface.

<p>This class wraps the Matlab COM interfaces and eases up the integration of Matlab in any Windows program. With this class, 
you can access Matlab engine in a few lines and without playing with the ugly COM syntax or linking with the Matlab libraries.</p>
<p><b>Initialization:</b>Each MatlabEngine object creates an instance of the Matlab engine (this is done automatically in the constructor).
The user can check that initialization has successed by calling IsInited.
Do not forget to initialize COM in the application thread by calling CoInitialize.</p>
<p><b>Example of use:</b></p>
\code
CMatlabEngine matlab; \endcode
<ul>
<li>Using matlab command line:
\code 
// showing a classic Matlab example:
matlab.Execute(_T("surf(peaks);"));
\endcode
</li>
<li>Sending a matrix of data to Matlab:
\code
int m,n;
vector<double> vMatrix(m*n);
// filling vMatrix with elements, line by line : vMatrix(i,j) = vMatrix[i * n + j]
...

matlab.PutMatrix(_T("matrix"), vMatrix, m, n); 
\endcode
</li>
</ul>
<p><b>Requisites:</b> 
<ul>
<li>Matlab ActiveX control installed on your machine to make it work.</li>
<li>Does not need MFC</li>
</ul>
</p>
<p><b>Licensing:</b></p>This code is totally free. Just don't forget to add the authors name in the credits...</p>
\author Jonathan de Halleux, dehalleux@auto.ucl.ac.be
*/
class CMatlabEngine  
{
public:
	//! \name Constructors
	//@{
	/*! \brief Default constructor

	This constructor initializes the Matlab Engine. Successfull initialization can be checked with IsInited .
	\sa IsInited
	*/
	CMatlabEngine();
	virtual ~CMatlabEngine();
	//@}

	//! \name Engine Initialization checkers
	//@{
	//! returns true if the matlab engine has been properly initialized
	bool IsInited() const	{ return m_bInitialized;};
	//@}

	//! \name Matlab window handling
	//@{
	//! returns true if matlab is visible
	bool IsVisible();
	//! show / hide matlab console
	HRESULT Show(bool bShow = true);
	//! minimize matlab console
	HRESULT MinimizeWindow();
	//! maximize matlab console
	HRESULT MaximiseWidow();
	//! Quit console
	HRESULT Quit();
	//@}

	//! \name Engine Kernel
	//@{
	/*! \brief Execute matlab instructions

	\param szCode string containing the matlab code to execute

	Here's an example of use:
	\code 
	CMatlabEngine mt;
	...
	mt.Execute(_T("surf(peaks)"));
	mt.Execute(_T("title('demo of use')"));
	\endcode
	*/
	HRESULT Execute( LPCTSTR szCode);

	//! Get the latest string result of Execute...
	const BSTR& GetResult() const	{	m_vResult.bstrVal;};

	/*! \brief Add a matrix to matlab workspace

	\param szName name of the variable in matlab 
	\param vArray vector of data, filled line by lines
	\param nRows number of rows in array
	\param nCols number of columns in array
	
	If nRows * nCols is greater than the size of vArray, nothing is done.

	Here's an example of use: plotting a 2 columns vector
	\code 
	CMatlabEngine mt;
	...
	vector<double> v(200);
	... // v[i] =... etc
	mt.PutMatrix(_T("v"), v, 100, 2);
	mt.Execute(_T("plot(v)"));
	\endcode
	*/
	HRESULT PutMatrix( LPCTSTR szName, const std::vector<double>& vArray, UINT nRows, UINT nCols);

	/*! \brief Add a complexmatrix to matlab workspace

	\param szName name of the variable in matlab 
	\param vRealArray vector of data (real part), filled line by lines
	\param vImgArray vector of data (real part), filled line by lines
	\param nRows number of rows in array
	\param nCols number of columns in array
	
	If nRows * nCols is greater than the size of vArray, nothing is done.
	*/
	HRESULT PutMatrix( LPCTSTR szName, const std::vector<double>& vRealArray, const std::vector<double>& vImgArray, UINT nRows, UINT nCols);

	//! The inverse of PutArray
	HRESULT GetMatrix( LPCTSTR szName, std::vector<double>& vArray, UINT& nRows, UINT& nCols);
	//@}

	//! \name Workspace
	//@{
	//! returns the current workspace (default is "base")
	LPCTSTR GetWorkspace() const			{	return m_sWorkspace;};
	//! sets the current workspace
	void SetWorkspace(LPCTSTR szWorkspace)	{	m_sWorkspace = szWorkspace;};
	//@}

	//! \name Cell handling
	//@{
	SAFEARRAY* CreateCell( UINT nRows, UINT nCols );
	HRESULT PutElem(SAFEARRAY *saCellArray, UINT i, UINT j, double d);
	HRESULT PutElem(SAFEARRAY *saCellArray, UINT i, UINT j, float f);
	HRESULT PutElem( SAFEARRAY* saCellArray, UINT i, UINT j, LPCTSTR szString);
	HRESULT DestroyCell(SAFEARRAY* saCellArray);
	//@}

	//! \name Error handling
	//@{
	//! Displays a message box with error description
	void GetLastErrorMessage() const;
	//! Returns last HRESULT
	HRESULT GetLastHResult() const	{	return m_hr;};
	//! returns last VARIANT result
	const VARIANT& GetLastVResult() const	{	return m_vResult;};
	//! returns last EXECPINFO
	const EXCEPINFO& GetLastExcep() const	{	return m_excep;};
	//! returns last ArgErr
	UINT GetLastArgErr() const		{	return m_uArgErr;};
	//@}

protected:
	//! \name Internal methods
	//@{
	//! Display a error message defined by hr, excep and uArgErr
	static void ErrHandler(HRESULT hr, EXCEPINFO excep, UINT uArgErr);
	//! Allocates bstrName and transforms / copy szName to bstrName
	void ProcessString( LPCTSTR szName, BSTR& bstrName);
	//@}

private:
	bool m_bInitialized;
	CString m_sWorkspace;

	IDispatch* m_pMtlbDispApp;
	
	DISPID m_dispid_GetFullMatrix;
	DISPID m_dispid_PutFullMatrix;
	DISPID m_dispid_Execute;
	DISPID m_dispid_MinimizeCommandWindow;
	DISPID m_dispid_MaximizeCommandWindow;
	DISPID m_dispid_GetCharArray;
	DISPID m_dispid_PutCharArray;
	DISPID m_dispid_Visible;
	DISPID m_dispid_Quit;

	HRESULT m_hr;
	VARIANT m_vResult;
	EXCEPINFO m_excep;
	UINT m_uArgErr;
	DISPPARAMS m_dpNoArgs;

// non unicode handling...
#ifndef _UNICODE
	void AllocateBuffer(UINT uSize)
	{
		if (uSize <= m_uBufferSize-1) 
			return;
		if (m_pBuffer) 
			delete[] m_pBuffer;
		m_pBuffer = new WCHAR[m_uBufferSize = uSize+1];
	};
	WCHAR* m_pBuffer;
	UINT m_uBufferSize;
#endif
};

#endif // !defined(AFX_MATLABENGINE_H__68399C4F_F2D7_4111_B685_0B4778EE6F16__INCLUDED_)
