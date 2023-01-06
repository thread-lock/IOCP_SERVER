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
		retval = GetQueuedCompletionStatus(mPort, &cbTransferred,(PULONG_PTR)&client,&overlap, INFINITE); //비동기 입출력이 완료되기를 기다림
		
		if (overlap == &mExit) return 1;

		if (retval == 0 || cbTransferred == 0) //클라이언트 강제 종료
		{
			if (retval == 0)//비정상 종료
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(client->GetSock(), overlap, &temp1, FALSE, &temp2);//무슨 에러인지 확인
				cErrManager::GetInstance()->err_display("WSAGetOverlappedResult()");//에러 출력
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
	mPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);  // 입출력 완료 포트 생성
	if (mPort == NULL) return false;

	// CPU 개수 확인
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU 개수 * 2)개의 작업자 스레드 생성
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
