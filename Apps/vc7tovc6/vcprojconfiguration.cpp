
/////////////////////////////////////////////////////////////////////////////////
//
// vcprojconfiguration class implementation
//
// S.Rodriguez - Sept 2002
//
//
// purpose : fill class members with actual configuration data from the .vcproj file
//
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
#include "symbols.h"
#include "vcprojconfiguration.h"



vcprojconfiguration::vcprojconfiguration()
{
	setMasterProjConfigurations(NULL);
}

// Accessors


void vcprojconfiguration::setMasterProjConfigurations(vcprojconfiguration *p) // used for FileConfiguration
{
	m_cpParentConfigurations = p;
}

CString vcprojconfiguration::getConfigName()
{
	CString s;

	s = General.GetValue(XMLATTRIB_NAME);

	return s;
}

BOOL vcprojconfiguration::hasVCConfigTool(CString &szToolName)
{
	if (szToolName.CompareNoCase(VCCOMPILERTOOL))
		return VCCLCompilerTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCLIBRARIANTOOL))
		return VCLibrarianTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCLINKERTOOL))
		return VCLinkerTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCRESOURCECOMPILERTOOL))
		return VCResourceCompilerTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCMIDLTOOL))
		return VCMidlTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCBSCMAKETOOL))
		return VCBscMakeTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCPREBUILDEVENTTOOL))
		return VCPreBuildEventTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCPRELINKEVENTTOOL))
		return VCPreLinkEventTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCPOSTBUILDEVENTTOOL))
		return VCPostBuildEventTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCCUSTOMBUILDTOOL))
		return VCCustomBuildTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCNMAKETOOL))
		return VCNMakeTool.GetValue(XMLATTRIB_NAME).GetLength()>0;
	else if (szToolName.CompareNoCase(VCDEBUGSETTINGSTOOL))
		return VCDebugSettingsTool.GetValue(XMLATTRIB_NAME).GetLength()>0;

	return FALSE;
}


void vcprojconfiguration::fill(/*in*/IXMLDOMElement *p) // fill class members
{
	if (!p) return; // good bye!

	// first of all, store all attribute names/values in the "General" member
	//
	fillFromAttributes(p, General);

	// then proceed, with all <Tool> occurences
	//
	CComPtr<IXMLDOMNodeList> pTools;
	p->getElementsByTagName( _bstr_t(XMLNODE_TOOL), &pTools);
    if (pTools)
	{

		long nb = 0;
		pTools->get_length(&nb);

		for (long i=0; i<nb; i++)
		{
			CComPtr<IXMLDOMNode> pToolNode;
			pTools->get_item(i,&pToolNode);
			if (pToolNode)
			{
				CComQIPtr<IXMLDOMElement> pTool( pToolNode );

				CString szToolName;
				getAttribValue(pTool, XMLATTRIB_NAME, szToolName);
				if (szToolName.CompareNoCase(VCCOMPILERTOOL))
					fillFromAttributes(pTool, VCCLCompilerTool);
				else if (szToolName.CompareNoCase(VCLIBRARIANTOOL))
					fillFromAttributes(pTool, VCLibrarianTool);
				else if (szToolName.CompareNoCase(VCLINKERTOOL))
					fillFromAttributes(pTool, VCLinkerTool);
				else if (szToolName.CompareNoCase(VCRESOURCECOMPILERTOOL))
					fillFromAttributes(pTool, VCResourceCompilerTool);
				else if (szToolName.CompareNoCase(VCMIDLTOOL))
					fillFromAttributes(pTool, VCMidlTool);
				else if (szToolName.CompareNoCase(VCBSCMAKETOOL))
					fillFromAttributes(pTool, VCBscMakeTool);
				else if (szToolName.CompareNoCase(VCPREBUILDEVENTTOOL))
					fillFromAttributes(pTool, VCPreBuildEventTool);
				else if (szToolName.CompareNoCase(VCPRELINKEVENTTOOL))
					fillFromAttributes(pTool, VCPreLinkEventTool);
				else if (szToolName.CompareNoCase(VCPOSTBUILDEVENTTOOL))
					fillFromAttributes(pTool, VCPostBuildEventTool);
				else if (szToolName.CompareNoCase(VCCUSTOMBUILDTOOL))
					fillFromAttributes(pTool, VCCustomBuildTool);
				else if (szToolName.CompareNoCase(VCNMAKETOOL))
					fillFromAttributes(pTool, VCNMakeTool);
				else if (szToolName.CompareNoCase(VCDEBUGSETTINGSTOOL))
					fillFromAttributes(pTool, VCDebugSettingsTool);

			}
		}
	} // end if (pTools)

}

void vcprojconfiguration::fillFromAttributes(/*in*/IXMLDOMElement *p, /*out*/FindableArray &arrAttribs)
{
	CComPtr<IXMLDOMNamedNodeMap> pAttributes;
	p->get_attributes(&pAttributes);
	if (pAttributes)
	{
		long nbAttribs = 0;
		pAttributes->get_length(&nbAttribs);

		for (long i=0; i<nbAttribs; i++)
		{

			CComPtr<IXMLDOMNode> pAttrib;
			pAttributes->get_item(i,&pAttrib);
			if (pAttrib)
			{
				BSTR bstrName;
				pAttrib->get_nodeName(&bstrName);
				CString szName;
				BSTR_to_CString(bstrName,szName);

				VARIANT vtValue;
				pAttrib->get_nodeValue( &vtValue);
				CString szValue;
				VARIANT_to_CString( vtValue, szValue);

				// add this name/value pair
				if (!szName.IsEmpty())
				{
					SINGLEVALUEPARAM *p = new SINGLEVALUEPARAM();
					if (p)
					{
						p->szName = szName;
						p->szValue = szValue;
					}

					arrAttribs.Add( p );
				}

			}
		}
	} // end if (pAttributes)

}








CString vcprojconfiguration::serializeCPPSymbols(BOOL bFileConfiguration)
{
	long i;
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//
	CString szAdditionalIncludeDirectories;
	ArrayCString arrAdditionalIncludeDirectories;
	s = VCCLCompilerTool.GetValue("AdditionalIncludeDirectories");
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrAdditionalIncludeDirectories); // parse comma-separated path
	else 
		TokenizeString(s,';',arrAdditionalIncludeDirectories); // or parse semi-colon-separated path

	for (i=0; i<arrAdditionalIncludeDirectories.GetSize(); i++)
	{
		CString szDirectory = arrAdditionalIncludeDirectories.GetAt(i);
		if ( !szDirectory.CompareNoCase("$(NOINHERIT)") )
			szAdditionalIncludeDirectories += "/I \"" + szDirectory + "\" ";
	}


	CString szDebugInformationFormat;
	s = VCCLCompilerTool.GetValue("DebugInformationFormat");
	if (s.CompareNoCase("1"))
		szDebugInformationFormat = "/Z7 ";
	else if (s.CompareNoCase("2"))
		szDebugInformationFormat = "/Zd ";
	else if (s.CompareNoCase("3"))
		szDebugInformationFormat = "/Zi ";
	else if (s.CompareNoCase("4"))
		szDebugInformationFormat = "/ZI ";

	CString szSuppressStartupBanner = "/nologo "; // default VC7 behaviour is "suppress banner"
	if ( VCCLCompilerTool.GetValue("SuppressStartupBanner").CompareNoCase("FALSE") )
		szSuppressStartupBanner.Empty();

	CString szWarningLevel;
	s = VCCLCompilerTool.GetValue("WarningLevel");
	if (s.CompareNoCase("0") || s.CompareNoCase("1") || s.CompareNoCase("2") || s.CompareNoCase("3") || s.CompareNoCase("4"))
	{
		szWarningLevel = "/W" + s + " ";
	}

	CString szWarnAsError;
	if ( VCCLCompilerTool.GetValue("WarnAsError").CompareNoCase("TRUE") )
		szWarnAsError += "/WX ";


	// -- optimization tab
	//
	CString szOptimization;
	s = VCCLCompilerTool.GetValue("Optimization");
	if (s.CompareNoCase("0"))
		szOptimization = "/Od "; // disabled
	else if (s.CompareNoCase("1"))
		szOptimization = "/O1 "; // minimize size
	else if (s.CompareNoCase("2"))
		szOptimization = "/O2 "; // maximize speed
	else if (s.CompareNoCase("3"))
		szOptimization = "/Ox "; // combined optim (/Ob1 /Og /Oi /Ot /Oy /Gs)

	CString szGlobalOptimizations;
	if ( VCCLCompilerTool.GetValue("GlobalOptimizations").CompareNoCase("TRUE") )
		szGlobalOptimizations = "/Og ";
		
	CString szInlineFunctionExpansion; // disabled (/Ob0 is useless because it is the default VC++ 6.0 value)
	s = VCCLCompilerTool.GetValue("InlineFunctionExpansion");
	if (s.CompareNoCase("1"))
		szInlineFunctionExpansion = "/Ob1 "; // only __inline
	else if (s.CompareNoCase("2"))
		szInlineFunctionExpansion = "/Ob2 "; // any suitable

	CString szEnableIntrinsicFunctions;
	if ( VCCLCompilerTool.GetValue("EnableIntrinsicFunctions").CompareNoCase("TRUE") )
		szEnableIntrinsicFunctions = "/Oi ";

	CString szImproveFloatingPointConsistency;
	if ( VCCLCompilerTool.GetValue("ImproveFloatingPointConsistency").CompareNoCase("TRUE") )
		szImproveFloatingPointConsistency = "/Op ";

	CString szFavorSizeOrSpeed;
	s = VCCLCompilerTool.GetValue("FavorSizeOrSpeed");
	if (s.CompareNoCase("1"))
		szFavorSizeOrSpeed = "/Ot "; // favor speed
	else if (s.CompareNoCase("2"))
		szFavorSizeOrSpeed = "/Os "; // favor size

	CString szOmitFramePointers;
	if ( VCCLCompilerTool.GetValue("OmitFramePointers").CompareNoCase("TRUE") )
		szOmitFramePointers = "/Oy ";

	CString szEnableFiberSafeOptimizations;
	if ( VCCLCompilerTool.GetValue("EnableFiberSafeOptimizations").CompareNoCase("TRUE") )
		szEnableFiberSafeOptimizations = "/GT ";

	CString szOptimizeForProcessor;
	s = VCCLCompilerTool.GetValue("OptimizeForProcessor");
	if (s.CompareNoCase("1"))
		szOptimizeForProcessor = "/G5 "; // for Pentium
	else if (s.CompareNoCase("2"))
		szOptimizeForProcessor = "/G6 "; // for Pentium Pro

	CString szOptimizeForWindowsApplication;
	if ( VCCLCompilerTool.GetValue("OptimizeForWindowsApplication").CompareNoCase("TRUE") )
		szOptimizeForWindowsApplication = "/GA ";


	// -- preprocessor tab
	//
	s = VCCLCompilerTool.GetValue("PreprocessorDefinitions");

	CString szPreprocessorDefs;
	ArrayCString arrPreprocessorDefs;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrPreprocessorDefs); // parse comma-separated symbols
	else 
		TokenizeString(s,';',arrPreprocessorDefs); // or parse semi-colon-separated symbols

	for (i=0; i<arrPreprocessorDefs.GetSize(); i++)
	{
		CString szSymbol = arrPreprocessorDefs.GetAt(i);
		if ( !szSymbol.CompareNoCase("$(NOINHERIT)") )
			szPreprocessorDefs += "/D \"" + szSymbol + "\" ";

		// if we see the _AFXEXT symbol, then don't forget to add the _WINDLL too
		if ( szSymbol.CompareNoCase("_AFXEXT") )
			szPreprocessorDefs += "/D \"_WINDLL\" ";
	}

	// special treatment if we are using shared MFC
	// (we have to add this symbol by hand, because in VC++7 this symbol is inherited instead of explicit)
	if ( General.GetValue("UseOfMFC").CompareNoCase("2") )
	{
		szPreprocessorDefs += "/D \"_AFXDLL\" "; // MFC dynamically linked
	}

	// special treatment if we are using shared ATL		
	// (we have to add this symbol by hand, because in VC++7 this symbol is inherited instead of explicit)
	if ( General.GetValue("UseOfATL").CompareNoCase("2") )
	{
		// ATL dynamically linked (see msdev atl source code)
		szPreprocessorDefs += "/D \"_ATL_DLL\" ";
	}

	// special treatment if we are using a specific charset
	// (we have to add this symbol by hand, because in VC++7 this symbol is inherited instead of explicit)
	CString szMBCSSymbol;
	s = General.GetValue("CharacterSet");
	if (s.CompareNoCase("1"))
		szMBCSSymbol = "_UNICODE"; // 16-bit chars
	else if (s.CompareNoCase("2"))
		szMBCSSymbol = "_MBCS"; // standard multi-byte chars (local charset)
	if (!szMBCSSymbol.IsEmpty())
	{
		szPreprocessorDefs += "/D \"" + szMBCSSymbol + "\" ";
	}

	CString szIgnoreStandardIncludePath;
	if ( VCCLCompilerTool.GetValue("IgnoreStandardIncludePath").CompareNoCase("TRUE") )
		szIgnoreStandardIncludePath = "/X ";

	CString szGeneratePreprocessedFile;
	s = VCCLCompilerTool.GetValue("GeneratePreprocessedFile");
	if (s.CompareNoCase("1"))
		szGeneratePreprocessedFile = "/P "; // with #lines
	else if (s.CompareNoCase("2"))
		szGeneratePreprocessedFile = "/EP "; // without #lines

	CString szKeepComments;
	if ( VCCLCompilerTool.GetValue("KeepComments").CompareNoCase("TRUE") )
		szKeepComments = "/C ";


	// -- code generation tab
	//

	CString szStringPooling;
	if ( VCCLCompilerTool.GetValue("StringPooling").CompareNoCase("TRUE") )
		szStringPooling = "/GF ";

	CString szMinimalRebuild;
	if ( VCCLCompilerTool.GetValue("MinimalRebuild").CompareNoCase("TRUE") )
		szMinimalRebuild = "/Gm ";

	CString szExceptionHandling;
	if ( VCCLCompilerTool.GetValue("ExceptionHandling").CompareNoCase("TRUE") )
		szExceptionHandling = "/EHsc ";

	CString szRuntimeLibrary;
	s = VCCLCompilerTool.GetValue("RuntimeLibrary");
	if (s.CompareNoCase("0"))
		szRuntimeLibrary = "/MT "; // MultiThreaded
	else if (s.CompareNoCase("1"))
		szRuntimeLibrary = "/MTd "; // MultiThreadedDebug
	else if (s.CompareNoCase("2"))
		szRuntimeLibrary = "/MD "; // MultiThreadedDLL
	else if (s.CompareNoCase("3"))
		szRuntimeLibrary = "/MDd "; // MultiThreadedDebugDLL
	else if (s.CompareNoCase("4"))
		szRuntimeLibrary = "/ML "; // SingleThreaded
	else if (s.CompareNoCase("5"))
		szRuntimeLibrary = "/MLd "; // SingleThreadedDebug
	// of course, at this point, if we are in a Release config, and we see runtimelibrary=1,3 or 5 then there is a problem


	CString szStructMemberAlignment;
	s = VCCLCompilerTool.GetValue("StructMemberAlignment");
	if (s.CompareNoCase("1"))
		szStructMemberAlignment = "/Zp1 "; // 1-byte alignment
	else if (s.CompareNoCase("2"))
		szStructMemberAlignment = "/Zp2 "; // 2-byte alignment
	else if (s.CompareNoCase("3"))
		szStructMemberAlignment = "/Zp4 "; // 4-byte alignment
	else if (s.CompareNoCase("4"))
		szStructMemberAlignment = "/Zp8 "; // 8-byte alignment
	else if (s.CompareNoCase("5"))
		szStructMemberAlignment = "/Zp16 "; // 16-byte alignment

	CString szEnableFunctionLevelLinking;
	if ( VCCLCompilerTool.GetValue("EnableFunctionLevelLinking").CompareNoCase("TRUE") )
		szEnableFunctionLevelLinking = "/Gy ";


	// -- language tab
	//
	CString szDisableLanguageExtensions;
	if ( VCCLCompilerTool.GetValue("DisableLanguageExtensions").CompareNoCase("TRUE") )
		szDisableLanguageExtensions = "/Za ";

	CString szDefaultCharIsUnsigned;
	if ( VCCLCompilerTool.GetValue("DefaultCharIsUnsigned").CompareNoCase("TRUE") )
		szDefaultCharIsUnsigned = "/J ";

	CString szRuntimeTypeInfo;
	if ( VCCLCompilerTool.GetValue("RuntimeTypeInfo").CompareNoCase("TRUE") )
		szRuntimeTypeInfo = "/GR ";


	// -- precompiled headers tab
	//

	CString szUsePrecompiledHeader;
	s = VCCLCompilerTool.GetValue("UsePrecompiledHeader");
	if (s.CompareNoCase("1"))
	{
		s = VCCLCompilerTool.GetValue("PrecompiledHeaderThrough");
		if (s.IsEmpty()) s = "stdafx.h";  // default VC7 precompiled harder

		szUsePrecompiledHeader = "/Yc\"" + s + "\" "; // create precompiled headers

		// specific code for file configuration
		if (bFileConfiguration && 
			VCCLCompilerTool.GetValue("PrecompiledHeaderThrough").IsEmpty() &&
			m_cpParentConfigurations)
		{
			s = m_cpParentConfigurations->VCCLCompilerTool.GetValue("PrecompiledHeaderThrough");
			if (s.IsEmpty()) s = "stdafx.h"; // default VC7 precompiled harder
			szUsePrecompiledHeader = "/Yc\"" + s + "\" "; // create precompiled headers
		}

	}
	else if (s.CompareNoCase("2"))
		szUsePrecompiledHeader = "/YX "; // auto
	else if (s.CompareNoCase("3"))
	{
		s = VCCLCompilerTool.GetValue("PrecompiledHeaderThrough");
		if (s.IsEmpty()) s = "stdafx.h";  // default VC7 precompiled harder

		szUsePrecompiledHeader = "/Yu\"" + s + "\" "; // use

		// specific code for file configuration
		if (bFileConfiguration && 
			VCCLCompilerTool.GetValue("PrecompiledHeaderThrough").IsEmpty() &&
			m_cpParentConfigurations)
		{
			s = m_cpParentConfigurations->VCCLCompilerTool.GetValue("PrecompiledHeaderThrough");
			if (s.IsEmpty()) s = "stdafx.h"; // default VC7 precompiled harder
			szUsePrecompiledHeader = "/Yu\"" + s + "\" "; // use precompiled headers
		}
	}
	else if (s.CompareNoCase("0"))
	{
		szUsePrecompiledHeader = "PRECOMP_VC7_TOBEREMOVED ";
	}
	else if (bFileConfiguration)
	{
		// for individual files, VC7 may actually use precompiled headers
		// without even signaling it in the .vcproj settings
		// The only thing we know is the parent configuration setting has UsePrecompiledHeader=3
		if (m_cpParentConfigurations && 
			m_cpParentConfigurations->VCCLCompilerTool.GetValue("UsePrecompiledHeader").CompareNoCase("3") )
			szUsePrecompiledHeader = "/Yu\"stdafx.h\" "; // use default VC7 precompiled headers
	}

	CString szPrecompiledHeaderFile;
	s = VCCLCompilerTool.GetValue("PrecompiledHeaderFile");
	if (!s.IsEmpty())
	{
		szPrecompiledHeaderFile = "/Fp\"" + s + "\" ";
	}


	// -- output tab
	//

	CString szAssemblerOutput;
	s = VCCLCompilerTool.GetValue("AssemblerOutput");
	CString szAssemblerListingLocation = "/Fa\"";
	szAssemblerListingLocation += VCCLCompilerTool.GetValue("AssemblerListingLocation");
	szAssemblerListingLocation += "\" ";
	if (s.CompareNoCase("1"))
	{
		szAssemblerOutput = "/FA " + szAssemblerListingLocation; // assembly only (.asm)
	}
	else if (s.CompareNoCase("2"))
	{
		szAssemblerOutput = "/FAcs " + szAssemblerListingLocation; // assembly + machine + source code (.asm + .cod)
	}
	else if (s.CompareNoCase("3"))
	{
		szAssemblerOutput = "/FAc " + szAssemblerListingLocation; // machine code (.cod)
	}
	else if (s.CompareNoCase("4"))
	{
		szAssemblerOutput = "/FAs " + szAssemblerListingLocation; // source code (.cod)
	}

	CString szObjectFile;
	s = VCCLCompilerTool.GetValue("ObjectFile");
	if (!s.IsEmpty())
	{
		szObjectFile = "/Fo\"" + s + "\" ";
	}

	CString szProgramDataBaseFileName;
	s = VCCLCompilerTool.GetValue("ProgramDataBaseFileName");
	if (!s.IsEmpty())
	{
		szProgramDataBaseFileName = "/Fd\"" + s + "\" ";
	}


	// -- browse information tab (generate .sbr files)
	//


	CString szBrowseInformation;
	CString szBrowseInformationFile;
	s = VCCLCompilerTool.GetValue("BrowseInformationFile");
	if (!s.IsEmpty())
	{
		szBrowseInformationFile = "\"" + s + "\"";
	}
	s = VCCLCompilerTool.GetValue("BrowseInformation");
	if (s.CompareNoCase("1"))
	{// browse all infos
		szBrowseInformation = "/FR" + szBrowseInformationFile + " ";
	}
	else if (s.CompareNoCase("2"))
	{// browse all except local infos
		szBrowseInformation = "/Fr" + szBrowseInformationFile + " ";
	}

	// -- advanced tab
	//
	
	CString szCallingConvention;
	s = VCCLCompilerTool.GetValue("CallingConvention");
	if (s.CompareNoCase("0"))
		szCallingConvention = "/Gd "; // __cdecl
	else if (s.CompareNoCase("1"))
		szCallingConvention = "/Gr "; // __fastcall
	else if (s.CompareNoCase("2"))
		szCallingConvention = "/Gz "; // __stdcall

	CString szCompileAs;
	s = VCCLCompilerTool.GetValue("CompileAs");
	if (s.CompareNoCase("1"))
		szCompileAs = "/TC "; // compile as C file
	else if (s.CompareNoCase("2"))
		szCompileAs = "/TP "; // compile as C++ file


	s = VCCLCompilerTool.GetValue("ForcedIncludeFiles");
	CString szForceIncludeFiles;
	ArrayCString arrForceIncludeFiles;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrForceIncludeFiles); // parse comma-separated filenames
	else 
		TokenizeString(s,';',arrForceIncludeFiles); // or parse semi-colon-separated filenames

	for (i=0; i<arrForceIncludeFiles.GetSize(); i++)
	{
		szForceIncludeFiles += "/FI\"" + arrForceIncludeFiles.GetAt(i) + "\" ";
	}


	CString szUndefineAllPreprocessorDefinitions;
	if ( VCCLCompilerTool.GetValue("UndefineAllPreprocessorDefinitions").CompareNoCase("TRUE") )
		szUndefineAllPreprocessorDefinitions = "/u ";


	s = VCCLCompilerTool.GetValue("UndefinePreprocessorDefinitions");
	CString szUndefPrepDefs;
	ArrayCString arrUndefPrepDefs;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrUndefPrepDefs); // parse comma-separated symbols
	else 
		TokenizeString(s,';',arrUndefPrepDefs); // or parse semi-colon-separated symbols

	for (i=0; i<arrUndefPrepDefs.GetSize(); i++)
	{
		szUndefPrepDefs += "/U \"" + arrUndefPrepDefs.GetAt(i) + "\" ";
	}

	// -- command line
	//

	CString szReleaseBuildErrors; 
	if ( getConfigName().Find(0,"Debug")>-1 ) // debug config ?
		szReleaseBuildErrors = "/GZ "; // fill stack with 0xCC chars if we are in a debug config


	CString szAdditionalOptions = VCCLCompilerTool.GetValue("AdditionalOptions");

	// add /GX (enable exception handling)
	// (VC7 reference says this option if enabled is in the cmdline, not presented with a checkbox)
	if (szAdditionalOptions.Find(0,"/GX")==-1)
		szAdditionalOptions += "/GX ";

	// mandatory
	CString szCompileWithoutLinking;
	if (!bFileConfiguration) szCompileWithoutLinking = "/c ";


	// concatenate everything to form the line
	szReturn = szSuppressStartupBanner;
	szReturn += szRuntimeLibrary;
	szReturn += szAdditionalIncludeDirectories;
	szReturn += szDebugInformationFormat;
	szReturn += szWarningLevel;
	szReturn += szWarnAsError;
	szReturn += szOptimization;
	szReturn += szGlobalOptimizations;
	szReturn += szInlineFunctionExpansion;
	szReturn += szEnableIntrinsicFunctions;
	szReturn += szImproveFloatingPointConsistency;
	szReturn += szFavorSizeOrSpeed;
	szReturn += szOmitFramePointers;
	szReturn += szEnableFiberSafeOptimizations;
	szReturn += szOptimizeForProcessor;
	szReturn += szOptimizeForWindowsApplication;
	szReturn += szPreprocessorDefs;
	szReturn += szIgnoreStandardIncludePath;
	szReturn += szGeneratePreprocessedFile;
	szReturn += szKeepComments;
	szReturn += szStringPooling;
	szReturn += szMinimalRebuild;
	szReturn += szExceptionHandling;
	szReturn += szStructMemberAlignment;
	szReturn += szEnableFunctionLevelLinking;
	szReturn += szDisableLanguageExtensions;
	szReturn += szDefaultCharIsUnsigned;
	szReturn += szRuntimeTypeInfo;
	szReturn += szUsePrecompiledHeader;
	szReturn += szPrecompiledHeaderFile;
	szReturn += szAssemblerOutput;
	szReturn += szObjectFile;
	szReturn += szProgramDataBaseFileName;
	szReturn += szBrowseInformation;
	szReturn += szCallingConvention;
	szReturn += szCompileAs;
	szReturn += szForceIncludeFiles;
	szReturn += szUndefineAllPreprocessorDefinitions;
	szReturn += szUndefPrepDefs;
	szReturn += szReleaseBuildErrors;
	szReturn += szCompileWithoutLinking;
	szReturn += szAdditionalOptions;

	return szReturn;
}

CString vcprojconfiguration::serializeLinkerSymbols(BOOL bFileConfiguration)
{
	long i;
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//

	CString szDllOutput;
	if ( General.GetValue("ConfigurationType").CompareNoCase("2") )
		szDllOutput = "/dll ";


	CString szOutputFile = VCLinkerTool.GetValue("OutputFile");
	if (!szOutputFile.IsEmpty())
	{
		szOutputFile = "/out:\"" + ExpandMacros(szOutputFile) + "\" ";
	}


	CString szShowProgress;
	s = VCLinkerTool.GetValue("ShowProgress");
	if (s.CompareNoCase("1"))
		szShowProgress = "/verbose "; // full verbose
	else if (s.CompareNoCase("2"))
		szShowProgress = "/verbose:lib "; // search-lib verbose only
	
	CString szVersion = VCLinkerTool.GetValue("Version");
	if (!szVersion.IsEmpty())
	{
		szVersion = "/version:" + szVersion + " ";
	}

	CString szLinkIncremental;
	s = VCLinkerTool.GetValue("LinkIncremental");
	if (s.CompareNoCase("1"))
		szLinkIncremental = "/incremental:no "; // not incremental
	else if (s.CompareNoCase("2"))
		szLinkIncremental = "/incremental:yes "; // incremental


	CString szSuppressStartupBanner = "/nologo "; // default VC7 behaviour is "suppress banner"
	if ( VCLinkerTool.GetValue("SuppressStartupBanner").CompareNoCase("FALSE") )
		szSuppressStartupBanner.Empty();


	// "IgnoreImportLibrary" : ignored because does not exist in VC++ 6
	// Purpose : Tells the linker not to try to link any .lib output generated from this 
	// build into any dependent project. This allows the project system to handle .dll files 
	// that do not produce a .lib file when built. If a project is dependent on another 
	// project that produces a DLL, the project system automatically will link the .lib file 
	// produced by that child project. This may not be needed by projects that are producing 
	// COM DLLs or resource-only DLLs; these DLLs do not have any meaningful exports. If a 
	// DLL has no exports, the linker will not generate a .lib file. If no export .lib file 
	// is present on the disk, and the project system tells the linker to link with this 
	// (missing) DLL, the link will fail. 
	// Use Ignore Import Library to resolve this problem. When set to Yes, the project 
	// system will ignore the presence or absence of that .lib file and cause any project 
	// that is dependent on this project to not link with the nonexistent .lib file. 

	s = VCLinkerTool.GetValue("AdditionalLibraryDirectories");
	CString szAdditionalLibraryDirectories;
	ArrayCString arrAdditionalLibraryDirectories;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrAdditionalLibraryDirectories); // parse comma-separated path
	else 
		TokenizeString(s,';',arrAdditionalLibraryDirectories); // or parse semi-colon-separated path

	for (i=0; i<arrAdditionalLibraryDirectories.GetSize(); i++)
	{
		CString szLibraryDir = arrAdditionalLibraryDirectories.GetAt(i);
		if ( !szLibraryDir.CompareNoCase("$(NOINHERIT)") )
			szAdditionalLibraryDirectories += "/libpath:\"" + szLibraryDir + "\" ";
	}


	// -- input tab
	//

	CString szAdditionalDependencies = VCLinkerTool.GetValue("AdditionalDependencies");
	szAdditionalDependencies.ReplaceChar(';',' '); // replace semi-colons with spaces
	szAdditionalDependencies.ReplaceChar(',',' '); // replace commas with spaces
	if (!szAdditionalDependencies.IsEmpty()) szAdditionalDependencies += " ";

	// additional dependencies behave a bit different between VC7 and VC6
	// in VC7, default windows libraries (such as kernel32) are not even listed
	// in VC7, with a console app, the same.
	// whether win32 or console app, if MFC are used, then default libraries are not listed (not useful)
	szAdditionalDependencies = "kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib " \
		"ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib " + szAdditionalDependencies;


	CString szIgnoreAllDefaultLibraries;
	if ( VCLinkerTool.GetValue("IgnoreAllDefaultLibraries").CompareNoCase("TRUE") )
		szIgnoreAllDefaultLibraries = "/nodefaultlib "; // ignore all default libraries

	s = VCLinkerTool.GetValue("IgnoreDefaultLibraryNames");
	CString szIgnoreDefaultLibraryNames;
	ArrayCString arrIgnoreDefaultLibraryNames;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrIgnoreDefaultLibraryNames); // parse comma-separated names
	else 
		TokenizeString(s,';',arrIgnoreDefaultLibraryNames); // or parse semi-colon-separated names

	for (i=0; i<arrIgnoreDefaultLibraryNames.GetSize(); i++)
	{
		CString szDefaultLib = arrIgnoreDefaultLibraryNames.GetAt(i);
		if ( !szDefaultLib.CompareNoCase("$(NOINHERIT)") )
			szIgnoreDefaultLibraryNames += "/nodefaultlib:\"" + szDefaultLib + "\" ";
	}



	CString szModuleDefinitionFile = VCLinkerTool.GetValue("ModuleDefinitionFile");
	if (!szModuleDefinitionFile.IsEmpty())
	{
		szModuleDefinitionFile = "/def:\"" + szModuleDefinitionFile + "\" ";
	}

	s = VCLinkerTool.GetValue("ForceSymbolReferences");
	CString szForceSymbolReferences;
	ArrayCString arrForceSymbolReferences;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrForceSymbolReferences); // parse comma-separated symbols
	else if (s.Find(0,";")>-1)
		TokenizeString(s,';',arrForceSymbolReferences); // or parse semi-colon-separated symbols
	else 
		TokenizeString(s,' ',arrForceSymbolReferences); // or parse space-separated symbols

	for (i=0; i<arrForceSymbolReferences.GetSize(); i++)
	{
		CString szForceSymbol = arrForceSymbolReferences.GetAt(i);
		if ( !szForceSymbol.CompareNoCase("$(NOINHERIT)") )
			szForceSymbolReferences += "/include:\"" + szForceSymbol + "\" ";
	}

	s = VCLinkerTool.GetValue("DelayLoadDLLs");
	CString szDelayLoadDLLs;
	ArrayCString arrDelayLoadDLLs;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrDelayLoadDLLs); // parse comma-separated dllpath
	else 
		TokenizeString(s,';',arrDelayLoadDLLs); // or parse semi-colon-separated dllpath

	for (i=0; i<arrDelayLoadDLLs.GetSize(); i++)
	{
		CString szDelayLoad = arrDelayLoadDLLs.GetAt(i);
		if ( !szDelayLoad.CompareNoCase("$(NOINHERIT)") )
			szDelayLoadDLLs += "/delayload:\"" + szDelayLoad + "\" ";
	}


	// -- debug tab
	//

	CString szGenerateDebugInformation;
	if ( VCLinkerTool.GetValue("GenerateDebugInformation").CompareNoCase("TRUE") )
		szGenerateDebugInformation = "/debug "; // generate debug info

	CString szProgramDatabaseFile = VCLinkerTool.GetValue("ProgramDatabaseFile");
	if (!szProgramDatabaseFile.IsEmpty())
	{
		szProgramDatabaseFile = "/pdb:\"" + ExpandMacros(szProgramDatabaseFile) + "\" ";
	}

	CString szPdbSeparated = "/pdbtype:sept "; // separate pdbs
	if ( VCLinkerTool.GetValue("StripPrivateSymbols").CompareNoCase("FALSE") )
		szPdbSeparated.Empty();


	CString szGenerateMapFile;
	if ( VCLinkerTool.GetValue("GenerateMapFile").CompareNoCase("TRUE") )
	{
		szGenerateMapFile = VCLinkerTool.GetValue("MapFileName");
		if (!szGenerateMapFile.IsEmpty())
		{
			szGenerateMapFile = "/map:\"" + ExpandMacros(szGenerateMapFile) + "\" ";
		}
		else szGenerateMapFile = "/map ";

		if ( VCLinkerTool.GetValue("MapExports").CompareNoCase("TRUE") )
			szGenerateMapFile += "/mapinfo:exports ";
		else if ( VCLinkerTool.GetValue("MapLines").CompareNoCase("TRUE") )
			szGenerateMapFile += "/mapinfo:lines ";
	}


	// -- system tab
	//

	CString szSubSystem = "/subsystem:windows "; // generic windows app (entry point)
	if ( VCLinkerTool.GetValue("SubSystem").CompareNoCase("1") )
		szSubSystem = "/subsystem:console "; // console app (entry point)

	CString szHeapReserveCommitSize;
	s = VCLinkerTool.GetValue("HeapReserveSize");
	if (!s.IsEmpty())
	{
		szHeapReserveCommitSize = "/heap:" + s;

		s = VCLinkerTool.GetValue("HeapCommitSize");
		if (!s.IsEmpty())
		{
			szHeapReserveCommitSize += "," + s;
		}
		szHeapReserveCommitSize += " ";
	}
	
	CString szStackReserveCommitSize;
	s = VCLinkerTool.GetValue("StackReserveSize");
	if (!s.IsEmpty())
	{
		szStackReserveCommitSize = "/stack:" + s;

		s = VCLinkerTool.GetValue("StackCommitSize");
		if (!s.IsEmpty())
		{
			szStackReserveCommitSize += "," + s;
		}
		szStackReserveCommitSize += " ";
	}

	CString szLargeAddressAware;
	if ( VCLinkerTool.GetValue("LargeAddressAware").CompareNoCase("2") )
		szLargeAddressAware = "/largeaddressaware "; // >2GB process aware (see /3GB flag in boot.ini)

	CString szSwapRunFromCD;
	if ( VCLinkerTool.GetValue("SwapRunFromCD").CompareNoCase("TRUE") )
		szSwapRunFromCD = "/swaprun:cd "; // copies library from cd to local file system

	CString szSwapRunFromNET;
	if ( VCLinkerTool.GetValue("swSwapRunFromNET").CompareNoCase("TRUE") )
		szSwapRunFromNET = "/swaprun:net "; // copies library from net to local file system


	// -- optimization tab
	//

	CString szOptimizeReferences;
	s = VCLinkerTool.GetValue("OptimizeReferences");
	if (s.CompareNoCase("1"))
		szOptimizeReferences = "/opt:noref "; // no references optimization
	else if (s.CompareNoCase("2"))
		szOptimizeReferences = "/opt:ref "; // optimize references

	CString szEnableCOMDATFolding;
	s = VCLinkerTool.GetValue("EnableCOMDATFolding");
	if (s.CompareNoCase("1"))
		szEnableCOMDATFolding = "/opt:noicf "; // no COMDAT folding
	else if (s.CompareNoCase("2"))
		szEnableCOMDATFolding = "/opt:icf "; // COMDAT folding

	// ignore "OptimizeForWindows98" (not supported by VC++ 6)
	// Purpose : Align code on 4 KB boundaries. This improves performance on Windows 98 systems. 
	// Exposes the functionality of the /OPT:WIN98 linker option.

	CString szFunctionOrder = VCLinkerTool.GetValue("FunctionOrder");
	if (!szFunctionOrder.IsEmpty())
	{// renames all exported functions (by adding an underscore char as prefix, except decorated functions (@) )
		szFunctionOrder = "/order:@\"" + szFunctionOrder + "\" ";
	}


	// -- embedded IDL tab
	//

	// ignored (IDL attributes not supported in .cpp files with VC++6)
	// --> may raise issues with projects build using VC++7 project templates (ATL,...)
	//   (in this case, the user may create a separate .idl file and paste all interface declaration there)


	// -- advanced tab
	//

	CString szEntryPointSymbol = VCLinkerTool.GetValue("EntryPointSymbol");
	if (!szEntryPointSymbol.IsEmpty())
	{ // entry-point name (.dll or .exe)
		szEntryPointSymbol = "/entry:\"" + szEntryPointSymbol + "\" ";
	}

	CString szResourceOnlyDLL;
	if ( VCLinkerTool.GetValue("ResourceOnlyDLL").CompareNoCase("TRUE") )
		szResourceOnlyDLL = "/noentry "; // resource-only dll

	CString szSetChecksum;
	if ( VCLinkerTool.GetValue("SetChecksum").CompareNoCase("TRUE") )
		szSetChecksum = "/release "; // set checksum

	CString szBaseAddress = VCLinkerTool.GetValue("BaseAddress");
	if (!szBaseAddress.IsEmpty())
	{ // base address
		szBaseAddress = "/base:\"" + szBaseAddress + "\" ";
	}

	CString szSupportUnloadOfDelayLoadedDLL;
	if ( VCLinkerTool.GetValue("SupportUnloadOfDelayLoadedDLL").CompareNoCase("TRUE") )
		szSupportUnloadOfDelayLoadedDLL = "/delay:unload "; // supportd auto unload of delay-load dlls

	CString szImportLibrary = VCLinkerTool.GetValue("ImportLibrary");
	if (!szImportLibrary.IsEmpty())
	{ // override .lib filename
		szImportLibrary = "/implib:\"" + szImportLibrary + "\" ";
	}

	CString szMergeSections = VCLinkerTool.GetValue("MergeSections");
	if (!szMergeSections.IsEmpty())
	{ // merge from=to code sections
		szMergeSections = "/merge:" + szMergeSections + " ";
	}

	CString szTargetMachine;
	if ( VCLinkerTool.GetValue("TargetMachine").CompareNoCase("1") )
		szTargetMachine = "/machine:ix86 "; // target CPU

	// -- cmd line tab
	//
	
	CString szAdditionalOptions = VCLinkerTool.GetValue("AdditionalOptions");


	szReturn = szAdditionalDependencies;
	szReturn += szSuppressStartupBanner;
	szReturn += szDllOutput;
	szReturn += szOutputFile;
	szReturn += szShowProgress;
	szReturn += szVersion;
	szReturn += szLinkIncremental;
	szReturn += szAdditionalLibraryDirectories;
	szReturn += szIgnoreAllDefaultLibraries;
	szReturn += szIgnoreDefaultLibraryNames;
	szReturn += szModuleDefinitionFile;
	szReturn += szForceSymbolReferences;
	szReturn += szDelayLoadDLLs;
	szReturn += szGenerateDebugInformation;
	szReturn += szProgramDatabaseFile;
	szReturn += szPdbSeparated;
	szReturn += szGenerateMapFile;
	szReturn += szSubSystem;
	szReturn += szHeapReserveCommitSize;
	szReturn += szStackReserveCommitSize;
	szReturn += szLargeAddressAware;
	szReturn += szSwapRunFromCD;
	szReturn += szSwapRunFromNET;
	szReturn += szOptimizeReferences;
	szReturn += szEnableCOMDATFolding;
	szReturn += szFunctionOrder;
	szReturn += szEntryPointSymbol;
	szReturn += szResourceOnlyDLL;
	szReturn += szSetChecksum;
	szReturn += szBaseAddress;
	szReturn += szSupportUnloadOfDelayLoadedDLL;
	szReturn += szImportLibrary;
	szReturn += szMergeSections;
	szReturn += szTargetMachine;
	szReturn += szAdditionalOptions;

	return szReturn;
}


CString vcprojconfiguration::serializeLibrarianSymbols(BOOL bFileConfiguration)
{
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//

	CString szOutputFile;
	s = VCLibrarianTool.GetValue("OutputFile");
	if (!s.IsEmpty())
	{ // .lib fully qualified filename
		szOutputFile = "/out:\"" + ExpandMacros(s) + "\" ";
	}


	CString szSuppressStartupBanner = "/nologo "; // default VC7 behaviour is "suppress banner"
	if ( VCLibrarianTool.GetValue("SuppressStartupBanner").CompareNoCase("FALSE") )
		szSuppressStartupBanner.Empty();


	// -- cmdline tab
	//

	CString szAdditionalOptions = VCLibrarianTool.GetValue("AdditionalOptions");


	szReturn = szSuppressStartupBanner;
	szReturn += szOutputFile;
	szReturn += szAdditionalOptions;

	return szReturn;

}

CString vcprojconfiguration::serializeResourceSymbols(BOOL bFileConfiguration)
{
	long i;
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//

	s = VCResourceCompilerTool.GetValue("PreprocessorDefinitions");
	CString szPreprocessorDefinitions;
	ArrayCString arrPreprocessorDefinitions;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrPreprocessorDefinitions); // parse comma-separated symbols
	else if (s.Find(0,";")>-1)
		TokenizeString(s,';',arrPreprocessorDefinitions); // or parse semi-colon-separated symbols
	else
		TokenizeString(s,' ',arrPreprocessorDefinitions); // or parse space-separated symbols

	for (i=0; i<arrPreprocessorDefinitions.GetSize(); i++)
	{
		CString szSymbol = arrPreprocessorDefinitions.GetAt(i);
		if ( !szSymbol.CompareNoCase("$(NOINHERIT)") )
			szPreprocessorDefinitions += "/d \"" + szSymbol + "\" ";
	}


	CString szCulture = "/l 1033 "; // default is english US
	s = VCResourceCompilerTool.GetValue("Culture");
	if (!s.IsEmpty())
	{
		szCulture = "/l " + s + " ";
	}

	s = VCResourceCompilerTool.GetValue("AdditionalIncludeDirectories");
	CString szAdditionalIncludeDirectories;
	ArrayCString arrAdditionalIncludeDirectories;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrAdditionalIncludeDirectories); // parse comma-separated path
	else 
		TokenizeString(s,';',arrAdditionalIncludeDirectories); // or parse semi-colon-separated path

	for (i=0; i<arrAdditionalIncludeDirectories.GetSize(); i++)
	{
		CString szDirectory = arrAdditionalIncludeDirectories.GetAt(i);
		if ( !szDirectory.CompareNoCase("$(NOINHERIT)") )
			szAdditionalIncludeDirectories += "/i \"" + ReplaceMacros(szDirectory) + "\" ";
	}

	CString szIgnoreStandardIncludePath;
	if ( VCResourceCompilerTool.GetValue("IgnoreStandardIncludePath").CompareNoCase("TRUE") )
		szIgnoreStandardIncludePath = "/x "; // ignore std include path

	CString szShowProgress;
	if ( VCResourceCompilerTool.GetValue("ShowProgress").CompareNoCase("TRUE") )
		szShowProgress = "/v "; // verbose


	CString szResourceOutputFileName;
	s = VCResourceCompilerTool.GetValue("ResourceOutputFileName");
	if (!s.IsEmpty())
	{
		szResourceOutputFileName = "/fo\"" + s + "\" ";
	}

	// cmdline tab
	//

	CString szAdditionalOptions = VCResourceCompilerTool.GetValue("AdditionalOptions");


	szReturn = szCulture;
	szReturn += szPreprocessorDefinitions;
	szReturn += szAdditionalIncludeDirectories;
	szReturn += szIgnoreStandardIncludePath;
	szReturn += szShowProgress;
	szReturn += szResourceOutputFileName;
	szReturn += szAdditionalOptions;

	return szReturn;
}


CString vcprojconfiguration::serializeMidlSymbols(BOOL bFileConfiguration)
{
	long i;
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//

	s = VCMidlTool.GetValue("PreprocessorDefinitions");

	CString szPreprocessorDefs;
	ArrayCString arrPreprocessorDefs;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrPreprocessorDefs); // parse comma-separated symbols
	else 
		TokenizeString(s,';',arrPreprocessorDefs); // or parse semi-colon-separated symbols

	for (i=0; i<arrPreprocessorDefs.GetSize(); i++)
	{
		CString szSymbol = arrPreprocessorDefs.GetAt(i);
		if ( !szSymbol.CompareNoCase("$(NOINHERIT)") )
			szPreprocessorDefs += "/D\"" + szSymbol + "\" ";
	}


	CString szAdditionalIncludeDirectories;
	ArrayCString arrAdditionalIncludeDirectories;
	s = VCMidlTool.GetValue("AdditionalIncludeDirectories");
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrAdditionalIncludeDirectories); // parse comma-separated path
	else 
		TokenizeString(s,';',arrAdditionalIncludeDirectories); // or parse semi-colon-separated path

	for (i=0; i<arrAdditionalIncludeDirectories.GetSize(); i++)
	{
		CString szDirectory = arrAdditionalIncludeDirectories.GetAt(i);
		if ( !szDirectory.CompareNoCase("$(NOINHERIT)") )
			szAdditionalIncludeDirectories += "/I \"" + szDirectory + "\" ";
	}

	CString szIgnoreStandardIncludePath;
	if ( VCMidlTool.GetValue("IgnoreStandardIncludePath").CompareNoCase("TRUE") )
		szIgnoreStandardIncludePath = "/no_def_idir "; // ignore std include paths

	CString szMkTypLibCompatible;
	if ( VCMidlTool.GetValue("MkTypLibCompatible").CompareNoCase("TRUE") )
		szMkTypLibCompatible = "/mktyplib203 "; // old maketypelib compatible flag

	CString szWarningLevel;
	s = VCMidlTool.GetValue("WarningLevel");
	if (s.CompareNoCase("0") || s.CompareNoCase("1") || s.CompareNoCase("2") || s.CompareNoCase("3") || s.CompareNoCase("4"))
	{
		szWarningLevel = "/W" + s + " ";
	}

	CString szWarnAsError;
	if ( VCMidlTool.GetValue("WarnAsError").CompareNoCase("TRUE") )
		szWarnAsError += "/WX ";

	CString szSuppressStartupBanner = "/nologo "; // default VC7 behaviour is "suppress banner"
	if ( VCMidlTool.GetValue("SuppressStartupBanner").CompareNoCase("FALSE") )
		szSuppressStartupBanner.Empty();


	CString szDefaultCharset;
	s = VCMidlTool.GetValue("DefaultCharType");
	if (s.CompareNoCase("0"))
		szDefaultCharset = "/char unsigned ";
	else if (s.CompareNoCase("1"))
		szDefaultCharset = "/char signed ";
	else if (s.CompareNoCase("2"))
		szDefaultCharset = "/char ascii7 ";

	CString szGenerateStublessProxies;
	if ( VCMidlTool.GetValue("GenerateStublessProxies").CompareNoCase("TRUE") )
		szGenerateStublessProxies = "/Oicf ";


	// -- output tab
	//
	CString szOutputDirectory;
	s = VCMidlTool.GetValue("OutputDirectory");
	if (!s.IsEmpty())
	{
		szOutputDirectory = "/out\"" + ExpandMacros(s) + "\" ";
	}

	CString szHeaderFileName;
	s = VCMidlTool.GetValue("HeaderFileName");
	if (!s.IsEmpty())
	{
		szHeaderFileName = "/h\"" + ExpandMacros(s) + "\" ";
	}

	CString szInterfaceIdentifierFileName;
	s = VCMidlTool.GetValue("InterfaceIdentifierFileName");
	if (!s.IsEmpty())
	{
		szInterfaceIdentifierFileName = "/iid\"" + ExpandMacros(s) + "\" ";
	}

	CString szDLLDataFileName;
	s = VCMidlTool.GetValue("DLLDataFileName");
	if (!s.IsEmpty())
	{
		szDLLDataFileName = "/dlldata\"" + ExpandMacros(s) + "\" ";
	}

	CString szProxyFileName;
	s = VCMidlTool.GetValue("ProxyFileName");
	if (!s.IsEmpty())
	{
		szProxyFileName = "/proxy\"" + ExpandMacros(s) + "\" ";
	}

	CString szTypeLibraryName;
	s = VCMidlTool.GetValue("TypeLibraryName");
	if (!s.IsEmpty())
	{
		szTypeLibraryName = "/tlb\"" + ExpandMacros(s) + "\" ";
	}

	// -- advanced tab
	//
	CString szEnableErrorChecks;
	CString szErrorCheckAllocations;
	CString szErrorCheckBounds;
	CString szErrorCheckEnumRange;
	CString szErrorCheckRefPointers;
	CString szErrorCheckStubData;
	s = VCMidlTool.GetValue("EnableErrorChecks");
	if (s.CompareNoCase("1"))
	{
		szEnableErrorChecks = "/error none ";
	}
	else if (s.CompareNoCase("2"))
	{
		szEnableErrorChecks = "/error allocation /error bounds_check /error enum /error ref /error stub_data ";
	}
	else
	{
		if (VCMidlTool.GetValue("ErrorCheckAllocations").CompareNoCase("TRUE"))
			szErrorCheckAllocations = "/error allocation ";
		if (VCMidlTool.GetValue("ErrorCheckBounds").CompareNoCase("TRUE"))
			szErrorCheckBounds = "/error bounds_check ";
		if (VCMidlTool.GetValue("ErrorCheckEnumRange").CompareNoCase("TRUE"))
			szErrorCheckEnumRange = "/error enum ";
		if (VCMidlTool.GetValue("ErrorCheckRefPointers").CompareNoCase("TRUE"))
			szErrorCheckRefPointers = "/error ref ";
		if (VCMidlTool.GetValue("ErrorCheckStubData").CompareNoCase("TRUE"))
			szErrorCheckStubData = "/error stub_data ";
	}

	CString szValidateParameters;
	if (VCMidlTool.GetValue("ValidateParameters").CompareNoCase("TRUE"))
		szValidateParameters = "/robust ";

	CString szStructMemberAlignment;
	s = VCMidlTool.GetValue("StructMemberAlignment");
	if (s.CompareNoCase("1"))
		szStructMemberAlignment = "/Zp1 "; // 1-byte alignment
	else if (s.CompareNoCase("2"))
		szStructMemberAlignment = "/Zp2 "; // 2-byte alignment
	else if (s.CompareNoCase("3"))
		szStructMemberAlignment = "/Zp4 "; // 4-byte alignment
	else if (s.CompareNoCase("4"))
		szStructMemberAlignment = "/Zp8 "; // 8-byte alignment
	else if (s.CompareNoCase("5"))
		szStructMemberAlignment = "/Zp8 "; // no 16-byte alignment in MIDL VC++6.0

	CString szRedirectOutputAndErrors;
	s = VCMidlTool.GetValue("RedirectOutputAndErrors");
	if (!s.IsEmpty())
	{
		szRedirectOutputAndErrors = "/o\"" + s + "\" ";
	}

	
	s = VCMidlTool.GetValue("CPreprocessOptions");

	CString szCPreprocessOptions;
	ArrayCString arrCPreprocessOptions;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrCPreprocessOptions); // parse comma-separated symbols
	else 
		TokenizeString(s,';',arrCPreprocessOptions); // or parse semi-colon-separated symbols

	for (i=0; i<arrCPreprocessOptions.GetSize(); i++)
	{
		CString szCPreprocss = arrCPreprocessOptions.GetAt(i);
		if ( !szCPreprocss.CompareNoCase("$(NOINHERIT)") )
			szCPreprocessOptions += "/cpp_opt\"" + szCPreprocss + "\" ";
	}



	s = VCMidlTool.GetValue("UndefinePreprocessorDefinitions");

	CString szUndefinePreprocessorDefinitions;
	ArrayCString arrUndefinePreprocessorDefinitions;
	if (s.Find(0,",")>-1)
		TokenizeString(s,',',arrUndefinePreprocessorDefinitions); // parse comma-separated symbols
	else 
		TokenizeString(s,';',arrUndefinePreprocessorDefinitions); // or parse semi-colon-separated symbols

	for (i=0; i<arrUndefinePreprocessorDefinitions.GetSize(); i++)
	{
		CString szUndefSymbol = arrUndefinePreprocessorDefinitions.GetAt(i);
		if ( !szUndefSymbol.CompareNoCase("$(NOINHERIT)") )
			szUndefinePreprocessorDefinitions += "/U \"" + szUndefSymbol + "\" ";
	}

	// target win32 environment (almost always)
	//
	CString szTargetEnv = "/win32 ";
	if (General.GetValue("Name").FindNoCase(0,"Win64")>-1)
		szTargetEnv = "/win64 ";

	// -- cmdline tab
	//

	CString szAdditionalOptions = VCMidlTool.GetValue("AdditionalOptions");


	szReturn = szSuppressStartupBanner;
	szReturn += szPreprocessorDefs;
	szReturn += szAdditionalIncludeDirectories;
	szReturn += szIgnoreStandardIncludePath;
	szReturn += szMkTypLibCompatible;
	szReturn += szWarningLevel;
	szReturn += szWarnAsError;
	szReturn += szDefaultCharset;
	szReturn += szGenerateStublessProxies;
	szReturn += szOutputDirectory;
	szReturn += szHeaderFileName;
	szReturn += szInterfaceIdentifierFileName;
	szReturn += szDLLDataFileName;
	szReturn += szProxyFileName;
	szReturn += szTypeLibraryName;
	szReturn += szEnableErrorChecks;
	szReturn += szErrorCheckAllocations;
	szReturn += szErrorCheckBounds;
	szReturn += szErrorCheckEnumRange;
	szReturn += szErrorCheckRefPointers;
	szReturn += szErrorCheckStubData;
	szReturn += szValidateParameters;
	szReturn += szStructMemberAlignment;
	szReturn += szRedirectOutputAndErrors;
	szReturn += szCPreprocessOptions;
	szReturn += szUndefinePreprocessorDefinitions;
	szReturn += szTargetEnv;
	szReturn += szAdditionalOptions;

	return szReturn;
}


CString vcprojconfiguration::serializeBscMakeSymbols(BOOL bFileConfiguration)
{
	CString szReturn, s;

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//
	CString szSuppressStartupBanner = "/nologo "; // default VC7 behaviour is "suppress banner"
	if ( VCBscMakeTool.GetValue("SuppressStartupBanner").CompareNoCase("FALSE") )
		szSuppressStartupBanner.Empty();

	CString szOutputFile;
	s = VCBscMakeTool.GetValue("OutputFile");
	if (!s.IsEmpty())
	{
		szOutputFile = "/o \"" + ExpandMacros(s) + "\" ";
	}

	// -- cmdline tab
	//

	CString szAdditionalOptions = VCBscMakeTool.GetValue("AdditionalOptions");

	szReturn = szSuppressStartupBanner;
	szReturn += szOutputFile;
	szReturn += szAdditionalOptions;

	return szReturn;
}


void vcprojconfiguration::serializePreBuildCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration)
{

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//
	
	CString szDescription = VCPreBuildEventTool.GetValue("Description");
	output.Add( szDescription );
	
	CString szCommandLine = VCPreBuildEventTool.GetValue("CommandLine");
	szCommandLine = ReplaceMacros(szCommandLine,FALSE);
	szCommandLine.ReplaceChar('\n','\t'); // switch to tab char instead
	szCommandLine.ReplaceCharWithString('\r',""); // remove these
	output.Add( szCommandLine );

	if (szCommandLine.IsEmpty())
		output.RemoveAll();
}

void vcprojconfiguration::serializePreLinkCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration)
{

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//
	
	CString szDescription = VCPreLinkEventTool.GetValue("Description");
	output.Add( szDescription );
	
	CString szCommandLine = VCPreLinkEventTool.GetValue("CommandLine");
	szCommandLine = ReplaceMacros(szCommandLine,FALSE);
	szCommandLine.ReplaceChar('\n','\t'); // switch to tab char instead
	szCommandLine.ReplaceCharWithString('\r',""); // remove these
	output.Add( szCommandLine );

	if (szCommandLine.IsEmpty())
		output.RemoveAll();

}

void vcprojconfiguration::serializePostBuildCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration)
{

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//
	
	CString szDescription = VCPostBuildEventTool.GetValue("Description");
	output.Add( szDescription );
	
	CString szCommandLine = VCPostBuildEventTool.GetValue("CommandLine");
	szCommandLine = ReplaceMacros(szCommandLine,FALSE);
	szCommandLine.ReplaceChar('\n','\t'); // switch to tab char instead
	szCommandLine.ReplaceCharWithString('\r',""); // remove these
	output.Add( szCommandLine );

	// check whether the user has checked "auto register" in the VCLinkerTool
	// and produce a COM registration command
	if ( VCLinkerTool.GetValue("RegisterOutput").CompareNoCase("TRUE") )
	{
		; // create a post build cmd line "Regsvr32.exe /s $(TargetPath)"
		// make sure there is no registration already
		if (output.GetAt(1).FindNoCase(0,"regsvr32")==-1)
		{
			szCommandLine = output.GetAt(1);
			if (!szCommandLine.IsEmpty()) szCommandLine += "\t";
			szCommandLine += "Regsvr32.exe /s $(TargetPath)";
			output.SetAt(1, szCommandLine );
		}
	}


	if (szCommandLine.IsEmpty())
		output.RemoveAll();
}

void vcprojconfiguration::serializeCustomBuildCommands(/*out*/CString &szDescription, 
													   /*out*/ArrayCString &cmds, 
													   /*out*/ArrayCString &outputFiles, 
													   /*out*/ArrayCString &additionalDeps, 
													   BOOL bFileConfiguration)
{

// sections are divided wrt to VC++7 (rescrambled for any reason by MS from VC++6)

	// -- general tab
	//

	szDescription = VCCustomBuildTool.GetValue("Description");

	CString szCommandLines = VCCustomBuildTool.GetValue("CommandLine"); // EOL-separated lines
	szCommandLines = ReplaceMacros(szCommandLines,FALSE);
	if (!szCommandLines.IsEmpty())
		TokenizeString(szCommandLines, '\n', cmds);

	CString szOutputFiles = VCCustomBuildTool.GetValue("Outputs"); // semicolon-separated filenames
	szOutputFiles = ReplaceMacros(szOutputFiles);
	if (!szOutputFiles.IsEmpty())
		TokenizeString(szOutputFiles, ';', outputFiles);

	CString szAdditionalDependencies = VCCustomBuildTool.GetValue("AdditionalDependencies"); // semicolon-separated filenames
	szAdditionalDependencies = ReplaceMacros(szAdditionalDependencies);
	if (!szAdditionalDependencies.IsEmpty())
		TokenizeString(szAdditionalDependencies, ';', additionalDeps);



}







void vcprojconfiguration::BSTR_to_CString(/*in*/BSTR bstr, /*out*/CString &s)
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


void vcprojconfiguration::getAttribValue(/*in*/IXMLDOMElement *p, /*in*/char *szAttribName, /*out*/CString &szValue)
{
	szValue.Empty();
	if (!p) return;

	VARIANT vtValue;
	p->getAttribute( _bstr_t(szAttribName), &vtValue);
	VARIANT_to_CString( vtValue, szValue);
}

void vcprojconfiguration::VARIANT_to_CString(/*in*/VARIANT &vt, /*out*/CString &s)
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


void vcprojconfiguration::TokenizeString(/*in*/CString &szInput, char cToken, /*out*/ArrayCString &arrStrings)
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


void vcprojconfiguration::TokenizeString(/*in*/CString &szInput, /*in*/CString &szTokenString, /*out*/ArrayCString &arrStrings)
{
	long i;

	CString s = szInput;

	arrStrings.RemoveAll();

	while ( (i=s.Find(0,szTokenString))>-1 )
	{
		arrStrings.Add( s.Left(i) );
		s = s.ExcludeLeft(i+szTokenString.GetLength());
	}
	if (!s.IsEmpty())
		arrStrings.Add ( s );
}

void vcprojconfiguration::UntokenizeString(/*in*/ArrayCString &arrStrings, char cToken, /*out*/CString &szOutput)
{
	szOutput.Empty();

	for (long i=0;i<arrStrings.GetSize(); i++)
	{
		if (!szOutput.IsEmpty()) szOutput += cToken;

		szOutput += arrStrings.GetAt(i);
	}
}

// expand the $(OutDir) and $(IntDir) macros
CString vcprojconfiguration::ExpandMacros(/*in*/CString &szInputString)
{
	CString s = szInputString;

	CString szOutputDir = General.GetValue("OutputDirectory");
	CString szIntermediateDir = General.GetValue("IntermediateDirectory");

	if (!szOutputDir.IsEmpty())
	{
		long n;
		while ( (n=s.Find(0, "$(OutDir)"))>-1)
		{
			s = s.Left(n) + 
				szOutputDir + 
				s.ExcludeLeft(n+CString("$(OutDir)").GetLength());
		}
	} // end if

	if (!szIntermediateDir.IsEmpty())
	{
		long n;
		while ( (n=s.Find(0, "$(IntDir)"))>-1)
		{
			s = s.Left(n) + 
				szIntermediateDir + 
				s.ExcludeLeft(n+CString("$(IntDir)").GetLength());
		}
	} // end if

	s.ReplaceChar('/','\\');

	return s;
}

// replace VC7 macro names with VC6 macro names (thanks MS for changing them!)
CString vcprojconfiguration::ReplaceMacros(/*in*/CString &szInputString, BOOL bReplaceBackslash)
{
	CString s = szInputString;
	if (s.IsEmpty()) return s;

	// replace $(ProjectDir) with $(ProjDir)
	long n;
	while ( (n=s.Find(0, "$(ProjectDir)"))>-1)
	{
		s = s.Left(n) + 
			CString("$(ProjDir)") + 
			s.ExcludeLeft(n+CString("$(ProjDir)").GetLength());
	}

	// remove $(NoInherit) and $(Inherit) : not supported on VC6
	while ( (n=s.Find(0, "$(NoInherit)"))>-1)
	{
		s = s.Left(n) + 
			s.ExcludeLeft(n+CString("$(NoInherit)").GetLength());
	}

	while ( (n=s.Find(0, "$(Inherit)"))>-1)
	{
		s = s.Left(n) + 
			s.ExcludeLeft(n+CString("$(Inherit)").GetLength());
	}

	if ( bReplaceBackslash )
		s.ReplaceChar('/','\\');

	return s;
}