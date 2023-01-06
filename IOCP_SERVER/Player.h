#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "ClientInfo.h"
#include "Charactor.h"


class cClientInfo;
class cCharactor;

struct sPlayer
{
	cClientInfo* info;
	cCharactor* charactor;
	sPlayer(cClientInfo* _info, cCharactor* _char)
	{
		info = _info;
		charactor = _char;
	}
	~sPlayer()
	{
		//DB�� ĳ���� ���� ������Ʈ
		delete charactor;
	}
};


#endif // !PLAYER_H
