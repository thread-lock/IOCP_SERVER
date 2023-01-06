#pragma once
#ifndef MOB_H
#define MOB_H
#include "Game.h"
#include "Mob_AI.h"
#include "Dungeon.h"
class cSector;
class cMap;
class cMob_AI;
class cDungeonField;

class cMob
{
	static int codemaker;

	int code;
	int mMob_Code;
	cDungeonField* mEnter_map;
	cSector * mEnter_Sector;
	cVector2D mLocation;
	cMob_AI* mAi;

	int mMax_Hp;
	int mNow_Hp;
	float mAtk;
public:
	cMob();
	cMob(int _mobcode, float _x, float _y, int _max_hp, float _atk);
	cVector2D & Get_Location();
	cSector* Get_Enter_Sector();
	cDungeonField* Get_Enter_Map();

	void Set_Mob_AI(cMob_AI*);
	void Set_Enter_Map(cDungeonField*);
	void Set_Enter_Sector(cSector*);

	cMob_AI* Get_AI();


	int Get_Code();
	int Get_Mob_Code();
	int Get_Max_Hp();
	int Get_Now_Hp();
	float Get_Atk();


};

#endif // !MOB_H
