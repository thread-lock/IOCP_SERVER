#include "CharManager.h"
#include "PlayerManager.h"
#include "DBManager.h"
#include "Map_Town.h"
#include "MapManger.h"
#include "PartyManager.h"

cCharManager * cCharManager::mInstance = NULL; //�ν��Ͻ� �ʱ�ȭ

void cCharManager::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cCharManager();
	}
}

cCharManager * cCharManager::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cCharManager();
	}
	return mInstance;
}

void cCharManager::Destroy() //�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cCharManager::cCharManager() //������
{

}

cCharManager::~cCharManager() //�Ҹ���
{

}


//�ش� ���̵� �����ϰ� �ִ� ĳ���� ����
void cCharManager::Req_Char_Info(cClientInfo * _info, cBuf & data)
{
	data.Clear();

	//ĳ���� ���� ���� ����
	int count = 0;
	cCharactor info[3];
	//ĳ������ ������ �ϳ��� ������
	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//������ ������ �ڵ尡 ĳ���͸� ������ ������ �ڵ�� ��ġ �ҽ� 
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

	//�˻��� ���� ��ŭ ��ŷ
	data.Append(count);
	for (int i = 0; i < count; i++)
	{
		data.Append((char*)info[i].GetName());
		data.Append(info[i].Get_Job().mCode);
	}


	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_CHAR_INFO);//ĳ���� ���� 

	_info->Pack(protocol, data);
	_info->SendMsg();
}

//ĳ���� ����
void cCharManager::Req_Create_Char(cClientInfo * _info, cBuf & data)
{
	char name[ID_SIZE];
	int jobcode;

	//������ ĳ������ �̸��� �����ڵ带 ����
	data.separate(name);
	data.separate(jobcode);
	data.Clear();

	bool overlap = false;

	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//ĳ���� �̸� �ߺ� �˻�
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
		data.Append((char*)"ĳ���� �̸� �ߺ�");
	}
	else
	{
		data.Append(true);
		cCharactor new_char(_info->Get_User_Info()->Get_Code(),name, jobcode);
		DBManager::GetInstance()->InsertData(new_char);
	}


	cProtocol protocol;
	protocol.Add_Protocol(cProtocol::P::SERVER_RE_CREATE_CHAR);

	//��� ��ŷ, �����Ұ�� ������ ������ ��ŷ

	_info->Pack(protocol, data);
	_info->SendMsg();

}

bool cCharManager::Req_Select_Char(cClientInfo * _info, cBuf & data)
{
	char name[ID_SIZE];
	//������ ĳ������ �̸� ����
	data.separate(name);
	data.Clear();

	//ĳ������ ������ �ϳ��� ������
	bool result = false;
	cCharactor chardata;
	DBManager::GetInstance()->SearchStart(DB_TABLE_CHAR);
	while (DBManager::GetInstance()->SearchData(chardata))
	{
		//������ ������ �ڵ尡 ĳ���͸� ������ ������ �ڵ�� ��ġ �ҽ� 
		if (_info->Get_User_Info()->Get_Code() == chardata.Get_User_Code())
		{ 
			//ĳ������ �̸��� ��
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

//ĳ���� ����
void cCharManager::Req_Delete_Char(cClientInfo * _info, cBuf & data)
{
	char name[CHAR_NAME_SIZE];
	//������ ĳ������ �̸� ����
	data.separate(name);
	data.Clear();
	//�ش� ĳ���� ����
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

