#include "Charactor.h"
#include "Map_Town.h"

cCharactor::cCharactor(int _user_code, const char * _name, int _jobcode)
{
	mCode = 0;
	mUser_Code = _user_code;
	strcpy_s(mName, _name);
	mJob.mCode = _jobcode;
	mAbility.mSumLv = 1;
	mAbility.mSumLvExpMax = 100;
	mAbility.mSumLvExpNow = 0;
	Enter_map = nullptr;
	Enter_party = nullptr;
	Enter_sector = nullptr;
	mEqinfo = new sEqInfo(mJob.mCode);
	mInven = new cInventory();
	location.SetXY(0, 0);
}

cCharactor::cCharactor(int _code, int _user_code, const char * _name, int _jobcode, int _sumLv, int _sumLvExpMax, int _sumLvExpNow)
{
	mCode = _code;
	mUser_Code = _user_code;
	strcpy_s(mName, _name);
	mJob.mCode = _jobcode;
	mAbility.mSumLv = _sumLv;
	mAbility.mSumLvExpMax = _sumLvExpMax;
	mAbility.mSumLvExpNow = _sumLvExpNow;
	Enter_map = nullptr;
	Enter_party = nullptr;
	Enter_sector = nullptr;
	mEqinfo = new sEqInfo(mJob.mCode);
	mInven = new cInventory();
	location.SetXY(0, 0);

}

cCharactor::cCharactor(cCharactor & _char)
{
	mCode = _char.mCode;
	mUser_Code = _char.mUser_Code;
	strcpy_s(mName, _char.mName);
	mJob.mCode = _char.mJob.mCode;
	mAbility.mSumLv = _char.mAbility.mSumLv;
	mAbility.mSumLvExpMax = _char.mAbility.mSumLvExpMax;
	mAbility.mSumLvExpNow = _char.mAbility.mSumLvExpNow;
	Enter_map = nullptr;
	Enter_sector = nullptr;
	Enter_party = nullptr;
	mEqinfo = new sEqInfo(mJob.mCode);
	mInven = new cInventory();
	location.SetXY(0, 0);
}

cCharactor::~cCharactor()
{
	//if(mEqinfo) delete mEqinfo;
}

int cCharactor::Get_User_Code() const
{
	return mUser_Code;
}

int cCharactor::Get_Char_Code() const
{
	return mCode;
}

const char * cCharactor::GetName() const
{
	return mName;
}

cVector2D & cCharactor::Get_Location()
{
	return location;
}

sJob& cCharactor::Get_Job()
{
	return mJob;
}

sAbility & cCharactor::Get_Ability()
{
	return mAbility;
}

cInventory * cCharactor::Get_Inventory()
{
	return mInven;
}

sEqInfo * cCharactor::Get_EqInfo()
{
	return mEqinfo;
}

cMap * cCharactor::Get_Enter_Map()
{
	return Enter_map;
}

cSector * cCharactor::Get_Enter_Sector()
{
	return Enter_sector;
}

cParty * cCharactor::Get_Enter_Party()
{
	return Enter_party;
}

void cCharactor::Set_Enter_Map(cMap* _map)
{
	Enter_map = _map;
}

void cCharactor::Set_Enter_Sector(cSector * _sector)
{
	Enter_sector = _sector;
}

void cCharactor::Set_Enter_Party(cParty * _party)
{
	Enter_party = _party;
}
