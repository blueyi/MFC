//////////////////////////////////////////////////////////////////////////
//		Coded by   Hirosh ,India										//
//////////////////////////////////////////////////////////////////////////
//					MSN hirr@hotmail.com								//	
//					yahoo hirosh22@yahoo.com							//
//					ICQ 109619370										//
//					Email :hirhirhir@hotpop.com							//	
//					www.hirosh.tk									//
//////////////////////////////////////////////////////////////////////////
//	I am the one mad from india	!!!!!!!									//	
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

TCHAR g_szTargetPath[MAX_PATH];
void IterateCabinet(PTSTR pszCabFile,char *p);

 LRESULT
   WINAPI
   CabinetCallback ( IN PVOID pMyInstallData,
                     IN UINT Notification,
                     IN UINT Param1,
                     IN UINT Param2 )
   {
      LRESULT lRetVal = NO_ERROR;
      TCHAR szTarget[MAX_PATH];
      FILE_IN_CABINET_INFO *pInfo = NULL;
      FILEPATHS *pFilePaths = NULL;

      lstrcpy(szTarget,g_szTargetPath);

      switch(Notification)
      {
         case SPFILENOTIFY_FILEINCABINET:
            pInfo = (FILE_IN_CABINET_INFO *)Param1;
            lstrcat(szTarget, pInfo->NameInCabinet);
            lstrcpy(pInfo->FullTargetName, szTarget);
            lRetVal = FILEOP_DOIT;  // Extract the file.
            break;

         case SPFILENOTIFY_FILEEXTRACTED:
            pFilePaths = (FILEPATHS *)Param1;
            lRetVal = NO_ERROR;
            break;

         case SPFILENOTIFY_NEEDNEWCABINET: // Unexpected.
            lRetVal = NO_ERROR;
            break;
      }

      return lRetVal;
   }


 
 void IterateCabinet(PTSTR pszCabFile,char *p)
 {
   lstrcpy(g_szTargetPath, p);
   SetupIterateCabinet(pszCabFile,
        0, (PSP_FILE_CALLBACK)CabinetCallback, 0) ;
      
         
      
} 

