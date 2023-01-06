#pragma once
#ifndef DUNGEONMANAGER_H
#define DUNGEONMANAGER_H
#include "Dungeon.h"






class cDungeonManger
{
	list<sDungeon*> mDungeon_List;
	//ΩÃ±€≈Ê ∆–≈œ
	cDungeonManger();
	~cDungeonManger();
	static cDungeonManger * mInstance;
public:
	//ΩÃ±€≈Ê ∆–≈œ
	static void Create();
	static cDungeonManger * GetInstance();
	static void Destroy();


	sDungeon* CreateDungeon();




};





#endif // !DUNGEONMANAGER_H
