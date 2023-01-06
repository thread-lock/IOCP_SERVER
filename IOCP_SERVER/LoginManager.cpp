#include "LoginManager.h"
#include "DBManager.h"



cLoginManager * cLoginManager::mInstance = NULL; //�ν��Ͻ� �ʱ�ȭ

void cLoginManager::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cLoginManager();
	}
}

cLoginManager * cLoginManager::GetInstance() //�̱��� ��ü ��ȯ
{
	if (!mInstance)
	{
		mInstance = new cLoginManager();
	}
	return mInstance;
}

void cLoginManager::Destroy() //�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}


cLoginManager::cLoginManager() //������
{

}

cLoginManager::~cLoginManager() //�Ҹ���
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

	//�̹� ���� ������ Ȯ��
	if (Get_Enter_User(id) == nullptr)
	{
		cUser userdata;
		DBManager::GetInstance()->SearchStart(DB_TABLE_USER);
		while (DBManager::GetInstance()->SearchData(userdata))
		{
			//���̵� Ȯ��
			if (!strcmp(userdata.Get_Id(), id))
			{
				search = true;
				//��й�ȣ Ȯ��
				if (!strcmp(userdata.Get_Pw(), pw))
				{
					result = true;
					data.Append(result);
					cUser* new_user = new cUser(userdata);
					// �������� ���� ��Ͽ� �߰�
					user_list.push_back(new_user);
					// Ŭ���̾�Ʈ�� ���� ������ ����
					_info->Set_User_Info(new_user);
					DBManager::GetInstance()->SearchEnd();
					break;
				}
				//��й�ȣ �� ��ġ
				else
				{
					data.Append(result);
					data.Append((char*)"��й�ȣ�� Ʋ�Ƚ��ϴ�.");
					DBManager::GetInstance()->SearchEnd();
					break;
				}
			}
		}
		//���̵� ���� ��ã�� ���
		if (!search)
		{
			data.Append(result);
			data.Append((char*)"��ġ�ϴ� ���̵� �����ϴ�.");
		}

	}
	else
	{
		data.Append(result);
		data.Append((char*)"�̹� �������� ���� �Դϴ�.");
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
		//���̵� Ȯ��
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
		data.Append((char*)"�̹� �����ϴ� ���̵� �Դϴ�.");
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