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
		//DB에 캐릭터 정보 업데이트
		delete charactor;
	}
};


#endif // !PLAYER_H
