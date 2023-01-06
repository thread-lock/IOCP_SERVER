#include "Room.h"
#include "Map_Town.h"

cMap::cMap()
{
}

void cMap::Out_Player_Data_Send(cClientInfo *_player)
{
	Enter_CS();

	cBuf buf;

	buf.Append(_player->Get_Char_Info()->Get_Char_Code());

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_OUT_CHAR_DATA);
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();

}

void cMap::Player_Action_Data_Send(cClientInfo* _player, Chractor_Action _action_type, bool _left)
{
	Enter_CS();

	cBuf buf;
	cProtocol protocol;

	buf.Append((int)_action_type);
	buf.Append(_left);
	buf.Append(_player->Get_Char_Info()->Get_Char_Code());

	protocol.Add_Protocol(cProtocol::P::SERVER_ACTION_CHAR_DATA);
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}


void cMap::Player_Move_Data_Send(cClientInfo* _player, int _move)
{
	Enter_CS();

	cBuf buf;

	cCharactor* pchar = _player->Get_Char_Info();

	buf.Append(pchar->Get_Char_Code());
	buf.Append(_move);
	buf.Append(pchar->Get_Location().GetX());
	buf.Append(pchar->Get_Location().GetY());

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MOVE_CHAR_DATA);

	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}



void cMap::Player_Chat_Data_Send(cClientInfo * _player, char * _str)
{
	Enter_CS();

	cBuf buf;
	buf.Append((char*)_player->Get_Char_Info()->GetName());
	buf.Append((char*)_str);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_CHAT_DATA);

	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

void cMap::Req_Party_invite(cClientInfo * _info, int _code)
{
	Enter_CS();

	cClientInfo* invite = nullptr;
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i)->Get_Char_Info()->Get_Char_Code() == _code)
		{
			invite = (*i);
			break;
		}
	}

	cProtocol protocol;
	cBuf buf;

	//초대할 플레이어 코드를 찾았어 초대
	if (invite != nullptr)
	{
		//초대한 플레이어가 파티에 가입되있지 않을 경우
		if (invite->Get_Char_Info()->Get_Enter_Party() == nullptr)
		{
			buf.Append((char*)_info->Get_Char_Info()->GetName());
			protocol.Add_Protocol(cProtocol::P::SERVER_INVITE_PARTY_REQ);
			invite->Pack(protocol, buf);
			invite->SendMsg();
		}
		else
		{
			buf.Append(false);
			buf.Append((char*) "다른 파티에 가입중 입니다.");
			protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
			_info->Pack(protocol, buf);
			_info->SendMsg();
		}
	}
	else
	{
		buf.Append(false);
		buf.Append((char*) "존재하지 않는 유저");
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
		_info->Pack(protocol, buf);
		_info->SendMsg();
	}

	Out_CS();
}

void cMap::Re_Party_invite(cClientInfo* _info, char * _leadername)
{
	Enter_CS();

	cClientInfo* Leader = nullptr;
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if (!strcmp((*i)->Get_Char_Info()->GetName(), _leadername))
		{
			Leader = (*i);
			break;
		}
	}


	if (Leader != nullptr)
	{
		cParty* party = Leader->Get_Char_Info()->Get_Enter_Party();
		if (party != nullptr)
		{
			party->Enter_Player(_info);
			_info->Get_Char_Info()->Set_Enter_Party(party);
			party->Party_Enter_Data_Send(_info);
			party->Enter_Player_Data_Send(_info);
		}
	}

	Out_CS();
}
