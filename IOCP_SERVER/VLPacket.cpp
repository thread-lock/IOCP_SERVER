#include "VLPacket.h"
#include "ErrManager.h"


cVLPacket::cVLPacket(SOCKET socket, SOCKADDR_IN addr) : cTcpClient(socket, addr)//������
{
	mRecvBuf = cBuf(sizeof(int));
}

cVLPacket::~cVLPacket()//�Ҹ���
{

}

bool cVLPacket::IsPacking()
{
	return (mSendBuf.size() > 0);
}

bool cVLPacket::IsSendSuccess(int _trans)
{
	cBuf* sendbuf = mSendBuf.front();
	sendbuf->transsize += _trans;
	if (sendbuf->bufsize == sendbuf->transsize)//���� ���������Ϳ� �� ���� �����Ͱ� ������
	{
		mSendBuf.pop();
		delete sendbuf;
		return true;//������ ���� �Ϸ� ����
	}
	return false;//������ ���� ������ ����
}

bool cVLPacket::IsRecvSuccess(int _trans)
{
	mRecvBuf.transsize += _trans; //������ŭ ���� ���� �����ͷ��� �߰�
	if (mRecvBuf.transsize == mRecvBuf.bufsize)//���� ���������Ϳ� �� ���� �����Ͱ� ������
	{
		if (mRecvBuf.bufsize == sizeof(int))//�ѹ��������Ͱ� ��Ŷ�� ũ�� ������
		{
			int recvsize;
			mRecvBuf.separate(recvsize);
			mRecvBuf.Clear(recvsize);
			return false;//������ ���� ������ ����
		}//��Ŷ�� ũ�� �ƴҽ�
		return true;//������ ���� �Ϸ� ����
	}
	return false;//������ ���� ������ ����
}

bool cVLPacket::IsRecvOverLap(OVERLAPPED * _overlap)
{
	return (&(mRecvOverlap.overlapped) == _overlap);
}

bool cVLPacket::IsSendOverLap(OVERLAPPED * _overlap)
{
	return  (&(mSendOverlap.overlapped) == _overlap);
}

void cVLPacket::Pack(const cProtocol& _protocol, cBuf& _data)//��Ŷ ����
{
	cBuf* sendbuf = new cBuf();
	sendbuf->Append((int)sizeof(__int64) + (int)sizeof(int) + _data.bufsize);
	sendbuf->Append(_protocol);
	sendbuf->Append(_data);
	mSendBuf.push(sendbuf);
}

void cVLPacket::Pack(const cProtocol& _protocol)//��Ŷ ����
{
	cBuf* sendbuf = new cBuf();
	cBuf data;
	sendbuf->Append((int)sizeof(__int64) + (int)sizeof(int) + data.bufsize);
	sendbuf->Append(_protocol);
	sendbuf->Append(data);
	mSendBuf.push(sendbuf);
}


void cVLPacket::UnPack(cProtocol& _protocol, cBuf& _data)//��Ŷ ����
{
	mRecvBuf.separate(_protocol);
	mRecvBuf.separate(_data);
	mRecvBuf.Clear(sizeof(int));
}


bool cVLPacket::SendPacket()
{
	if (mSendBuf.size() > 1) return true;
	cBuf* sendBuf = mSendBuf.front();
	char* ptr = sendBuf->buf.get() + sendBuf->transsize;
	int size = sendBuf->bufsize - sendBuf->transsize;
	int retval = Send(ptr, size, 0, false);
	if (retval == SOCKET_ERROR || retval == 0)
	{
		return false;
	}
	return true;

}

bool cVLPacket::RecvPacket()
{
	mRecvBuf.Clear(sizeof(int));
	int retval = Recvn(mRecvBuf.buf.get(),sizeof(int), 0);//��Ŷ�� ũ�⸦ ����
	if (retval == SOCKET_ERROR || retval == 0)
	{
		return false;
	}
	int size;
	memcpy(&size, mRecvBuf.buf.get(), sizeof(int)); //��Ŷ�� ũ�⸦ ������ ������ ����
	mRecvBuf.Clear(size);
	retval = Recvn(mRecvBuf.buf.get(), size, 0); //��Ŷ�� ũ�⸸ŭ ����
	if (retval == SOCKET_ERROR || retval == 0)
	{
		return false;
	}
	return true;
}

bool cVLPacket::WSArecvPacket()
{
	ZeroMemory(&mRecvOverlap.overlapped, sizeof(mRecvOverlap.overlapped));
	mRecvOverlap.wsabuf.buf = mRecvBuf.buf.get() + mRecvBuf.transsize;
	mRecvOverlap.wsabuf.len = mRecvBuf.bufsize - mRecvBuf.transsize;

	DWORD recvbytes, flags = 0;
	int retval = WSARecv(mSock, &mRecvOverlap.wsabuf, 1, &recvbytes, &flags, &mRecvOverlap.overlapped, NULL);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			return false;
		}
	}
	return true;
}

bool cVLPacket::WSAsendPacket()
{
	if (mSendBuf.size() > 1) return true;
	cBuf* sendBuf = mSendBuf.front();
	ZeroMemory(&mSendOverlap.overlapped, sizeof(mSendOverlap.overlapped));
	mSendOverlap.wsabuf.buf = sendBuf->buf.get() + sendBuf->transsize;
	mSendOverlap.wsabuf.len = sendBuf->bufsize - sendBuf->transsize;

	DWORD sendbytes, flags = 0;
	int retval = WSASend(mSock, &mSendOverlap.wsabuf, 1, &sendbytes, flags, &mSendOverlap.overlapped, NULL);
	if (retval == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			return false;
		}
	}
	return true;
}
