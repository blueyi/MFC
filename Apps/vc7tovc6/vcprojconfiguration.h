
#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// vcprojconfiguration class
//
// S.Rodriguez - Sept 2002
//
//
// purpose : fill class members with actual configuration data from the .vcproj file
//
//
//




class vcprojconfiguration
{
public:
	FindableArray General;
	FindableArray VCCLCompilerTool;
	FindableArray VCLibrarianTool;
	FindableArray VCLinkerTool;
	FindableArray VCResourceCompilerTool;
	FindableArray VCMidlTool;
	FindableArray VCBscMakeTool;
	FindableArray VCPreBuildEventTool;
	FindableArray VCPreLinkEventTool;
	FindableArray VCPostBuildEventTool;
	FindableArray VCCustomBuildTool;
	FindableArray VCNMakeTool;
	FindableArray VCDebugSettingsTool;


// Constructor
public:
	vcprojconfiguration();

// Accessors
	void setMasterProjConfigurations(vcprojconfiguration *p); // used for FileConfiguration
	CString getConfigName();
	BOOL hasVCConfigTool(CString &szToolName);


// Methods
	void fill(/*in*/IXMLDOMElement *p); // fill class members

	CString serializeCPPSymbols(BOOL bFileConfiguration=FALSE);
	CString serializeLinkerSymbols(BOOL bFileConfiguration=FALSE);
	CString serializeLibrarianSymbols(BOOL bFileConfiguration=FALSE);
	CString serializeResourceSymbols(BOOL bFileConfiguration=FALSE);
	CString serializeMidlSymbols(BOOL bFileConfiguration=FALSE);
	CString serializeBscMakeSymbols(BOOL bFileConfiguration=FALSE);
	void serializePreBuildCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration=FALSE);
	void serializePreLinkCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration=FALSE);
	void serializePostBuildCommands(/*out*/ArrayCString &output, BOOL bFileConfiguration=FALSE);
	void serializeCustomBuildCommands(/*out*/CString &szDescription, /*out*/ArrayCString &cmds, /*out*/ArrayCString &outputFiles, /*out*/ArrayCString &additionalDeps, BOOL bFileConfiguration=FALSE);


	// Helpers
protected:
	void fillFromAttributes(/*in*/IXMLDOMElement *p, /*out*/FindableArray &arrAttribs);
	void BSTR_to_CString(/*in*/BSTR bstr, /*out*/CString &s);
	void getAttribValue(/*in*/IXMLDOMElement *p,/*in*/char *szAttribName, /*out*/CString &szValue);
	void VARIANT_to_CString(/*in*/VARIANT &vt, /*out*/CString &s);
	void TokenizeString(/*in*/CString &szInput, char cToken, /*out*/ArrayCString &arrStrings);
	void TokenizeString(/*in*/CString &szInput, /*in*/CString &szTokenString, /*out*/ArrayCString &arrStrings);
	void UntokenizeString(/*in*/ArrayCString &arrStrings, char cToken, /*out*/CString &szOutput);
	CString ExpandMacros(/*in*/CString &szInputString);
	CString ReplaceMacros(/*in*/CString &szInputString, BOOL bReplaceBackslash=TRUE);

	// other class members
protected:
	vcprojconfiguration* m_cpParentConfigurations; // copy ptr
};


typedef CTemplateObjArray<vcprojconfiguration*> ConfigurationArray;