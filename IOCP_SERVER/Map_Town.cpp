#include "Map_Town.h"

cMap_Town * cMap_Town::mInstance = NULL; //�ν��Ͻ� �ʱ�ȭ

void cMap_Town::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cMap_Town();
	}
}

cMap_Town * cMap_Town::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cMap_Town();
	}
	return mInstance;
}

void cMap_Town::Destroy() //�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

void cMap_Town::Map_Enter_Data_Send(cClientInfo* _player)
{
	Enter_CS();

	cBuf buf;

	buf.Append((int)(mPlayer_List.size() - 1));
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		buf.Append((*i)->Get_Char_Info()->Get_Char_Code());
		buf.Append((char*)(*i)->Get_Char_Info()->GetName());
		buf.Append((*i)->Get_Char_Info()->Get_Job().mCode);
		buf.Append((*i)->Get_Char_Info()->Get_Location().GetX());
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_DATA);
	_player->Pack(protocol, buf);
	_player->SendMsg();

	Out_CS();
}



void cMap_Town::Enter_Player_Data_Send(cClientInfo* _player)
{
	Enter_CS();

	cBuf buf;
	//�ʿ� ���ο� �÷��̾ ���Դ� (ĳ������ �ڵ�(�̸�), ���� ��ġ)
	buf.Append(_player->Get_Char_Info()->Get_Char_Code());
	buf.Append((char*)_player->Get_Char_Info()->GetName());
	buf.Append(_player->Get_Char_Info()->Get_Job().mCode);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_ENTER_NEW_CHAR_DATA);
	//���� ���� �÷��̾ ���Դٰ� Ŭ���̾�Ʈ�� �˸�(Ŭ���̾�Ʈ������ �ش���ġ�� ������Ʈ ����)
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

cMap_Town::cMap_Town()
{
	//mCode = TOWN_MAP_CODE;
}

cMap_Town::~cMap_Town()
{

}

