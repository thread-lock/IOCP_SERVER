#include "MapManger.h"
#include "Dungeon.h"
#include "DungeonManager.h"

cMapManger * cMapManger::mInstance = nullptr; //인스턴스 초기화

void cMapManger::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cMapManger();
	}
}

cMapManger * cMapManger::GetInstance() //싱글톤 객체 반환
{
	if (!mInstance)
	{
		mInstance = new cMapManger();
	}
	return mInstance;
}

void cMapManger::Destroy() //싱글톤 삭제
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

//던전을 생성하고 파티원들 이동
void cMapManger::Req_Enter_Dungeon(cClientInfo * _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	cProtocol protocol;

	int level;
	_data.separate(level);

	//파티에 가입되있지 않을 경우
	if (player->Get_Enter_Party() == nullptr)
	{
		//마을에서 플레이어 나감
		cMap* map = player->Get_Enter_Map();
		map->Out_Player(_info);
		map->Out_Player_Data_Send(_info);
		//던전으로 맵 설정
		sDungeon* dungeon = cDungeonManger::GetInstance()->CreateDungeon();
		dungeon->mField[0]->Enter_Player(_info);
		player->Set_Enter_Map(dungeon->mField[0]);
		//입장 성공
		_data.Append(true);
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
		_info->Pack(protocol, _data);
		_info->SendMsg();
		return;
		//던전을 생성
	}
	else
	{
		//파티에 가입되있으나 방장이 아닌경우
		if (player->Get_Enter_Party()->Get_Leader() != _info)
		{
			_data.Clear();
			//입장 실패
			_data.Append(false);
			_data.Append((char*) "방장이 아닙니다.");
			protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
			_info->Pack(protocol, _data);
			_info->SendMsg();
			return;
		}
		else
		{
			//마을에서 플레이어 나감
			cMap* map = player->Get_Enter_Map();
			map->Out_Player(_info);
			map->Out_Player_Data_Send(_info);
			//던전 입장
			sDungeon* dungeon = cDungeonManger::GetInstance()->CreateDungeon();
			dungeon->mField[0]->Enter_Player(_info);
			player->Set_Enter_Map(dungeon->mField[0]);
			//파티원들도 던전 입장
			player->Get_Enter_Party()->Player_Enter_Dungeon(dungeon->mField[0]);
			//입장 성공
			_data.Append(true);
			protocol.Add_Protocol(cProtocol::P::SERVER_RE_ENTER_DUNGEON);
			_info->Pack(protocol, _data);
			_info->SendMsg();
			return;
		}
	}
}
