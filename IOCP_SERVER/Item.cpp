#include "Item.h"
#include"DBManager.h"

cItem::cItem()
{

}

int cItem::Get_Code()
{
	return mCode;
}

int cItem::Get_Price()
{
	return 0;
}

char * cItem::Get_Name()
{
	return mName;
}

cItem * cItem::Get_Item(int _code)
{
	char code[5];

	itoa(_code, code, 10);

	if ((code[2] - 48) == 1)//무기 일경우
	{
		cWeapon itemdata;
		DBManager::GetInstance()->SearchStart(DB_TABLE_WEAPON);
		while (DBManager::GetInstance()->SearchData(itemdata))
		{
			if (_code == itemdata.Get_Code())
			{
				DBManager::GetInstance()->SearchEnd();
				return new cWeapon(itemdata);
			}
		}
	}
	else
	{
		cEquipment itemdata;
		DBManager::GetInstance()->SearchStart(DB_TABLE_EQUIP);
		while (DBManager::GetInstance()->SearchData(itemdata))
		{
			if (_code == itemdata.Get_Code())
			{
				DBManager::GetInstance()->SearchEnd();
				return new cEquipment(itemdata);
			}
		}
	}

	return nullptr;

}


