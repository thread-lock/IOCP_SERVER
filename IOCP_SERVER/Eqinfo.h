#pragma once
#ifndef EQINFO_H
#define EQINFO_H
#include "Weapon.h"
#include "Equipment.h"

class cCharactor;
class cItem;
class cWeapon;
class cEquipment;



struct sEqInfo
{
	int mJob_code;
	cWeapon* mWeapon;
	cEquipment* mAmor;
	cEquipment* mShose;
	cEquipment* mGlove;
	cEquipment* mHat;

	sEqInfo(int);
	~sEqInfo();

	bool Equipment(cWeapon*);
	bool Equipment(cEquipment*);
	int GetAtk();
	int GetHp();
};


#endif // !EQINFO_H
