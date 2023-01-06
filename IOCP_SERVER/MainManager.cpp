#include "MainManager.h"
#include "ErrManager.h"
#include "DBManager.h"

cMainManager * cMainManager::mInstance = NULL;//�ν��Ͻ� �ʱ�ȭ

void cMainManager::Create()//�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cMainManager();
	}
	cThreadManager::Create();
	cErrManager::Create(); //���� �Ŵ��� ����
}

cMainManager * cMainManager::GetInstance()//�ν��Ͻ� ��ȯ
{
	return mInstance;
}

void cMainManager::Destroy()//�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
	cErrManager::Destroy();//���� �Ŵ��� ����
	cThreadManager::Destroy();
}

cMainManager::cMainManager()//������
{

}

cMainManager::~cMainManager()//�Ҹ���
{

}

void cMainManager::Run() //���ν����� �Լ�
{
	Initialize();

	cTcpServer* server = new cTcpServer(INADDR_ANY, SERVERPORT); //TCP ���� ����

	 //������ Ŭ�� ���� ���� ����
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;

	DBManager::GetInstance()->Init();

	//���ӿ�û ���� ������ true ����
	while (server->Accept(clientsock, clientaddr))
	{
		cClientInfo* mClient = new cClientInfo(clientsock, clientaddr);//Ŭ���̾�Ʈ ���� ����
		AcceptProcess(mClient);
	}
	DBManager::GetInstance()->End();
	End();
}

void cMainManager::AcceptProcess(cClientInfo * _client)
{
	CreateIoCompletionPort((HANDLE)_client->GetSock(), mPort, (ULONG_PTR)_client, 0);//��Ʈ�� Ŭ���̾�Ʈ ���� ���ø���Ű�� Ŭ���̾�Ʈ ��ü��
	if (!_client->RecvMsg()) delete _client;//wsa ���ú� ����
}

void cMainManager::RecvProcess(cClientInfo * _client, DWORD _trans)
{
	if (_client->IsRecvSuccess(_trans))
	{	
		_client->Get_State()->RecvProc();
	}
	else
	{
		if (!_client->RecvMsg()) delete _client;//wsa ���ú� ����
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
		if (!_client->SendMsg()) delete _client;//wsa ���ú� ����
	}
}

void cMainManager::DisconnectProcess(cClientInfo * _client)
{
	delete _client;
}
