// Crypt.h: interface for the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=45C1883701C5
class CCrypt  
{
public:
	//##ModelId=45C1883701E4
	CCrypt();
	//##ModelId=45C1883701F4
	virtual ~CCrypt();
public:
	//##ModelId=45C1883701F6
	static CString Encrypt(CString S, WORD Key);
	//##ModelId=45C1883701FA
	static CString Decrypt(CString S, WORD Key);
};

#endif // !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
