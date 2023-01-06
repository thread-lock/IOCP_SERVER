#include "ErrManager.h"



cErrManager * cErrManager::mInstance = NULL; //인스턴스 초기화

void cErrManager::Create() //싱글톤 생성
{
	if (!mInstance)
	{
		mInstance = new cErrManager();
	}
}

cErrManager * cErrManager::GetInstance() //싱글톤 객체 반환
{
	return mInstance;
}

void cErrManager::Destroy() //싱글톤 삭제
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cErrManager::cErrManager() //생성자
{

}

cErrManager::~cErrManager() //소멸자
{

}

//에러 메세지 출력후 종료
void cErrManager::err_quit(const char *msg)
{
	LPVOID lpMsgBuf;//에러저장할 포인터
	FormatMessage(//WSAGetLastError에러번호를 우리가 보기 쉽게 알려주는 함수
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//시스템으로부터 오류메세지를 얻어 오고 FORMAT_MESSAGE_ALLOCATE_BUFFER는 오류 메세지를 받을 메모리를 동적 할당
		NULL, WSAGetLastError(),//원래는 테이블의 주소가 NULL에 들어가야함// WSAGetLastError는 마지막으로 발생한 윈속 에러 코드를 알려주는 함수
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//오류메세지를 어떠한 언어로 받을지 LANG_NEUTRAL 제어판 기본언어 
		(LPTSTR)&lpMsgBuf, 0, NULL);//lpMsgBuf로 할당된 메모리의 주소를 받음
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);//윈도우에서 동적할당된 메모리 반환
	exit(1);
}

//에러 메세지 출력
void cErrManager::err_display(const char *msg)
{
	LPVOID lpMsgBuf;//에러저장할 포인터
	FormatMessage(//WSAGetLastError에러번호를 우리가 보기 쉽게 알려주는 함수
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//시스템으로부터 오류메세지를 얻어 오고 FORMAT_MESSAGE_ALLOCATE_BUFFER는 오류 메세지를 받을 메모리를 동적 할당
		NULL, WSAGetLastError(),//원래는 테이블의 주소가 NULL에 들어가야함// WSAGetLastError는 마지막으로 발생한 윈속 에러 코드를 알려주는 함수
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//오류메세지를 어떠한 언어로 받을지 LANG_NEUTRAL 제어판 기본언어 
		(LPTSTR)&lpMsgBuf, 0, NULL);//lpMsgBuf로 할당된 메모리의 주소를 받음
	printf("[%s]%d %s", msg, WSAGetLastError(), (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

//에러코드로 에러 출력
void cErrManager::err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[오류] %s", (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}



