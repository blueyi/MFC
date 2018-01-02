// Folder.cpp: implementation of the CFolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Folder.h"
#include <windows.h>
#include <shlobj.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolder::CFolder()
{

}

CFolder::~CFolder()
{

}

std::string CFolder::GetFolder()
{
	BROWSEINFO BrowseInfo ;
	std::string  strret;

	memset(&BrowseInfo,0,sizeof(BrowseInfo));
    BrowseInfo.lpszTitle = "Please choose a directory";
	BrowseInfo.ulFlags   = BIF_RETURNONLYFSDIRS ;  
    LPITEMIDLIST lpItemIDList = SHBrowseForFolder ( &BrowseInfo );
    if ( lpItemIDList != 0 )
    {
        char path[MAX_PATH];
        if (SHGetPathFromIDList ( lpItemIDList, path ) )
        {
			////////////////////
			strret = path; 
			
			////////////////////
        }
        IMalloc * iMalloc = 0;
        if (  SHGetMalloc ( &iMalloc ) )
        {
            iMalloc->Free ( lpItemIDList );
            iMalloc->Release ( );
        }
    }	
	return strret; 
}
