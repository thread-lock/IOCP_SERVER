#pragma once
#ifndef AITHREAD_H
#define AITHREAD_H
#include "FrameThread.h"
#include "Mob.h"

using std::list;

//AI Thread
class cAI_Thread : public cFrameThread
{
protected:
	virtual void Run(void* data) override;
	virtual void Exception() override;
public:
	// cFrameThread를 통해 상속
	cAI_Thread(int _frame, void *_data);

};




#endif // !AITHREAD_H
