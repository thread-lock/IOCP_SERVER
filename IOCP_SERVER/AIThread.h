#pragma once
#ifndef AITHREAD_H
#define AITHREAD_H
#include "FrameThread.h"
#include "Mob.h"

using std::list;

//AI������
class cAI_Thread : public cFrameThread
{
protected:
	virtual void Run(void* data) override;
	virtual void Exception() override;
public:
	// cFrameThread��(��) ���� ��ӵ�
	cAI_Thread(int _frame, void *_data);

};




#endif // !AITHREAD_H
