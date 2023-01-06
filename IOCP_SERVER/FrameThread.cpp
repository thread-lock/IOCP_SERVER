#include "FrameThread.h"
#include "Mob.h"


cFrameThread::cFrameThread(int _frame, void* _data)
{
	delata_time = (float)1 / (float)_frame; //delta frame;
	frame = _frame;//������ 
	frame_data = _data;
}

void cFrameThread::FrameRun()
{
	int count = 0;//������ ī��Ʈ	
	while (1)
	{
		total_time = clock(); // �ð� ���� �ʱ�ȭ
		while (count < frame)//���� �������� �� ���� �ʾҴٸ� 
		{
			frame_time = clock();//1 ������ �ð� ����
			Run(frame_data);//�Լ� ����
			float gap = delata_time - ((float)(clock() - frame_time) / CLOCKS_PER_SEC);//������ 1������ �ð� - ����� 1������ �ð� ����
			if (gap > 0.0) Sleep(gap * 1000);//�� ���� ������ �����ٸ� Sleep
			count += 1;//ī��Ʈ ����
		}
		delata_time = ((float)(clock() - total_time) / CLOCKS_PER_SEC) / frame;//�������ѹ� ���µ� �� �ð��� ������ delta �ٽü���
		count = 0;//ī��Ʈ �ʱ�ȭ
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

