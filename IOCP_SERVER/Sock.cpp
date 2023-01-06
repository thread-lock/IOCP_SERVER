#include "Sock.h"
#include "ErrManager.h"

//�ν��Ͻ� �ʱ�ȭ
int cSock::mSockCount = 0;


cSock::cSock()//�⺻ ������
{
	if (mSockCount == 0)  //���� ������ ������ ���ٸ�
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//������ dll �ʱ�ȭ ���� �Ҵ�
			exit(-1);
	}
	mSock = NULL; //���� �ʱ�ȭ
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //�ּ� �޸� �ʱ�ȭ
	mSockCount++; //�� ���ϼ� ����
}

cSock::cSock(SOCKET _sock, SOCKADDR_IN _addr)//������
{
	if (mSockCount == 0)  //���� ������ ������ ���ٸ�
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//������ dll �ʱ�ȭ ���� �Ҵ�
			exit(-1);
	}
	mSock = _sock;//���� ����
	memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //�ּ� ����
	mSockCount++;//�� ���ϼ� ����
}

cSock::~cSock()//�Ҹ���
{
	closesocket(mSock);//���� ��ȯ
	mSockCount--;//�Ѽ��ϼ� ����
	if (mSockCount == 0) //�� ���ϼ��� 0�̸�
	{
		WSACleanup();//������ dll �ʱ�ȭ ���� ��ȯ
	}
}

const SOCKET cSock::GetSock()//���� ��ȯ
{
	return mSock;
}

const SOCKADDR_IN& cSock::GetAddr()//�ּ� ��ȯ
{
	return mAddr;
}

//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�


cTcpServer::cTcpServer(char* _serveraddr, int _serverport) //������
{
	int retval;

	// TCP socket()
	mSock = socket(AF_INET, SOCK_STREAM, 0); //tcp , ipv4 �� ���� ����
	if (mSock == INVALID_SOCKET) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("socket()"); //�������н� ���� ��� ����

																											   //SO_REUSEADDR
	BOOL optval = TRUE;
	retval = setsockopt(mSock, SOL_SOCKET,// REUSEADDR ����
		SO_REUSEADDR, (char *)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("setsockopt()");//���� ������ ��� ����


																												 // bind()
	ZeroMemory(&mAddr, sizeof(mAddr)); //mAddr �ʱ�ȭ
	mAddr.sin_family = AF_INET; //ipv4
	mAddr.sin_port = htons(_serverport);//���� ��Ʈ
	mAddr.sin_addr.s_addr = inet_addr(_serveraddr);//���� �ּ�
	retval = bind(mSock, (SOCKADDR *)&mAddr, sizeof(mAddr)); //���� �ּҷ� ���ε�
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("bind()"); //bind ������ ��� ����

																											// listen()
	retval = listen(mSock, SOMAXCONN); //listen �������� ����
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("listen()"); //listen ������ ��� ����

}

cTcpServer::cTcpServer(ULONG _serveraddr, int _serverport)
{
	int retval;

	// TCP socket()
	mSock = socket(AF_INET, SOCK_STREAM, 0);
	if (mSock == INVALID_SOCKET) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("socket()");//�������н� ���� ��� ����

    //SO_REUSEADDR
	BOOL optval = TRUE;
	retval = setsockopt(mSock, SOL_SOCKET, // REUSEADDR ����
		SO_REUSEADDR, (char *)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("setsockopt()");//���� ������ ��� ����

	// bind()
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //mAddr �ʱ�ȭ
	mAddr.sin_family = AF_INET;//ipv4
	mAddr.sin_port = htons(_serverport);//���� ��Ʈ
	mAddr.sin_addr.s_addr = htonl(_serveraddr);//���� �ּ�
	retval = bind(mSock, (SOCKADDR *)&mAddr, sizeof(mAddr));//���� �ּҷ� ���ε�
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("bind()");  //bind ������ ��� ����

	// listen()
	retval = listen(mSock, SOMAXCONN); //listen �������� ����
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("listen()"); //listen ������ ��� ����
}

cTcpServer::~cTcpServer()//�Ҹ���
{

}

//Ŭ�� ���� ��û ����
bool cTcpServer::Accept(SOCKET& _clientsock, SOCKADDR_IN& _clientaddr)
{
	int addrlen = sizeof(_clientaddr);
	_clientsock = accept(mSock, (SOCKADDR *)&_clientaddr, &addrlen);//Ŭ������ ��û ���� Ŭ�� ���ϰ� �ּҸ� �ܺη� ����
	if (_clientsock == INVALID_SOCKET)//��Ĺ ���� ���н�
	{
		cErrManager::GetInstance()->err_display("accept()");// �����޼��� ���
		return false; //���� ��ȯ
	}
	return true; //���� ��ȯ
}

//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

cTcpClient::cTcpClient(SOCKET socket, SOCKADDR_IN addr) : cSock(socket, addr) //������
{

}

cTcpClient::~cTcpClient() //�Ҹ���
{

}

int cTcpClient::Send(char* _buf, int _size, int _flags, bool _quit)
{
	int retval = send(mSock, _buf, _size, _flags); //�ܺο��� ���۷� send
	if (retval == SOCKET_ERROR)
	{
		if (!_quit)//quit�� true �϶� ������ ���� ������ ����ϰ� â�� �ݴ´�
		{
			cErrManager::GetInstance()->err_display("send()");
		}
		else
		{
			cErrManager::GetInstance()->err_quit("send()");
		}
	}
	return retval;
}


int cTcpClient::Recv(char* _buf, int _size, int _flags, bool _quit)
{
	int retval = recv(mSock, _buf, _size, _flags);//�ܺ� ���۷� recv 
	if (retval == SOCKET_ERROR)
	{
		if (!_quit)//quit�� true �϶� ������ ���� ������ ����ϰ� â�� �ݴ´�
		{
			cErrManager::GetInstance()->err_display("recv()");
			return retval;
		}
		else
		{
			cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("recv()");
			return retval;
		}
	}
	else if (retval == 0)
	{
		return retval;
	}
	return retval;
}

int cTcpClient::Recvn(char* _buf, int _size, int _flags)//�ܺι��۷� recv
{
	int received;
	char *ptr = _buf;
	int left = _size;

	while (left > 0) {//���� �޸𸮰� �����ִٸ�
		received = recv(mSock, ptr, left, _flags);//�����͸� ���Ź��ۿ��� ������
		if (received == SOCKET_ERROR)//����üũ
			return SOCKET_ERROR;//������ȯ
		else if (received == 0)//����üũ
			break;//�ݺ��� Ż��
		left -= received;//��ǥ �޸𸮿��� ���������� �뷮��ŭ ���� ����
		ptr += received;//������ŭ �ּҸ� �̵���Ŵ �����͸� �̾�ޱ� ����
	}

	return (_size - left);//���������� ����
}



