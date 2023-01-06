#include "ChatManager.h"
#include "Map.h"

cChatManager * cChatManager::mInstance = NULL; //�ν��Ͻ� �ʱ�ȭ

cChatManager::cChatManager()
{
}


cChatManager::~cChatManager()
{
}

void cChatManager::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cChatManager();
	}
}

cChatManager * cChatManager::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cChatManager();
	}
	return mInstance;
}

void cChatManager::Destroy() //�̱��� ����
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
