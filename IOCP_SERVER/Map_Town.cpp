#include "Map_Town.h"

cMap_Town * cMap_Town::mInstance = NULL; //인스턴스 초기화

void cMap_Town::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cMap_Town();
	}
}

cMap_Town * cMap_Town::GetInstance() //싱글톤 객체 반환
{
	if (!mInstance)
	{
		mInstance = new cMap_Town();
	}
	return mInstance;
}

void cMap_Town::Destroy() //싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

void cMap_Town::Map_Enter_Data_Send(cClientInfo* _player)
{
	Enter_CS();

	cBuf buf;

	buf.Append((int)(mPlayer_List.size() - 1));
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		buf.Append((*i)->Get_Char_Info()->Get_Char_Code());
		buf.Append((char*)(*i)->Get_Char_Info()->GetName());
		buf.Append((*i)->Get_Char_Info()->Get_Job().mCode);
		buf.Append((*i)->Get_Char_Info()->Get_Location().GetX());
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_DATA);
	_player->Pack(protocol, buf);
	_player->SendMsg();

	Out_CS();
}



void cMap_Town::Enter_Player_Data_Send(cClientInfo* _player)
{
	Enter_CS();

	cBuf buf;
	//맵에 새로운 플레이어가 들어왔다 (캐릭터의 코드(이름), 현재 위치)
	buf.Append(_player->Get_Char_Info()->Get_Char_Code());
	buf.Append((char*)_player->Get_Char_Info()->GetName());
	buf.Append(_player->Get_Char_Info()->Get_Job().mCode);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_ENTER_NEW_CHAR_DATA);
	//새로 들어온 플레이어가 들어왔다고 클라이언트에 알림(클라이언트에서는 해당위치에 오브젝트 생성)
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

cMap_Town::cMap_Town()
{
	//mCode = TOWN_MAP_CODE;
}

cMap_Town::~cMap_Town()
{

}

