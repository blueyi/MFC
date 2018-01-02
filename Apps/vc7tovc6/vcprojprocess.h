
#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// vcprojprocess class
//
// S.Rodriguez - Sept 2002
//
//
// purpose : convert a .vcproj file format to a .dsp file format
//           (a .vcproj file is the makefile of a VisualStudio 7 C++ project)
//
//






class vcprojprocess
{

	// Members
protected:
	CString				m_szSolutionName; // .sln fully qualified filename
	PROJECTPARAM*		m_cpPrj; // copy ptr (no need to destroy)
	
	CFile				m_inputFile; // to read the .vcproj file
	CFile				m_outputFile; // to write the .dsp file

	// extracted from the .vcproj file
	CString				m_szProjname;
	CString				m_szTargetType;
	BOOL				m_bIsConsoleApp;
	CString				m_szSccProjectName; // source control
	CString				m_szSccLocalPath;
	ArrayCString		m_arrConfigurationNames;
	ConfigurationArray	m_arrConfigs;


	// Constructor
public:
	vcprojprocess();
	~vcprojprocess();

	// Methods
public:
	void process(CString &szSolutionName, PROJECTPARAM *p);
	void getSourceControlInfo(CString &szSccName, CString &szSccPath);


	// Helpers
protected:
	void extractHeader(IXMLDOMDocument *pDoc);
	void extractConfigurations(IXMLDOMDocument *pDoc);
	void extractFileConfigurations(IXMLDOMElement *pFileElement, ConfigurationArray &arrFileConfigs);

	void writeDspHeader();
	void writeDspConfigurations(IXMLDOMDocument *pDoc);
	void writeDspMakefile(long i);
	void writeDspFiles(IXMLDOMDocument *pDoc);
	void writeDspGroup(IXMLDOMElement *pGroupFilter);
	void writeDspFileConfigurations(CString &szFilename, ConfigurationArray &arrFileConfigs, ConfigurationArray &projectConfigs);
	void writeDspFooter();

	BOOL isFullPath(CString &szFilepath);
	void getAttribValue(/*in*/IXMLDOMElement *p,/*in*/char *szAttribName, /*out*/CString &szValue);
	void getNodeName(/*in*/IXMLDOMElement *p, /*out*/CString &szName);
	void VARIANT_to_CString(/*in*/VARIANT &vt, /*out*/CString &s);
	void BSTR_to_CString(/*in*/BSTR bstr, /*out*/CString &s);
	CString TranslateConfigurationName(CString &sInputConfigName);
	CString ExtractPlatform(CString &sInputConfigName);
	void TokenizeString(/*in*/CString &szInput, char cToken, /*out*/ArrayCString &arrStrings);
	void UntokenizeString(/*in*/ArrayCString &arrStrings, char cToken, /*out*/CString &szOutput);
};
