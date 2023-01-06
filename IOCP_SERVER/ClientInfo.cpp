#include "ClientInfo.h"
#include "CharManager.h"
#include "LoginManager.h"


//������
cClientInfo::cClientInfo(SOCKET _sock, SOCKADDR_IN _addr) : cVLPacket(_sock, _addr)
{
	User_Info = nullptr;
	Char_Info = nullptr;
	cState::CreateState(this, State);
	printf("����: IP �ּ�=%s, ��Ʈ ��ȣ=%d \n", inet_ntoa(mAddr.sin_addr), ntohs(mAddr.sin_port));
}

cClientInfo::~cClientInfo()
{
	cState::DeleteState(State);
	cCharManager::GetInstance()->Char_Out(this);
	cLoginManager::GetInstance()->LogOut(this);
	printf("����  : IP �ּ�=%s, ��Ʈ ��ȣ=%d \n", inet_ntoa(mAddr.sin_addr), ntohs(mAddr.sin_port));
}

cState * cClientInfo::Get_State()
{
	return now_State;
}

void cClientInfo::Set_State(eSTATE _state)
{
	now_State = State[_state];
}

void cClientInfo::Set_User_Info(cUser * _user)
{
	User_Info = _user;
}

void cClientInfo::Set_Char_Info(cCharactor * _char)
{
	Char_Info = _char;
}

cUser * cClientInfo::Get_User_Info()
{
	return User_Info;
}

cCharactor * cClientInfo::Get_Char_Info()
{
	return Char_Info;
}

bool cClientInfo::SendMsg()
{
	bool retval = WSAsendPacket();
	if (retval)
	{

	}
	else
	{

	}
	return retval;
}

bool cClientInfo::RecvMsg()
{
	bool retval = WSArecvPacket();
	if (retval)
	{

	}
	else
	{

	}
	return retval;
}

