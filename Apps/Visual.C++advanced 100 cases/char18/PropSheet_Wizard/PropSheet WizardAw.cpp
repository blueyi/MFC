// PropSheet Wizardaw.cpp : implementation file
//

#include "stdafx.h"
#include "PropSheet Wizard.h"
#include "PropSheet Wizardaw.h"
#include "chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CPropSheetWizardAppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

	UndefMacro (_T ("PROJTYPE_MDI"));
	UndefMacro (_T ("PROJTYPE_SDI"));
	UndefMacro (_T ("PROJTYPE_DLG"));
	UndefMacro (_T ("PROJTYPE_DLL"));
	UndefMacro (_T ("PROJTYPE_CUSTOMAW"));
}

// This is called just before the custom AppWizard is unloaded.
void CPropSheetWizardAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CPropSheetWizardAppWiz::Next(CAppWizStepDlg* pDlg)
{
	if (!pDlg)
	{
		SetRootOptions ();
		InitMacros ();
	}
	// Delegate to the dialog chooser
	return m_pChooser->Next (pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CPropSheetWizardAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CPropSheetWizardAppWiz::SetRootOptions ()
{
	// Set "FILEBASE" macro
	CString strFileBase;
	m_Dictionary.Lookup (_T("Root"), strFileBase);
	DefineStringMacro (_T("filebase"), strFileBase);
	DefineStringMacro (_T ("SHEET_TITLE"), strFileBase);
}

void CPropSheetWizardAppWiz::GetPlatforms (CStringList &Platforms)
{
	for (POSITION pos = Platforms.GetHeadPosition ();pos;)
	{
		POSITION posCurr = pos;
		CString strPlatform = Platforms.GetNext (pos);
		if (strPlatform.Left (5) != _T ("Win32"))
			Platforms.RemoveAt (posCurr);
	}
}

void CPropSheetWizardAppWiz::InitMacros ()
{
	CString root, page, file;
	m_Dictionary.Lookup (_T ("Root"), root);
	m_Dictionary.Lookup (_T ("Safe_root"), root);
	root.SetAt (0, toupper (root[0]));
	page = _T ("C") + root + _T ("Page");

	DefineStringMacro (_T ("PAGE_CAPTION"), 0, root + _T (" Page"));
	DefineStringMacro (_T ("PAGE_CLASS"), 0, page);
	DefineStringMacro (_T ("PAGE_FILE"), 0, file = root + _T ("Page"));
	file.SetAt (0, tolower (file[0]));
	DefineStringMacro (_T ("PAGE_VAR"), 0, _T ("m_") + file);
	file.MakeUpper ();
	DefineStringMacro (_T ("PAGE_ID"), 0, _T ("IDD_") + file);
	DefineStringMacro (_T ("PAGE_BMP"), 0, _T ("IDB_") + file);
	DefineStringMacro (_T ("PAGE_FIRST_BMP"), _T ("IDB_") + file);
	DefineIntMacro (_T ("PAGE_VAL"), 0, 1000);
	DefineIntMacro (_T ("PAGE_ITERATOR"), 0, 1);

	DefineIntMacro (_T ("NUM_PAGES"), 1);
	DefineIntMacro (_T ("ABOUT_NUM"), 2);
	DefineIntMacro (_T ("NUM_CLASSES"), 4);
	DefineIntMacro (_T ("NUM_RESOURCES"), 3);
	DefineIntMacro (_T ("MAINSHEET_NUM"), 3);
	DefineIntMacro (_T ("APP_NUM"), 3);

	DefineBoolMacro (_T ("SMALL_PAGE"), FALSE);
	DefineBoolMacro (_T ("MEDIUM_PAGE"), TRUE);
	DefineBoolMacro (_T ("LARGE_PAGE"), FALSE);
}

// Here we define one instance of the CPropSheetWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global PropSheetWizardaw.
CPropSheetWizardAppWiz PropSheetWizardaw;


/////////////////////////////////////////////////////////////////////////////
// Miscellaneous utility functions

// You may find the macro-setting functions useful in your own custom
//  AppWizard.  Simply copy them to your own code, and replace references
//  to "PropSheetWizardaw" to your own CCustomAppWiz-derived class.

// These are generic macro-setting functions.  They set macros or remove
//  them from the dictionary.

void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	PropSheetWizardaw.m_Dictionary[lpszKey] = lpszValue;
}

void UndefMacro(LPCTSTR lpszKey)
{
	PropSheetWizardaw.m_Dictionary.RemoveKey(lpszKey);
}

// These are more specific macro-setting functions.  They set macros
//  depending on the "type", and work correctly in $$BEGINLOOP/$$ENDLOOP
//  blocks.

static void MakeKey(CString& strKey, int iItem)
{
	CString strOriginal = strKey;
	strKey.Format(_T("%s_%d"), (LPCTSTR) strKey, iItem);
}

void DefineIntMacro(LPCTSTR pszKey, int iValue)
{
	CString strValue;
	strValue.Format(_T("%d"), iValue);
	DefineMacro(pszKey, strValue);
}

void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineIntMacro(strKey, iValue);
}

void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue)
{
	if (bValue)
		DefineMacro(pszKey, _T("1"));
	else
		UndefMacro(pszKey);
}

void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineBoolMacro(strKey, bValue);
}

void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue)
{
	DefineMacro(pszKey, pszValue);
}

void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue)
{
	CString strKey(pszKey);
	MakeKey(strKey, iItem);
	DefineStringMacro(strKey, pszValue);
}

// Report an error
void ReportError(UINT nIDP, LPCTSTR szArg)
{
	CString strPrompt;
	AfxFormatString1(strPrompt, nIDP, szArg);
	AfxMessageBox(strPrompt);
}

// Report an error and throw a user exception
void ReportAndThrow(UINT nIDP, LPCTSTR szArg)
{
	ReportError(nIDP, szArg);
	AfxThrowUserException();
}
