#pragma once
#ifndef PARTYMANAGER_H
#define PARTYMANAGER_H
#include "ClientInfo.h"

class cPartyManager
{
	//�̱��� ����
	cPartyManager();
	~cPartyManager();
	static cPartyManager * mInstance;
public:
	//�̱��� ����
	static void Create();
	static cPartyManager * GetInstance();
	static void Destroy();

	//��Ƽ �Ŵ���
	void Req_Invite_Party(cClientInfo* _info, cBuf & _data);
	void Party_Invite_Re(cClientInfo* _info, cBuf & _data);
	void Req_Out_Party(cClientInfo* _info, cBuf & _data);

};






#endif // !PARTYMANAGER_H
