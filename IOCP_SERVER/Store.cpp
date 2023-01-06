#include "Store.h"

void cStore::Ransdom_Sell_List_Set()
{
	srand((int)time(NULL));

	for (int i = 0; i < 8; i++)
	{
		int first = (rand() % 2) + 1;
		int third = (rand() % 5) + 1;
		int fourth = (rand() % 3) + 1;

		int code = (first * 1000) + (third * 10) + fourth;
		mSell_List.push_back(cItem::Get_Item(code));
	}
}

bool cStore::Sell_Item(cInventory* _inven, int _code)
{

	cItem* item;
	bool find = false;
	for (list<cItem*>::iterator i = mSell_List.begin(); i != mSell_List.end(); ++i)
	{
		item = (*i);
		if (item->Get_Code() == _code)
		{
			find = true;
			break;
		}
	}

	if (find)
	{
		if (_inven->Get_Money() >= item->Get_Price())
		{
			_inven->Set_Money(-item->Get_Price());
			_inven->Add_Item(item);
			mSell_List.remove(item);
			return true;
		}
	}
	return false;
}

