#pragma once
#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include "Global.h"
#include "IocpManager.h"


//���� �Ŵ���
class cMainManager : public cIocpManager
{
	//�̱��� ����
	cMainManager();
	~cMainManager();
	static cMainManager * mInstance;
public:
	//�̱��� ����
	static void Create();
	static cMainManager * GetInstance();
	static void Destroy();
	//����
	void Run();


	void AcceptProcess(cClientInfo* _client);
	void RecvProcess(cClientInfo* _client, DWORD _trans);
	void SendProcess(cClientInfo* _client, DWORD _trans);
	void DisconnectProcess(cClientInfo* _client);



};

#endif // !MAINMANAGER_H
