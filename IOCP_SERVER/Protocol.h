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
		CLIENT_REQ_ENTER_MAP, //�÷��̾� �� ���� ��û
		SERVER_MAP_DATA, //������ ĳ���Ϳ��� �ʱ� �� ������ ����(�ڽ� ����)
		SERVER_MAP_ENTER_NEW_CHAR_DATA, //�ٸ� �����鿡�� ���ο� ������ ���Դ� �˸�
		CLIENT_REQ_OUT_MAP,
		SERVER_MAP_OUT_CHAR_DATA, //�ٸ� �����鿡�� ���� ������ ����Ÿ ����
		CLIENT_CHAR_MOVE_DATA, //ĳ���Ͱ� �����δٰ� �������� �˸�
		SERVER_MOVE_CHAR_DATA, //�ٸ� ĳ���Ͱ� �������ٰ� �˸�
		CLIENT_CHAR_ACTION_DATA,
		SERVER_ACTION_CHAR_DATA,
		CLIENT_REQ_INVITE_PARTY, //�÷��̾ ��Ƽ �ʴ븦 ��û
		SERVER_RE_INVITE_PARTY,//
		SERVER_INVITE_PARTY_REQ,//�ٸ� �÷��̾�� ��Ƽ �ʴ�â�� ��
		CLIENT_INVITE_PARTY_RE,//��Ƽ �ʴ븦 �����ߴ��� ����
		SERVER_PARTY_DATA, //������ ĳ���Ϳ��� �� ������ ����
		SERVER_PARTY_ENTER_CHAR_DATA, //�ٸ� �����鿡�� ���ο� ������ ���Դ� �˸�
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
