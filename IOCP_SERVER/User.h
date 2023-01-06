#pragma once
#ifndef USER_H
#define USER_H
#include "Global.h"
#include <list>

using std::list;
class cUser
{
	int code;
	char id[ID_SIZE];
	char pw[ID_SIZE];

public:
	cUser() {}
	cUser(const char*,const char*);
	cUser(int, const char*, const char*);
	cUser(cUser&);
	~cUser();

	int Get_Code() const;
	const char* Get_Id() const;
	const char* Get_Pw() const;





};

#endif // !USER_H
