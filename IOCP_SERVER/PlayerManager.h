#pragma once
#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include <list>
#include "ClientInfo.h"
#include "Game.h"

class cPlayerManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cPlayerManager() {}
	~cPlayerManager();
	static cPlayerManager* mInstance;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cPlayerManager * GetInstance();
	static void Destroy();

	//æ÷¥œ∏≈¿Ãº« ∏≈¥œ¿˙
	void Char_Move_Data(cClientInfo* _info, cBuf & _data);
	void Char_Action_Data(cClientInfo* _info, cBuf & _data);


};


#endif // !PLAYER_MANATER_H
