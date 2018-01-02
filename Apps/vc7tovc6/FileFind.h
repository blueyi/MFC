// FileFind.h: interface for the CFileFind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEFIND_H__F4100767_6B0B_425C_BCD4_FC17EEA2F650__INCLUDED_)
#define AFX_FILEFIND_H__F4100767_6B0B_425C_BCD4_FC17EEA2F650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iterator>
#include <string>
#include <vector>
#include <windows.h>
class CFileFind: public  std::iterator<std::bidirectional_iterator_tag,std::string >
{
std::vector<std::string> m_filter;
HANDLE m_handle;
bool m_end;
public:
	CFileFind begin();
	static CFileFind& end();
	CFileFind(const std::vector<std::string>&filter);
	std::string operator*();
	virtual ~CFileFind();
	bool operator!=(CFileFind&right);
protected:
	void NextFit();
};

#endif // !defined(AFX_FILEFIND_H__F4100767_6B0B_425C_BCD4_FC17EEA2F650__INCLUDED_)
