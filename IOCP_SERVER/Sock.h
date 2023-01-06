#pragma once
#ifndef SOCK_H
#define SOCK_H
#include "Global.h"



//기본 소켓 클래스
class cSock
{
	//wsa 초기화를위한 전역 변수
	static int mSockCount;
protected:
	//소켓정보, 리시브 버퍼
	SOCKET mSock;
	SOCKADDR_IN mAddr;
public:
	cSock();
	cSock(SOCKET, SOCKADDR_IN);
	virtual ~cSock();
	//소켓 정보 반환
	const SOCKET GetSock();
	const SOCKADDR_IN& GetAddr();
};

//tcp 서버 소켓
class cTcpServer : public cSock
{
public:
	cTcpServer(char*, int);
	cTcpServer(ULONG, int);
	virtual ~cTcpServer();
	//연결요청 받기
	bool Accept(SOCKET&, SOCKADDR_IN&);
};

//tcp 클라 소켓
class cTcpClient : public cSock
{
protected:
	int Send(char*, int, int, bool);
	int Recv(char*, int, int, bool);
	int Recvn(char*, int, int);
public:
	cTcpClient(SOCKET, SOCKADDR_IN);
	virtual ~cTcpClient();


};



#endif // !SOCK_H

