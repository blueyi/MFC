#pragma once



// CTcpChessSocket ÃüÁîÄ¿±ê

class CTcpChessSocket : public CSocket
{
public:
	CTcpChessSocket();
	virtual ~CTcpChessSocket();
	virtual void OnReceive(int nErrorCode);
public:
	void SetHwnd(HWND hw);
private:
	HWND hwnd;
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


