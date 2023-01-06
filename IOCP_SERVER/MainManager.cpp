#include "MainManager.h"
#include "ErrManager.h"
#include "DBManager.h"

cMainManager * cMainManager::mInstance = NULL;//인스턴스 초기화

void cMainManager::Create()//싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cMainManager();
	}
	cThreadManager::Create();
	cErrManager::Create(); //에러 매니저 생성
}

cMainManager * cMainManager::GetInstance()//인스턴스 반환
{
	return mInstance;
}

void cMainManager::Destroy()//싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
	cErrManager::Destroy();//에러 매니저 삭제
	cThreadManager::Destroy();
}

cMainManager::cMainManager()//생성자
{

}

cMainManager::~cMainManager()//소멸자
{

}

void cMainManager::Run() //메인스레드 함수
{
	Initialize();

	cTcpServer* server = new cTcpServer(INADDR_ANY, SERVERPORT); //TCP 서버 생성

	 //접속한 클라 정보 받을 변수
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;

	DBManager::GetInstance()->Init();

	//접속요청 받음 받을시 true 리턴
	while (server->Accept(clientsock, clientaddr))
	{
		cClientInfo* mClient = new cClientInfo(clientsock, clientaddr);//클라이언트 정보 생성
		AcceptProcess(mClient);
	}
	DBManager::GetInstance()->End();
	End();
}

void cMainManager::AcceptProcess(cClientInfo * _client)
{
	CreateIoCompletionPort((HANDLE)_client->GetSock(), mPort, (ULONG_PTR)_client, 0);//포트에 클라이언트 연결 컴플리션키는 클라이언트 객체로
	if (!_client->RecvMsg()) delete _client;//wsa 리시브 실행
}

void cMainManager::RecvProcess(cClientInfo * _client, DWORD _trans)
{
	if (_client->IsRecvSuccess(_trans))
	{	
		_client->Get_State()->RecvProc();
	}
	else
	{
		if (!_client->RecvMsg()) delete _client;//wsa 리시브 실행
	}
}

void cMainManager::SendProcess(cClientInfo * _client, DWORD _trans)
{
	if (_client->IsSendSuccess(_trans))
	{
		_client->Get_State()->SendProc();
	}
	else
	{
		if (!_client->SendMsg()) delete _client;//wsa 리시브 실행
	}
}

void cMainManager::DisconnectProcess(cClientInfo * _client)
{
	delete _client;
}
