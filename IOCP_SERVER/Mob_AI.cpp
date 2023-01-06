#include "Mob_AI.h"

bool cMob_AI::Around_chk()
{
	cSector * mySector = mMob->Get_Enter_Sector();

	cCharactor* char_data;
	mySector->Char_SearchStart();
	while (mySector->Char_SearchData(char_data))
	{
		if (cVector2D::GetLength(char_data->Get_Location(), mMob->Get_Location()) < Uggro_Range)
		{


			mState = MOB_STATE::MOB_MOVE;
			Destination = cVector2D(char_data->Get_Location());
			mTotal_trans = ABS(Destination.GetX() - char_data->Get_Location().GetX());
			mNow_trans = 0;
			Uggro_char = char_data;
			return true;
		}
		
	}
	return false;
}

void cMob_AI::Stanby_Run()
{

	srand((int)time(NULL));
	int num = (rand() % 10) + 1;
	//간격 5정도 여유를 준다.
	float rx = (mMob->Get_Enter_Sector()->Get_Right_x() - 5);
	float lx = (mMob->Get_Enter_Sector()->Get_Left_x() + 5);

	if (num <= 2)//20%확률로 멈춘다
	{
		stopcount = (rand() % 3) + 1;
		stopcount *= mFrame->Get_Frame();
		mState = MOB_STATE::MOB_STOP;
		mMob->Get_Enter_Map()->Mob_Stop_Data_Send(mMob, stopcount);


	}
	else//아닐경우 이동
	{
		float trans = (rand() % 10) + 1;//이동량을 랜덤으로 지정
		mTotal_trans = trans;
		mNow_trans = 0;
		if ((rand() % 2) == 1)//20%확률로 방향을 지정
		{
			trans *= -1;
		}
		if (mMob->Get_Location().GetX() + trans > rx) //오른 쪽 범위를 벗어난 경우 (trans가 양수일경우)
		{
			trans  = mMob->Get_Location().GetX() - rx;
		}
		else if (mMob->Get_Location().GetX() + trans < lx)// 왼쪽 범위를 벗어난 경우 (trans가 음수일경우)
		{
			trans = mMob->Get_Location().GetX() - lx;
		}

		Destination = cVector2D(mMob->Get_Location().GetX() + trans, mMob->Get_Location().GetY());
		mState = MOB_STATE::MOB_MOVE;
		mMob->Get_Enter_Map()->Mob_Move_Data_Send(mMob, Destination.GetX(), Destination.GetY());
	}


}
 
void cMob_AI::Move_Run()
{

	if (Uggro_char)
	{

	}
	else
	{
		if (mTotal_trans > mNow_trans)
		{
			cVector2D gap = Destination - mMob->Get_Location();
			mMob->Get_Location() = ((mMob->Get_Location() + gap) * speed * mFrame->Get_Delta_Time());//????
			mNow_trans += speed * mFrame->Get_Delta_Time();
		}
		else
		{
			mState = MOB_STATE::MOB_STANBY;
		}
	}


}

void cMob_AI::Stop_Run()
{
	stopcount--;
	if (stopcount == 0)
	{
		mState = MOB_STATE::MOB_STANBY;
	}

}

void cMob_AI::Uggro_Run()
{

}

cMob_AI::cMob_AI(cMob * _mob, cFrameThread * _frame)
{
	Uggro_char = nullptr;
	mState = MOB_STATE::MOB_STANBY;
	mMob = _mob;
	mFrame = _frame;
}

cVector2D & cMob_AI::Get_Destination()
{
	return Destination;
}

MOB_STATE cMob_AI::Get_State()
{
	return mState;
}

void cMob_AI::In_Action(MOB_INTERACTION)
{
}

void cMob_AI::Update()
{
	switch (mState)
	{
	case MOB_STATE::MOB_STANBY:
		Stanby_Run();
		break;
	case MOB_STATE::MOB_MOVE:
		Around_chk();
		Move_Run();
		break;
	case MOB_STATE::MOB_STOP:
		Around_chk();
		Move_Run();;
		break;
	case MOB_STATE::MOB_BATTLE:
		break;
	default:
		break;
	}
}
