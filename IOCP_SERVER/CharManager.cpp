#include "CharManager.h"
#include "PlayerManager.h"
#include "DBManager.h"
#include "Map_Town.h"
#include "MapManger.h"
#include "PartyManager.h"

cCharManager * cCharManager::mInstance = NULL; //인스턴스 초기화

void cCharManager::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cCharManager();
	}
}

cCharManager * cCharManager::GetInstance() //싱글톤 객체 반환
{
	if (!mInstance)
	{
		mInstance = new cCharManager();
	}
	return mInstance;
}

void cCharManager::Destroy() //싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cCharManager::cCharManager() //생성자
{

}

cCharManager::~cCharManager() //소멸자
{

}


//해당 아이디가 소유하고 있는 캐릭터 정보
void cCharManager::Req_Char_Info(cClientInfo * _info, cBuf & data)
{
	data.Clear();

	//캐릭터 정보 받을 변수
	int count = 0;
	cCharactor info[3];
	//캐릭터의 정보를 하나씩 가져옴
	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//접속한 유저의 코드가 캐릭터를 소유한 유저의 코드와 일치 할시 
		if (_info->Get_User_Info()->Get_Code() == chardata.Get_User_Code())
		{
			info[count++] = chardata;
		}

		if (count == 3)
		{
			DBManager::GetInstance()->SearchEnd();
			break;
		}
	}

	//검색한 정보 만큼 패킹
	data.Append(count);
	for (int i = 0; i < count; i++)
	{
		data.Append((char*)info[i].GetName());
		data.Append(info[i].Get_Job().mCode);
	}


	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_CHAR_INFO);//캐릭터 정보 

	_info->Pack(protocol, data);
	_info->SendMsg();
}

//캐릭터 생성
void cCharManager::Req_Create_Char(cClientInfo * _info, cBuf & data)
{
	char name[ID_SIZE];
	int jobcode;

	//생성할 캐릭터의 이름과 직업코드를 언팩
	data.separate(name);
	data.separate(jobcode);
	data.Clear();

	bool overlap = false;

	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//캐릭터 이름 중복 검사
		if (!strcmp(name,chardata.GetName()))
		{ 
			overlap = true;
			DBManager::GetInstance()->SearchEnd();
			break;
		}
	}

	if (overlap)
	{
		data.Append(false);
		data.Append((char*)"캐릭터 이름 중복");
	}
	else
	{
		data.Append(true);
		cCharactor new_char(_info->Get_User_Info()->Get_Code(),name, jobcode);
		DBManager::GetInstance()->InsertData(new_char);
	}


	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_CREATE_CHAR);

	//결과 패킹, 실패할경우 실패한 이유도 패킹

	_info->Pack(protocol, data);
	_info->SendMsg();

}

bool cCharManager::Req_Select_Char(cClientInfo * _info, cBuf & data)
{
	char name[ID_SIZE];
	//선택한 캐릭터의 이름 언팩
	data.separate(name);
	data.Clear();

	//캐릭터의 정보를 하나씩 가져옴
	bool result = false;
	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//접속한 유저의 코드가 캐릭터를 소유한 유저의 코드와 일치 할시 
		if (_info->Get_User_Info()->Get_Code() == chardata.Get_User_Code())
		{ 
			//캐릭터의 이름을 비교
			if (!strcmp(name, chardata.GetName()))
			{
				result = true;
				cCharactor* charactor = new cCharactor(chardata);
				_info->Set_Char_Info(charactor);
				_info->Get_Char_Info()->Set_Enter_Map(cMap_Town::GetInstance());
				cMap_Town::GetInstance()->Enter_Player(_info);
				DBManager::GetInstance()->SearchEnd();

				break;
			}
		}
	}

	data.Append(chardata.Get_Ability().Get_Main_Stat());
	data.Append(chardata.Get_Ability().Get_Max_Hp());
	data.Append(chardata.Get_Ability().Get_Max_Mp());

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_SELECT_CHAR);

	_info->Pack(protocol, data);
	_info->SendMsg();

	return result;

}

//캐릭터 삭제
void cCharManager::Req_Delete_Char(cClientInfo * _info, cBuf & data)
{
	char name[CHAR_NAME_SIZE];
	//삭제할 캐릭터의 이름 언팩
	data.separate(name);
	data.Clear();
	//해당 캐릭터 삭제
	cCharactor drop_char(0, name, 0);
	DBManager::GetInstance()->DropData(drop_char);

	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_DELETE_CHAR);
	_info->Pack(protocol);
	_info->SendMsg();
}

void cCharManager::Char_Out(cClientInfo * _info)
{
	if (_info->Get_Char_Info() == nullptr) return;
	cCharactor* char_info = _info->Get_Char_Info();
	cBuf buf;
	cPartyManager::GetInstance()->Req_Out_Party(_info, buf);
	cMapManger::GetInstance()->Req_Out_Map(_info, buf);
	DBManager::GetInstance()->UpdateData(*char_info);
	_info->Set_Char_Info(nullptr);
	delete char_info;


}

