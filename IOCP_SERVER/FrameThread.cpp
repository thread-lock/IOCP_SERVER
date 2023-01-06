#include "FrameThread.h"
#include "Mob.h"


cFrameThread::cFrameThread(int _frame, void* _data)
{
	delata_time = (float)1 / (float)_frame; //delta frame;
	frame = _frame;//프레임 
	frame_data = _data;
}

void cFrameThread::FrameRun()
{
	int count = 0;//프레임 카운트	
	while (1)
	{
		total_time = clock(); // 시간 측정 초기화
		while (count < frame)//아직 프레임이 다 돌지 않았다면 
		{
			frame_time = clock();//1 프레임 시간 측정
			Run(frame_data);//함수 실행
			float gap = delata_time - ((float)(clock() - frame_time) / CLOCKS_PER_SEC);//지정된 1프레임 시간 - 진행된 1프레임 시간 측정
			if (gap > 0.0) Sleep(gap * 1000);//더 빨리 연산이 끝났다면 Sleep
			count += 1;//카운트 증가
		}
		delata_time = ((float)(clock() - total_time) / CLOCKS_PER_SEC) / frame;//프레임한번 도는데 총 시간을 나눠서 delta 다시설정
		count = 0;//카운트 초기화
	}
}

float cFrameThread::Get_Delta_Time()
{
	return delata_time;
}

int cFrameThread::Get_Frame()
{
	return frame;
}

void cFrameThread::Set_Data(void * _data)
{
	frame_data = _data;
}

void MonsterThread::Run(void* frame_data)
{


}

void MonsterThread::Exception()
{
}

MonsterThread::MonsterThread(int _frame,void* _data) :cFrameThread(_frame, _data)
{

	
}

