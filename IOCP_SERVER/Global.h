#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#pragma comment(lib,"msimg32")
#pragma comment(lib,"ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <memory>

using std::shared_ptr;


template<typename T>
struct ArrayDeleter
{
	void operator() (T* p)
	{
		delete[] p;
	}
};



//아이디 사이즈
#define ID_SIZE 50
//버퍼 사이즈
#define BUFSIZE 4096
//서버 포트
#define SERVERPORT 9000


#endif // !GLOBAL_H

