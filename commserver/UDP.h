#ifndef UDP_H
#define UDP_H

#include <WinSock2.h>


class UDPComms
{
public:
	UDPComms(int port);
	UDPComms(const char* host, int port, int port2);
	~UDPComms();

	int Send(const char* buf);
	int Receive(char* buf, int len);

	char* GetClientIP() const;

protected:
	void Create();
	void Bind(long host, int port);

private:
	WSADATA wsadata;
	SOCKET socket;
	sockaddr_in sendaddr;
	mutable char client[80];
};

#endif
