#pragma once
#ifndef AITHREAD_H
#define AITHREAD_H
#include "FrameThread.h"
#include "Mob.h"

using std::list;

//AI스레드
class cAI_Thread : public cFrameThread
{
protected:
	virtual void Run(void* data) override;
	virtual void Exception() override;
public:
	// cFrameThread을(를) 통해 상속됨
	cAI_Thread(int _frame, void *_data);

};




#endif // !AITHREAD_H
