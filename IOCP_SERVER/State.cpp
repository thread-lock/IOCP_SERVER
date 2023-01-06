#include "State.h"
#include "LoginManager.h"
#include "CharManager.h"
#include "PlayerManager.h"
#include "PartyManager.h"
#include "ChatManager.h"
#include "MapManger.h"
#include "DungeonManager.h"

void cState::CreateState(cClientInfo * _user, cState * _state[])
{
	_state[eSTATE::LOG_IN_STATE] = new cLog_in_state(_user);
	_state[eSTATE::CHAR_STATE] = new cChar_state(_user);
	_state[eSTATE::IN_TOWN_STATE] = new cIn_Town_state(_user);
	_state[eSTATE::IN_DUNGEON_STATE] = new cIn_Dungeon_state(_user);


	_user->Set_State(eSTATE::LOG_IN_STATE);
}

void cState::DeleteState(cState * _state[])
{
	for (int i = 0; i < eSTATE::STATE_COUNT; i++)
	{
		delete _state[i];
	}
}

void cState::SendProc()
{
	if (client->IsPacking())
	{
		if (!client->SendMsg()) delete client;//wsa 리시브 실행
	}
}

cLog_in_state::cLog_in_state(cClientInfo* _client)
{
	client = _client;
}

void cLog_in_state::RecvProc()
{
	cProtocol Protocol;
	cBuf buf;
	client->UnPack(Protocol, buf);

	if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_LOGIN))
	{
		if (cLoginManager::GetInstance()->Req_Login(client, buf))
		{
			client->Set_State(eSTATE::CHAR_STATE);
		}
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_JOIN))
	{
		cLoginManager::GetInstance()->Req_Join(client, buf);
	}

	if (!client->RecvMsg()) delete client;//wsa 리시브 실행
}

cChar_state::cChar_state(cClientInfo* _client)
{
	client = _client;
}

void cChar_state::RecvProc()
{
	cProtocol Protocol;
	cBuf buf;
	client->UnPack(Protocol, buf);

	if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_CHAR_INFO))
	{
		cCharManager::GetInstance()->Req_Char_Info(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_CREATE_CHAR))
	{
		cCharManager::GetInstance()->Req_Create_Char(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_SELECT_CHAR))
	{
		if (cCharManager::GetInstance()->Req_Select_Char(client, buf))
		{
			client->Set_State(eSTATE::IN_TOWN_STATE);
		}
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_DELETE_CHAR))
	{
		cCharManager::GetInstance()->Req_Delete_Char(client, buf);
	}
	if (!client->RecvMsg()) delete client;//wsa 리시브 실행
}

cIn_Town_state::cIn_Town_state(cClientInfo* _client)
{
	client = _client;
}

void cIn_Town_state::RecvProc()
{
	cProtocol Protocol;
	cBuf buf;
	client->UnPack(Protocol, buf);

	if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_ENTER_MAP))
	{
		cMapManger::GetInstance()->Req_Enter_Map(client, buf);
	}
	if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_OUT_MAP))
	{
		cMapManger::GetInstance()->Req_Out_Map(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_CHAT_DATA))
	{
		cChatManager::GetInstance()->Chat_Data(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_CHAR_MOVE_DATA))
	{
		cPlayerManager::GetInstance()->Char_Move_Data(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_CHAR_ACTION_DATA))
	{
		cPlayerManager::GetInstance()->Char_Action_Data(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_INVITE_PARTY))
	{
		cPartyManager::GetInstance()->Req_Invite_Party(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_INVITE_PARTY_RE))
	{
		cPartyManager::GetInstance()->Party_Invite_Re(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_OUT_PARTY))
	{
		cPartyManager::GetInstance()->Req_Out_Party(client, buf);
	}
	else if (Protocol.Protocol_Is_In(cProtocol::P::CLIENT_REQ_ENTER_DUNGEON))
	{
		cMapManger::GetInstance()->Req_Enter_Dungeon(client, buf);
	}

	if (!client->RecvMsg()) delete client;//wsa 리시브 실행
}

cIn_Dungeon_state::cIn_Dungeon_state(cClientInfo * _client)
{
	client = _client;
}

void cIn_Dungeon_state::RecvProc()
{
	cProtocol Protocol;
	cBuf buf;
	client->UnPack(Protocol, buf);
}
