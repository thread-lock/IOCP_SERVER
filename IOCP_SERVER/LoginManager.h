#pragma once
#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H
#include "Global.h"
#include <list>
#include "ClientInfo.h"
#include "User.h"

using std::list;

class cLoginManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cLoginManager();
	~cLoginManager();
	static cLoginManager* mInstance;
	list<cUser*> user_list;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cLoginManager * GetInstance();
	static void Destroy();

	cUser* Get_Enter_User(char* _id);
	cUser* Get_Enter_User(int _code);
	bool Req_Login(cClientInfo* _info, cBuf& data);
	void Req_Join(cClientInfo* _info, cBuf& data);
	void Req_LogOut(cClientInfo* _info, cBuf& data);
	void Req_JoinOut(cClientInfo* _info, cBuf& data);


	void LogOut(cClientInfo* _info);

};




#endif // !LOGINMANAGER_H
