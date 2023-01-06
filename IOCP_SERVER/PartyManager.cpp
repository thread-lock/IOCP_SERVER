#include "PartyManager.h"
#include "PlayerManager.h"

cPartyManager * cPartyManager::mInstance = nullptr; //�ν��Ͻ� �ʱ�ȭ

void cPartyManager::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cPartyManager();
	}
} 

cPartyManager * cPartyManager::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cPartyManager();
	}
	return mInstance;
}

void cPartyManager::Destroy() //�̱��� ����
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

	//��Ƽ�� ���� �������� �ʾ��� ��� ������
	if (player->Get_Enter_Party() == nullptr)
	{
		cParty* party = new cParty();
		party->Enter_Player(_info);
		player->Set_Enter_Party(party);
	}

	cProtocol protocol;

	//��Ƽ ������ �ƴ� ���
	if (player->Get_Enter_Party()->Get_Leader() != _info)
	{
		_data.Clear();
		_data.Append(false);
		_data.Append((char*) "������ �ƴմϴ�.");
		protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
		_info->Pack(protocol, _data);
		_info->SendMsg();
		return;
	}

	//��Ƽ�� �ο����� �ʰ� ���� ���
	if (player->Get_Enter_Party()->Get_Count() >= 4)
	{
		_data.Clear();
		_data.Append(false);
		_data.Append((char*) "��Ƽ �ο��� �ʰ��Դϴ�.");
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

