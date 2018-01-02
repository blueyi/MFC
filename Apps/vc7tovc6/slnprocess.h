
#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// slnprocess class
//
// S.Rodriguez - Sept 2002
//
//
// purpose : convert a .sln file format to a .dsw file format
//           (a .sln file is the main file of a VisualStudio solution)
//
//

#include "CString.h"
#include "CFile.h"
#include "Templates.h"



class slnprocess
{

	// Members
protected:
	CString m_szSolutionName; // .sln fully qualified filename
	CStdioFile m_inputFile;
	CFile m_outputFile;
	ProjectArray m_projects;

	// Constructor
public:
	slnprocess();
	~slnprocess();

	// Methods
public:
	void process(CString &szSolutionName); // *.sln passed as parameter in the cmdline
	void processProjectOnly(CString &szProjectFullPath); // *.vcproj passed as parameter in the cmdline


	// Helpers
protected:
	void processProject(CString &sFirstLine);
	void processProjectDependencies(CString &sFirstLine);
	
	void writeDswHeader();
	void writeDswProject(PROJECTPARAM *p);
	void writeDswFooter();

	BOOL isFullPath(CString &szFilepath);
};
