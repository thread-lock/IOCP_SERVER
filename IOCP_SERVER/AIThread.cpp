#include "AIThread.h"

void cAI_Thread::Run(void*  _data)
{
	list<cMob*>* mob_list = (list<cMob*>*)_data;

	
	for (list<cMob*>::iterator i = (*mob_list).begin(); i != (*mob_list).end(); ++i)
	{
		(*i)->Get_AI()->Update();
	}
}

void cAI_Thread::Exception()
{
}

cAI_Thread::cAI_Thread(int _frame, void * _data) : cFrameThread(_frame,_data)
{
}
