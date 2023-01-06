#pragma once
#ifndef MOB_AI
#define MOB_AI
#include "AI.h"
#include "Mob.h"
#include "FrameThread.h"

class cMob;
class cCharactor;


//���� AI
class cMob_AI : public cAI
{
	cMob* mMob;
	cFrameThread* mFrame;
	MOB_STATE mState;

	//���� üũ
	float Uggro_Range;
	bool Around_chk();
	cCharactor* Uggro_char;

	//�ൿ ���
	void Stanby_Run();


	//�̵� ��
	void Move_Run();
	float speed;
	float mTotal_trans;
	float mNow_trans;
	cVector2D Destination;


	//����
	void Stop_Run();
	int stopcount;

	
	//��׷�
	void Uggro_Run();


public:
	cMob_AI(cMob*, cFrameThread*);

	cVector2D& Get_Destination();
	MOB_STATE Get_State();
	void In_Action(MOB_INTERACTION);
	void Update() override;

};


#endif // !MOB_AI
