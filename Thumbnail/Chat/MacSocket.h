#pragma once



// CMacSocket ÃüÁîÄ¿±ê

class CMacSocket : public CSocket
{
public:
	CMacSocket();
	virtual ~CMacSocket();
	virtual void OnReceive(int nErrorCode);
};


