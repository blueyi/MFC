#pragma once



// CMySocket ÃüÁîÄ¿±ê

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
public:
	void SetHWnd(HWND hwnd);
	HWND m_hwnd;
	virtual void OnReceive(int nErrorCode);
};


