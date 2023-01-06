#pragma once
#ifndef MAP_TOWN
#define MAP_TOWN
#include "Map.h"

class cMap_Town : public cMap
{
	cMap_Town();
	~cMap_Town();
	static cMap_Town* mInstance;
public:
	static void Create();
	static cMap_Town * GetInstance();
	static void Destroy();

	void Map_Enter_Data_Send(cClientInfo*) override;
	void Enter_Player_Data_Send(cClientInfo*) override;
};




#endif // !MAP_TOWN
