#include <iostream>
#include <stdio.h>

#include "TCP.h"


TCPComms::TCPComms(int port)
	: accepted(false)
{
	Create();
	Init(htonl(INADDR_ANY), port);
	if (bind(socket, (SOCKADDR*)&sendaddr, sizeof(sendaddr)))
	{
		std::cerr << "Failed to bind at port " << port << " " << WSAGetLastError() << std::endl;
		throw 0;
	}
	if (listen(socket, SOMAXCONN))
	{
		std::cerr << "Failed to listen at port " << port << " " << WSAGetLastError() << std::endl;
		throw 0;
	}
}

TCPComms::TCPComms(const char* host, int port)
	: accepted(false)
{
	Create();
	hostent* he = gethostbyname(host);
	if (he)
	{
		Init(((in_addr*)he->h_addr)->s_addr, port);
		if (connect(socket, (SOCKADDR*)&sendaddr, sizeof(sendaddr)))
		{
			std::cerr << "Failed to connect at port " << port << " " << WSAGetLastError() << std::endl;
			throw 0;
		}
	}
	else
	{
		std::cerr << "Failed to resolve host " << host << std::endl;
		throw 0;
	}
}

TCPComms::~TCPComms()
{
	if (accepted)
		closesocket(acceptsocket);
	closesocket(socket);
	WSACleanup();
}

void TCPComms::Create()
{
	WSAStartup(MAKEWORD(2,2), &wsadata);
	socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void TCPComms::Init(long host, int port)
{
	memset(&sendaddr, 0, sizeof(sendaddr));
	sendaddr.sin_family = AF_INET;
	sendaddr.sin_port = htons(port);
	sendaddr.sin_addr.s_addr = host;
}

int TCPComms::Send(const char* buf)
{
	return send(accepted ? acceptsocket : socket, buf, (int)strlen(buf), 0);
}

int TCPComms::Receive(char *buf, int len)
{
	return recv(accepted ? acceptsocket : socket, buf, len, 0);
}

int TCPComms::Accept()
{
	int addrsize = sizeof(sendaddr);
	acceptsocket = accept(socket, (SOCKADDR*)&sendaddr, &addrsize);
	if (acceptsocket != INVALID_SOCKET)
	{
		accepted = true;
		return 1;
	}
	std::cerr << "Failed to accept " << WSAGetLastError() << std::endl;
	return 0;
}

char* TCPComms::GetClientIP() const
{
	snprintf(client, sizeof(client), "%d.%d.%d.%d", sendaddr.sin_addr.S_un.S_un_b.s_b1, sendaddr.sin_addr.S_un.S_un_b.s_b2, sendaddr.sin_addr.S_un.S_un_b.s_b3, sendaddr.sin_addr.S_un.S_un_b.s_b4);
	return client;
}
