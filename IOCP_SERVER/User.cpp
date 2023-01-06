#include "User.h"

cUser::cUser(const char * _id, const char * _pw)
{
	code = 0;
	strcpy_s(id, _id);
	strcpy_s(pw, _pw);
}

cUser::cUser(int _code, const char * _id, const char * _pw)
{
	code = _code;
	strcpy_s(id, _id);
	strcpy_s(pw, _pw);
}

cUser::cUser(cUser & _user)
{
	code = _user.code;
	strcpy_s(id, _user.id);
	strcpy_s(pw, _user.pw);
}

cUser::~cUser()
{
}

int cUser::Get_Code() const
{
	return code;
}

const char * cUser::Get_Id() const
{
	return id;
}

const char * cUser::Get_Pw() const
{
	return pw;
}

