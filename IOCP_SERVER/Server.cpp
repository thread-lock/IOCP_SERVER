#include "MainManager.h"
 


/*
iocp로 구현한 테트리스 서버 

최대 5인가 동시에 대전가능

여러 방중에 원하는 받에 입장하여 게임진행

방장이 게임시작할시 게임시작

한명이 살아 남을때까지 게임 진행 

게임종료되면 자신의 등수를 보내줌

*/


int main(int argc, char *argv[])
{
	//메인매니저 생성 및 실행
	cMainManager::GetInstance()->Create();
	cMainManager::GetInstance()->Run();
	cMainManager::GetInstance()->Destroy();
}