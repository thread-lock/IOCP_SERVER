#include "Eqinfo.h"

sEqInfo::sEqInfo(int _jobcode)
{
	mJob_code = _jobcode;
	mAmor = nullptr;
	mWeapon = nullptr;
	mShose = nullptr;
	mGlove = nullptr;
	mHat = nullptr;
}

sEqInfo::~sEqInfo()
{
	if (mAmor) delete mAmor;
	if (mWeapon) delete mWeapon;
	if (mShose) delete mShose;
	if (mGlove) delete mGlove;
	if (mHat) delete mHat;
}

bool sEqInfo::Equipment(cEquipment* _equip)
{
	if (_equip->Get_Jop() != mJob_code)
	{
		return false;
	}
	switch (_equip->Get_Type())
	{
	case HAT:
		mHat = _equip;
		break;
	case ARMOR:
		mAmor = _equip;
		break;
	case SHOSE:
		mShose = _equip;
		break;
	case GLOVE:
		mGlove = _equip;
		break;
	default:
		return false;
	}
	return true;

}

bool sEqInfo::Equipment(cWeapon* _weapone)
{
	if (_weapone->Get_Jop() != mJob_code)
	{
		return false;
	}
	mWeapon = _weapone;
	return true;
}

int sEqInfo::GetAtk()
{
	return 0;
}

int sEqInfo::GetHp()
{
	return 0;
}


