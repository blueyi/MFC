// Crypt.cpp: implementation of the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Crypt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define C1 52845
#define C2 22719

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=45C1883701E4
CCrypt::CCrypt()
{

}

//##ModelId=45C1883701F4
CCrypt::~CCrypt()
{

}

//##ModelId=45C1883701F6
CString CCrypt::Encrypt(CString S, WORD Key) // Encryption function
{
	CString Result,str;
	int i,j;

	Result=S;
	for(i=0; i<S.GetLength(); i++)
	{
		Result.SetAt(i, S.GetAt(i)^(Key>>8));
		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2;
	}
	S=Result;
	Result.Empty();
	for(i=0; i<S.GetLength(); i++)
	{
		j=(BYTE)S.GetAt(i);

		str="12";
		str.SetAt(0, 65+j/26);
		str.SetAt(1, 65+j%26);
		Result += str;
	}
	return Result;
}

//##ModelId=45C1883701FA
CString CCrypt::Decrypt(CString S, WORD Key) // decryption function
{
	CString Result,str;
	int i,j;

	Result.Empty();
	for(i=0; i < S.GetLength()/2; i++)
	{
		j = ((BYTE)S.GetAt(2*i)-65)*26;
		j += (BYTE)S.GetAt(2*i+1)-65;
		str="1";
		str.SetAt(0, j);
		Result+=str;
	}
	S=Result;
	for(i=0; i<S.GetLength(); i++)
	{
		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8));
		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2;
	}
	return Result;
}
