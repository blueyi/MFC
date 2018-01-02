#include "stdafx.h"
#include "../BIGlobals/BI_ImageHeader.h"


CString	 dataTypetoString(int iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;

}


CString	 dataTypetoString(long iParam)
{
	char *cTemp = new char[15];
	ltoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	 dataTypetoString( char* iParam)
{
	int iCount=0;
	char* cTemp = iParam;
	/*
	while ((cTemp++)!='\0')
	{
		iCount++;
	}
	char* cTemp1 = new char[iCount+1];
	for(int i=0;i<=iCount;i++)
		*(cTemp1++) = *(iParam++);*/
	CString temp(cTemp);
	//delete[] cTemp1;
	cTemp =NULL;
	return temp;
}
CString	 dataTypetoString( short iParam)
{
/*	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;*/
	CString str;
	str.Format("%d",iParam);
	return str;
}

CString	 dataTypetoString( double iParam)
{
/*	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;*/
		CString str;
	str.Format("%f",iParam);
	return str;
}

CString	 dataTypetoString( float iParam)
{
	/*
	int iParamInteger,iParamDecimal,iParamTemp;
	iParamTemp = (int)(iParam*100000);
	iParamInteger = (int)iParam;
	iParamDecimal = iParamTemp - iParamInteger*100000;
	
	char *cParamIntegerTemp = new char[15];
	char *cParamDecimalTemp = new char[15];
	itoa(iParamInteger,cParamIntegerTemp,10);
	itoa(iParamDecimal,cParamDecimalTemp,10);
	*/
	CString str;
	str.Format("%f",iParam);
	return str;
}

CString	 F4ArraytoString( float iParam[],int length)
//用以下格式存储(以S字符为分隔)：float[0]Sfloat[1]S.....
{
//	char *cTemp = new char[15];
	CString temp("");
	for(int i=0;i<length;i++){
		/*ltoa((long)iParam[i],cTemp,10);
		temp.Format(temp+cTemp+'S');**/
		temp.Format(temp+"%fS",iParam);
	}
		
//	delete[] cTemp;
	return temp;
}
/*
CString	 dataTypetoString(unsigned float iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}*/
/*
CString	 dataTypetoString(unsigned double iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}
*/
CString	 dataTypetoString(unsigned short iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}




CString	 dataTypetoString(unsigned int iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;

}

CString	 dataTypetoString(unsigned long iParam)
{
	char *cTemp = new char[15];
	ltoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	 dataTypetoString(unsigned char* iParam)
{
	int iCount=0;
	unsigned char* cTemp = iParam;
	/*
	while ((cTemp++)!='\0')
	{
		iCount++;
	}
	char* cTemp1 = new char[iCount+1];
	for(int i=0;i<=iCount;i++)
		*(cTemp1++) = *(iParam++);*/
	CString temp(cTemp);
	//delete[] cTemp1;
	cTemp = NULL;
	return temp;
}





U1	CStringtoU1(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
	{
		
			cTemp[i] = parameter.GetAt(i);
		
	}
	cTemp[parameter.GetLength()] = '\0';
	int iTemp = atoi(cTemp);
	delete[] cTemp;
	return (U1)(iTemp);
}

U2		CStringtoU2(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	int iTemp = atoi(cTemp);
		delete[] cTemp;

	return (U2) iTemp;
	
}
U4		CStringtoU4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';

	int iTemp = atoi(cTemp);
		delete[] cTemp;

	return (U4) iTemp;
}
I1	CStringtoI1(CString parameter)
{
		char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
	{	
			cTemp[i] = parameter.GetAt(i);	
	}
	cTemp[parameter.GetLength()] = '\0';
	
	int iTemp = atoi(cTemp);
	delete[] cTemp;
	return (I1)(iTemp);
}
I2		CStringtoI2(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	int iTemp = atoi(cTemp);
	delete[] cTemp;

	return (I2) iTemp;
}
I4		CStringtoI4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	int iTemp = atoi(cTemp);
	delete[] cTemp;

	return (I4) iTemp;
}
I8		CStringtoI8(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	long iTemp = atol(cTemp);
	delete[] cTemp;

	return (U4) iTemp;
}
F4		CStringtoF4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	double iTemp = atof(cTemp);
	delete[] cTemp;

	return (F4) iTemp;
}
F8		CStringtoF8(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()+1];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	cTemp[parameter.GetLength()] ='\0';
	double iTemp = atof(cTemp);
	delete[] cTemp;

	return (F8) iTemp;
}

bool	CStringtoI1Array(CString parameter,int length,I1 I1Array[])
{
	if (parameter.GetLength()!=length) {
		//assert(0);
	}
	for(int i=0;i<parameter.GetLength();i++)
	{
		if (i<length) {
			I1Array[i] = parameter.GetAt(i);
		}
	}
	if (length<=parameter.GetLength()) {
		I1Array[length] = '\0';
	}
	else{
		I1Array[parameter.GetLength()] = '\0';
	}
	
	return true;
}
/*
I1[]	CStringtoI1Array(CString parameter,int length)
{
	char cTemp[100];
	if (parameter.GetLength()!=length) {
//		assert(0);
	}
	for(int i=0;i<parameter.GetLength();i++)
	{
		if (i<length) {
			cTemp[i] = parameter.GetAt(i);
		}
	}
	return cTemp;
}*/

bool 	CStringtoF4Array(CString parameter,int length,F4 F4Array[])
//解析格式： float[0]Sfloat[1]S.....float[length]S
{
	int iCount =0,iNum =0;
	while (iCount<parameter.GetLength()) {
		if (parameter.GetAt(iCount) =='S') {
			iNum++;
		}
		iCount++;
	}
	if (iNum!=length) 
	{
		for(int i =0;i<length;i++)
			F4Array[i] = 0.0;
		return false;
	}
		 
	/*	F4 resultF4Array = new F4[iNum] ;
		for(int i =0;i<iNum;i++)
			resultF4Array[i] = 0.0*/

	char *cTemp = new char[parameter.GetLength()+1];
	iCount =0;
	int istrF4ValueCount =0,iF4NumeberCount =0;
	//double F4ValueTemp = 0.0;
	while (iCount<parameter.GetLength()) {
		cTemp[istrF4ValueCount] = parameter.GetAt(iCount);
		istrF4ValueCount++;
		iCount++;
		if (parameter.GetAt(iCount) == 'S') {
			cTemp[istrF4ValueCount] ='\0';
			iCount++;
			istrF4ValueCount =0;
			if (iF4NumeberCount<length) 
			F4Array[iF4NumeberCount] = (F4)atof(cTemp);
			iF4NumeberCount++;
			delete[] cTemp;
			cTemp = new char[parameter.GetLength()+1];
		}
	}
	delete[] cTemp; 
	return true;
}
