#include "DungeonManager.h"
#include "tinyxml.h"


cDungeonManger * cDungeonManger::mInstance = NULL;

cDungeonManger::cDungeonManger()
{
}

cDungeonManger::~cDungeonManger()
{
}



void cDungeonManger::Create()
{
	if (mInstance == nullptr)
	{
		mInstance = new cDungeonManger();
	}

}

cDungeonManger * cDungeonManger::GetInstance()
{
	if (!mInstance)
	{
		mInstance = new cDungeonManger();
	}
	return mInstance;
}

void cDungeonManger::Destroy()
{
}

sDungeon* cDungeonManger::CreateDungeon()
{

	sDungeon* Dungeon = new sDungeon();

	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile("Dungeon.xml");// xml ���� �ε�
	TiXmlElement* Root = ReadDoc.FirstChildElement("Dungeon_Map");
	TiXmlElement* dungeon_field;
	TiXmlElement* sector;
	TiXmlElement* mob;
	TiXmlElement* store;
	TiXmlElement* trap;
	TiXmlAttribute * attribute;
	char dungeon_num[15];

	//���� �� ��ŭ �ݺ�
	for (int i = 0; i < DUNGEON_NUM; i++)
	{
		Dungeon->mField[i] = new cDungeonField(Dungeon);


		//������ ��ȣ �±׸� ��������
		sprintf_s(dungeon_num, "Dungeon_%d", i);
		//�ش� ��ȣ�� ������ �����´�.
		dungeon_field = Root->FirstChildElement(dungeon_num);
		//������ ������ �����´�.
		sector = dungeon_field->FirstChildElement("Sectors")->FirstChildElement();
		mob = dungeon_field->FirstChildElement("Monsters")->FirstChildElement();
		store = dungeon_field->FirstChildElement("Store")->FirstChildElement();
		trap = dungeon_field->FirstChildElement("Trap")->FirstChildElement();
		//������ ����ŭ �ݺ�
		while (sector)
		{
			attribute = sector->FirstAttribute();
			float point[4];
			int num = 0;
			while (attribute)
			{
				point[num++] = strtof(attribute->Value(), nullptr);
				attribute = attribute->Next();
			}

			cSector *pSector = new cSector(point[0], point[1], point[2], point[3]);
			Dungeon->mField[i]->Add_Sector(pSector);
			sector = sector->NextSiblingElement();
		}

		//������ �� ��ŭ �ݺ�
		while (mob)
		{

			attribute = mob->FirstAttribute();
			float point[5];
			int num = 0;
			while (attribute)
			{
				point[num++] = strtof(attribute->Value(), nullptr);
				attribute = attribute->Next();
			}

			cMob* pmob = new cMob(point[0], point[1], point[2], point[3], point[4]);
			Dungeon->mField[i]->Add_Mob(pmob);
			Dungeon->mField[i]->Sector_Chk(pmob);
			Dungeon->mField[i]->Init_Mob(pmob);
			mob = mob->NextSiblingElement();
		}

		//���� ���� ����Ʈ �� ��ŭ �ݺ�
		while (store)
		{
			attribute = store->FirstAttribute();
			float point[2];
			int num = 0;
			while (attribute)
			{
				point[num++] = strtof(attribute->Value(), nullptr);
				attribute = attribute->Next();
			}
			Dungeon->mField[i]->Add_Store_spawn(cVector2D(point[0], point[1]));
			store = store->NextSiblingElement();
		}

		//���� ���� ����Ʈ �� ��ŭ �ݺ�
		while (trap)
		{
			attribute = trap->FirstAttribute();
			float point[3];
			int num = 0;
			while (attribute)
			{
				point[num++] = strtof(attribute->Value(), nullptr);
				attribute = attribute->Next();
			}
			Dungeon->mField[i]->Add_Trap(sTrap(point[0], point[1],point[2]));
			trap = trap->NextSiblingElement();
		}		
	}
	mDungeon_List.push_back(Dungeon);
	return Dungeon;
}
