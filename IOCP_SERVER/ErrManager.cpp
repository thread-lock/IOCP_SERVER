#include "ErrManager.h"



cErrManager * cErrManager::mInstance = NULL; //�ν��Ͻ� �ʱ�ȭ

void cErrManager::Create() //�̱��� ����
{
	if (!mInstance)
	{
		mInstance = new cErrManager();
	}
}

cErrManager * cErrManager::GetInstance() //�̱��� ��ü ��ȯ
{
	return mInstance;
}

void cErrManager::Destroy() //�̱��� ����
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

cErrManager::cErrManager() //������
{

}

cErrManager::~cErrManager() //�Ҹ���
{

}

//���� �޼��� ����� ����
void cErrManager::err_quit(const char *msg)
{
	LPVOID lpMsgBuf;//���������� ������
	FormatMessage(//WSAGetLastError������ȣ�� �츮�� ���� ���� �˷��ִ� �Լ�
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//�ý������κ��� �����޼����� ��� ���� FORMAT_MESSAGE_ALLOCATE_BUFFER�� ���� �޼����� ���� �޸𸮸� ���� �Ҵ�
		NULL, WSAGetLastError(),//������ ���̺��� �ּҰ� NULL�� ������// WSAGetLastError�� ���������� �߻��� ���� ���� �ڵ带 �˷��ִ� �Լ�
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//�����޼����� ��� ���� ������ LANG_NEUTRAL ������ �⺻��� 
		(LPTSTR)&lpMsgBuf, 0, NULL);//lpMsgBuf�� �Ҵ�� �޸��� �ּҸ� ����
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);//�����쿡�� �����Ҵ�� �޸� ��ȯ
	exit(1);
}

//���� �޼��� ���
void cErrManager::err_display(const char *msg)
{
	LPVOID lpMsgBuf;//���������� ������
	FormatMessage(//WSAGetLastError������ȣ�� �츮�� ���� ���� �˷��ִ� �Լ�
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//�ý������κ��� �����޼����� ��� ���� FORMAT_MESSAGE_ALLOCATE_BUFFER�� ���� �޼����� ���� �޸𸮸� ���� �Ҵ�
		NULL, WSAGetLastError(),//������ ���̺��� �ּҰ� NULL�� ������// WSAGetLastError�� ���������� �߻��� ���� ���� �ڵ带 �˷��ִ� �Լ�
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//�����޼����� ��� ���� ������ LANG_NEUTRAL ������ �⺻��� 
		(LPTSTR)&lpMsgBuf, 0, NULL);//lpMsgBuf�� �Ҵ�� �޸��� �ּҸ� ����
	printf("[%s]%d %s", msg, WSAGetLastError(), (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

//�����ڵ�� ���� ���
void cErrManager::err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[����] %s", (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}



