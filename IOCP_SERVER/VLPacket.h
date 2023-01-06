#pragma once
#ifndef VLPACKET_H
#define VLPACKET_H
#include "Global.h"
#include "Sock.h"
#include "Buf.h"
#include "Protocol.h"
#include <queue>
using std::queue;

struct WSAoverlapEX
{
	OVERLAPPED overlapped;
	WSABUF wsabuf;
};


//가변길이 패킷 클래스
class cVLPacket : public cTcpClient
{
private:
	cBuf mRecvBuf;//send버퍼 배열
	queue<cBuf*> mSendBuf;//send버퍼 배열
	WSAoverlapEX mRecvOverlap;
	WSAoverlapEX mSendOverlap;
protected:
	bool SendPacket();
	bool RecvPacket();
	bool WSArecvPacket();
	bool WSAsendPacket();
public:
	cVLPacket(SOCKET, SOCKADDR_IN);
	virtual ~cVLPacket();
	//패킹,언패킹
	void UnPack(cProtocol&, cBuf&);
	void Pack(const cProtocol&, cBuf&);//패킹하고 패킹된 버퍼의 인덱스를 보내준다.
	void Pack(const cProtocol&);//패킹하고 패킹된 버퍼의 인덱스를 보내준다.
	//가변길이 패킷 recv,send (현재 프로그램에서 사용안함)

	bool IsPacking();
	bool IsSendSuccess(int _trans);
	bool IsRecvSuccess(int _trans);
	bool IsRecvOverLap(OVERLAPPED* _overlap);
	bool IsSendOverLap(OVERLAPPED* _overlap);

};

#endif // !VLPACKET_H
