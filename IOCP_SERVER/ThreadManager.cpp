#include "ThreadManager.h"

cThreadManager* cThreadManager::mInstance = nullptr;

cThreadManager::cThreadManager()
{

}

cThreadManager::~cThreadManager()
{

}

void cThreadManager::Create()
{
	if (mInstance == nullptr)
	{
		mInstance = new cThreadManager();
	}
}
cThreadManager* cThreadManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new cThreadManager();
	}
	return mInstance;
}
void cThreadManager::Destroy()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

HANDLE cThreadManager::AddThread(LPVOID data, cThreadUse* _pthis)
{
	HANDLE handle = CreateThread(NULL, 0, ThreadProcess, _pthis, 0, NULL);
	sThreadData* t = new sThreadData();
	t->data = data;
	t->thread = handle;
	mThreadList.push_back(t);
	return handle;
}

// 스레드 제거
void cThreadManager::RemoveThread(HANDLE thread)
{
	sThreadData* data;
	for (list<sThreadData*>::iterator i = mThreadList.begin(); i != mThreadList.end(); ++i)
	{
		data = (*i);
		if (data->thread == thread)
		{
			mThreadList.remove(data);
			delete data;
			return;
		}
	}
}

DWORD WINAPI cThreadManager::ThreadProcess(LPVOID _arg)
{
	return ((cThreadUse*)_arg)->Procces(mInstance->GetThreadData(GetCurrentThreadId()));
}

void* cThreadManager::GetThreadData(DWORD threadID)
{
	sThreadData* data;
	for (list<sThreadData*>::iterator i = mThreadList.begin(); i != mThreadList.end(); ++i)
	{
		data = (*i);
		if (GetThreadId(data->thread) == threadID)
		{
			return data->data;
		}
	}
	return nullptr;
}
