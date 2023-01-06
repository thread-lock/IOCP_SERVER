#include "Protocol.h"


cProtocol::cProtocol()
{
	protocol = 0;
}

cProtocol::cProtocol(__int64 _p)
{
	protocol = _p;
}

__int64 cProtocol::GetProtocol() const
{
	return protocol;
}
void cProtocol::Add_Protocol(P _p)
{
	__int64 square = Protocol_to_square(_p);
	protocol = protocol | square;
}

bool cProtocol::Protocol_Is_In(P _p)
{
	__int64 square = Protocol_to_square(_p);
	return protocol & square;
}

void cProtocol::Reset()
{
	protocol = 0;
}

__int64 cProtocol::Protocol_to_square(P _p)
{
	__int64 result = 1;

	for (int i = 0; i < (int)_p; i++)
	{
		result *= 2;
	}

	return result;
}