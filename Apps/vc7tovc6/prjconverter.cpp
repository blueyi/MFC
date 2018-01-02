// prjconverter.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <windows.h>
#include "slnprocess.h"
#include "Folder.h"
#include <algorithm>
	int g_sln;
	int g_handlebecall;
	int g_vcproject;
static void Handle(const std::string &path)
{
	g_handlebecall++;
	WIN32_FIND_DATA data;
	std::string  findsln=path;
	std::string  handlestr=path;
	findsln+="\\*.sln";
	bool isfindsln=false;
////////////找sln
	HANDLE handle=FindFirstFile (findsln.c_str (),&data);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		do{
			if(0==(data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				isfindsln=true;
				g_sln++;
				handlestr+='\\';
				handlestr+=data.cFileName ;
				CString szSolutionName(&handlestr[0] );
					slnprocess aslnprocess;
				aslnprocess.process (szSolutionName);			
			}
		}while(FindNextFile(handle,&data));
		FindClose(handle);
	}
	/////////////////////////////////////////////////////////
//假如在当前目录下未找到sln,就找vcproj,找到了sln就不找vcproj
	if(false==isfindsln)
	{
		std::string  findvcproject=path;
		findvcproject+="\\*.vcproj";
		
		handle=FindFirstFile (findvcproject.c_str (),&data);
		if(INVALID_HANDLE_VALUE!=handle)
		{do{
			if(0==(data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				handlestr=path;
				handlestr+='\\';
				handlestr+=data.cFileName ;
				CString szSolutionName(&handlestr[0]);
					slnprocess aslnprocess;
					aslnprocess.processProjectOnly (szSolutionName);			
				g_vcproject++;
			}
		}while(FindNextFile(handle,&data));
		FindClose(handle);
		}
	}
	///////////////////////////////////////////////	bottom content
	std::string  findcontext=path;
	findcontext+="\\*.*";
	
handle=FindFirstFile(findcontext.c_str (),&data);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		do{
			if((data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
		
					std::string  nextpath=data.cFileName ;;

				if(nextpath!="."&&nextpath!=".."){
					handlestr=path;
					handlestr+='\\';
				handlestr+=nextpath;
				Handle(handlestr);
				}
			}
		}while(FindNextFile(handle,&data));
		FindClose(handle);
	}
	
	
}
int main(int argc, char* argv[])
{
	CFolder folder;
	std::string pos=folder.GetFolder ();
	if (pos.empty ())
	{
		printf ("file path is need! \n");
		return 0;
	}
Handle(pos);
printf("sln is %i\n",g_sln);
printf("handle fun be call %i\n",g_handlebecall);
printf("only have vcproj is %i\n",g_vcproject);
	// make sure the .sln (or .vcproj) file actually exists
	//

/*	CString szSolutionName = argv[1];
	if (!szSolutionName.Right(strlen(".vcproj")).CompareNoCase(".vcproj") &&
		!szSolutionName.Right(strlen(".sln")).CompareNoCase(".sln"))
		szSolutionName += ".sln";

	HANDLE hFind;
	WIN32_FIND_DATA fd;

	if ((hFind=::FindFirstFile(szSolutionName,&fd))==INVALID_HANDLE_VALUE)
	{
		printf ("%s does not exist.\n",szSolutionName);
		return 0;
	}

	if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		printf ("%s is a directory!\n",szSolutionName);
		return 0;
	}

	::FindClose(hFind);


	slnprocess p;

	// *.sln passed in the cmdline
	if ( szSolutionName.Right(strlen(".sln")).CompareNoCase(".sln") )
	{
		p.process(szSolutionName);
	}
	else if ( szSolutionName.Right(strlen(".vcproj")).CompareNoCase(".vcproj") ) // *.vcproj passed in the cmdline
	{
		p.processProjectOnly(szSolutionName); // szSolutionName is not a *.sln name
	}
	else
	{
		printf ("Only .sln and .vcproj filenames are processed.\n",szSolutionName);
		return 0;
	}
*/
	return 0;
}


