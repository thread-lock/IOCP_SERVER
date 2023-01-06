#include "MapManger.h"
#include "Dungeon.h"
#include "DungeonManager.h"

cMapManger * cMapManger::mInstance = nullptr; //�ν��Ͻ� �ʱ�ȭ

void cMapManger::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cMapManger();
	}
}

cMapManger * cMapManger::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cMapManger();
	}
	return mInstance;
}

void cMapManger::Destroy() //�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cMapManger::cMapManger()
{
}


cMapManger::~cMapManger()
{
}



void cMapManger::Req_Enter_Map(cClientInfo* _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	cMap* map = player->Get_Enter_Map();
	map->Map_Enter_Data_Send(_info);
	map->Enter_Player_Data_Send(_info);
}

void cMapManger::Req_Out_Map(cClientInfo * _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	cMap* map = player->Get_Enter_Map();
	map->Out_Player(_info);
	player->Set_Enter_Map(nullptr);
	map->Out_Player_Data_Send(_info);
}

//������ �����ϰ� ��Ƽ���� �̵�
void cMapManger::Req_Enter_Dungeon(cClientInfo * _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	cProtocol protocol;

	int level;
	_data.separate(level);

	//��Ƽ�� ���Ե����� ���� ���
	if (player->Get_Enter_Party() == nullptr)
	{
		//�������� �÷��̾� ����
		cMap* map = player->Get_Enter_Map();
		map->Out_Player(_info);
		map->Out_Player_Data_Send(_info);
		//�������� �� ����
		sDungeon* dungeon = cDungeonManger::GetInstance()->CreateDungeon();
		dungeon->mField[0]->Enter_Player(_info);
		player->Set_Enter_Map(dungeon->mField[0]);
		//���� ����
		_data.Append(true);
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
		_info->Pack(protocol, _data);
		_info->SendMsg();
		return;
		//������ ����
	}
	else
	{
		//��Ƽ�� ���Ե������� ������ �ƴѰ��
		if (player->Get_Enter_Party()->Get_Leader() != _info)
		{
			_data.Clear();
			//���� ����
			_data.Append(false);
			_data.Append((char*) "������ �ƴմϴ�.");
			protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
			_info->Pack(protocol, _data);
			_info->SendMsg();
			return;
		}
		else
		{
			//�������� �÷��̾� ����
			cMap* map = player->Get_Enter_Map();
			map->Out_Player(_info);
			map->Out_Player_Data_Send(_info);
			//���� ����
			sDungeon* dungeon = cDungeonManger::GetInstance()->CreateDungeon();
			dungeon->mField[0]->Enter_Player(_info);
			player->Set_Enter_Map(dungeon->mField[0]);
			//��Ƽ���鵵 ���� ����
			player->Get_Enter_Party()->Player_Enter_Dungeon(dungeon->mField[0]);
			//���� ����
			_data.Append(true);
			protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
			_info->Pack(protocol, _data);
			_info->SendMsg();
			return;
		}
	}
}
