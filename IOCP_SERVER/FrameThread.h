#pragma once
#ifndef FRAMETHREAD_H
#define FRAMETHREAD_H
#include "Game.h"



class cFrameThread
{

	clock_t total_time;
	clock_t frame_time;
	float delata_time;
	int frame;
	void* frame_data;
protected:
	virtual void Run(void* data) = 0;
	virtual void Exception() = 0;
public:
	cFrameThread(int _frame, void* _data);
	void FrameRun();
	float Get_Delta_Time();
	int Get_Frame();
	void Set_Data(void* _data);
};


class MonsterThread : public cFrameThread
{
	// cFrameThread을(를) 통해 상속됨
	virtual void Run(void* data) override;
	virtual void Exception() override;
public:
	MonsterThread(int _frame, void* _data);


};



#endif // !FRAMETHREAD_H
