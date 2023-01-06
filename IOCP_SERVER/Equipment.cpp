#include "Equipment.h"


void cEquipment::Use_Item(cCharactor* _char)
{
	Equip_Equipment(_char->Get_EqInfo());
}

cEquipment::cEquipment()
{
}

cEquipment::cEquipment(cEquipment & _equip)
{
	mCode = _equip.mCode;
	strcpy_s(mName, _equip.mName);
	mHp = _equip.mHp;
	mPrice = _equip.mPrice;
	mJob = _equip.mJob;
	mType = _equip.mType;
}


cEquipment::cEquipment(int _code, char* _name, int _hp, int _price, int _jop, int _type)
{
	mCode = _code;
	strcpy_s(mName, _name);
	mHp = _hp;
	mPrice = _price;
	mJob = _jop;
	mType = (EQUIPMENT_TYPE)_type;
}

bool cEquipment::Equip_Equipment(sEqInfo* _info)
{
	return _info->Equipment(this);
}

int cEquipment::Get_HP()
{
	return mHp;
}

int cEquipment::Get_Jop()
{
	return mJob;
}

EQUIPMENT_TYPE cEquipment::Get_Type()
{
	return mType;
}

