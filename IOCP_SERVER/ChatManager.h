#pragma once
#ifndef CHAT_MANAGER_H
#define CHAT_MANAGER_H
#include "ClientInfo.h"

class cChatManager
{
	//�̱��� ����
	cChatManager();
	~cChatManager();
	static cChatManager * mInstance;
public:
	//�̱��� ����
	static void Create();
	static cChatManager * GetInstance();
	static void Destroy();

	//ä�� �Ŵ���
	void Chat_Data(cClientInfo* _info, cBuf & _data);


};





#endif // !CHAT_MANAGER_H
