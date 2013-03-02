#pragma once

/*******************************************************************
 * Socket.hpp
 * Really simple utility class for manipulating sockets (Windows/Linux)
 *
 * WIP !!
 *
 * Started on January 2013
 * Senryoku <maretverdant@gmail.com>
 * https://github.com/Senryoku/UtilityClass
********************************************************************/

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1 // Définition des macros normalment disponible uniquement sous Windows
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s) // permet l'utilisation de closesocket quelque soit l'OS
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif
  
#include <iostream> // Debug
#include <stdlib.h>
#include <string>
#include <vector>

class BaseSocket
{
	public:
	BaseSocket();
	BaseSocket(unsigned long addr, int Port, int Type = SOCK_STREAM, short Family = AF_INET);
	virtual ~BaseSocket();
	
	bool isBlocking() const { return _blocking; }
	void setBlocking(bool b = true);
	
	int bind();
	int close();
	
	bool isValid() const { return _socket != INVALID_SOCKET; }
	const SOCKET& getSocket() const { return _socket; }
	const SOCKADDR_IN& getContext() const { return _context; }
	std::string getAddr() const { return inet_ntoa(_context.sin_addr); }
	short getPort() const { return htons(_context.sin_port); }
	
	int sendStr(std::string Str);
	std::string recvStr();
	
	bool sendSize(size_t size);
	
	size_t recvSize();

	/** @brief Send len octets of buffer through the socket.
	 * If return value differs from len, the socket is likely to be broken.
	 * @return The number of octets effectively sent.
	**/
	size_t send(const char* buffer, size_t len = 0);
	
	/** @brief Receive len octets through the socket writing them into buffer. 
	 * If return value differs from len, the socket is likely to be broken.
	 * @return The number of octets effectively received.
	**/
	size_t recv(char* buffer, size_t len = 0);
	
	static int init();
	static void cleanup();
	
	friend class TCPServerSocket;
	
	protected:
	SOCKET			_socket;
	SOCKADDR_IN		_context;
	bool			_blocking;
};

class TCPSocket : public BaseSocket
{
	public:
	TCPSocket();
	TCPSocket(std::string IP, int Port);
	~TCPSocket();
	
	int connect();
	
	private:
};

class TCPServerSocket : public BaseSocket
{
	public:
	TCPServerSocket(int Port, int MaxConnect = 5);
	~TCPServerSocket();
	
	TCPSocket& accept();
	
	std::vector<TCPSocket>& getClients() { return _connections; }

	int send(std::string Str);
	int send(const char* buffer, size_t len = 0);
	
	private:
	std::vector<TCPSocket>	_connections;
};

class FTPClient : public TCPSocket
{
	public:
	FTPClient();
	~FTPClient();
	
	private:
};
