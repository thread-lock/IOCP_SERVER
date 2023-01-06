#pragma once
#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include "VLPacket.h"
#include "User.h"
#include "Charactor.h"
#include "State.h"



class cState;

class cCharactor;

//클라이언트 정보
class cClientInfo : public cVLPacket
{
	cUser* User_Info;
	cCharactor* Char_Info;
	cState* now_State;
	cState* State[eSTATE::STATE_COUNT];
public:
	//생성자, 소멸자
	cClientInfo(SOCKET, SOCKADDR_IN);
	~cClientInfo();

	//Get
	cState* Get_State();
	cUser* Get_User_Info();
	cCharactor* Get_Char_Info();

	//Set
	void Set_State(eSTATE);
	void Set_User_Info(cUser*);
	void Set_Char_Info(cCharactor*);

	//비동기 입출력 recv,send
	bool SendMsg();
	bool RecvMsg();
};
#endif // !CLIENTINFO_H

