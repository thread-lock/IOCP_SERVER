#include "Buf.h"





cBuf::cBuf()
{
	buf = CREATE_BUF(0);
	bufsize = 0;
	transsize = 0;
}

cBuf::cBuf(cBuf & _buf)
{
	buf = CREATE_BUF(_buf.bufsize);
	bufsize = _buf.bufsize;
	transsize = _buf.transsize;

	memcpy(buf.get(), _buf.buf.get(), bufsize);
}

cBuf::cBuf(int _size)
{
	buf = CREATE_BUF(_size);
	bufsize = _size;
	transsize = 0;
}

cBuf::~cBuf()
{

}

void cBuf::Clear()
{
	buf = CREATE_BUF(0);
	bufsize = 0;
	transsize = 0;
}

void cBuf::Clear(int _size)
{
	buf = CREATE_BUF(_size);
	bufsize = _size;
	transsize = 0;
}

void cBuf::Append(const cProtocol & _p)
{
	__int64 protocol = _p.GetProtocol();

	shared_ptr<char> empt = buf;
	buf = CREATE_BUF(bufsize + sizeof(__int64));

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, &protocol, sizeof(__int64));
	bufsize += sizeof(__int64);

}

void cBuf::Append(cBuf& _data)
{
	Append(_data.bufsize);

	BUF empt = buf;
	buf = CREATE_BUF(bufsize + _data.bufsize);

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, _data.buf.get(), _data.bufsize);

	bufsize += _data.bufsize;
}

void cBuf::Append(char * _str)
{
	int len = strlen(_str);
	Append(len);

	BUF empt = buf;
	buf = CREATE_BUF(bufsize + len);

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, _str, len);

	bufsize += len;
}


void cBuf::Append(bool _bool)
{
	BUF empt = buf;
	buf = CREATE_BUF(bufsize + sizeof(bool));

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, &_bool, sizeof(bool));

	bufsize += sizeof(bool);
}

void cBuf::Append(int _int)
{
	BUF empt = buf;
	buf = CREATE_BUF(bufsize + sizeof(int));

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, &_int, sizeof(int));

	bufsize += sizeof(int);
}

void cBuf::Append(float _float)
{
	BUF empt = buf;
	buf = CREATE_BUF(bufsize + sizeof(float));

	char* ptr = buf.get();
	memcpy(ptr, empt.get(), bufsize);
	ptr += bufsize;

	memcpy(ptr, &_float, sizeof(float));

	bufsize += sizeof(float);
}

void cBuf::separate(cProtocol& _p)
{
	__int64 protocol;

	BUF empt = buf;

	memcpy(&protocol, empt.get(), sizeof(__int64));
	bufsize -= sizeof(__int64);
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + sizeof(__int64);
		memcpy(buf.get(), ptr, bufsize);
	}
	_p = cProtocol(protocol);

}
void cBuf::separate(cBuf& _data)
{
	int size;
	separate(size);

	_data.Clear(size);
	memcpy(_data.buf.get(), buf.get(), size);

	BUF empt = buf;
	bufsize -= size;
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + size;
		memcpy(buf.get(), ptr, bufsize);
	}

}

void cBuf::separate(char* _str)
{
	int len;
	separate(len);

	memcpy(_str, buf.get(), len);
	_str[len] = '\0';

	BUF empt = buf;
	bufsize -= len;
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + len;
		memcpy(buf.get(), ptr, bufsize);
	}
}

void cBuf::separate(int& _int)
{


	memcpy(&_int, buf.get(), sizeof(int));
	bufsize -= sizeof(int);

	BUF empt = buf;
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + sizeof(int);
		memcpy(buf.get(), ptr, bufsize);
	}
}

void cBuf::separate(bool& _bool)
{
	memcpy(&_bool, buf.get(), sizeof(bool));

	BUF empt = buf;
	bufsize -= sizeof(bool);
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + sizeof(bool);
		memcpy(buf.get(), ptr, bufsize);
	}
}

void cBuf::separate(float& _float)
{
	memcpy(&_float, buf.get(), sizeof(float));

	BUF empt = buf;
	bufsize -= sizeof(float);
	buf = CREATE_BUF(bufsize);

	if (bufsize > 0)
	{
		char* ptr = empt.get() + sizeof(float);
		memcpy(buf.get(), ptr, bufsize);
	}
}
