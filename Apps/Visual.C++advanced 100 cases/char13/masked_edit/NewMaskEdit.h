#pragma once

class NewMaskEdit : public CEdit
{
public:
	NewMaskEdit();
	virtual ~NewMaskEdit();

	void	SetWindowText(LPCTSTR lpszString);

	void	setText(LPCTSTR pszText);
	CString	getText();

	void	setMask(LPCTSTR pszMask, char cPlaceHolder = '_');
	CString	getMask();

	//{{AFX_VIRTUAL(NewMaskEdit)
	//}}AFX_VIRTUAL

protected:

	char	m_cPlaceHolder;
	
	CString m_strMaskText;

	CString m_strSaveText;

	bool	m_bLastKeyWasDelete;
	bool	m_bLastKeyWasBackspace;

	bool	isMaskChar(int nPos);

	int		gotoNextEntryChar(int nPos);

	bool	getReplacementChar(int nPos, char cWant, char& cGet);

	//{{AFX_MSG(NewMaskEdit)
	afx_msg void OnUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

inline CString NewMaskEdit::getMask()
{
	return m_strMaskText;
}
