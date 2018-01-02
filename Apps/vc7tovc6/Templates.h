
#pragma once

/////////////////////////////////////////////////////////////////////////////////////
//
// collection templates
//
// taken from the Windows MFC
// templated
//
//
//


template <class T>
class CTemplateArray
{

public:

// Construction
	CTemplateArray();
	~CTemplateArray();

// Attributes
	int		GetSize() const;
	int		GetUpperBound() const;
	void	SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void	FreeExtra();
	void	RemoveAll();

	// Accessing elements
	T		GetAt(int nIndex) const;
	void	SetAt(int nIndex, T newElement);
	T&		ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const T* GetData() const;
	T*		 GetData();

	// Potentially growing the array
	void	SetAtGrow(int nIndex, T newElement);
	int		Add(T newElement);
	int		Append(const CTemplateArray& src);
	void	Copy(const CTemplateArray& src);

	// overloaded operator helpers
	T		operator[](int nIndex) const;
	T&		operator[](int nIndex);

	// Operations that move elements around
	void	InsertAt(int nIndex, T newElement, int nCount = 1);
	void	RemoveAt(int nIndex, int nCount = 1);
	void	InsertAt(int nStartIndex, CTemplateArray* pNewArray);
	void	Remove(T oldElement);

// Implementation
protected:
	T*  m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

protected:
	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};



template <class T> CTemplateArray<T>::CTemplateArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template <class T> CTemplateArray<T>::~CTemplateArray()
{
	delete[] (BYTE*)m_pData;
}

template <class T> int CTemplateArray<T>::GetSize() const
{ 
	return m_nSize; 
}

template <class T> int CTemplateArray<T>::GetUpperBound() const
{ 
	return m_nSize-1; 
}

template <class T> void CTemplateArray<T>::SetSize(int nNewSize, int nGrowBy)
{
	if (nNewSize < 0)
		return;

	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
		m_pData = (T*) new BYTE[nNewSize * sizeof(T)];

		memset(m_pData, 0, nNewSize * sizeof(T));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(T));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = (m_nSize/8 > 4)? m_nSize/8 : 4;
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		T* pNewData = (T*) new BYTE[nNewMax * sizeof(T)];

		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(T));

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(T));


		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

template <class T> void CTemplateArray<T>::FreeExtra()
{
	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
		T* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (T*) new BYTE[m_nSize * sizeof(T)];
			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(T));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template <class T> void CTemplateArray<T>::RemoveAll()
{ 
	SetSize(0); 
}

template <class T> T CTemplateArray<T>::GetAt(int nIndex) const
{ 
	if (nIndex<0 || nIndex>=m_nSize)
		return NULL;
	else
		return m_pData[nIndex]; 
}

template <class T> void CTemplateArray<T>::SetAt(int nIndex, T newElement)
{ 
	if (nIndex >= 0 && nIndex < m_nSize)
		m_pData[nIndex] = newElement; 
}

template <class T> T& CTemplateArray<T>::ElementAt(int nIndex)
{ 
	static T pVoid=NULL;

	if (nIndex<0 || nIndex>=m_nSize)
		return pVoid;
	else
		return m_pData[nIndex]; 
}

template <class T> const T* CTemplateArray<T>::GetData() const
{ 
	return (const T*)m_pData; 
}

template <class T> T* CTemplateArray<T>::GetData()
{ 
	return (T*)m_pData; 
}

template <class T> void CTemplateArray<T>::SetAtGrow(int nIndex, T newElement)
{
	if (nIndex < 0)
		return;

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}

template <class T> int CTemplateArray<T>::Add(T newElement)
{ 
	int nIndex = m_nSize;
	SetAtGrow(nIndex, newElement);
	return nIndex; 
}

template <class T> void CTemplateArray<T>::Remove(T oldElement)
{ 
	for( int i = 0; i < m_nSize; i++)
	{
		if( m_pData[i] == oldElement)
		{
			if( i < m_nSize - 1)
				m_pData[i] = m_pData[i+1];
			m_nSize--;
			return;
		}
	}
}

template <class T> int CTemplateArray<T>::Append(const CTemplateArray& src)
{
	int nOldSize = m_nSize;
	
	if (this != &src)
	{
		SetSize(m_nSize + src.m_nSize);

		memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(T));
	}
	return nOldSize;
}

template <class T> void CTemplateArray<T>::Copy(const CTemplateArray& src)
{
	if (this == &src)
		return;

	SetSize(src.m_nSize);

	memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(T));

}

template <class T> T CTemplateArray<T>::operator[](int nIndex) const
{ 
	return GetAt(nIndex); 
}

template <class T> T& CTemplateArray<T>::operator[](int nIndex)
{ 
	return ElementAt(nIndex); 
}


template <class T> void CTemplateArray<T>::InsertAt(int nIndex, T newElement, int nCount)
{
	if (nIndex<0 || nCount<=0)
		return;

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size
		// shift old data up to fill gap
		memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
			(nOldSize-nIndex) * sizeof(T));

		// re-init slots we copied from

		memset(&m_pData[nIndex], 0, nCount * sizeof(T));

	}

	// insert new value in the gap
	while (nCount-- && (nIndex + nCount <= m_nSize))
		m_pData[nIndex++] = newElement;
}

template <class T> void CTemplateArray<T>::RemoveAt(int nIndex, int nCount)
{
	if (nIndex >= 0 || nCount >= 0 || (nIndex + nCount <= m_nSize) )
	{
		// just remove a range
		int nMoveCount = m_nSize - (nIndex + nCount);

		if (nMoveCount)
			memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
				nMoveCount * sizeof(T));
		m_nSize -= nCount;
	}
}

template <class T> void CTemplateArray<T>::InsertAt(int nStartIndex, CTemplateArray* pNewArray)
{
	if (pNewArray && nStartIndex>=0 && pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}



/////////////////////////////////////////////////////////////////////////////


template <class T>
class CTemplateObjArray : public CTemplateArray<T>
{
public:
	~CTemplateObjArray();
};


template <class T> CTemplateObjArray<T>::~CTemplateObjArray()
{
	for( int i = 0; i < m_nSize; i++) // call objects destructor
		delete m_pData[i];
}





/////////////////////////////////////////////////////////////////////////////


typedef CTemplateArray<void*> ArrayLPVoid;
typedef CTemplateArray<long>  ArraySLong;
typedef CTemplateArray<long>  ArrayInt;
typedef CTemplateArray<char*>  ArrayString;
typedef CTemplateArray<CString>  ArrayCString;



struct SINGLEVALUEPARAM
{
	CString szName, szValue;
};



struct DOUBLEVALUEPARAM
{
	CString m_pParamName;
	CString m_pParamValue1, m_pParamValue2;
};

struct PROJECTPARAM
{
	PROJECTPARAM()
	{
		bHasDependencies = bIsWritten = FALSE;
	}

	CString szProjectName;
	CString szProjectPath, szProjectGUID;
	ArrayCString arrszProjectDependencies;

	BOOL bHasDependencies;
	BOOL bIsWritten;
};


typedef CTemplateObjArray<SINGLEVALUEPARAM*>	Param1Array;
typedef CTemplateObjArray<DOUBLEVALUEPARAM*>	Param2Array;
typedef CTemplateObjArray<PROJECTPARAM*>		ProjectArray;







class FindableArray : public CTemplateObjArray<SINGLEVALUEPARAM*>
{
public:
	CString GetValue(/*in*/char *szName, BOOL bUseCase=FALSE)
	{
		CString s;
		long nSize = GetSize();
		if (nSize==0) return s;

		BOOL bFound = FALSE;
		long i=0;
		
		while (!bFound && i<nSize)
		{
			SINGLEVALUEPARAM *p = GetAt(i++);
			if (p)
				bFound = bUseCase ? p->szName.Compare(szName) : p->szName.CompareNoCase(szName) ;
		}
		i--;
		if (bFound)
		{
			SINGLEVALUEPARAM *p = GetAt(i++);
			if (p)
				s = p->szValue;
		}

		return s;
	}
};









class XmlElement;
typedef CTemplateObjArray<XmlElement*>			XmlElementArray;

/////

class XmlElement
{
	// Members
protected:
	XmlElement *m_cpElementParent;
	CString		m_szName;
	Param1Array m_arrAttribs;
	XmlElementArray m_arrChildren;
	void*		m_cpParser;

	// Constructor
public:
	XmlElement(CString &szName)
	{
		m_szName = szName;
		m_cpElementParent = NULL;
		m_cpParser = NULL;
	}
	~XmlElement() {}

	// Accessors
public:
	void setParent(XmlElement *pParent) { m_cpElementParent = pParent; }
	XmlElement *getParent() { return m_cpElementParent; }


	void setParser(void *pParser) { m_cpParser = pParser; }
	void *getParser() { return m_cpParser; }

	CString getValue(CString &szAttribName)
	{
		CString s;
		BOOL bFound = FALSE;
		long i=0;
		long nSize = m_arrAttribs.GetSize();

		while (!bFound && i<nSize)
		{
			SINGLEVALUEPARAM *p = m_arrAttribs.GetAt(i++);
			bFound = (p && (szAttribName==p->szName) );
		}

		i--;
		if (bFound)
		{
			SINGLEVALUEPARAM *p = m_arrAttribs.GetAt(i);
			if (p)
			{
				s = p->szValue;
			}
		}

		return s;
	}


	// Methods
public:
	XmlElement *addChild(CString &szName)
	{
		XmlElement *newElem = new XmlElement(szName);
		if (newElem)
		{
			newElem->setParent( this );
			newElem->setParser( getParser() );

			m_arrChildren.Add( newElem );
		}

		return newElem;
	}
	
	void addNameValue(CString &szAttribName, CString &szAttribValue)
	{
		SINGLEVALUEPARAM *p = new SINGLEVALUEPARAM();
		if (!p) return;

		p->szName = szAttribName;
		p->szValue = szAttribValue;
		m_arrAttribs.Add( p );
	}
	
};