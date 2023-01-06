#pragma once
#ifndef CHARACTOR_H
#define CHARACTOR_H
#include "Game.h"
#include "Job.h"
#include "Party.h"
#include "Map.h"
#include "Ability.h"
#include "Eqinfo.h"
#include "Inventory.h"

class cMap;
class cParty;
class cSector;
class cItem;
class cInventory;
struct sEqInfo;


class cCharactor
{
	int mCode;
	int mUser_Code;
	char mName[CHAR_NAME_SIZE];

	sJob mJob;
	cVector2D location;
	sAbility mAbility;


	//shared_ptr<cMap> mEnter_Map;
	//shared_ptr< cSector> mEnter_Sector;
	//shared_ptr<cParty> mEnter_Party;



	cMap* Enter_map;	 
	cSector* Enter_sector;
	cParty* Enter_party;
	sEqInfo* mEqinfo;
	cInventory* mInven;
public:
	cCharactor() {}
	cCharactor(int _user_code, const char* _name, int _jobcode);//
	cCharactor(int _code, int _user_code, const char* _name, int _jobcode, int _sumLv, int _sumLvExpMax, int _sumLvExpNow);
	cCharactor(cCharactor&);
	~cCharactor();

	int Get_User_Code() const;
	int Get_Char_Code() const;


	const char* GetName() const;
	cVector2D& Get_Location();
	sJob& Get_Job();
	sAbility& Get_Ability();

	cInventory* Get_Inventory();
	sEqInfo* Get_EqInfo();

	cMap* Get_Enter_Map();
	cSector* Get_Enter_Sector();
	cParty* Get_Enter_Party();



	void Set_Enter_Map(cMap*);
	void Set_Enter_Sector(cSector*);
	void Set_Enter_Party(cParty*);
};




#endif // !CHARACTOR_H
