#pragma once
#ifndef ERRMANAGER_H
#define ERRMANAGER_H
#include"Global.h"

//���� �Ŵ���
class cErrManager
{
	//�̱��� ����
	cErrManager();
	~cErrManager();
	static cErrManager* mInstance;
public:
	//�̱��� ����
	static void Create();
	static cErrManager * GetInstance();
	static void Destroy();
	//�����޼��� ���
	void err_quit(const char *msg);
	void err_display(const char *msg);
	void err_display(int errcode);
};



#endif // !ERRMANAGER_H
