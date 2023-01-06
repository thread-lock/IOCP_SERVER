#include "Sock.h"
#include "ErrManager.h"

//인스턴스 초기화
int cSock::mSockCount = 0;


cSock::cSock()//기본 생성자
{
	if (mSockCount == 0)  //아직 생성된 소켓이 없다면
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//윈도우 dll 초기화 윈속 할당
			exit(-1);
	}
	mSock = NULL; //소켓 초기화
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //주소 메모리 초기화
	mSockCount++; //총 소켓수 증가
}

cSock::cSock(SOCKET _sock, SOCKADDR_IN _addr)//생성자
{
	if (mSockCount == 0)  //아직 생성된 소켓이 없다면
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//윈도우 dll 초기화 윈속 할당
			exit(-1);
	}
	mSock = _sock;//소켓 대입
	memcpy(&mAddr, &_addr, sizeof(SOCKADDR_IN)); //주소 복사
	mSockCount++;//총 소켓수 증가
}

cSock::~cSock()//소멸자
{
	closesocket(mSock);//소켓 반환
	mSockCount--;//총소켓수 감소
	if (mSockCount == 0) //총 소켓수가 0이면
	{
		WSACleanup();//윈도우 dll 초기화 윈속 반환
	}
}

const SOCKET cSock::GetSock()//소켓 반환
{
	return mSock;
}

const SOCKADDR_IN& cSock::GetAddr()//주소 반환
{
	return mAddr;
}

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


cTcpServer::cTcpServer(char* _serveraddr, int _serverport) //생성자
{
	int retval;

	// TCP socket()
	mSock = socket(AF_INET, SOCK_STREAM, 0); //tcp , ipv4 로 소켓 생성
	if (mSock == INVALID_SOCKET) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("socket()"); //생성실패시 에러 출력 종료

																											   //SO_REUSEADDR
	BOOL optval = TRUE;
	retval = setsockopt(mSock, SOL_SOCKET,// REUSEADDR 설정
		SO_REUSEADDR, (char *)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("setsockopt()");//소켓 에러시 출력 종료


																												 // bind()
	ZeroMemory(&mAddr, sizeof(mAddr)); //mAddr 초기화
	mAddr.sin_family = AF_INET; //ipv4
	mAddr.sin_port = htons(_serverport);//서버 포트
	mAddr.sin_addr.s_addr = inet_addr(_serveraddr);//서버 주소
	retval = bind(mSock, (SOCKADDR *)&mAddr, sizeof(mAddr)); //설정 주소로 바인딩
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("bind()"); //bind 에러시 출력 종료

																											// listen()
	retval = listen(mSock, SOMAXCONN); //listen 소켓으로 설정
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("listen()"); //listen 에러시 출력 종료

}

cTcpServer::cTcpServer(ULONG _serveraddr, int _serverport)
{
	int retval;

	// TCP socket()
	mSock = socket(AF_INET, SOCK_STREAM, 0);
	if (mSock == INVALID_SOCKET) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("socket()");//생성실패시 에러 출력 종료

    //SO_REUSEADDR
	BOOL optval = TRUE;
	retval = setsockopt(mSock, SOL_SOCKET, // REUSEADDR 설정
		SO_REUSEADDR, (char *)&optval, sizeof(optval));
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("setsockopt()");//소켓 에러시 출력 종료

	// bind()
	ZeroMemory(&mAddr, sizeof(SOCKADDR_IN)); //mAddr 초기화
	mAddr.sin_family = AF_INET;//ipv4
	mAddr.sin_port = htons(_serverport);//서버 포트
	mAddr.sin_addr.s_addr = htonl(_serveraddr);//서버 주소
	retval = bind(mSock, (SOCKADDR *)&mAddr, sizeof(mAddr));//설정 주소로 바인딩
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("bind()");  //bind 에러시 출력 종료

	// listen()
	retval = listen(mSock, SOMAXCONN); //listen 소켓으로 설정
	if (retval == SOCKET_ERROR) cErrManager::GetInstance()->cErrManager::GetInstance()->err_quit("listen()"); //listen 에러시 출력 종료
}

cTcpServer::~cTcpServer()//소멸자
{

}

//클라 접속 요청 받음
bool cTcpServer::Accept(SOCKET& _clientsock, SOCKADDR_IN& _clientaddr)
{
	int addrlen = sizeof(_clientaddr);
	_clientsock = accept(mSock, (SOCKADDR *)&_clientaddr, &addrlen);//클라접속 요청 받음 클라 소켓과 주소를 외부로 전달
	if (_clientsock == INVALID_SOCKET)//소캣 생성 실패시
	{
		cErrManager::GetInstance()->err_display("accept()");// 에러메세지 출력
		return false; //실패 반환
	}
	return true; //성공 반환
}

//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

cTcpClient::cTcpClient(SOCKET socket, SOCKADDR_IN addr) : cSock(socket, addr) //생성자
{

}

cTcpClient::~cTcpClient() //소멸자
{

}

int cTcpClient::Send(char* _buf, int _size, int _flags, bool _quit)
{
	int retval = send(mSock, _buf, _size, _flags); //외부에서 버퍼로 send
	if (retval == SOCKET_ERROR)
	{
		if (!_quit)//quit가 true 일때 오류가 날시 에러를 출력하고 창을 닫는다
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
	int retval = recv(mSock, _buf, _size, _flags);//외부 버퍼로 recv 
	if (retval == SOCKET_ERROR)
	{
		if (!_quit)//quit가 true 일때 오류가 날시 에러를 출력하고 창을 닫는다
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

int cTcpClient::Recvn(char* _buf, int _size, int _flags)//외부버퍼로 recv
{
	int received;
	char *ptr = _buf;
	int left = _size;

	while (left > 0) {//받을 메모리가 남아있다면
		received = recv(mSock, ptr, left, _flags);//데이터를 수신버퍼에서 가져옴
		if (received == SOCKET_ERROR)//에러체크
			return SOCKET_ERROR;//에러반환
		else if (received == 0)//종료체크
			break;//반복문 탈출
		left -= received;//목표 메모리에서 실제가져온 용량만큼 빼서 저장
		ptr += received;//받음만큼 주소를 이동시킴 데이터를 이어받기 위해
	}

	return (_size - left);//받은데이터 리턴
}



