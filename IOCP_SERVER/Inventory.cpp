#include "Inventory.h"

cInventory::cInventory()
{
	mMoney = 0;
}

cInventory::~cInventory()
{
	Reset();
}

int cInventory::Get_Money()
{
	return mMoney;
}

void cInventory::Set_Money(int _money)
{
	mMoney += _money;
}

bool cInventory::Add_Item(cItem* _item)
{
	if(mItem_List.size() >= INVENTORY_SIZE) return false;
	mItem_List.push_back(_item);
	return true;
}

void cInventory::Delete_Item(cItem* _item)
{
	mItem_List.remove(_item);
}

void cInventory::Reset()
{
	while (mItem_List.size() > 0)
	{
		cItem* item = mItem_List.front();
		mItem_List.pop_front();
		delete item;
	}
}
