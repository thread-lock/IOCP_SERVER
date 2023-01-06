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
	//�ʿ� ���ο� �÷��̾ ���Դ� (ĳ������ �ڵ�(�̸�), ���� ��ġ)
	buf.Append(_player->Get_Char_Info()->Get_Char_Code());
	buf.Append(_player->Get_Char_Info()->Get_Ability().Get_Max_Hp());
	buf.Append(_player->Get_Char_Info()->Get_Ability().Now_Hp);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_ENTER_CHAR_DATA);
	//���� ���� �÷��̾ ���Դٰ� Ŭ���̾�Ʈ�� �˸�(Ŭ���̾�Ʈ������ �ش���ġ�� ������Ʈ ����)
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



	//��Ƽ���� ��Ƽ�� �����ϰ� �� ��� �������� ����
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == Get_Leader()) continue;

		//�������� �÷��̾� ����
		cMap* map = (*i)->Get_Char_Info()->Get_Enter_Map();
		map->Out_Player((*i));
		map->Out_Player_Data_Send((*i));

		_entermap->Enter_Player((*i));
		(*i)->Get_Char_Info()->Set_Enter_Map(_entermap);
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_PARTY_ENTER_DUNGEON);
	//���� �����϶�� �˸�
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == Get_Leader()) continue;

		(*i)->Pack(protocol);
		(*i)->SendMsg();
	}



	Out_CS();
}



