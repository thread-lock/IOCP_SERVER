#pragma once
#ifndef STORE_H
#define STORE_H
#include "Item.h"
#include "Inventory.h"
#include <list>
using std::list;

class cStore
{
	cVector2D location;
	list<cItem*> mSell_List;
public:

	void Ransdom_Sell_List_Set();
	bool Sell_Item(cInventory* _inven, int _code);

};


#endif // !STORE_H
