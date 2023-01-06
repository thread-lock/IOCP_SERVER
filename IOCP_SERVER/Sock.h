#pragma once
#ifndef SOCK_H
#define SOCK_H
#include "Global.h"



//�⺻ ���� Ŭ����
class cSock
{
	//wsa �ʱ�ȭ������ ���� ����
	static int mSockCount;
protected:
	//��������, ���ú� ����
	SOCKET mSock;
	SOCKADDR_IN mAddr;
public:
	cSock();
	cSock(SOCKET, SOCKADDR_IN);
	virtual ~cSock();
	//���� ���� ��ȯ
	const SOCKET GetSock();
	const SOCKADDR_IN& GetAddr();
};

//tcp ���� ����
class cTcpServer : public cSock
{
public:
	cTcpServer(char*, int);
	cTcpServer(ULONG, int);
	virtual ~cTcpServer();
	//�����û �ޱ�
	bool Accept(SOCKET&, SOCKADDR_IN&);
};

//tcp Ŭ�� ����
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

