#pragma once
#ifndef DUNGEONMANAGER_H
#define DUNGEONMANAGER_H
#include "Dungeon.h"






class cDungeonManger
{
	list<sDungeon*> mDungeon_List;
	//�̱��� ����
	cDungeonManger();
	~cDungeonManger();
	static cDungeonManger * mInstance;
public:
	//�̱��� ����
	static void Create();
	static cDungeonManger * GetInstance();
	static void Destroy();


	sDungeon* CreateDungeon();




};





#endif // !DUNGEONMANAGER_H
