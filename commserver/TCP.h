#ifndef TCP_H
#define TCP_H

#include <WinSock2.h>


class TCPComms
{
public:
	TCPComms(int port);
	TCPComms(const char* host, int port);
	~TCPComms();

	int Send(const char* buf);
	int Receive(char* buf, int len);
	int Accept();

	char* GetClientIP() const;

protected:
	void Create();
	void Init(long host, int port);

private:
	WSADATA wsadata;
	SOCKET socket;
	bool accepted;
	SOCKET acceptsocket;
	sockaddr_in sendaddr;
	mutable char client[80];
};

#endif
