#pragma once
#ifndef STATE_H
#define STATE_H
enum eSTATE { NONE = -1, LOG_IN_STATE, CHAR_STATE, IN_TOWN_STATE , IN_DUNGEON_STATE, STATE_COUNT};
#include "ClientInfo.h"

class cClientInfo;

class cState
{
protected:
	cClientInfo * client;
public:
	static void CreateState(cClientInfo* _client, cState* _state[]);
	static void DeleteState(cState* _state[]);

	virtual void RecvProc() = 0;
	virtual void SendProc();
};


class cLog_in_state : public cState
{
public:
	cLog_in_state(cClientInfo* _client);
	void RecvProc();
};

class cChar_state : public cState
{
public:
	cChar_state(cClientInfo* _client);
	void RecvProc();
};

class cIn_Town_state : public cState
{
public:
	cIn_Town_state(cClientInfo* _client);
	void RecvProc();
};


class cIn_Dungeon_state : public cState
{
public:
	cIn_Dungeon_state(cClientInfo* _client);
	void RecvProc();
};


#endif // !STATE_H
