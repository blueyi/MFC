
/////////////////////////////////////////////////////////////////////////////////
//
// vcprojprocess class implementation
//
// S.Rodriguez - Sept 2002
//
//
// purpose : convert a .vcproj file format to a .dsp file format
//           (a .vcproj file is the makefile of a VisualStudio 7 C++ project)
//
//


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <atlbase.h> // CComPtr

#include <comutil.h> // _variant_t
#pragma comment(lib, "comsupp.lib")

#include "msxml2.h"

#include "slnprocess.h"
#include "vcprojconfiguration.h"
#include "symbols.h"
#include "vcprojprocess.h"





// Constructor
vcprojprocess::vcprojprocess()
{
	::CoInitialize(NULL);
}
vcprojprocess::~vcprojprocess()
{
	::CoUninitialize();
}



// Methods
void vcprojprocess::process(CString &szSolutionName, PROJECTPARAM *p)
{
	m_szSolutionName = szSolutionName;
	m_cpPrj = p; // copy ptr

	if (!m_cpPrj) return; // good bye!

	CString szVcprojPath = m_cpPrj->szProjectPath;
	if ( !isFullPath(szVcprojPath) )
	{
		long i = m_szSolutionName.ReverseFind(0, '\\');

		CString szDirectory = m_szSolutionName.Left(i+1);

		szVcprojPath = szDirectory + szVcprojPath;
	}



	HRESULT hr;
	IXMLDOMDocument *pXMLDoc=NULL;

	hr = ::CoCreateInstance(CLSID_DOMDocument, 
							NULL, 
							CLSCTX_INPROC_SERVER, 
							IID_IXMLDOMDocument, 
							(void**)&pXMLDoc);

	if (FAILED(hr))
	{
		printf ("Cannot instantiate msxml2.dll\n");
		printf ("Please download the MSXML run-time (url below)\n");
		printf ("http://msdn.microsoft.com/downloads/default.asp?url=/downloads/sample.asp?url=/msdn-files/027/001/766/msdncompositedoc.xml\n");
		return;
	}

	VARIANT_BOOL vtbool;
	_variant_t bstrFilepath(szVcprojPath);

	pXMLDoc->put_async( VARIANT_BOOL(FALSE) );
	hr = pXMLDoc->load(bstrFilepath,&vtbool);

	if (FAILED(hr) || vtbool==VARIANT_FALSE)
	{
		printf ("Could not open %s.\n", szVcprojPath);
		pXMLDoc->Release();
		return;
	} 


	// ok, now the vcproj file is read
	// let's translate the content to the .dsp file
	//
	CString szDspFilename = szVcprojPath.Left( szVcprojPath.GetLength()-strlen(".vcproj") ) + ".dsp";


	// create empty .dsp file
	//
	BOOL bResult = m_outputFile.Open(szDspFilename,CFile::modeCreate|CFile::modeWrite);
	if (!bResult)
	{
		printf("Couldn't create %s\n.",szDspFilename);
		pXMLDoc->Release();
		return;
	}


	// now process the content
	//

	extractHeader( pXMLDoc );
	extractConfigurations( pXMLDoc );

	writeDspHeader();

	writeDspConfigurations( pXMLDoc );

	writeDspFiles( pXMLDoc );

	writeDspFooter();

	pXMLDoc->Release();
}



// extractHeader()
//
// purpose : extract key data from the .vcproj file content
//
void vcprojprocess::extractHeader(IXMLDOMDocument *pDoc)
{
	if (!pDoc) return;

	m_bIsConsoleApp = FALSE;

	// begin with the <VisualStudioProject> element
	//
	CComPtr<IXMLDOMNodeList> pRootNode;
	pDoc->getElementsByTagName( _bstr_t(XMLNODE_VISUALSTUDIOPROJECT), &pRootNode);
    if (pRootNode)
	{
		long nb = 0;
		pRootNode->get_length(&nb);
		if (nb==1)
		{
			CComPtr<IXMLDOMNode> pNode;
			pRootNode->get_item(0,&pNode);
			if (pNode)
			{
				CComQIPtr<IXMLDOMElement> pElem( pNode );

				getAttribValue(pElem,XMLATTRIB_NAME,m_szProjname);
				getAttribValue(pElem,XMLATTRIB_SCCPROJECTNAME,m_szSccProjectName);
				getAttribValue(pElem,XMLATTRIB_SCCPROJECTPATH,m_szSccLocalPath);

			}
		} // end if (nb==1)

	} // end if (pRootNode)


	// now get the list of project configurations, <Configuration> elements
	//
	CComPtr<IXMLDOMNodeList> pConfigs;
	pDoc->getElementsByTagName( _bstr_t(XMLNODE_CONFIGURATION), &pConfigs);
    if (pConfigs)
	{

		long nb = 0;
		pConfigs->get_length(&nb);

		for (long i=0; i<nb; i++)
		{
			CComPtr<IXMLDOMNode> pNode;
			pConfigs->get_item(i,&pNode);
			if (pNode)
			{
				CComQIPtr<IXMLDOMElement> pElem( pNode );

				if (i==0) // retrieve target type
				{
					getAttribValue(pElem,XMLATTRIB_TARGETTYPE,m_szTargetType);

					
					if ( m_szTargetType.Compare("1") ) // check if the application is also a console app
					{
						CComPtr<IXMLDOMNodeList> pResult;
						HRESULT hr = pElem->selectNodes(_bstr_t("Tool[@Name='VCLinkerTool']"), &pResult);
						if (pResult)
						{
							long nbResult = 0;
							pResult->get_length(&nbResult);

							if (nbResult>0)
							{
								CComPtr<IXMLDOMNode> pResult0;
								pResult->get_item(0,&pResult0);
								if (pResult0)
								{
									CComQIPtr<IXMLDOMElement> pElem0( pResult0 );

									CString szPreProcDefs;
									getAttribValue(pElem0,XMLATTRIB_SUBSYSTEM,szPreProcDefs);

									m_bIsConsoleApp = szPreProcDefs.CompareNoCase("1"); // console app if = 1
								}
							}

						} // end if (pResult)
					}
				} // if (i==0) 

				// get configuration name
				CString szConfigName;
				getAttribValue(pElem,XMLATTRIB_NAME,szConfigName);

				if ( !szConfigName.IsEmpty() )
					m_arrConfigurationNames.Add( szConfigName );


			} // end if pNode

		} // end for


	} // end if (pConfigs)
}


// extractConfigurations()
//
// purpose : extract configuration data from the .vcproj file content
//
void vcprojprocess::extractConfigurations(IXMLDOMDocument *pDoc)
{
	if (!pDoc) return; // good bye!

	CComPtr<IXMLDOMNodeList> pConfigs;
	pDoc->getElementsByTagName( _bstr_t(XMLNODE_CONFIGURATION), &pConfigs);
    if (pConfigs)
	{

		long nb = 0;
		pConfigs->get_length(&nb);

		for (long i=0; i<nb; i++)
		{
			CComPtr<IXMLDOMNode> pNode;
			pConfigs->get_item(i,&pNode);
			if (pNode)
			{
				CComQIPtr<IXMLDOMElement> pConfiguration( pNode );
	
				// create a container in memory, and fill it with the configuration data
				//
				vcprojconfiguration *pVCConfig = new vcprojconfiguration();
				if (pVCConfig)
				{
					m_arrConfigs.Add( pVCConfig );
					pVCConfig->fill( pConfiguration );
				}
			}
		} // end for all configurations

	} // end if (pConfigs)
}


// extractFileConfigurations()
//
// purpose : extract configuration data from the a custom file content
//
void vcprojprocess::extractFileConfigurations(IXMLDOMElement *pFileElement, ConfigurationArray &arrFileConfigs)
{
	if (!pFileElement) return; // good bye!

	CComPtr<IXMLDOMNodeList> pConfigs;
	pFileElement->getElementsByTagName( _bstr_t(XMLNODE_FILECONFIGURATION), &pConfigs);
    if (pConfigs)
	{

		long nb = 0;
		pConfigs->get_length(&nb);

		for (long i=0; i<nb; i++)
		{
			CComPtr<IXMLDOMNode> pNode;
			pConfigs->get_item(i,&pNode);
			if (pNode)
			{
				CComQIPtr<IXMLDOMElement> pConfiguration( pNode );
	
				// create a container in memory, and fill it with the configuration data
				//
				vcprojconfiguration *pVCConfig = new vcprojconfiguration();
				if (pVCConfig)
				{
					arrFileConfigs.Add( pVCConfig );
					pVCConfig->fill( pConfiguration );
				}
			}
		} // end for all configurations

	} // end if (pConfigs)
}



void vcprojprocess::writeDspHeader()
{
	if (m_szProjname.IsEmpty() || m_arrConfigurationNames.GetSize()==0) return;

// Win32 (x86) Dynamic-Link Library 
// Win32 (x86) Application
// Win32 (x86) Console Application
// Win32 (x86) Static Library
// Win32 (x86) External Target  = makefile project

	CString szFriendlyTargetType;
	CString szHexaTargetType;
	if (m_szTargetType.Compare("1"))
	{
		szFriendlyTargetType = m_bIsConsoleApp ? " (x86) Console Application" : " (x86) Application";
		szHexaTargetType = m_bIsConsoleApp ? "0x0103" : "0x0101";
	}
	else if (m_szTargetType.Compare("2"))
	{
		szFriendlyTargetType = " (x86) Dynamic-Link Library";
		szHexaTargetType = "0x0102";
	}
	else if (m_szTargetType.Compare("4"))
	{
		szFriendlyTargetType = " (x86) Static Library";
		szHexaTargetType = "0x0104";
	}
	else if (m_szTargetType.Compare("0"))
	{
		szFriendlyTargetType = " (x86) External Target"; // makefile project
		szHexaTargetType = "0x0106";
	}
	else
	{
		szFriendlyTargetType = " (x86) Unknown Target"; // not likely to happen, though
		szHexaTargetType = "0x0100";
	}

	CString szPlatform = ExtractPlatform( m_arrConfigurationNames.GetAt(0) ); // usually it is Win32

	szFriendlyTargetType = szPlatform + szFriendlyTargetType;


	CString s = "# Microsoft Developer Studio Project File - Name=\"";
	s += m_szProjname;
	s += "\" - Package Owner=<4>\r\n";
	m_outputFile.Write(s);
	s = "# Microsoft Developer Studio Generated Build File, Format Version 6.00\r\n";
	m_outputFile.Write(s);
	s = "# ** DO NOT EDIT **\r\n\r\n";
	m_outputFile.Write(s);
	s = "# TARGTYPE \"" + szFriendlyTargetType + "\" " + szHexaTargetType + "\r\n\r\n";
	m_outputFile.Write(s);
	s = "CFG=" + TranslateConfigurationName( m_arrConfigurationNames.GetAt(0) ) + "\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE This is not a valid makefile. To build this project using NMAKE,\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE use the Export Makefile command and run\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE \r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE NMAKE /f \"" + m_szProjname + ".mak\".\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE \r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE You can specify a configuration when running NMAKE\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE by defining the macro CFG on the command line. For example:\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE \r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE NMAKE /f \"" + m_szProjname + ".mak\" CFG=\"";
	s += TranslateConfigurationName( m_arrConfigurationNames.GetAt(0) );
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE \r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE Possible choices for configuration are:\r\n";
	m_outputFile.Write(s);
	s = "!MESSAGE \r\n";
	m_outputFile.Write(s);

	// all configs
	long nConfigNb = m_arrConfigurationNames.GetSize();
	for (long i=0; i<nConfigNb; i++)
	{
		s = "!MESSAGE \"";
		s += TranslateConfigurationName( m_arrConfigurationNames.GetAt(i) );
		s += "\" (based on \"";
		s += szFriendlyTargetType;
		s += "\")\r\n";
		m_outputFile.Write(s);
	}

	s = "!MESSAGE \r\n\r\n";
	m_outputFile.Write(s);
	s = "# Begin Project\r\n";
	m_outputFile.Write(s);
	s = "# PROP AllowPerConfigDependencies 0\r\n";
	m_outputFile.Write(s);
	s = "# PROP Scc_ProjName \"" + m_szSccProjectName + "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Scc_LocalPath \"" + m_szSccLocalPath + "\"\r\n";
	m_outputFile.Write(s);
	s = "CPP=cl.exe\r\n";
	m_outputFile.Write(s);
	s = "MTL=midl.exe\r\n";
	m_outputFile.Write(s);
	s = "RSC=rc.exe\r\n\r\n";
	m_outputFile.Write(s);
}	


void vcprojprocess::writeDspConfigurations(IXMLDOMDocument *pDoc)
{
	if (!pDoc) return;

	// all configs
	long nConfigNb = m_arrConfigs.GetSize();
	if (nConfigNb==0) return;

	CString s;

	for (long i=0; i<nConfigNb; i++)
	{
		if (i==0)
			s = "!IF  \"$(CFG)\" == \"";
		else
			s = "!ELSEIF  \"$(CFG)\" == \"";

		vcprojconfiguration *pConfig = m_arrConfigs.GetAt(i);

		CString szConfigName = pConfig->getConfigName();

		s += TranslateConfigurationName( szConfigName ) + "\"\r\n\r\n";

		m_outputFile.Write(s);

		if ( m_szTargetType.Compare("0") && pConfig->hasVCConfigTool(CString(VCNMAKETOOL)) )
		{
			// that's a makefile project, no need of muscles here
			writeDspMakefile(i);
		}
		else
		{

			CString szUseMFC = "0";
			CString szTemp = pConfig->General.GetValue("UseOfMFC");
			if (szTemp.CompareNoCase("1"))
				szUseMFC = "5"; // MFC statically linked
			else if (szTemp.CompareNoCase("2"))
				szUseMFC = "6"; // MFC as shared DLL

			s = "# PROP BASE Use_MFC " + szUseMFC + "\r\n";
			m_outputFile.Write(s);
			s = "# PROP BASE Use_Debug_Libraries ";
			s += (szConfigName.FindNoCase(0,"debug")>-1) ? "1" : "0";
			s += "\r\n";
			m_outputFile.Write(s);
			s = "# PROP BASE Output_Dir \"";
			s += pConfig->General.GetValue("OutputDirectory");
			s += "\"\r\n";
			m_outputFile.Write(s);
			s = "# PROP BASE Intermediate_Dir \"";
			s += pConfig->General.GetValue("IntermediateDirectory");
			s += "\"\r\n";
			m_outputFile.Write(s);
			s = "# PROP BASE Target_Dir \"\"\r\n";
			m_outputFile.Write(s);

			s = "# PROP Use_MFC " + szUseMFC + "\r\n";
			m_outputFile.Write(s);
			s = "# PROP Use_Debug_Libraries ";
			s += (szConfigName.FindNoCase(0,"debug")>-1) ? "1" : "0";
			s += "\r\n";
			m_outputFile.Write(s);
			s = "# PROP Output_Dir \"";
			s += pConfig->General.GetValue("OutputDirectory");
			s += "\"\r\n";
			m_outputFile.Write(s);
			s = "# PROP Intermediate_Dir \"";
			s += pConfig->General.GetValue("IntermediateDirectory");
			s += "\"\r\n";
			m_outputFile.Write(s);
			s = "# PROP Target_Dir \"\"\r\n";
			m_outputFile.Write(s);

				
			// build compiling symbols line
			//
			CString szCPPSymbols = pConfig->serializeCPPSymbols();

			// build Linker symbol line
			//
			CString szLinkerSymbols = pConfig->serializeLinkerSymbols();

			// build Librarian symbol line
			//
			CString szLibSymbols = pConfig->serializeLibrarianSymbols();

			// build ResourceCompiler symbol line
			//
			CString szResourceSymbols = pConfig->serializeResourceSymbols();

			// build BrowseInformation symbol line
			//
			CString szBscMakeSymbols = pConfig->serializeBscMakeSymbols();

			// build Midl symbol line
			//
			CString szMidlSymbols = pConfig->serializeMidlSymbols();

			// build PreBuild cmd line
			//
			ArrayCString arrPreBuildCommands;
			pConfig->serializePreBuildCommands(arrPreBuildCommands);

			// build PreLink cmd line
			//
			ArrayCString arrPreLinkCommands;
			pConfig->serializePreLinkCommands(arrPreLinkCommands);

			// build PostBuild cmd line
			//
			ArrayCString arrPostBuildCommands;
			pConfig->serializePostBuildCommands(arrPostBuildCommands);

			// build CustomBuild cmd line
			//
			CString szCustomBuildDescription;
			ArrayCString arrCustomBuildCommands;
			ArrayCString arrCustomOutputFiles;
			ArrayCString arrAdditionalDeps;
			pConfig->serializeCustomBuildCommands(	szCustomBuildDescription, 
													arrCustomBuildCommands,
													arrCustomOutputFiles,
													arrAdditionalDeps);

			
			// compiler line (mandatory)
			s = "# ADD BASE CPP " + szCPPSymbols + "\r\n";
			m_outputFile.Write(s);
			s = "# ADD CPP " + szCPPSymbols + "\r\n";
			m_outputFile.Write(s);

			// midl line (optional)
			if (!szMidlSymbols.IsEmpty())
			{
				s = "# ADD BASE MTL " + szMidlSymbols + "\r\n";
				m_outputFile.Write(s);
				s = "# ADD MTL " + szMidlSymbols + "\r\n";
				m_outputFile.Write(s);
			}

			// resource compiler (optional)
			if (!szResourceSymbols.IsEmpty())
			{
				s = "# ADD BASE RSC " + szResourceSymbols + "\r\n";
				m_outputFile.Write(s);
				s = "# ADD RSC " + szResourceSymbols + "\r\n";
				m_outputFile.Write(s);
			}

			// browseinformation (mandatory)
			s = "BSC32=bscmake.exe\r\n";
			s += "# ADD BASE BSC32 " + szBscMakeSymbols + "\r\n";
			m_outputFile.Write(s);
			s = "# ADD BSC32 " + szBscMakeSymbols + "\r\n";
			m_outputFile.Write(s);

			// linker line (mandatory)
			BOOL bIsStaticLibrary = m_szTargetType.Compare("4");
			CString szLinkTool = bIsStaticLibrary ? "LIB32" : "LINK32";
			s = szLinkTool + "=link.exe";
			if (bIsStaticLibrary)
				s += " -lib";
			s += "\r\n";
			s += "# ADD BASE " + szLinkTool + " ";
			s += bIsStaticLibrary ? szLibSymbols : szLinkerSymbols;
			s += "\r\n";
			m_outputFile.Write(s);
			s = "# ADD " + szLinkTool + " ";
			s += bIsStaticLibrary ? szLibSymbols : szLinkerSymbols;
			s += "\r\n";
			m_outputFile.Write(s);

			// custom build (optional)
			if ( arrCustomBuildCommands.GetSize()>0 )
			{
				s = "# Begin Custom Build - " + szCustomBuildDescription + "\r\n";
				m_outputFile.Write(s);
				s = "SOURCE=\"$(InputPath)\"\r\n"; // don't know why VC++ 6.0 needs this
				m_outputFile.Write(s);
				s = "\r\nBuildCmds= \\\r\n";
				m_outputFile.Write(s);
				long j;
				for (j=0; j<arrCustomBuildCommands.GetSize(); j++)
				{
					s = "\t";
					s += arrCustomBuildCommands.GetAt(j);
					s += " \\\r\n";
					m_outputFile.Write(s);
				}
				s = "\r\n";
				m_outputFile.Write(s);

				for (j=0; j<arrCustomOutputFiles.GetSize(); j++)
				{
					s = "\r\n\"";
					s += arrCustomOutputFiles.GetAt(j);
					s += "\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\r\n";
					s += "   $(BuildCmds)\r\n";
					m_outputFile.Write(s);
				}

				s = "# End Custom Build\r\n";
				m_outputFile.Write(s);
			}

			// prelink or postbuild tool (both are optional)
			BOOL bHasPrelink = ( arrPreLinkCommands.GetSize()>0 );
			BOOL bHasPostBuild = ( arrPostBuildCommands.GetSize()>0 );
			if (bHasPrelink || bHasPostBuild)
			{
				s = "# Begin Special Build Tool\r\n";
				m_outputFile.Write(s);
				s = "SOURCE=\"$(InputPath)\"\r\n"; // don't know why VC++ 6.0 needs this
				m_outputFile.Write(s);

				if (bHasPrelink)
				{
					if (arrPreLinkCommands.GetAt(0).GetLength()>0)
					{
						s = "PreLink_Desc=" + arrPreLinkCommands.GetAt(0) + "\r\n";
						m_outputFile.Write(s);
					}
					s = "PreLink_Cmds=" + arrPreLinkCommands.GetAt(1) + "\r\n";
					m_outputFile.Write(s);
				} // end if (bHasPrelink)

				if (bHasPostBuild)
				{
					if (arrPostBuildCommands.GetAt(0).GetLength()>0)
					{
						s = "PostBuild_Desc=" + arrPostBuildCommands.GetAt(0) + "\r\n";
						m_outputFile.Write(s);
					}
					s = "PostBuild_Cmds=" + arrPostBuildCommands.GetAt(1) + "\r\n";
					m_outputFile.Write(s);
				} // end if (bHasPostBuild)

				s = "# End Special Build Tool\r\n";
				m_outputFile.Write(s);
			}

			s = "\r\n";
			m_outputFile.Write(s);

		}

	}
	
	s = "!ENDIF\r\n\r\n";
	m_outputFile.Write(s);
}


void vcprojprocess::getSourceControlInfo(CString &szSccName, CString &szSccPath)
{
	szSccName = m_szSccProjectName;
	szSccPath = m_szSccLocalPath;
}





void vcprojprocess::writeDspMakefile(long i)
{
	long nConfigNb = m_arrConfigurationNames.GetSize();
	if (nConfigNb==0 || i<0 || i>=nConfigNb) return;

	vcprojconfiguration *pConfig = m_arrConfigs.GetAt(i);
	if (!pConfig) return;

	CString szConfigName = pConfig->getConfigName();

	CString s = "# PROP BASE Use_MFC\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Use_Debug_Libraries ";
	s += (szConfigName.FindNoCase(0,"debug")>-1) ? "1" : "0";
	s += "\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Output_Dir \"";
	s += pConfig->General.GetValue("OutputDirectory");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Intermediate_Dir \"";
	s += pConfig->General.GetValue("IntermediateDirectory");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Cmd_Line \"";
	s += pConfig->VCNMakeTool.GetValue("BuildCommandLine");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Rebuild_Opt \"";
	s += pConfig->VCNMakeTool.GetValue("ReBuildCommandLine");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Target_File \"";
	s += pConfig->VCNMakeTool.GetValue("Output");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Bsc_Name \"" + m_szProjname + ".bsc" + "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP BASE Target_Dir \"\"\r\n";
	m_outputFile.Write(s);

	s = "# PROP Use_MFC\r\n";
	m_outputFile.Write(s);
	s = "# PROP Use_Debug_Libraries ";
	s += (szConfigName.FindNoCase(0,"debug")>-1) ? "1" : "0";
	s += "\r\n";
	m_outputFile.Write(s);
	s = "# PROP Output_Dir \"";
	s += pConfig->General.GetValue("OutputDirectory");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Intermediate_Dir \"";
	s += pConfig->General.GetValue("IntermediateDirectory");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Cmd_Line \"";
	s += pConfig->VCNMakeTool.GetValue("BuildCommandLine");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Rebuild_Opt \"";
	s += pConfig->VCNMakeTool.GetValue("ReBuildCommandLine");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Target_File \"";
	s += pConfig->VCNMakeTool.GetValue("Output");
	s += "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Bsc_Name \"" + m_szProjname + ".bsc" + "\"\r\n";
	m_outputFile.Write(s);
	s = "# PROP Target_Dir \"\"\r\n\r\n";
	m_outputFile.Write(s);
}

void vcprojprocess::writeDspFiles(IXMLDOMDocument *pDoc)
{
	if (!pDoc) return;

	long nConfigNb = m_arrConfigurationNames.GetSize();
	if (nConfigNb==0) return;


	CString s = "# Begin Target\r\n\r\n";
	m_outputFile.Write(s);

	for (long i=0; i<nConfigNb; i++)
	{
		s = "# Name \"" + TranslateConfigurationName( m_arrConfigurationNames.GetAt(i) ) + "\"\r\n";
		m_outputFile.Write(s);
	}


	CComPtr<IXMLDOMNodeList> pFilesNodelist;
	pDoc->getElementsByTagName( _bstr_t(XMLNODE_FILES), &pFilesNodelist);
    if (pFilesNodelist)
	{

		long nb = 0;
		pFilesNodelist->get_length(&nb);

		if (nb!=1) return;
		
		CComPtr<IXMLDOMNode> pNode;
		pFilesNodelist->get_item(0,&pNode);
		if (pNode)
		{
			CComQIPtr<IXMLDOMElement> pFiles( pNode );
			if (pFiles)
			{
				writeDspGroup(pFiles); // recurse call
			}
		}

	} // end if (pFilesList)


}

void vcprojprocess::writeDspGroup(IXMLDOMElement *pGroupFilter)
{
	CString s;

	if (!pGroupFilter) return;

	// now go through all children

	CComPtr<IXMLDOMNodeList> pChildren;
	pGroupFilter->get_childNodes( &pChildren);	
	if (!pChildren) return;

	long nb = 0;
	pChildren->get_length(&nb);
	
	for (long i=0; i<nb; i++)
	{

		CComPtr<IXMLDOMNode> pNode;
		pChildren->get_item(i,&pNode);
		if (pNode)
		{
			CComQIPtr<IXMLDOMElement> pElem( pNode );

			CString szNodename;
			getNodeName(pElem, szNodename);

			// is it a file or a filter ?
			//
			if ( szNodename.CompareNoCase(XMLNODE_FILE) )
			{
				CString szFilename;

				// attribute Filter
				getAttribValue(pElem,XMLATTRIB_RELATIVEPATH,szFilename);

				if (szFilename.IsEmpty()) // try absolute path instead
					getAttribValue(pElem,XMLATTRIB_FULLPATH,szFilename);

				if (szFilename.Find(0,' ')>-1)
					szFilename = "\"" + szFilename + "\"";

				s = "# Begin Source File\r\n\r\n";
				s += "SOURCE=" + szFilename + "\r\n";
				m_outputFile.Write(s);

				// now we need to check the custom configs
				//
				ConfigurationArray arrFileConfigs;
				extractFileConfigurations(pElem, arrFileConfigs);
				writeDspFileConfigurations(szFilename, arrFileConfigs, m_arrConfigs);

				s = "# End Source File\r\n";
				m_outputFile.Write(s);

			}
			else if ( szNodename.CompareNoCase(XMLNODE_FILTER) )// it is a filter
			{
				//
				s = "# Begin Group \"";

				CString szFilterName, szFilter;

				// attribute Name
				getAttribValue(pElem,XMLATTRIB_NAME,szFilterName);

				// attribute Filter
				getAttribValue(pElem,XMLNODE_FILTER,szFilter);

				s += szFilterName + "\"\r\n\r\n";
				m_outputFile.Write(s);

				s = "# PROP Default_Filter \"" + szFilter + "\"\r\n";
				m_outputFile.Write(s);

				// manage all files inside
				//
				writeDspGroup(pElem);

				// finish group of files
				s = "# End Group\r\n";
				m_outputFile.Write(s);
			}
				
		} // end if pNode

	} // end for
}


void vcprojprocess::writeDspFileConfigurations(CString &szFilename, ConfigurationArray &arrFileConfigs, ConfigurationArray &projectConfigs)
{

	// make sure we have anything to output here
	long nConfigNb = arrFileConfigs.GetSize();
	if (nConfigNb==0) return;

	CString s;

	for (long i=0; i<nConfigNb; i++)
	{
		if (i==0)
			s = "\r\n!IF  \"$(CFG)\" == \"";
		else
			s = "!ELSEIF  \"$(CFG)\" == \"";

		vcprojconfiguration *pConfig = arrFileConfigs.GetAt(i);

		CString szConfigName = pConfig->getConfigName();

		s += TranslateConfigurationName( szConfigName ) + "\"\r\n\r\n";

		m_outputFile.Write(s);


		// do we have an intermediate directory
		// 
		CString szIntermediateDirectory;
		szIntermediateDirectory = pConfig->VCCLCompilerTool.GetValue("ObjectFile");
		if (!szIntermediateDirectory.IsEmpty())
		{
			s = "# PROP Intermediate_Dir \"" + szIntermediateDirectory + "\"\r\n";
			m_outputFile.Write(s);
		}


		// do we exclude this file from the build ?
		//
		if ( pConfig->General.GetValue("ExcludedFromBuild").CompareNoCase("TRUE") )
		{
			s = "# PROP Exclude_From_Build 1\r\n\r\n";
			m_outputFile.Write(s);
		}
		else // do we have a custom build, or any standard build tool ?
		{

			// find the equivalent project configuration
			// (debug project configuration, if this file configuration is debug)
			long nbProjConfigs = projectConfigs.GetSize();
			BOOL bFound = FALSE;
			vcprojconfiguration *pProjConfig = NULL;
			for (long iP=0; iP<projectConfigs.GetSize() && !bFound; iP++)
			{
				pProjConfig = projectConfigs.GetAt(iP);
				if (pProjConfig)
				{
					s = pProjConfig->getConfigName();;
					bFound = ( s.CompareNoCase(szConfigName) );
				}
			}
			pConfig->setMasterProjConfigurations( bFound ? pProjConfig : NULL );


			if (pConfig->VCCustomBuildTool.GetValue("Name").IsEmpty()) // standard build
			{

				if ( !pConfig->VCCLCompilerTool.GetValue("Name").IsEmpty() )
				{
					// build compiling symbols line
					//
					CString szCPPSymbols = pConfig->serializeCPPSymbols(TRUE);
					int nPrcmpHeadersTag;
					if ( (nPrcmpHeadersTag=szCPPSymbols.Find(0,"PRECOMP_VC7_TOBEREMOVED"))>-1 )
					{
						szCPPSymbols = szCPPSymbols.Left(nPrcmpHeadersTag) + szCPPSymbols.ExcludeLeft(nPrcmpHeadersTag+strlen("PRECOMP_VC7_TOBEREMOVED")+1);

						s = "# ADD CPP " + szCPPSymbols + "\r\n";
						s += "# SUBTRACT CPP /YX /Yc /Yu\r\n";
					}
					else
						s = "# ADD CPP " + szCPPSymbols + "\r\n";

					m_outputFile.Write(s);
				}
				else if ( !pConfig->VCResourceCompilerTool.GetValue("Name").IsEmpty() )
				{
					// build ResourceCompiler symbol line
					//
					CString szResourceSymbols = pConfig->serializeResourceSymbols(TRUE);
					s = "# ADD RSC " + szResourceSymbols + "\r\n";
					m_outputFile.Write(s);
				}
				else if ( !pConfig->VCMidlTool.GetValue("Name").IsEmpty() )
				{
					// build Midl symbol line
					//
					CString szMidlSymbols = pConfig->serializeMidlSymbols(TRUE);
					s = "# ADD MTL " + szMidlSymbols + "\r\n";
					m_outputFile.Write(s);
				}

			}
			else // custom build
			{
				s = "# PROP Ignore_Default_Tool 1\r\n";
				m_outputFile.Write(s);


				// build CustomBuild cmd line
				//
				CString szCustomBuildDescription;
				ArrayCString arrCustomBuildCommands;
				ArrayCString arrCustomOutputFiles;
				ArrayCString arrAdditionalDeps;
				pConfig->serializeCustomBuildCommands(	szCustomBuildDescription, 
														arrCustomBuildCommands,
														arrCustomOutputFiles,
														arrAdditionalDeps,
														TRUE);


				// custom build (optional)
				if ( arrCustomBuildCommands.GetSize()>0 )
				{
					long j;

					// write user deps
					if (arrAdditionalDeps.GetSize()>0)
					{
						s = "USERDEP_FILE=";

						for (j=0; j<arrAdditionalDeps.GetSize(); j++)
						{
							s += "\"";
							s += arrAdditionalDeps.GetAt(j);
							s += "\"\t";
						}
						s += "\r\n";
						m_outputFile.Write(s);
					}

					s = "# Begin Custom Build - " + szCustomBuildDescription + "\r\n";
					m_outputFile.Write(s);
					s = "SOURCE=\"$(InputPath)\"\r\n"; // don't know why VC++ 6.0 needs this
					m_outputFile.Write(s);
					s = "\r\nBuildCmds= \\\r\n";
					m_outputFile.Write(s);

					for (j=0; j<arrCustomBuildCommands.GetSize(); j++)
					{
						s = "\t";
						s += arrCustomBuildCommands.GetAt(j);
						s += " \\\r\n";
						m_outputFile.Write(s);
					}
					s = "\r\n";
					m_outputFile.Write(s);

					for (j=0; j<arrCustomOutputFiles.GetSize(); j++)
					{
						s = "\r\n\"";
						s += arrCustomOutputFiles.GetAt(j);
						s += "\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\r\n";
						s += "   $(BuildCmds)\r\n";
						m_outputFile.Write(s);
					}

					s = "# End Custom Build\r\n";
					m_outputFile.Write(s);

					s = "\r\n";
					m_outputFile.Write(s);
				}



			}

		}

	}

	s = "!ENDIF\r\n\r\n";
	m_outputFile.Write(s);

}

void vcprojprocess::writeDspFooter()
{
	CString s ="# End Target\r\n";
	m_outputFile.Write(s);
	s = "# End Project\r\n\r\n";
	m_outputFile.Write(s);
}

// isFullPath -------------------------------
//
// purpose : tells if 'szFilepath' is a fully qualified filepath, or a relative path
BOOL vcprojprocess::isFullPath(CString &szFilepath)
{
	BOOL bResult = TRUE;

	// extract directory
	long i = m_szSolutionName.ReverseFind(0, '\\');
	if (i==-1) 
		return FALSE;

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


void vcprojprocess::getAttribValue(/*in*/IXMLDOMElement *p, /*in*/char *szAttribName, /*out*/CString &szValue)
{
	szValue.Empty();
	if (!p) return;

	VARIANT vtValue;
	p->getAttribute( _bstr_t(szAttribName), &vtValue);
	VARIANT_to_CString( vtValue, szValue);
}

void vcprojprocess::getNodeName(/*in*/IXMLDOMElement *p, /*out*/CString &szName)
{
	szName.Empty();
	if (!p) return;

	BSTR bstrName;
	p->get_nodeName(&bstrName);
	BSTR_to_CString(bstrName,szName);
}


void vcprojprocess::VARIANT_to_CString(/*in*/VARIANT &vt, /*out*/CString &s)
{
	s.Empty();

	if (vt.vt!=VT_BSTR) return;

	_bstr_t bstrTag(vt);

	UINT uLen = bstrTag.length();
	if (uLen==0) return;

	TCHAR *szTemp= new TCHAR[uLen+1];
	memset (szTemp, 0, uLen+1);

	LPOLESTR wszTag = bstrTag; // get ptr to Unicode

	int iBytes = ::WideCharToMultiByte(CP_ACP, 0,
			wszTag, uLen,
			szTemp, uLen, NULL, NULL);

	s = szTemp;

	delete [] szTemp;

	::SysFreeString(vt.bstrVal);
}


void vcprojprocess::BSTR_to_CString(/*in*/BSTR bstr, /*out*/CString &s)
{
	s.Empty();

	_bstr_t bstrTag(bstr);

	UINT uLen = bstrTag.length();
	if (uLen==0) return;

	TCHAR *szTemp= new TCHAR[uLen+1];
	memset (szTemp, 0, uLen+1);

	LPOLESTR wszTag = bstrTag; // get ptr to Unicode

	int iBytes = ::WideCharToMultiByte(CP_ACP, 0,
			wszTag, uLen,
			szTemp, uLen, NULL, NULL);

	s = szTemp;

	delete [] szTemp;

	::SysFreeString(bstr);
}

CString vcprojprocess::TranslateConfigurationName(CString &sInputConfigName)
{
	CString s;
	s = m_szProjname + " - ";

	long i = sInputConfigName.Find(0,'|');
	if (i>-1)
	{
		CString sConfig = sInputConfigName.Left(i);
		CString sPlatform = sInputConfigName.ExcludeLeft(i+1);
		s += sPlatform + " " + sConfig;
	}
	else
		s += sInputConfigName;

	return s;
}

CString vcprojprocess::ExtractPlatform(CString &sInputConfigName)
{
	CString s;
	long i = sInputConfigName.Find(0,'|');
	if (i>-1)
		s= sInputConfigName.ExcludeLeft(i+1);

	return s;
}


void vcprojprocess::TokenizeString(/*in*/CString &szInput, char cToken, /*out*/ArrayCString &arrStrings)
{
	long i;

	CString s = szInput;

	arrStrings.RemoveAll();

	while ( (i=s.Find(0,cToken))>-1 )
	{
		arrStrings.Add( s.Left(i) );
		s = s.ExcludeLeft(i+1);
	}
	if (!s.IsEmpty())
		arrStrings.Add ( s );
}


void vcprojprocess::UntokenizeString(/*in*/ArrayCString &arrStrings, char cToken, /*out*/CString &szOutput)
{
	szOutput.Empty();

	for (long i=0;i<arrStrings.GetSize(); i++)
	{
		if (!szOutput.IsEmpty()) szOutput += cToken;

		szOutput += arrStrings.GetAt(i);
	}
}

void __stdcall _com_issue_error(HRESULT)
{
}
