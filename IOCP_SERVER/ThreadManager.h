#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H
#include "Global.h"
#include <list>
using std::list;

struct sThreadData
{
	HANDLE thread;
	void* data;
};

class cThreadUse
{
public:
	virtual DWORD Procces(void* _data) = 0;
};

class cThreadManager
{

private:
	static cThreadManager* mInstance;
	cThreadManager();
	~cThreadManager();
	list<sThreadData*> mThreadList;
public:
	static void Create();
	static cThreadManager* GetInstance();
	static void Destroy();

	HANDLE AddThread(LPVOID data, cThreadUse* _pthis);
	void RemoveThread(HANDLE thread);
	static DWORD WINAPI ThreadProcess(LPVOID arg);
	void* GetThreadData(DWORD threadID);
};

#endif
