#include <iostream>
#include <stdio.h>

#include "UDP.h"


UDPComms::UDPComms(int port)
{
	Create();
	Bind(htonl(INADDR_ANY), port);
}

UDPComms::UDPComms(const char* host, int port, int port2)
{
	Create();
	hostent* he = gethostbyname(host);
	if (he)
	{
		Bind(((in_addr*)he->h_addr)->s_addr, port2);
		sendaddr.sin_port = htons(port);
	}
	else
	{
		std::cerr << "Failed to resolve host " << host << std::endl;
		throw 0;
	}
}

UDPComms::~UDPComms()
{
	closesocket(socket);
	WSACleanup();
}

void UDPComms::Create()
{
	WSAStartup(MAKEWORD(2,2), &wsadata);
	socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void UDPComms::Bind(long host, int port)
{
	memset(&sendaddr, 0, sizeof(sendaddr));
	sendaddr.sin_family = AF_INET;
	sendaddr.sin_port = htons(port);
	sendaddr.sin_addr.s_addr = host;
	if (bind(socket, (SOCKADDR*)&sendaddr, sizeof(sendaddr)))
	{
		std::cerr << "Failed to bind at port " << port << std::endl;
		throw 0;
	}
}

int UDPComms::Send(const char* buf)
{
	return sendto(socket, buf, (int)strlen(buf), 0, (SOCKADDR*)&sendaddr, sizeof(sendaddr));
}

int UDPComms::Receive(char *buf, int len)
{
	int addrsize = sizeof(sendaddr);
	return recvfrom(socket, buf, len, 0, (SOCKADDR*)&sendaddr, &addrsize);
}

char* UDPComms::GetClientIP() const
{
	snprintf(client, sizeof(client), "%d.%d.%d.%d", sendaddr.sin_addr.S_un.S_un_b.s_b1, sendaddr.sin_addr.S_un.S_un_b.s_b2, sendaddr.sin_addr.S_un.S_un_b.s_b3, sendaddr.sin_addr.S_un.S_un_b.s_b4);
	return client;
}
