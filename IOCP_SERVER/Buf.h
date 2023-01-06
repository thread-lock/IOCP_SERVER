#pragma once
#ifndef BUF_H
#define BUF_H
#include"Global.h"
#include "Protocol.h"

#define BUF shared_ptr<char>
#define CREATE_BUF(X) shared_ptr<char>(new char[X],ArrayDeleter<char>())


class cBuf
{
public:
	BUF buf;
	int bufsize;
	int transsize;

	cBuf();
	cBuf(cBuf&);
	cBuf(int);
	~cBuf();
	void Clear();
	void Clear(int);

	void Append(const cProtocol& _p);
	void Append(cBuf& _data);
	void Append(char* _str);
	void Append(bool _bool);
	void Append(int _int);
	void Append(float _float);

	void separate(cProtocol& _p);
	void separate(cBuf& _data);
	void separate(char*);
	void separate(int&);
	void separate(bool&);
	void separate(float&);

};


#endif // !BUF_H
