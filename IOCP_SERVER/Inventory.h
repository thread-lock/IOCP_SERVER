#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H
#include "Game.h"
#include "Item.h"
#include <list>



using std::list;

class cItem;

class cInventory
{
	int mMoney;
	list<cItem*> mItem_List;
public:
	cInventory();
	~cInventory();

	int Get_Money();

	void Set_Money(int _money);

	bool Add_Item(cItem*);
	void Delete_Item(cItem*);

	void Reset();
};


#endif // !INVENTORY_H
