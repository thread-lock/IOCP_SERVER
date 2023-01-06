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


//�������� ��Ŷ Ŭ����
class cVLPacket : public cTcpClient
{
private:
	cBuf mRecvBuf;//send���� �迭
	queue<cBuf*> mSendBuf;//send���� �迭
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
	//��ŷ,����ŷ
	void UnPack(cProtocol&, cBuf&);
	void Pack(const cProtocol&, cBuf&);//��ŷ�ϰ� ��ŷ�� ������ �ε����� �����ش�.
	void Pack(const cProtocol&);//��ŷ�ϰ� ��ŷ�� ������ �ε����� �����ش�.
	//�������� ��Ŷ recv,send (���� ���α׷����� ������)

	bool IsPacking();
	bool IsSendSuccess(int _trans);
	bool IsRecvSuccess(int _trans);
	bool IsRecvOverLap(OVERLAPPED* _overlap);
	bool IsSendOverLap(OVERLAPPED* _overlap);

};

#endif // !VLPACKET_H
