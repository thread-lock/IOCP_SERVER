#include "Weapon.h"

void cWeapon::Use_Item(cCharactor* _char)
{
	Equip_Weapon(_char->Get_EqInfo());
}

cWeapon::cWeapon()
{
}

cWeapon::cWeapon(cWeapon & _weapon)
{
	mCode = _weapon.mCode;
	strcpy_s(mName, _weapon.mName);
	mAtk = _weapon.mAtk;
	mPrice = _weapon.mPrice;
	mJob = _weapon.mJob;
	mType = _weapon.mType;
}

cWeapon::cWeapon(int _code, char * _name, int _atk, int _price, int _jop, int _type)
{
	mCode = _code;
	strcpy_s(mName, _name);
	mAtk = _atk;
	mPrice = _price;
	mJob = _jop;
	mType = (WEAPON_TYPE)_type;
}

bool cWeapon::Equip_Weapon(sEqInfo * _info)
{
	return _info->Equipment(this);
}

int cWeapon::Get_Jop()
{
	return mJob;
}

int cWeapon::Get_Akt()
{
	return mAtk;
}

WEAPON_TYPE cWeapon::Get_Type()
{
	return mType;
}
