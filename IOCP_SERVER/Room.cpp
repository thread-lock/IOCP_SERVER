#include "Room.h"

cRoom::cRoom()
{
	InitializeCriticalSection(&cs);
}

cRoom::~cRoom()
{
	DeleteCriticalSection(&cs);
}


int cRoom::Get_Code()
{
	return mCode;
}

int cRoom::Get_Count()
{
	return mPlayer_List.size();
}

bool cRoom::Enter_Player(cClientInfo * _player)
{
	Enter_CS();
	mPlayer_List.push_back(_player);
	Out_CS();
	return true;
}

bool cRoom::Out_Player(cClientInfo * _player)
{
	Enter_CS();
	mPlayer_List.remove(_player);
	Out_CS();
	return true;
}

void cRoom::SearchStart()
{
	mSearch = mPlayer_List.begin();
}

bool cRoom::SearchData(cClientInfo*& _client)
{
	if (mSearch != mPlayer_List.end())
	{
		_client = *mSearch;
		++mSearch;
		return true;
	}
	return false;
}

void cRoom::Enter_CS()
{
	EnterCriticalSection(&cs);
}

void cRoom::Out_CS()
{
	LeaveCriticalSection(&cs);
}
