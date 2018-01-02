// PropSheet Wizardaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see PropSheet Wizard.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CPropSheetWizardAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void GetPlatforms (CStringList& rPlatforms);

protected:
	CDialogChooser* m_pChooser;
private:
	void InitMacros ();
	void SetRootOptions ();
};

// This declares the one instance of the CPropSheetWizardAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global PropSheetWizardaw.  (Its definition is in PropSheet Wizardaw.cpp.)
extern CPropSheetWizardAppWiz PropSheetWizardaw;
