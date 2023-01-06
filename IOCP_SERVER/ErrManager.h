#pragma once
#ifndef ERRMANAGER_H
#define ERRMANAGER_H
#include"Global.h"

//에러 매니저
class cErrManager
{
	//싱글톤 패턴
	cErrManager();
	~cErrManager();
	static cErrManager* mInstance;
public:
	//싱글톤 패턴
	static void Create();
	static cErrManager * GetInstance();
	static void Destroy();
	//에러메세지 출력
	void err_quit(const char *msg);
	void err_display(const char *msg);
	void err_display(int errcode);
};



#endif // !ERRMANAGER_H
