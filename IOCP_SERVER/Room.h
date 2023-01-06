#pragma once
#ifndef ROOM_H
#define ROOM_H
#include "ClientInfo.h"
#include <list>
class cClientInfo;
using std::list;


class cRoom
{
protected:
	int mCode;
	list<cClientInfo*> mPlayer_List;
	list<cClientInfo*>::iterator mSearch;

	CRITICAL_SECTION cs;
public:
	cRoom();
	~cRoom();
	int Get_Code();
	int Get_Count();
	virtual bool Enter_Player(cClientInfo* _player);
	virtual bool Out_Player(cClientInfo* _player);

	void SearchStart();
	bool SearchData(cClientInfo*&);

	void Enter_CS();
	void Out_CS();
};


class cMap : public cRoom
{

public:
	cMap();

	virtual void Map_Enter_Data_Send(cClientInfo*) = 0;
	virtual void Enter_Player_Data_Send(cClientInfo*) = 0;

	virtual void Out_Player_Data_Send(cClientInfo*);
	virtual void Player_Action_Data_Send(cClientInfo*, Chractor_Action,bool );
	virtual void Player_Move_Data_Send(cClientInfo*, int);
	virtual void Player_Chat_Data_Send(cClientInfo*, char*);

	virtual void Req_Party_invite(cClientInfo*, int);
	virtual void Re_Party_invite(cClientInfo*,char*);


};

class cParty : public cRoom
{
	static int CodeMaker;
public:
	cParty();
	cClientInfo * Get_Leader();

	void Party_Enter_Data_Send(cClientInfo*);
	void Enter_Player_Data_Send(cClientInfo*);


	void Out_Player_Data_Send(cClientInfo*);

	void Player_Enter_Dungeon(cMap*);

	void Player_State_Data_Send(cClientInfo*);






}; 







#endif // !ROOM_H
