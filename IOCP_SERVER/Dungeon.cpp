#include "Dungeon.h"

bool cDungeonField::Enter_Player(cClientInfo * _player)
{
	Enter_CS();
	mPlayer_List.push_back(_player);
	Sector_Chk(_player->Get_Char_Info());
	Out_CS();
	return true;
}

void cDungeonField::Set_Store(cStore * _store)
{
	mStore = _store;
}

void cDungeonField::Player_Move_Data_Send(cClientInfo * _player, int _move)
{

	Enter_CS();


	cCharactor* pchar = _player->Get_Char_Info();

	Sector_Chk(pchar);

	cBuf buf;

	buf.Append(pchar->Get_Char_Code());
	buf.Append(_move);
	buf.Append(pchar->Get_Location().GetX());
	buf.Append(pchar->Get_Location().GetY());

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MOVE_CHAR_DATA);

	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

void cDungeonField::Map_Enter_Data_Send(cClientInfo* _player)
{
	Enter_CS();

	if (!mThread_on)
	{
		Frame_Start();
		mThread_on = true;
	}

	cBuf buf;

	buf.Append((int)(mPlayer_List.size() - 1));
	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		if ((*i) == _player) continue;
		buf.Append((*i)->Get_Char_Info()->Get_Char_Code());
		buf.Append((char*)(*i)->Get_Char_Info()->GetName());
		buf.Append((*i)->Get_Char_Info()->Get_Ability().Get_Max_Hp());
		buf.Append((*i)->Get_Char_Info()->Get_Ability().Now_Hp);
	}


	buf.Append((int)mMob_List.size());
	for (list<cMob*>::iterator i = mMob_List.begin(); i != mMob_List.end(); ++i)
	{   
		buf.Append((*i)->Get_Mob_Code());
		buf.Append((*i)->Get_Code());
		buf.Append((*i)->Get_Location().GetX());
		buf.Append((*i)->Get_Location().GetY());
		buf.Append((*i)->Get_Now_Hp());
		buf.Append((*i)->Get_Max_Hp());
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_MAP_DATA);
	_player->Pack(protocol, buf);
	_player->SendMsg();

	Out_CS();
}

void cDungeonField::Enter_Player_Data_Send(cClientInfo *)
{
	//없음
}

void cDungeonField::Req_Party_invite(cClientInfo * _info, int _code)
{
	Enter_CS();

	cProtocol protocol;
	cBuf buf;

	buf.Append(false);
	buf.Append((char*)"마을에서만 가능합니다.");
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_INVITE_PARTY);
	_info->Pack(protocol, buf);
	_info->SendMsg();

	Out_CS();

}

void cDungeonField::Mob_Move_Data_Send(cMob * _mob, float _x, float _y)
{
	Enter_CS();

	cProtocol protocol;
	cBuf buf;

	buf.Append(_mob->Get_Code()); //해당 코드의 몬스터가
	buf.Append(MOB_STATE::MOB_MOVE); //해당상태로 변경
	buf.Append(_x);
	buf.Append(_y);

	protocol.Add_Protocol(cProtocol::SERVER_MOB_STATE);

	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

void cDungeonField::Mob_Stop_Data_Send(cMob * _mob, int stop_count)
{
	Enter_CS();

	cProtocol protocol;
	cBuf buf;

	buf.Append(_mob->Get_Code()); //해당 코드의 몬스터가
	buf.Append(MOB_STATE::MOB_STOP); //해당상태로 변경
	buf.Append(stop_count);

	protocol.Add_Protocol(cProtocol::SERVER_MOB_STATE);

	for (list<cClientInfo*>::iterator i = mPlayer_List.begin(); i != mPlayer_List.end(); ++i)
	{
		(*i)->Pack(protocol, buf);
		(*i)->SendMsg();
	}

	Out_CS();
}

void cDungeonField::Frame_Start()
{
	mhandle = cThreadManager::GetInstance()->AddThread(0, this);
}

void cDungeonField::Frame_Stop()
{
	cThreadManager::GetInstance()->RemoveThread(mhandle);
}


//cDungeonField::cDungeonField()
//{
//
//}

cDungeonField::cDungeonField(sDungeon *)
{
	mStore = nullptr;
	mAI_thread = new cAI_Thread(40, &mMob_List);
}

DWORD cDungeonField::Procces(void * _data)
{
	mAI_thread->FrameRun();
	return 0;
}

void cDungeonField::Sector_Chk(cCharactor * _char)
{
	cSector* now_sector = _char->Get_Enter_Sector();
	if (now_sector)
	{
		if (!(now_sector->Is_Sector_Area(_char->Get_Location()))) //캐릭터의 위치가 지금 현재 섹터위치인지 검사 아닐경우
		{
			//현재 있는 섹터에서 나온다.
			now_sector->Out_Sector(_char);
			_char->Set_Enter_Sector(nullptr);
			//섹터 리스트에서 들어갈 섹터를 찾는다.
			for (list<cSector*>::iterator i = mSector_List.begin(); i != mSector_List.end(); ++i)
			{
				//위치를 찾으면 해당 섹터로 이동한다.
				if ((*i)->Is_Sector_Area(_char->Get_Location()))
				{
					(*i)->Enter_Sector(_char);
					_char->Set_Enter_Sector((*i));
					break;
				}
			}
		}
	}
	else
	{
		for (list<cSector*>::iterator i = mSector_List.begin(); i != mSector_List.end(); ++i)
		{
			//위치를 찾으면 해당 섹터로 이동한다.
			if ((*i)->Is_Sector_Area(_char->Get_Location()))
			{
				(*i)->Enter_Sector(_char);
				_char->Set_Enter_Sector((*i));
				break;
			}
		}
	}
}

void cDungeonField::Sector_Chk(cMob* _mob)
{
	cSector* now_sector = _mob->Get_Enter_Sector();
	if (now_sector)
	{
		if (!(now_sector->Is_Sector_Area(_mob->Get_Location()))) //캐릭터의 위치가 지금 현재 섹터위치인지 검사 아닐경우
		{
			//현재 있는 섹터에서 나온다.
			now_sector->Out_Sector(_mob);
			_mob->Set_Enter_Sector(nullptr);
			//섹터 리스트에서 들어갈 섹터를 찾는다.
			for (list<cSector*>::iterator i = mSector_List.begin(); i != mSector_List.end(); ++i)
			{
				//위치를 찾으면 해당 섹터로 이동한다.
				if ((*i)->Is_Sector_Area(_mob->Get_Location()))
				{
					(*i)->Enter_Sector(_mob);
					_mob->Set_Enter_Sector((*i));
					break;
				}
			}
		}
	}
	else
	{
		for (list<cSector*>::iterator i = mSector_List.begin(); i != mSector_List.end(); ++i)
		{
			//위치를 찾으면 해당 섹터로 이동한다.
			if ((*i)->Is_Sector_Area(_mob->Get_Location()))
			{
				(*i)->Enter_Sector(_mob);
				_mob->Set_Enter_Sector((*i));
				break;
			}
		}
	}
}

void cDungeonField::Add_Mob(cMob * _mob)
{
	mMob_List.push_back(_mob);
}

void cDungeonField::Init_Mob(cMob * _mob)
{
	_mob->Set_Enter_Map(this);
	_mob->Set_Mob_AI(new cMob_AI(_mob, mAI_thread));
}

void cDungeonField::Add_Sector(cSector* _secotr)
{
	mSector_List.push_back(_secotr);
}

void cDungeonField::Add_Trap(sTrap _trap)
{
	mTrap_List.push_back(sTrap(_trap));
}

void cDungeonField::Add_Store_spawn(cVector2D _store)
{
	mStore_spawn_List.push_back(cVector2D(_store));
}

cSector::cSector()
{

}

cSector::cSector(float _left, float _right, float _top, float _bottom)
{
	left = _left;
	right = _right;
	top = _top;
	bottom = _bottom;
}

bool cSector::Is_Sector_Area(cVector2D& _location)
{

	if (left <= _location.GetX() && _location.GetX() <= right)
	{
		return true;
	}
	return false;
}

bool cSector::Enter_Sector(cMob *)
{


	return false;
}

bool cSector::Char_Is_In(cMob *)
{
	return false;
}

bool cSector::Out_Sector(cMob *)
{
	return false;
}

bool cSector::Char_Is_In(cCharactor* _char)
{
	for (list<cCharactor*>::iterator i = mChar_List.begin(); i != mChar_List.end(); ++i)
	{
		if (_char == (*i)) return true;
	}
	return false;
}

bool cSector::Enter_Sector(cCharactor * _char)
{
	mChar_List.push_back(_char);
	return true;
}

bool cSector::Out_Sector(cCharactor * _char)
{
	mChar_List.remove(_char);
	return true;
}

void cSector::Char_SearchStart()
{
	Char_Search = mChar_List.begin();
}

bool cSector::Char_SearchData(cCharactor *& _char)
{
	if (Char_Search != mChar_List.end())
	{
		_char = *Char_Search;
		++Char_Search;
		return true;
	}
	else
	{
		return false;
	}
}

void cSector::Char_SerachEnd()
{
}

int cSector::Get_Mob_Num()
{
	return mMob_List.size();
}

void cSector::Mob_SearchStart()
{
	Mob_Search = mMob_List.begin();
}

bool cSector::Mob_SearchData(cMob *& _mob)
{
	if (Mob_Search != mMob_List.end())
	{
		_mob = *Mob_Search;
		++Mob_Search;
		return true;
	}
	else
	{
		return false;
	};
}

void cSector::Mob_SerachEnd()
{
}

float cSector::Get_Right_x()
{
	return right;
}

float cSector::Get_Left_x()
{
	return left;
}

