#pragma once
#ifndef PARTYMANAGER_H
#define PARTYMANAGER_H
#include "ClientInfo.h"

class cPartyManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cPartyManager();
	~cPartyManager();
	static cPartyManager * mInstance;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cPartyManager * GetInstance();
	static void Destroy();

	//∆ƒ∆º ∏≈¥œ¿˙
	void Req_Invite_Party(cClientInfo* _info, cBuf & _data);
	void Party_Invite_Re(cClientInfo* _info, cBuf & _data);
	void Req_Out_Party(cClientInfo* _info, cBuf & _data);

};






#endif // !PARTYMANAGER_H
