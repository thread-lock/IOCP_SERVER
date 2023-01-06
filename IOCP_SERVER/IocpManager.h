#pragma once
#ifndef IOCP_MANAGER_H
#define IOCP_MANAGER_H
#include "Global.h"
#include "ThreadManager.h"
#include "ClientInfo.h"


class cIocpManager : public cThreadUse
{
protected:
	HANDLE mPort;
	OVERLAPPED mExit;
	int mThreadCount;
public:
	DWORD Procces(void* _data);
	
	bool Initialize();
	void End();

	virtual void AcceptProcess(cClientInfo* _client) = 0;
	virtual void RecvProcess(cClientInfo* _client, DWORD _trans) = 0;
	virtual void SendProcess(cClientInfo* _client, DWORD _trans) = 0;
	virtual void DisconnectProcess(cClientInfo* _client) = 0;
	

};


#endif


