#pragma once
#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include "Global.h"
#include "IocpManager.h"


//∏ﬁ¿Œ ∏≈¥œ¿˙
class cMainManager : public cIocpManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cMainManager();
	~cMainManager();
	static cMainManager * mInstance;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cMainManager * GetInstance();
	static void Destroy();
	//Ω««‡
	void Run();


	void AcceptProcess(cClientInfo* _client);
	void RecvProcess(cClientInfo* _client, DWORD _trans);
	void SendProcess(cClientInfo* _client, DWORD _trans);
	void DisconnectProcess(cClientInfo* _client);



};

#endif // !MAINMANAGER_H
