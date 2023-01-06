
#include "PlayerManager.h"
#include "Room.h"
#include "Map_Town.h"
#include "DBManager.h"
#include "Dungeon.h"

cPlayerManager * cPlayerManager::mInstance = NULL; //ÀÎ½ºÅÏ½º ÃÊ±âÈ­

cPlayerManager::~cPlayerManager()
{
}

void cPlayerManager::Create() //½Ì±ÛÅæ »ý¼º
{
	if (!mInstance)
	{
		mInstance = new cPlayerManager();
	}
}

cPlayerManager * cPlayerManager::GetInstance() //½Ì±ÛÅæ °´Ã¼ ¹ÝÈ¯
{
	if (!mInstance)
	{
		mInstance = new cPlayerManager();
	}
	return mInstance;
}

void cPlayerManager::Destroy() //½Ì±ÛÅæ »èÁ¦
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

void cPlayerManager::Char_Move_Data(cClientInfo* _info, cBuf & _data)
{

	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	int move;
	float last_x;
	float last_y;

	_data.separate(move);
	_data.separate(last_x);
	_data.separate(last_y);

	player->Get_Location().SetXY(last_x, last_y);

	cMap* map = player->Get_Enter_Map();
	if (map == nullptr) return;
	map->Player_Move_Data_Send(_info, move);
}

void cPlayerManager::Char_Action_Data(cClientInfo* _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	int type;
	bool left;
	_data.separate(type);
	_data.separate(left);
	

	cMap* map = player->Get_Enter_Map();
	if (map == nullptr) return;
	map->Player_Action_Data_Send(_info,(Chractor_Action)type,left);
}
