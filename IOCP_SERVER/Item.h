#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Charactor.h"

class cCharactor;
struct sEqInfo;

class cItem
{	
protected:
	int mCode;
	char mName[ITEM_NAME_SIZE];
	int mPrice;
	virtual void Use_Item(cCharactor*) = 0;
public:
	cItem();
	int Get_Code();
	int Get_Price();
	char* Get_Name();

	static cItem* Get_Item(int _code);
};

class cEquipment : public cItem
{
protected:
	int mHp;
	int mJob;
	EQUIPMENT_TYPE mType;
	void Use_Item(cCharactor*);
public:
	cEquipment();
	cEquipment(cEquipment&);
	cEquipment(int, char*, int, int, int, int);
	bool Equip_Equipment(sEqInfo*);
	int Get_HP();
	int Get_Jop();
	EQUIPMENT_TYPE Get_Type();
};

class cWeapon : public cItem
{

protected:
	int mAtk;
	int mJob;
	WEAPON_TYPE mType;
	void Use_Item(cCharactor*);
public:
	cWeapon();
	cWeapon(cWeapon&);
	cWeapon(int, char*, int, int, int, int);
	bool Equip_Weapon(sEqInfo*);
	int Get_Jop();
	int Get_Akt();
	WEAPON_TYPE Get_Type();
};


class cPotion : public cItem
{
	void Use_Item(cCharactor&);
	POTION_TYPE mType;
public:
	void Use_Potion(cCharactor&);
};
#endif // !ITEM_H
