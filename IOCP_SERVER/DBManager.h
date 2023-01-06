#pragma once
#ifndef DBMANAGER_H
#define DBMANAGER_H
#pragma comment(lib,"libmysql.lib") 
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include "User.h"
#include "Charactor.h"
#include "Item.h"

#define DB_HOST "localhost"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "GAME_DB"
#define DB_TABLE_USER "USER_TABLE"
#define DB_TABLE_CHAR "CHAR_TABLE"
#define DB_TABLE_EQUIP "EQUI_TABLE"
#define DB_TABLE_WEAPON "WEAPON_TABLE"

class DBManager
{
private:
	static DBManager* Instance;
	DBManager();
	~DBManager();

	MYSQL * connection; //쿼리와 연결되는 포인터 
	MYSQL_RES * sql_result; //쿼리의 결과를 가져올 포인터
	MYSQL_ROW sql_row;//쿼리의 행
	char query[255];//쿼리 사용할 문자열
	int retval;//결과 값
public:
	static void CreateInstance();
	static DBManager* GetInstance();
	static void DestroyInstance();

	void Init();
	void End();

	//INSERT
	bool InsertData(cUser & _user);
	bool InsertData(cCharactor & _char);
	//SELECT
	bool SearchData(cUser& _user);
	bool SearchData(cCharactor& _char);
	bool SearchData(cEquipment& _item);
	bool SearchData(cWeapon& _item);
	//DELETE
	bool DropData(cUser& _user);
	bool DropData(cCharactor& _char);
	//UPDATE
	bool UpdateData(cCharactor& _char);


	bool SearchStart(const char* _tablename);
	void SearchEnd();
};



#endif // !DBMANAGER_H

