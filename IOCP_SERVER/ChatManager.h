#pragma once
#ifndef CHAT_MANAGER_H
#define CHAT_MANAGER_H
#include "ClientInfo.h"

class cChatManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cChatManager();
	~cChatManager();
	static cChatManager * mInstance;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cChatManager * GetInstance();
	static void Destroy();

	//√§∆√ ∏≈¥œ¿˙
	void Chat_Data(cClientInfo* _info, cBuf & _data);


};





#endif // !CHAT_MANAGER_H
