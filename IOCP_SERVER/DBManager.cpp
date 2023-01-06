#include "DBManager.h"

DBManager* DBManager::Instance = nullptr;

DBManager::DBManager()
{
	sql_result = NULL;
}

DBManager::~DBManager()
{
}

void DBManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new DBManager();
	}
}

DBManager * DBManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new DBManager();
	}
	return Instance;
}

void DBManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void DBManager::Init()
{
	//���� ������ �ʱ�ȭ
	connection = mysql_init(NULL);

	//���������ڷ� mysql ������ ����
	if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0) == NULL)
	{
		//���� üũ
		fprintf(stderr, "Mysql connection error : %s", mysql_error(connection));
		return;
	}
}

void DBManager::End()
{
	mysql_close(connection);
}


bool DBManager::InsertData(cUser & _user)
{
	sprintf_s(query, "Insert into %s(_id,_pw) values ('%s', '%s')", DB_TABLE_USER, _user.Get_Id(), _user.Get_Pw());
	retval = mysql_query(connection, query);
	if (retval != 0)
	{
		//���� üũ
		fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
		return false;
	}
	return true;
}

bool DBManager::InsertData(cCharactor & _char)
{
	sprintf_s(query, "Insert into %s(_user_code,_name,_job_code,_sumLv, _sumLvExpMax, _sumLvExpNow) values (%d, '%s', %d, %d, %d, %d)",
		DB_TABLE_CHAR, _char.Get_User_Code(), _char.GetName(), _char.Get_Job().mCode, _char.Get_Ability().mSumLv, _char.Get_Ability().mSumLvExpMax, _char.Get_Ability().mSumLvExpNow);
	retval = mysql_query(connection, query);
	if (retval != 0)
	{
		//���� üũ
		fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
		return false;
	}
	return true;
}

bool DBManager::SearchData(cUser& _user)
{
	//mysql_fetch_row �Լ��� �������� ������ ������
	//�����Ͱ� ���ٸ� null����
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		_user = cUser(atoi(sql_row[0]), sql_row[1], sql_row[2]);
		return true;
	}
	//������� ���̻� ����� �ʿ䰡 ���ٸ� �޸𸮸� ��ȯ ��Ų��.
	//��ȯ���� ������� �޸� ����
	SearchEnd();
	return false;
}

bool DBManager::SearchData(cCharactor & _char)
{
	//mysql_fetch_row �Լ��� �������� ������ ������
	//�����Ͱ� ���ٸ� null����
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		_char = cCharactor(atoi(sql_row[0]), atoi(sql_row[1]), sql_row[2], atoi(sql_row[3]),
			atoi(sql_row[4]), atoi(sql_row[5]), atoi(sql_row[6]));
		return true;
	}
	//������� ���̻� ����� �ʿ䰡 ���ٸ� �޸𸮸� ��ȯ ��Ų��.
	//��ȯ���� ������� �޸� ����
	SearchEnd();
	return false;
}

bool DBManager::SearchData(cEquipment& _item)
{
	//mysql_fetch_row �Լ��� �������� ������ ������
	//�����Ͱ� ���ٸ� null����
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		_item = cEquipment(atoi(sql_row[0]), sql_row[1], atoi(sql_row[2]), atoi(sql_row[3]), atoi(sql_row[4]), atoi(sql_row[5]));
		return true;
	}
	//������� ���̻� ����� �ʿ䰡 ���ٸ� �޸𸮸� ��ȯ ��Ų��.
	//��ȯ���� ������� �޸� ����
	SearchEnd();
	return false;
}

bool DBManager::SearchData(cWeapon & _item)
{
	//mysql_fetch_row �Լ��� �������� ������ ������
	//�����Ͱ� ���ٸ� null����
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		_item = cWeapon(atoi(sql_row[0]), sql_row[1], atoi(sql_row[2]), atoi(sql_row[3]), atoi(sql_row[4]), atoi(sql_row[5]));
		return true;
	}
	//������� ���̻� ����� �ʿ䰡 ���ٸ� �޸𸮸� ��ȯ ��Ų��.
	//��ȯ���� ������� �޸� ����
	SearchEnd();
	return false;
}

bool DBManager::DropData(cUser& _user)
{
		sprintf_s(query, "delete from %s where _id = '%s'", DB_TABLE_USER, _user.Get_Id());
		retval = mysql_query(connection, query);
		if (retval != 0)
		{
			//���� üũ
			fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
			return false;
		}
		return true;
}

bool DBManager::DropData(cCharactor & _char)
{
	sprintf_s(query, "delete from %s where _code = '%s'", DB_TABLE_CHAR, _char.GetName());
	retval = mysql_query(connection, query);
	if (retval != 0)
	{
		//���� üũ
		fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
		return false;
	}
	return true;
}

bool DBManager::UpdateData(cCharactor & _char)
{
	sprintf_s(query, "update from %s set _sumLv = %d, _sumLvExpMax = %d, _sumLvExpNow = %d where _name = '%s' ",
		DB_TABLE_CHAR, _char.Get_Ability().mSumLv, _char.Get_Ability().mSumLvExpMax, _char.Get_Ability().mSumLvExpNow, _char.GetName());
	retval = mysql_query(connection, query);
	if (retval != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
		return false;
	}
	return true;
}

bool DBManager::SearchStart(const char* _tablename)
{
	sprintf_s(query, "select * from %s", _tablename);
	retval = mysql_query(connection, query);
	if (retval != 0)
	{
		//���� üũ
		fprintf(stderr, "Mysql query error : %s", mysql_error(connection));
		return false;
	}

	//�����κ��� ��� ������
	sql_result = mysql_store_result(connection);
	return true;
}

void DBManager::SearchEnd()
{
	if (sql_result)
	{
		mysql_free_result(sql_result);
		sql_result = NULL;
	}
}
