#include "MainManager.h"
 


/*
iocp�� ������ ��Ʈ���� ���� 

�ִ� 5�ΰ� ���ÿ� ��������

���� ���߿� ���ϴ� �޿� �����Ͽ� ��������

������ ���ӽ����ҽ� ���ӽ���

�Ѹ��� ��� ���������� ���� ���� 

��������Ǹ� �ڽ��� ����� ������

*/


int main(int argc, char *argv[])
{
	//���θŴ��� ���� �� ����
	cMainManager::GetInstance()->Create();
	cMainManager::GetInstance()->Run();
	cMainManager::GetInstance()->Destroy();
}