#pragma once
#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include "ClientInfo.h"

class cMapManger
{
	//�̱��� ����
	cMapManger();
	~cMapManger();
	static cMapManger * mInstance;
public:
	//�̱��� ����
	static void Create();
	static cMapManger * GetInstance();
	static void Destroy();  


	void Req_Enter_Map(cClientInfo* _info, cBuf & _data);
	void Req_Out_Map(cClientInfo* _info, cBuf & _data);
	void Req_Enter_Dungeon(cClientInfo* _info, cBuf & _data);

};


#endif // 
