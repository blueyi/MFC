// SeriesManager.cpp: implementation of the CSeriesManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QTImage.h"
#include "SeriesManager.h"
#include "vtkDICOMImageReader.h"
#include "vtkCallBackCommand.h"
#include "vtkXMLImageDataReader.h"
#include "vtkPNGReader.h"
#include "vtkJPEGReader.h"
#include "vtkBMPReader.h"
#include "vtkStringArray.h"
#include "vtkPNGWriter.h"
#include "vtkXMLImageDataWriter.h"
#include "QTImageDlg.h"
#include "MRISeries.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CString g_sProcessTitle;
extern CQTImageDlg* gpMainDlg;

void ProcessEventCallBack(vtkObject *obj, unsigned long event , void *clientdata, void *calldata)
{
	CQTImageDlg* pMainDlg = gpMainDlg;
	double progress=*((double*)calldata);
	CString sTmp;
	if(progress<=0.99)
	{
		sTmp.Format("%s %.0f",g_sProcessTitle,progress*100);
	}else
	{
		sTmp.Format("%s end.",g_sProcessTitle);
	}
	
	pMainDlg->SendMessage(WM_SETMESSAGESTRING,WPARAM(&sTmp),NULL);
}

CSeriesManager::CSeriesManager()
{

}

CSeriesManager::~CSeriesManager()
{
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	while(pos)
	{
		series=m_list.GetNext(pos);
		series.Data->Delete();
		if(series.SegmentedData)
		{
			series.SegmentedData->Delete();
		}
	}

	m_list.RemoveAll();
}

vtkImageData * CSeriesManager::OpenSeries(CString sFile)
{
	SERIES series;
	CString sTmp;
	POSITION pos;
	
	g_sProcessTitle="Reading";

	BOOL bFindDot=FALSE;
	BOOL bFindParent=FALSE;
	BOOL bFindHeng=FALSE;
	CString sExt;
	CString sParent;
	vtkImageData *pData=NULL;
	CString sNoExt=sFile;
	

	for(int i=1;i<sFile.GetLength();i++)
	{
		sTmp=sFile.Mid(sFile.GetLength()-i,1);
		if(bFindDot==FALSE && sTmp==".")
		{
			bFindDot=TRUE;
			sExt=sFile.Right(i-1);
		}
		if(bFindHeng==FALSE && sTmp=="_")
		{
			bFindHeng=TRUE;	
			sNoExt=sFile.Left(sFile.GetLength()-i);
		}
		if(bFindParent==FALSE && sTmp=="\\")
		{
			bFindParent=TRUE;
			sParent=sFile.Left(sFile.GetLength()-i);
		}
	}

	sExt.MakeUpper();
	if(sExt=="IMG")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sParent)
			{

				return series.Data;
			}
		}
		pData = ReadImgSeries(sParent);
		sprintf(series.Name,"%s",sParent);
	}else if(sExt=="JPG")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sNoExt)
			{

				return series.Data;
			}
		}
		pData = ReadJPGFile(sNoExt,sFile);
		sprintf(series.Name,"%s",sNoExt);
	}else if(sExt=="BMP")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sNoExt)
			{

				return series.Data;
			}
		}
		pData = ReadBMPFile(sNoExt,sFile);
		sprintf(series.Name,"%s",sNoExt);
	}else if(sExt=="PNG")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sNoExt)
			{

				return series.Data;
			}
		}
		pData = ReadPNGFile(sNoExt,sFile);
		sprintf(series.Name,"%s",sNoExt);
	}else if(sExt=="DCM")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sParent)
			{

				return series.Data;
			}
		}
		pData = ReadDcmFile(sParent);
		sprintf(series.Name,"%s",sParent);
	}else if(sExt=="VTI")
	{
		pos=m_list.GetHeadPosition();
		while(pos)
		{
			series=m_list.GetNext(pos);
			sTmp.Format("%s",series.Name);
			if(sTmp==sFile)
			{

				return series.Data;
			}
		}
		pData = ReadVtiData(sFile);
		sprintf(series.Name,"%s",sFile);
	}

	if(pData!=NULL)
	{
		series.Data=pData;
		series.SegmentedData=NULL;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(j==j)
				{
					series.base1[i][j]=1;
					series.base2[i][j]=1;
					series.base3[i][j]=1;
				}else
				{
					series.base1[i][j]=0;
					series.base2[i][j]=0;
					series.base3[i][j]=0;
				}
			}
		}
		m_list.AddTail(series);
	}

	return pData;
}

vtkImageData* CSeriesManager::ReadImgSeries(CString sFile)
{
	
	if(sFile=="")
	{
		return NULL;
	}

	CString strWildcard;
	strWildcard = sFile + _T("\\*.img");
	CFileFind finder;
	BOOL bXinaoImage = finder.FindFile(strWildcard);
	if (!bXinaoImage)
	{
		return NULL;
	}

	CMRISeries *pMRISeries = new CMRISeries;
	if (pMRISeries->Load( sFile ))
	{		
		delete pMRISeries;
		pMRISeries = NULL;
		return NULL;
	}
	
	int iSize[3];
	iSize[0] = pMRISeries->GetImageAt(0)->GetResolutionX();
	iSize[1] = pMRISeries->GetImageAt(0)->GetResolutionY();
	iSize[2] = pMRISeries->GetNumOfImages();
	double dPixelSpacing[3];
	dPixelSpacing[0] = pMRISeries->GetImageAt(0)->GetFOVX()/pMRISeries->GetImageAt(0)->GetResolutionX();
	dPixelSpacing[1] = pMRISeries->GetImageAt(0)->GetFOVY()/pMRISeries->GetImageAt(0)->GetResolutionY();
	dPixelSpacing[2] = pMRISeries->GetImageAt(0)->GetThickness()+pMRISeries->GetImageAt(0)->GetGap();
	dPixelSpacing[2] = fabs(dPixelSpacing[2]);

	if(iSize[2]>1)
	{
		double *dCenter1=pMRISeries->GetImageAt(0)->GetCenterInScanner();
		double *dCenter2=pMRISeries->GetImageAt(1)->GetCenterInScanner();
		dPixelSpacing[2]=sqrt((dCenter1[0]-dCenter2[0])*(dCenter1[0]-dCenter2[0])+
		                     (dCenter1[1]-dCenter2[1])*(dCenter1[1]-dCenter2[1])+
							 (dCenter1[2]-dCenter2[2])*(dCenter1[2]-dCenter2[2]));
	}
	
	unsigned short* pImageData = new unsigned short [iSize[0]*iSize[1]*iSize[2]];	
		
	for(int i=0;i<iSize[2];i++)
	{
		unsigned short* p = &pImageData[i*iSize[0]*iSize[1]];
		for(int j=0;j<iSize[1];j++)
		{
			memcpy(p+(iSize[1]-1-j)*iSize[0],pMRISeries->GetImageAt(i)->GetRotatedData()+iSize[0]*j,sizeof(short)*iSize[0]);
		}
			
	}

	delete pMRISeries;

	vtkImageData *pData=vtkImageData::New();

	vtkUnsignedShortArray *array =  vtkUnsignedShortArray::New();
	array ->SetArray(pImageData, iSize[0]*iSize[1]*iSize[2],0) ;
	pData->GetPointData()->SetScalars(array);
	pData ->SetDimensions(iSize[0],iSize[1],iSize[2]);
	pData ->SetScalarType(VTK_UNSIGNED_SHORT);
		
	pData ->SetSpacing(dPixelSpacing[0], dPixelSpacing[1], dPixelSpacing[2]);
	pData ->SetOrigin(0.0, 0.0, 0.0);
	array->Delete();

	return pData;
		
}

vtkImageData* CSeriesManager::ReadVtiData(CString sFile)
{
	vtkXMLImageDataReader *pRead=vtkXMLImageDataReader::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pRead->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	pRead->SetFileName(sFile);

	try
	{
		pRead->Update();

	}
	catch(...)
	{
	
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pData=vtkImageData::New();
	vtkImageCast *cast=vtkImageCast::New();

	int i=pRead->GetOutput()->GetScalarType();

	cast->SetInput(pRead->GetOutput());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->SetClampOverflow(1);
	cast->AddObserver(vtkCommand::ProgressEvent, callback);
	cast->Update();
	pData->DeepCopy(cast->GetOutput());
	pData->SetOrigin(0,0,0);

	pRead->Delete();
	cast->Delete();
	
	unsigned short *pSrcData=(unsigned short *)pData->GetScalarPointer(0,0,0);
	if(!pSrcData)
	{
		AfxMessageBox("No enough memory.");
		return NULL;
	}else
	{
		return pData;
	}
	
}

vtkImageData* CSeriesManager::ReadJPGFile(CString sFileNoExt,CString sFile)
{
	vtkJPEGReader* pRead = vtkJPEGReader::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pRead->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	vtkStringArray *lstFile=vtkStringArray::New();

	CFileFind finder;
	CString sTmp;
	for(int i=0;i<300;i++)
	{
		sTmp.Format("%s_%d.jpg",sFileNoExt,i);
		if(finder.FindFile(sTmp))
		{
			finder.FindNextFile();
			lstFile->InsertNextValue((LPCTSTR)finder.GetFilePath());
		}else
		{
			break;
		}
	}

	

	if(lstFile->GetNumberOfValues()<=0)
	{
		lstFile->InsertNextValue((LPCTSTR)sFile);
	}
		
	
	try
	{
		pRead->SetFileNames(lstFile);
		lstFile->Delete();

		pRead->Update();
		
	}
	catch(...)
	{
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pImage=pRead->GetOutput();
	int iDim[3];
	pImage->GetDimensions(iDim);
	if(iDim[0]<=2 && iDim[1]<=2 && iDim[2]<=0)
	{
		pRead->Delete();
		return NULL;
	}

	unsigned short *pDestData=new unsigned short[iDim[0]*iDim[1]*iDim[2]];
	int iComponents=pImage->GetNumberOfScalarComponents();
	unsigned char *pSrcData=(unsigned char*)pImage->GetScalarPointer(0,0,0);
	for(i=0;i<iDim[0]*iDim[1]*iDim[2];i++)
	{
		pDestData[i]=pSrcData[i*iComponents];
	}

	vtkImageData *pData=vtkImageData::New();
	vtkUnsignedShortArray *array =  vtkUnsignedShortArray::New();
	array ->SetArray(pDestData, iDim[0]*iDim[1]*iDim[2],0) ;
	pData->GetPointData()->SetScalars(array);
	pData->SetDimensions(iDim[0],iDim[1],iDim[2]);
	pData->SetScalarType(VTK_UNSIGNED_SHORT);
	pData ->SetSpacing(1,1,1);
	pData ->SetOrigin(0.0, 0.0, 0.0);
	array->Delete();

	pRead->Delete();

	return pData;
	
}

vtkImageData* CSeriesManager::ReadBMPFile(CString sFileNoExt,CString sFile)
{
	vtkBMPReader* pRead = vtkBMPReader::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pRead->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	vtkStringArray *lstFile=vtkStringArray::New();

	CFileFind finder;
	CString sTmp;
	for(int i=0;i<300;i++)
	{
		sTmp.Format("%s_%d.bmp",sFileNoExt,i);
		if(finder.FindFile(sTmp))
		{
			finder.FindNextFile();
			lstFile->InsertNextValue((LPCTSTR)finder.GetFilePath());
		}else
		{
			break;
		}
	}


	if(lstFile->GetNumberOfValues()<=0)
	{
		lstFile->InsertNextValue((LPCTSTR)sFile);
	}
		
	
	try
	{
		pRead->SetFileNames(lstFile);
		lstFile->Delete();

		pRead->Update();
		
	}
	catch(...)
	{
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pImage=pRead->GetOutput();
	int iDim[3];
	pImage->GetDimensions(iDim);
	if(iDim[0]<=2 && iDim[1]<=2 && iDim[2]<=0)
	{
		pRead->Delete();
		return NULL;
	}

	unsigned short *pDestData=new unsigned short[iDim[0]*iDim[1]*iDim[2]];
	int iComponents=pImage->GetNumberOfScalarComponents();
	unsigned char *pSrcData=(unsigned char*)pImage->GetScalarPointer(0,0,0);
	for(i=0;i<iDim[0]*iDim[1]*iDim[2];i++)
	{
		pDestData[i]=pSrcData[i*iComponents];
	}

	vtkImageData *pData=vtkImageData::New();
	vtkUnsignedShortArray *array =  vtkUnsignedShortArray::New();
	array ->SetArray(pDestData, iDim[0]*iDim[1]*iDim[2],0) ;
	pData->GetPointData()->SetScalars(array);
	pData->SetDimensions(iDim[0],iDim[1],iDim[2]);
	pData->SetScalarType(VTK_UNSIGNED_SHORT);
	pData ->SetSpacing(1,1,1);
	pData ->SetOrigin(0.0, 0.0, 0.0);
	array->Delete();

	pRead->Delete();

	return pData;
}

vtkImageData* CSeriesManager::ReadPNGFile(CString sFileNoExt,CString sFile)
{
	vtkPNGReader* pRead = vtkPNGReader::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pRead->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	vtkStringArray *lstFile=vtkStringArray::New();

	CFileFind finder;
	CString sTmp;
	for(int i=0;i<300;i++)
	{
		sTmp.Format("%s_%d.png",sFileNoExt,i);
		if(finder.FindFile(sTmp))
		{
			finder.FindNextFile();
			lstFile->InsertNextValue((LPCTSTR)finder.GetFilePath());
		}else
		{
			break;
		}
	}


	if(lstFile->GetNumberOfValues()<=0)
	{
		lstFile->InsertNextValue((LPCTSTR)sFile);
	}
		
	
	try
	{
		pRead->SetFileNames(lstFile);
		lstFile->Delete();

		pRead->Update();
		
	}
	catch(...)
	{
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pImage=pRead->GetOutput();
	int iDim[3];
	pImage->GetDimensions(iDim);
	if(iDim[0]<=2 && iDim[1]<=2 && iDim[2]<=0)
	{
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pData=vtkImageData::New();
	vtkImageCast *cast=vtkImageCast::New();


	cast->SetInput(pRead->GetOutput());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->SetClampOverflow(1);
	cast->AddObserver(vtkCommand::ProgressEvent, callback);
	cast->Update();
	pData->DeepCopy(cast->GetOutput());

	pRead->Delete();
	cast->Delete();

	unsigned short *pSrcData=(unsigned short *)pData->GetScalarPointer(0,0,0);
	if(!pSrcData)
	{
		AfxMessageBox("No enough memory.");
		return NULL;
	}else
	{
		return pData;
	}
}

vtkImageData* CSeriesManager::ReadDcmFile(CString sFile)
{
	vtkDICOMImageReader* pRead = vtkDICOMImageReader::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pRead->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	CFileFind finder;
	CString sTmp=sFile+"\\*.*";
	BOOL bWorking = finder.FindFile(sTmp);
	BOOL bIsDCM=FALSE;

	try
	{
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (pRead->CanReadFile((LPCTSTR)finder.GetFilePath()))
			{
				bIsDCM = TRUE;
				break;
			}
		}
		if (!bIsDCM)
		{
			pRead->Delete();
			return NULL;
		}
	}catch(...)
	{
		pRead->Delete();
		return NULL;
	}
	
	BOOL bNew=FALSE;
	try
	{
		pRead->SetDirectoryName(LPCSTR(sFile));
		pRead->Update();
	}
	catch(...)
	{
		pRead->Delete();
		return NULL;
	}

	vtkImageData *pData=vtkImageData::New();
	vtkImageCast *cast=vtkImageCast::New();

	int i=pRead->GetOutput()->GetScalarType();

	cast->SetInput(pRead->GetOutput());
	cast->SetOutputScalarTypeToUnsignedShort();
	cast->SetClampOverflow(1);
	cast->AddObserver(vtkCommand::ProgressEvent, callback);
	cast->Update();
	pData->DeepCopy(cast->GetOutput());
	pData->SetOrigin(0,0,0);

	pRead->Delete();
	cast->Delete();

	unsigned short *pSrcData=(unsigned short *)pData->GetScalarPointer(0,0,0);
	if(!pSrcData)
	{
		AfxMessageBox("No enough memory.");
		return NULL;
	}else
	{
		return pData;
	}
}

int CSeriesManager::Count()
{
	return m_list.GetCount();
}

vtkImageData* CSeriesManager::GetAt(int index)
{
	SERIES series;
	vtkImageData *pData=NULL;
	if(index>=0 && index<m_list.GetCount())
	{
		series=m_list.GetAt(m_list.FindIndex(index));
		pData=series.Data;
	}

	return pData;
}

CString CSeriesManager::GetName(vtkImageData *pImage)
{
	CString sTmp="";
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	while(pos)
	{
		series=m_list.GetNext(pos);
		if(series.Data==pImage)
		{
			sTmp.Format("%s",series.Name);
			break;
		}
	}

	return sTmp;
}

BOOL CSeriesManager::SaveSeries(vtkImageData *pImage, CString sFile)
{
	g_sProcessTitle="Writing";

	BOOL bFindDot=FALSE;
	BOOL bFindParent=FALSE;
	CString sTmp;
	CString sExt;
	CString sParent;
	CString sNoExt=sFile;

	for(int i=1;i<sFile.GetLength();i++)
	{
		sTmp=sFile.Mid(sFile.GetLength()-i,1);
		if(bFindDot==FALSE && sTmp==".")
		{
			bFindDot=TRUE;
			sExt=sFile.Right(i-1);
			sNoExt=sFile.Left(sFile.GetLength()-i);
		}
		if(bFindParent==FALSE && sTmp=="\\")
		{
			bFindParent=TRUE;
			sParent=sFile.Left(sFile.GetLength()-i);
		}
	}

	sExt.MakeUpper();
	if(sExt=="VTI")
	{
		return WriteVTISeries(pImage,sFile);
	}else if(sExt=="RAW")
	{
		return WriteRAWSeries(pImage,sFile);

	}else if(sExt=="PNG")
	{
		return WritePNGSeries(pImage,sNoExt);

	}else
	{
		return FALSE;
	}

	return FALSE;
}

BOOL CSeriesManager::WritePNGSeries(vtkImageData *pImage, CString sFile)
{
	if(!pImage)
		return FALSE;
		
	vtkPNGWriter *pWriter=vtkPNGWriter::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pWriter->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	try
	{
		pWriter->SetFilePrefix(sFile);
		pWriter->SetFilePattern("%s_%d.png");
		pWriter->SetInput(pImage);
		pWriter->Write();
	}catch(...)
	{
		pWriter->Delete();
		return FALSE;
	}

	pWriter->Delete();
	return TRUE;

}

BOOL CSeriesManager::WriteRAWSeries(vtkImageData *pImage, CString sFile)
{
	if(!pImage)
		return FALSE;

	int *pDim=pImage->GetDimensions();
	unsigned short *pData=(unsigned short *)pImage->GetScalarPointer(0,0,0);
	
	FILE *file;
	if((file = fopen (sFile, "w+b")) == NULL)
	{
		return FALSE;
	}

	BOOL bClosed=FALSE;
	try
	{
		fseek(file,0,SEEK_SET);
		fwrite((char*)pData,sizeof(char),sizeof(short)*pDim[0]*pDim[1]*pDim[2],file);
		fclose(file);
		bClosed=TRUE;
	}catch(...)
	{
		if(!bClosed)
		{
			fclose(file);
		}
		return FALSE;
	}

	return TRUE;
}

BOOL CSeriesManager::WriteVTISeries(vtkImageData *pImage, CString sFile)
{
	if(!pImage)
		return FALSE;
		
	vtkXMLImageDataWriter *pWriter=vtkXMLImageDataWriter::New();
	vtkCallbackCommand* callback = vtkCallbackCommand::New();
	callback->SetCallback(ProcessEventCallBack);
	callback->SetClientData(this);
	pWriter->AddObserver(vtkCommand::ProgressEvent, callback);
	callback->Delete();

	BOOL bResult=FALSE;
	try
	{
		
		pWriter->SetFileName(sFile);
		pWriter->SetInput(pImage);
		bResult=pWriter->Write();
	}catch(...)
	{
		pWriter->Delete();
		return FALSE;
	}

	pWriter->Delete();
	return bResult;

}

BOOL CSeriesManager::GetBase(vtkImageData *pImage, Matrix &m1, 
							 Matrix &m2, Matrix &m3)
{
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	while(pos)
	{
		series=m_list.GetNext(pos);
		if(series.Data==pImage)
		{
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					m1.value[i][j]=series.base1[i][j];
					m2.value[i][j]=series.base2[i][j];
					m3.value[i][j]=series.base3[i][j];
				}
			}
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSeriesManager::SetBase(vtkImageData *pImage, Matrix m1, Matrix m2, Matrix m3)
{
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	int iCount=0;
	while(pos)
	{
		series=m_list.GetNext(pos);
		if(series.Data==pImage)
		{
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					series.base1[i][j]=m1.value[i][j];
					series.base2[i][j]=m2.value[i][j];
					series.base3[i][j]=m3.value[i][j];
				}
			}
			if(iCount==m_list.GetCount()-1)
			{
				m_list.RemoveAt(m_list.FindIndex(iCount));
				m_list.AddTail(series);
			}else
			{
				m_list.RemoveAt(m_list.FindIndex(iCount));
				m_list.InsertBefore(m_list.FindIndex(iCount),series);
			}

			return TRUE;
		}
		iCount++;
	}

	return FALSE;
}



BOOL CSeriesManager::SetSegmentedImage(vtkImageData *pImage, vtkImageData *pSegmentedImage)
{
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	int iCount=0;
	while(pos)
	{
		series=m_list.GetNext(pos);
		if(series.Data==pImage)
		{
			series.SegmentedData=pSegmentedImage;
			if(iCount==m_list.GetCount()-1)
			{
				m_list.RemoveAt(m_list.FindIndex(iCount));
				m_list.AddTail(series);
			}else
			{
				m_list.RemoveAt(m_list.FindIndex(iCount));
				m_list.InsertBefore(m_list.FindIndex(iCount),series);
			}

			return TRUE;
		}
		iCount++;
	}

	return FALSE;
}

vtkImageData* CSeriesManager::GetSegmentedImage(vtkImageData *pImage)
{
	SERIES series;
	POSITION pos=m_list.GetHeadPosition();
	int iCount=0;
	while(pos)
	{
		series=m_list.GetNext(pos);
		if(series.Data==pImage)
		{
			
			return series.SegmentedData;
		}
		iCount++;
	}

	return NULL;
}
