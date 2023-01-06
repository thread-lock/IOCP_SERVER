#include "Mob.h"

int cMob::codemaker = 0;

cMob::cMob()
{
	mEnter_Sector = nullptr;
}

cMob::cMob(int _mobcode, float _x, float _y, int _max_hp, float _atk)
{
	code = codemaker++;
	mEnter_Sector = nullptr;
	mMob_Code = _mobcode;
	mMax_Hp = _max_hp;
	mNow_Hp = mMax_Hp;
	mLocation.SetXY(_x, _y);
	mAtk = _atk;
}

cVector2D & cMob::Get_Location()
{
	return mLocation;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

cSector * cMob::Get_Enter_Sector()
{
	return mEnter_Sector;
}

cDungeonField * cMob::Get_Enter_Map()
{
	return mEnter_map;
}

void cMob::Set_Mob_AI(cMob_AI * _ai)
{
	mAi = _ai;
}

void cMob::Set_Enter_Map(cDungeonField *_map)
{
	mEnter_map = _map;
}


void cMob::Set_Enter_Sector(cSector *_sector)
{
	mEnter_Sector = _sector;
}

cMob_AI * cMob::Get_AI()
{
	return mAi;
}

int cMob::Get_Code()
{
	return code;
}

int cMob::Get_Mob_Code()
{
	return mMob_Code;
}

int cMob::Get_Max_Hp()
{
	return mMax_Hp;
}

int cMob::Get_Now_Hp()
{
	return mNow_Hp;
}

float cMob::Get_Atk()
{
	return mAtk;
}
