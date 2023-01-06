#include "ChatManager.h"
#include "Map.h"

cChatManager * cChatManager::mInstance = NULL; //ÀÎ½ºÅÏ½º ÃÊ±âÈ­

cChatManager::cChatManager()
{
}


cChatManager::~cChatManager()
{
}

void cChatManager::Create() //½Ì±ÛÅæ »ý¼º
{
	if (!mInstance)
	{
		mInstance = new cChatManager();
	}
}

cChatManager * cChatManager::GetInstance() //½Ì±ÛÅæ °´Ã¼ ¹ÝÈ¯
{
	if (!mInstance)
	{
		mInstance = new cChatManager();
	}
	return mInstance;
}

void cChatManager::Destroy() //½Ì±ÛÅæ »èÁ¦
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

void cChatManager::Chat_Data(cClientInfo * _info, cBuf & _data)
{
	if (_info->Get_Char_Info() == nullptr) return;
	char str[255];

	_data.separate(str);

	cMap* map = _info->Get_Char_Info()->Get_Enter_Map();
	map->Player_Chat_Data_Send(_info, str);

}
