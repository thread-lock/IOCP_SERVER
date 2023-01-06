#include "LoginManager.h"
#include "DBManager.h"



cLoginManager * cLoginManager::mInstance = NULL; //인스턴스 초기화

void cLoginManager::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cLoginManager();
	}
}

cLoginManager * cLoginManager::GetInstance() //싱글톤 객체 반환
{
	if (!mInstance)
	{
		mInstance = new cLoginManager();
	}
	return mInstance;
}

void cLoginManager::Destroy() //싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}


cLoginManager::cLoginManager() //생성자
{

}

cLoginManager::~cLoginManager() //소멸자
{

}

cUser * cLoginManager::Get_Enter_User(char * _id)
{
	cUser* userdata;
	for (list<cUser*>::iterator i = user_list.begin(); i != user_list.end(); ++i)
	{
		userdata = (*i);
		if (!strcmp(userdata->Get_Id(), _id))
		{
			return userdata;
		}
	}
	return nullptr;
}

bool cLoginManager::Req_Login(cClientInfo * _info, cBuf&  data)
{
	char id[ID_SIZE];
	char pw[ID_SIZE];

	data.separate(id);
	data.separate(pw);
	data.Clear();


	bool result = false;
	bool search = false;

	//이미 접속 중인지 확인
	if (Get_Enter_User(id) == nullptr)
	{
		cUser userdata;
		DBManager::GetInstance()->SearchStart(DB_TABLE_USER);
		while (DBManager::GetInstance()->SearchData(userdata))
		{
			//아이디 확인
			if (!strcmp(userdata.Get_Id(), id))
			{
				search = true;
				//비밀번호 확인
				if (!strcmp(userdata.Get_Pw(), pw))
				{
					result = true;
					data.Append(result);
					cUser* new_user = new cUser(userdata);
					// 접속중인 유저 목록에 추가
					user_list.push_back(new_user);
					// 클라이언트에 유저 정보를 저장
					_info->Set_User_Info(new_user);
					DBManager::GetInstance()->SearchEnd();
					break;
				}
				//비밀번호 불 일치
				else
				{
					data.Append(result);
					data.Append((char*)"비밀번호가 틀렸습니다.");
					DBManager::GetInstance()->SearchEnd();
					break;
				}
			}
		}
		//아이디를 아직 못찾은 경우
		if (!search)
		{
			data.Append(result);
			data.Append((char*)"일치하는 아이디가 없습니다.");
		}

	}
	else
	{
		data.Append(result);
		data.Append((char*)"이미 접속중인 유저 입니다.");
	}
	
	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_LOGIN);
	
	_info->Pack(protocol, data);
	_info->SendMsg();

	return result;
}

void cLoginManager::Req_Join(cClientInfo * _info, cBuf&  data)
{
	char id[ID_SIZE];
	char pw[ID_SIZE];

	data.separate(id);
	data.separate(pw);
	data.Clear();


	bool search = false;
	cUser userdata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_USER);
	while (DBManager::GetInstance()->SearchData(userdata))
	{
		//아이디 확인
		if (!strcmp(userdata.Get_Id(), id))
		{
			search = true;
			DBManager::GetInstance()->SearchEnd();
			break;
		}
	}


	if (search)
	{
		data.Append(false);
		data.Append((char*)"이미 존재하는 아이디 입니다.");
	}
	else
	{
		cUser user(id, pw);
		DBManager::GetInstance()->InsertData(user);
		data.Append(true);
	}

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_JOIN);

	_info->Pack(protocol, data);
	_info->SendMsg();
}

void cLoginManager::LogOut(cClientInfo * _info)
{
	if (_info->Get_User_Info() == nullptr) return;
	cUser* userinfo = _info->Get_User_Info();
	user_list.remove(userinfo);
	_info->Set_User_Info(nullptr);
	delete userinfo;

}