#include "IocpManager.h"
#include "ErrManager.h"

DWORD cIocpManager::Procces(void * _arg)
{
	int retval;
	DWORD cbTransferred;
	cClientInfo* client;
	LPOVERLAPPED overlap;
	while (1)
	{	
		retval = GetQueuedCompletionStatus(mPort, &cbTransferred,(PULONG_PTR)&client,&overlap, INFINITE); //�񵿱� ������� �Ϸ�Ǳ⸦ ��ٸ�
		
		if (overlap == &mExit) return 1;

		if (retval == 0 || cbTransferred == 0) //Ŭ���̾�Ʈ ���� ����
		{
			if (retval == 0)//������ ����
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//���� �������� Ȯ��
				cErrManager::GetInstance()->err_display("WSAGetOverlappedResult()");//���� ���
			}
			DisconnectProcess(client);
			continue;
		}

		if (client->IsRecvOverLap(overlap)) RecvProcess(client, cbTransferred);
		if (client->IsSendOverLap(overlap)) SendProcess(client, cbTransferred);
	}
}

bool cIocpManager::Initialize()
{
	mThreadCount = 0;
	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // ����� �Ϸ� ��Ʈ ����
	if (mPort == NULL) return false;

	// CPU ���� Ȯ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU ���� * 2)���� �۾��� ������ ����
	HANDLE hThread;
	for (int i = 0; i<(int)si.dwNumberOfProcessors * 2; i++) {
		hThread = cThreadManager::GetInstance()->AddThread(0, this);
		if (hThread == NULL) return false;
		CloseHandle(hThread);
	}
	mThreadCount = (int)si.dwNumberOfProcessors * 2;
	return true;
}

void cIocpManager::End()
{
	ZeroMemory(&mExit, sizeof(mExit));
	for (int i = 0; i < mThreadCount; i++)
	{
		PostQueuedCompletionStatus(mPort, 1, NULL, &mExit);
	}
	CloseHandle(mPort);

}
