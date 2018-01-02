// Block.h: interface for the CBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCK_H__77B3477A_4B8D_42BE_B1C7_ECEB11AA5391__INCLUDED_)
#define AFX_BLOCK_H__77B3477A_4B8D_42BE_B1C7_ECEB11AA5391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBlock : public CObject  
{
	friend class CGisInterface;
public:
	CBlock();
	virtual ~CBlock();

};

#endif // !defined(AFX_BLOCK_H__77B3477A_4B8D_42BE_B1C7_ECEB11AA5391__INCLUDED_)
