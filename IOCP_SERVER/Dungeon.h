#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H
#include "Map.h"
#include "Mob.h"
#include "Store.h"
#include "ThreadManager.h"
#include <list>
#include "AIThread.h"
#define DUNGEON_NUM 4

using std::list;
struct sDungeon;
class cMob;
class cAI_Thread;

class cSector
{
	list<cMob*> mMob_List;
	list<cCharactor*> mChar_List;
	list<cMob*>::iterator Mob_Search;
	list<cCharactor*>::iterator Char_Search;
	float left, right;
	float top, bottom;

public:
	cSector();
	cSector(float, float, float, float);

	bool Is_Sector_Area(cVector2D&); 


	bool Enter_Sector(cCharactor*);
	bool Char_Is_In(cCharactor*);
	bool Out_Sector(cCharactor*);

	bool Enter_Sector(cMob*);
	bool Char_Is_In(cMob*);
	bool Out_Sector(cMob*);


	void Char_SearchStart();
	bool Char_SearchData(cCharactor*&);
	void Char_SerachEnd();

	int Get_Mob_Num();

	void Mob_SearchStart();
	bool Mob_SearchData(cMob*&);
	void Mob_SerachEnd();

	float Get_Right_x();
	float Get_Left_x();



	

};

struct sTrap
{
	cVector2D location;
	float range;


	sTrap(float _x, float _y, float _range)
	{

	}
};







class cDungeonField : public cMap, public cThreadUse
{
	sDungeon* mDungeon;
	cAI_Thread* mAI_thread;
	list<cSector*> mSector_List;
	list<cMob*> mMob_List;
	list<sTrap> mTrap_List;
	list<cVector2D> mStore_spawn_List;	
	cStore* mStore;
	
	HANDLE mhandle;

	bool mThread_on;

//	MonsterThread* mMob_thread;
public:
	// cThreadUse을(를) 통해 상속됨
	//cDungeonField();
	cDungeonField(sDungeon*);
	DWORD Procces(void * _data) override;
	// cMap을(를) 통해 상속됨


	void Sector_Chk(cCharactor*);
	void Sector_Chk(cMob*);

	void Add_Mob(cMob*);
	void Init_Mob(cMob*);
	void Add_Sector(cSector*);
	void Add_Trap(sTrap);
	void Add_Store_spawn(cVector2D);

	bool Enter_Player(cClientInfo* _player) override;

	void Set_Store(cStore* _store);

	void Player_Move_Data_Send(cClientInfo*, int) override;
	void Map_Enter_Data_Send(cClientInfo*) override;
	void Enter_Player_Data_Send(cClientInfo *) override;
	void Req_Party_invite(cClientInfo*, int) override;

	void Mob_Move_Data_Send(cMob* , float , float );
	void Mob_Stop_Data_Send(cMob*, int);

	sDungeon* Get_Dungeon();

	void Frame_Start();
	void Frame_Stop();
};





struct sDungeon
{
	int mCode;
	cDungeonField* mField[DUNGEON_NUM];
	int mNow_field;
	sDungeon()
	{
		mNow_field = 0;
	}

	void Frame_Start(int _index)
	{
		mField[_index]->Frame_Start();
	}

	void Frame_Stop(int _index)
	{
		mField[_index]->Frame_Stop();
	}


};




#endif // !DUNGEON_H
