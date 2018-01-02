

/////////////////////////////////////////////////////////////////////////////////
//
// slnprocess class implementation
//
// S.Rodriguez - Sept 2002
//
//
// purpose : convert a .sln file format to a .dsw file format
//           (a .sln file is the main file of a VisualStudio solution)
//
//

/****************** SAMPLE .SLN FILE ********************************

Microsoft Visual Studio Solution File, Format Version 7.00
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "SaxAnalyzer", "SaxAnalyzer\SaxAnalyzer.vcproj", "{D26C149E-1AAE-4956-9FEC-184806B4F448}"
EndProject
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "betterxml", "betterxml.vcproj", "{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}"
EndProject
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "xmlparser", "xmlparser\xmlparser.vcproj", "{A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}"
EndProject
Global
	GlobalSection(SolutionConfiguration) = preSolution
		ConfigName.0 = Debug
		ConfigName.1 = Release
	EndGlobalSection
	GlobalSection(ProjectDependencies) = postSolution
		{D26C149E-1AAE-4956-9FEC-184806B4F448}.0 = {A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.0 = {D26C149E-1AAE-4956-9FEC-184806B4F448}
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.1 = {A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}
	EndGlobalSection
	GlobalSection(ProjectConfiguration) = postSolution
		{D26C149E-1AAE-4956-9FEC-184806B4F448}.Debug.ActiveCfg = Debug|Win32
		{D26C149E-1AAE-4956-9FEC-184806B4F448}.Debug.Build.0 = Debug|Win32
		{D26C149E-1AAE-4956-9FEC-184806B4F448}.Release.ActiveCfg = Release|Win32
		{D26C149E-1AAE-4956-9FEC-184806B4F448}.Release.Build.0 = Release|Win32
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.Debug.ActiveCfg = Debug|Win32
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.Debug.Build.0 = Debug|Win32
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.Release.ActiveCfg = Release|Win32
		{A8D81237-B0A6-4B8F-828C-C78E72DD7A72}.Release.Build.0 = Release|Win32
		{A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}.Debug.ActiveCfg = Debug|Win32
		{A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}.Debug.Build.0 = Debug|Win32
		{A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}.Release.ActiveCfg = Release|Win32
		{A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}.Release.Build.0 = Release|Win32
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
	EndGlobalSection
	GlobalSection(ExtensibilityAddIns) = postSolution
	EndGlobalSection
EndGlobal


This sample .sln file reflects a workspace called betterxml.dsw
 with projects :
	SaxAnalyzer.dsp
	  dependencies = xmlparser.dsp
	betterxml.dsp
	  dependencies = SaxAnalyze.dsp, xmlparser.dsp
	xmlparser.dsp

*/

#include <stdio.h>
#include <windows.h>
#include <comutil.h>
#include "msxml2.h"

#include "symbols.h"
#include "slnprocess.h"
#include "vcprojconfiguration.h"
#include "vcprojprocess.h"



// Constructor
slnprocess::slnprocess()
{
}
slnprocess::~slnprocess()
{
}

// Methods
void slnprocess::process(CString &szSolutionName)
{
	m_szSolutionName = szSolutionName;
	if (m_szSolutionName.IsEmpty()) return; // come on!!!!

	CString szDswFilename = m_szSolutionName.Left( m_szSolutionName.GetLength()-strlen(".sln") );
	szDswFilename += ".dsw";


	// open .sln file
	//
	BOOL bResult = m_inputFile.Open(szSolutionName,CFile::modeRead|CFile::typeText);
	if (!bResult)
	{
		printf("Couldn't open %s\n.",szSolutionName);
		return;
	}

	// create empty .dsw file
	//
	bResult = m_outputFile.Open(szDswFilename,CFile::modeCreate|CFile::modeWrite);
	if (!bResult)
	{
		printf("Couldn't create %s\n.",szDswFilename);
		return;
	}

	writeDswHeader();


	CString s;
	
	// scan all lines
	//

	while ( m_inputFile.ReadString(s) )
	{
		if (!s.IsEmpty())
		{

			// process line 
			if ( s.Find(0,SLN_PROJECT)>-1 )
				processProject(s);
			else if ( s.Find(0,SLN_GLOBALSECTION)>-1 && s.Find(0,SLN_SECTIONDEPENDENCIES)>-1 )
				processProjectDependencies(s);

		}
	} // end while


	// write projects
	long i=0;
	long nSize = m_projects.GetSize();
	while (i<nSize)
	{
		PROJECTPARAM *p = m_projects.GetAt(i++);
		if (p) writeDswProject(p);
	}


	writeDswFooter();

	m_outputFile.Close();

}


// this method is used when a *.vcproj is passed in the cmdline, instead of a *.sln name
//
void slnprocess::processProjectOnly(CString &szProjectFullPath)
{
	PROJECTPARAM params;
	params.szProjectPath = szProjectFullPath;

	vcprojprocess proj;
	proj.process(szProjectFullPath,&params);
}



void slnprocess::processProject(CString &sFirstLine)
{
	// the first line is of the form 
	// "Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "SaxAnalyzer", "SaxAnalyzer\SaxAnalyzer.vcproj", "{D26C149E-1AAE-4956-9FEC-184806B4F448}"

	CString szProjectName, szProjectPath, szProjectGUID, s;

	// parse the string
	long n = sFirstLine.Find(0,'='),m;
	if (n>-1)
	{
		s = sFirstLine.ExcludeLeft(n);
		n = s.Find(0,'\"');
		m = s.Find(n+1,'\"');
		if (n>-1 && m>-1 && m>n)
		{
			n++;
			szProjectName = s.Mid(n,m-n);

			s = s.ExcludeLeft(m+1);

			n = s.Find(0,'\"');
			m = s.Find(n+1,'\"');
			if (n>-1 && m>-1 && m>n)
			{
				n++;
				szProjectPath = s.Mid(n,m-n);

				s = s.ExcludeLeft(m+1);

				n = s.Find(0,'\"');
				m = s.Find(n+1,'\"');
				if (n>-1 && m>-1 && m>n)
				{
					n++;
					szProjectGUID = s.Mid(n,m-n);

					s = s.ExcludeLeft(m+1);

				} // 

			} // 

		} // 
	}

	// store project params in memory for later use
	if ( !szProjectName.IsEmpty() && 
		 !szProjectPath.IsEmpty() && 
		 !szProjectGUID.IsEmpty() &&
		 (szProjectPath.Find(0,".vcproj")>-1) ) // must be a *.vcproj project
	{
		PROJECTPARAM *p = new PROJECTPARAM();
		if (p)
		{
			p->szProjectName = szProjectName;
			p->szProjectPath = szProjectPath;
			p->szProjectGUID = szProjectGUID;

			m_projects.Add( p );
		}
	}


	// find end project tag
	while ( m_inputFile.ReadString(s) )
	{
		if (!s.IsEmpty() && s.Find(0,SLN_ENDPROJECT)>-1)
			return;
	}

}



void slnprocess::processProjectDependencies(CString &sFirstLine)
{
	// arrszProjectDependencies

	// in fact, we don't care the first line, 
	// it is of the form : "GlobalSection(ProjectDependencies) = postSolution"

	CString s;

	// read project dependencies
	//
	while ( m_inputFile.ReadString(s) )
	{
		if (!s.IsEmpty())
		{
			if ( s.Find(0,SLN_ENDGLOBALSECTION)>-1 )
				return;
			else
			{
// a dependency is of the form "     {D26C149E-1AAE-4956-9FEC-184806B4F448}.0 = {A7FAC6D9-33CB-4AA0-8553-A1B7DA7929E8}"
// or more formally <masterprojectGUID>.ith_dependency = <subprojectGUID>

				long n,m;
				n = s.Find(0,'{');
				m = s.Find(n+1,'}');
				if (n>-1 && m>-1 && m>n)
				{
					CString szMasterProjectGUID = s.Mid(n,m+1-n); // keep { and }

					s = s.ExcludeLeft(m+1);

					n = s.Find(0,'{');
					m = s.Find(n+1,'}');
					if (n>-1 && m>-1 && m>n)
					{
						CString szSubProjectGUID = s.Mid(n,m+1-n); // keep { and }

						// find the master project in the list of known projects
						//
						BOOL bFound = FALSE;
						long i=0;
						long nSize = m_projects.GetSize();
						while (!bFound && i<nSize)
						{
							PROJECTPARAM *p = m_projects.GetAt(i++);
							bFound = (p && (szMasterProjectGUID==p->szProjectGUID) );
						}

						i--;
						if (bFound)
						{
							PROJECTPARAM *p = m_projects.GetAt(i);
							if (p)
							{
								p->arrszProjectDependencies.Add( szSubProjectGUID );
							}

						}

					}
				}
			} //
		}
	}

}



void slnprocess::writeDswHeader()
{
	CString s = "Microsoft Developer Studio Workspace File, Format Version 6.00\r\n";
	m_outputFile.Write(s);
	s = "# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!\r\n\r\n";
	m_outputFile.Write(s);
	s = "###############################################################################\r\n\r\n";
	m_outputFile.Write(s);
}

void slnprocess::writeDswProject(PROJECTPARAM *p)
{
	if (!p) return; // good bye!


	// now create the .dsp file
	vcprojprocess proj;
	proj.process(m_szSolutionName,p);



	CString s = "Project: \"";
	s += p->szProjectName;
	s += "\"=";
	CString szDspProjectPath = p->szProjectPath;
	szDspProjectPath = szDspProjectPath.Left( szDspProjectPath.GetLength()-strlen(".vcproj") );
	szDspProjectPath += ".dsp";
	if ( !isFullPath(p->szProjectPath) ) s += ".\\";
	s += szDspProjectPath;
	s += " - Package Owner=<4>\r\n\r\n";
	m_outputFile.Write(s);
	s = "Package=<5>\r\n{{{\r\n";
	m_outputFile.Write(s);
	CString szSccName, szSccPath;
	proj.getSourceControlInfo(szSccName,szSccPath);
	if (!szSccName.IsEmpty()) // under source control (vss, clearcase, cvs, ...)
	{
		s = "    begin source code control\r\n    " + szSccName + "\r\n    " + szSccPath + "\r\n";
		s += "    end source code control\r\n";
		m_outputFile.Write(s);
	}

	s = "}}}\r\n\r\n";
	m_outputFile.Write(s);
	s = "Package=<4>\r\n{{{\r\n";
	m_outputFile.Write(s);


	long nSize = p->arrszProjectDependencies.GetSize();
	if (nSize>0)
	{
	
		for (long i=0; i<nSize; i++)
		{
			CString szProjGUID = p->arrszProjectDependencies.GetAt(i);
			CString szProjName;

			BOOL bFound = FALSE;
			long j=0;
			long nSizeNames = m_projects.GetSize();
			while (!bFound && j<nSizeNames)
			{
				PROJECTPARAM *p = m_projects.GetAt(j++);
				bFound = (p && (szProjGUID==p->szProjectGUID) );
			}

			j--;
			if (bFound)
			{

				PROJECTPARAM *p = m_projects.GetAt(j);
				if (p)
				{

					// -- write dependencies
					s = "    Begin Project Dependency\r\n";
					m_outputFile.Write(s);


					s = "    Project_Dep_Name " + p->szProjectName + "\r\n";
					m_outputFile.Write(s);

					s = "    End Project Dependency\r\n";
					m_outputFile.Write(s);

				}
			}
		} // end for

		// -- end write dependencies 

	}

	s = "}}}\r\n\r\n";
	m_outputFile.Write(s);
	s = "###############################################################################\r\n\r\n";
	m_outputFile.Write(s);


}

void slnprocess::writeDswFooter()
{
	CString s = "Global:\r\n\r\n";
	m_outputFile.Write(s);
	s = "Package=<5>\r\n{{{\r\n}}}\r\n\r\n";
	m_outputFile.Write(s);
	s = "Package=<3>\r\n{{{\r\n}}}\r\n\r\n";
	m_outputFile.Write(s);
	s = "###############################################################################\r\n\r\n";
	m_outputFile.Write(s);
}



// isFullPath -------------------------------
//
// purpose : tells if 'szFilepath' is a fully qualified filepath, or a relative path
BOOL slnprocess::isFullPath(CString &szFilepath)
{
	BOOL bResult = TRUE;

	// extract directory
	long i = m_szSolutionName.ReverseFind(0, '\\');
	if (i==-1) return TRUE;

	CString szDirectory = m_szSolutionName.Left(i+1);

	// try to find the file made whose full filepath is "directory"+"finalpath"
	CString szFullfilepath = szDirectory + szFilepath;

	HANDLE hFind;
	WIN32_FIND_DATA fd;

	if ((hFind=::FindFirstFile(szFullfilepath,&fd))==INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}

	::FindClose(hFind);

	return FALSE;
}