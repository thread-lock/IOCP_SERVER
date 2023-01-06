#pragma once
#ifndef ABILITY_H
#define ABILITY_H
#include "Game.h"

struct sAbility
{
	JOB_CODE job_code;


	int mSumLv;
	int mSumLvExpMax;
	int mSumLvExpNow;


	int Now_Hp;
	int Now_Mp;

	int stat;


	int Get_Max_Hp()
	{
		switch (job_code)
		{
		case JOB_WARRIOR:
			return 20 + (stat * 3);
			break;
		case JOB_ARCHER:
			break;
		case JOB_MAGICIAN:
			break;
		}
		return 0;
	}

	int Get_Max_Mp()
	{
		switch (job_code)
		{
		case JOB_WARRIOR:
			return 15 + (stat * 1);
			break;
		case JOB_ARCHER:
			break;
		case JOB_MAGICIAN:
			break;
		}
		return 0;
	}

	int Get_Main_Stat()
	{
		switch (job_code)
		{
		case JOB_WARRIOR:
			return stat;
			break;
		case JOB_ARCHER:
			break;
		case JOB_MAGICIAN:
			break;
		}
		return 0;
	}

};


#endif // !ABILITY_H
