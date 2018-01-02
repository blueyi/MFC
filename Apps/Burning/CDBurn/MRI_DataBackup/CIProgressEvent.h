#ifndef _IPROGRESSEVENT_
#define _IPROGRESSEVENT_
// extern ULONG g_TotalBlock;
// extern ULONG g_WrittenBlock;
// //#include"fstream.h"
// //#include"iostream.h"
// #include"../BIGlobals/ConfigManager.h"
// extern ULONG g_TotalBlock;
// extern ULONG g_WrittenBlock;
//{4A9D146B-C847-46b3-879F-3B262AF39D12}
DEFINE_GUID(CLSID_DiscProgressEvents, 
0x4a9d146b, 0xc847, 0x46b3, 0x87, 0x9f, 0x3b, 0x26, 0x2a, 0xf3, 0x9d, 0x12);

class IDiscProgressEvents : public IDiscMasterProgressEvents  
{
	 ULONG   m_cRef;
	//    wchar_t m_szFile[MAX_PATH];
public:
	IDiscProgressEvents()
	{
		m_cRef = 0L;
	//  m_szFile[0] = \'\\0\';
	//  g_cRef++;
	}
	~IDiscProgressEvents()
	{
	// g_cRef--;
	}

	HRESULT  STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv)
	{
		if(riid == IID_IUnknown)
		{
			*ppv = (LPUNKNOWN)(IDiscMasterProgressEvents*)this;
			m_cRef++;
			return NOERROR;
		}
		else if(riid == IID_IDiscMasterProgressEvents)
		{
			*ppv = (IDiscMasterProgressEvents*)this;
			m_cRef++;
			return NOERROR;
		}
		else
		{
			*ppv = NULL;
			return E_NOINTERFACE;
		}
		////////////////////////////////////////
		
		///////////////////////////
	}
        
	ULONG   STDMETHODCALLTYPE AddRef( void)
	{
		return ++m_cRef;
	}
        
	ULONG   STDMETHODCALLTYPE Release( void)
	{
		if (--m_cRef)
			return m_cRef;
		delete this;
		return 0L;
	}


	HRESULT  STDMETHODCALLTYPE NotifyAddProgress(long nCompletedSteps,  long nTotalSteps)
	{
		//g_TotalBlock=nTotalSteps;
		//	g_WrittenBlock=nCompletedSteps;
		//	fstream f1;
		//	CString tn;
		//	tn.Format("total:%d-----%d\n",g_TotalBlock);
		//	//AfxMessageBox(tn);
		//	long timex=GetTickCount();
		//	f1.open("temp.log",ios::app|ios::in|ios::out);
		//	f1<<"GetTickCount()---"<<timex<<endl;
		//	f1<<"nCompletedSteps---"<<g_WrittenBlock<<endl;
		//	f1<<"nTotalSteps---"<<g_TotalBlock<<endl;
		//	f1.close();
	// 	g_TotalBlock=nTotalSteps;
	// 	g_WrittenBlock=nCompletedSteps;
	// 	long timex=GetTickCount();
			
	// 	fstream f1;
	// 	f1.open("temp.log",ios::in|ios::out|ios::app);
	// 	f1<<"GetTickCount()---"<<timex<<endl;
	// 	f1<<"nCurrentTrack---"<<g_WrittenBlock<<endl;
	// 	f1<<"nTotalTracks---"<<g_TotalBlock<<endl;
	// 	f1.close();
		
		
	 return S_OK ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyBlockProgress(long nCompleted,long nTotal )
	{//Display nCompleted / nTotal ) 
		
		/*
		g_TotalBlock=nCompleted;
			g_WrittenBlock=nTotal;
			long timex=GetTickCount();
			fstream f1;
			f1.open("temp.log",ios::in|ios::out|ios::app);
			f1<<timex<<endl;
			f1<<"nCurrentTrack---"<<g_WrittenBlock<<endl;
			f1<<"nTotalTracks---"<<g_TotalBlock<<endl;
			f1<<endl;
			f1.close();*/
		return S_OK ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyBurnComplete(HRESULT status)
	{
	 if (status == S_OK)
	 {
		  CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_WRITE_SUCCESS")/*"congratulation! record successfully!"*/);
	 }

		 return S_OK;
	}

	HRESULT  STDMETHODCALLTYPE QueryCancel(boolean* pbCancel)
	{
		 return E_NOTIMPL ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyPnPActivity( )
	{
		 return E_NOTIMPL ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyTrackProgress(long nCurrentTrack, long nTotalTracks)
	{
		/*
		g_TotalBlock=nTotalTracks;
		g_WrittenBlock=nCurrentTrack;
		fstream f1;
		f1.open("temp.log",ios::app|ios::in|ios::out);
		f1<<"nCurrentTrack---"<<g_WrittenBlock<<endl;
		f1<<"nTotalTracks---"<<g_TotalBlock<<endl;
		f1.close();*/
		
		 return E_NOTIMPL ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyClosingDisc(long nEstimatedSeconds)
	{
		 return E_NOTIMPL ;
	}

	HRESULT  STDMETHODCALLTYPE NotifyPreparingBurn(long nEstimatedSeconds)
	{
		return E_NOTIMPL ;
	}

	HRESULT  STDMETHODCALLTYPE  NotifyEraseComplete(HRESULT status)
	{
		return E_NOTIMPL ;
	}

};

#endif