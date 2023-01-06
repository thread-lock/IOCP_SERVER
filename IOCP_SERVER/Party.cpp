#include "Room.h"

int cParty::CodeMaker = 0;

cParty::cParty()
{
	mCode = CodeMaker++;
}

cClientInfo * cParty::Get_Leader()
{
	return mPlayer_List.front();
}

void cParty::Party_Enter_Data_Send(cClientInfo* _player)
{

	Enter_CS();

	cBuf buf;
	buf.Append((int)(mPlayer_List.size() - 1));
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		buf.Append((*i)->Get_Char_Info()->Get_Char_Code());
		buf.Append((*i)->Get_Char_Info()->Get_Ability().Get_Max_Hp());
		buf.Append((*i)->Get_Char_Info()->Get_Ability().Now_Hp);
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_DATA);
	_player->Pack(protocol, buf);
	_player->SendMsg();

	Out_CS();
}

void cParty::Enter_Player_Data_Send(cClientInfo * _player)
{
	Enter_CS();

	cBuf buf;
	//맵에 새로운 플레이어가 들어왔다 (캐릭터의 코드(이름), 현재 위치)
	buf.Append(_player->Get_Char_Info()->Get_Char_Code());
	buf.Append(_player->Get_Char_Info()->Get_Ability().Get_Max_Hp());
	buf.Append(_player->Get_Char_Info()->Get_Ability().Now_Hp);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_ENTER_CHAR_DATA);
	//새로 들어온 플레이어가 들어왔다고 클라이언트에 알림(클라이언트에서는 해당위치에 오브젝트 생성)
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}


void cParty::Out_Player_Data_Send(cClientInfo * _player)
{
	Enter_CS();

	cBuf buf;

	buf.Append(_player->Get_Char_Info()->Get_Char_Code());

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_OUT_CHAR_DATA);
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

void cParty::Player_Enter_Dungeon(cMap* _entermap)
{
	Enter_CS();



	//파티원들 파티장 제외하고 맵 모두 던전으로 설정
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == Get_Leader()) continue;

		//마을에서 플레이어 나감
		cMap* map = (*i)->Get_Char_Info()->Get_Enter_Map();
		map->Out_Player((*i));
		map->Out_Player_Data_Send((*i));

		_entermap->Enter_Player((*i));
		(*i)->Get_Char_Info()->Set_Enter_Map(_entermap);
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_ENTER_DUNGEON);
	//던전 입장하라고 알림
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == Get_Leader()) continue;

		(*i)->Pack(protocol);
		(*i)->SendMsg();
	}



	Out_CS();
}



