#pragma once
#ifndef PROTOCOL_H
#define PROTOCOL_H

class cProtocol
{
	__int64 protocol;
public:
	enum P
	{
		CLIENT_REQ_LOGIN,//
		SERVER_RE_LOGIN,//
		CLIENT_REQ_JOIN,//
		SERVER_RE_JOIN,//
		CLIENT_REQ_CHAR_INFO,//
		SERVER_RE_CHAR_INFO,//
		CLIENT_REQ_CREATE_CHAR,//
		SERVER_RE_CREATE_CHAR,//
		CLIENT_REQ_SELECT_CHAR,//
		SERVER_RE_SELECT_CHAR,//
		CLIENT_REQ_DELETE_CHAR,//
		SERVER_RE_DELETE_CHAR,//
		CLIENT_CHAT_DATA,//
		SERVER_CHAT_DATA,//
		CLIENT_REQ_ENTER_MAP, //플레이어 맵 접속 요청
		SERVER_MAP_DATA, //접속한 캐릭터에게 초기 맵 데이터 전송(자신 제외)
		SERVER_MAP_ENTER_NEW_CHAR_DATA, //다른 유저들에게 새로운 유저가 들어왔다 알림
		CLIENT_REQ_OUT_MAP,
		SERVER_MAP_OUT_CHAR_DATA, //다른 유저들에게 나간 유저의 데이타 전송
		CLIENT_CHAR_MOVE_DATA, //캐릭터가 움직인다고 서버에게 알림
		SERVER_MOVE_CHAR_DATA, //다른 캐릭터가 움직였다고 알림
		CLIENT_CHAR_ACTION_DATA,
		SERVER_ACTION_CHAR_DATA,
		CLIENT_REQ_INVITE_PARTY, //플레이어가 파티 초대를 요청
		SERVER_RE_INVITE_PARTY,//
		SERVER_INVITE_PARTY_REQ,//다른 플레이어에게 파티 초대창이 뜸
		CLIENT_INVITE_PARTY_RE,//파티 초대를 수락했는지 응답
		SERVER_PARTY_DATA, //접속한 캐릭터에게 맵 데이터 전송
		SERVER_PARTY_ENTER_CHAR_DATA, //다른 유저들에게 새로운 유저가 들어왔다 알림
		CLIENT_REQ_OUT_PARTY,
		SERVER_PARTY_OUT_CHAR_DATA,
		CLIENT_REQ_ENTER_DUNGEON,
		SERVER_RE_ENTER_DUNGEON,
		SERVER_PARTY_ENTER_DUNGEON,
		SERVER_MOB_STATE,
		CLIENT_EXIT,
	};
	cProtocol();
	cProtocol(__int64);
	__int64 GetProtocol() const;
	void Add_Protocol(P);
	bool Protocol_Is_In(P);
	void Reset();
private:
	__int64 Protocol_to_square(P);

};


#endif // !PROTOCOL_H
