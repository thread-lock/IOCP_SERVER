#include "PartyManager.h"
#include "PlayerManager.h"

cPartyManager * cPartyManager::mInstance = nullptr; //인스턴스 초기화

void cPartyManager::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cPartyManager();
	}
} 

cPartyManager * cPartyManager::GetInstance() //싱글톤 객체 반환
{
	if (!mInstance)
	{
		mInstance = new cPartyManager();
	}
	return mInstance;
}

void cPartyManager::Destroy() //싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cPartyManager::cPartyManager()
{
}

cPartyManager::~cPartyManager()
{
}


void cPartyManager::Req_Invite_Party(cClientInfo * _info, cBuf & _data)
{
	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	//파티가 아직 생성되지 않았을 경우 생성함
	if (player->Get_Enter_Party() == nullptr)
	{
		cParty* party = new cParty();
		party->Enter_Player(_info);
		player->Set_Enter_Party(party);
	}

	cProtocol protocol;

	//파티 방장이 아닐 경우
	if (player->Get_Enter_Party()->Get_Leader() != _info)
	{
		_data.Clear();
		_data.Append(false);
		_data.Append((char*) "방장이 아닙니다.");
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
		_info->Pack(protocol, _data);
		_info->SendMsg();
		return;
	}

	//파티이 인원수가 초고 됬을 경우
	if (player->Get_Enter_Party()->Get_Count() >= 4)
	{
		_data.Clear();
		_data.Append(false);
		_data.Append((char*) "파티 인원수 초과입니다.");
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
		_info->Pack(protocol, _data);
		_info->SendMsg();
		return;
	}

	int code;
	_data.separate(code);

	player->Get_Enter_Map()->Req_Party_invite(_info, code);
}

void cPartyManager::Party_Invite_Re(cClientInfo * _info, cBuf & _data)
{

	bool result;
	_data.separate(result);

	cProtocol protocol;

	if (result)
	{
		char leader[CHAR_NAME_SIZE];
		_data.separate(leader);

		_info->Get_Char_Info()->Get_Enter_Map()->Re_Party_invite(_info, leader);

	}
}

void cPartyManager::Req_Out_Party(cClientInfo * _info, cBuf & _data)
{

	cCharactor* player = _info->Get_Char_Info();
	if (player == nullptr) return;

	cParty* party = player->Get_Enter_Party();
	party->Out_Player(_info);
	player->Set_Enter_Party(nullptr);
	party->Out_Player_Data_Send(_info);
}

