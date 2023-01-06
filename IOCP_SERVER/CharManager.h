#pragma once
#ifndef CHARMANAGER_H
#define CHARMANAGER_H
#include "Global.h"
#include "ClientInfo.h"
#include "Charactor.h"
#include <list>
using std::list;

class cCharManager
{
	//ΩÃ±€≈Ê ∆–≈œ
	cCharManager();
	~cCharManager();
	static cCharManager* mInstance;
	list<cCharactor*> mChar_List;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cCharManager * GetInstance();
	static void Destroy();

	cCharactor* Get_Char(int _code);

	void Req_Char_Info(cClientInfo* _info, cBuf& data);
	void Req_Create_Char(cClientInfo* _info, cBuf& data);
	bool Req_Select_Char(cClientInfo* _info, cBuf& data);
	void Req_Delete_Char(cClientInfo* _info, cBuf& data);
	void Req_Char_Out(cClientInfo* _info, cBuf& data);


	void Char_Out(cClientInfo* _info);



};

#endif // !CHARMANAGER_H
