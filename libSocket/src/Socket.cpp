#include "Socket.hpp"

/* ================== BaseSocket =================== */

BaseSocket::BaseSocket() : _blocking(false)
{
}

BaseSocket::BaseSocket(unsigned long addr, int Port, int Type, short Family) : _blocking(false)
{
	_socket = socket(Family, Type, 0);

	_context.sin_addr.s_addr = addr;
	_context.sin_family = Family;
	_context.sin_port = htons(Port);
}

BaseSocket::~BaseSocket()
{
	if(isValid()) close();
}

void BaseSocket::setBlocking(bool b)
{
#if defined (WIN32)
	unsigned long int arg = (b) ? 0 : 1;
	if(ioctlsocket(_socket, FIONBIO, &arg) == SOCKET_ERROR)
		std::cerr << "Error ioctlsocket() : " << WSAGetLastError() << std::endl;
#elif defined (linux)
	int flags = fcntl(_socket, F_GETFL);
	if(b) fcntl(_socket, F_SETFL, flags & ~O_NONBLOCK);
	else fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
#endif
	_blocking = b;
}

int BaseSocket::bind()
{
	return ::bind(_socket, (SOCKADDR*) &_context, sizeof(_context));
}

int BaseSocket::close()
{
	int r = closesocket(_socket);
	_socket = INVALID_SOCKET;
	return r;
}

int BaseSocket::sendStr(std::string Str)
{
	return sendSize(Str.length() + 1) && send(Str.c_str(), Str.length() + 1) == Str.length() + 1;
}

std::string BaseSocket::recvStr()
{
	size_t size = recvSize();
	char* buff = (char*) malloc(size);
	recv(buff, size);
	std::string rStr(buff);
	free(buff);
	return rStr;
}

bool BaseSocket::sendSize(size_t size)
{
	char buff[64];
	itoa(size, buff, 10);
	return send(buff, 64);
}
	
size_t BaseSocket::recvSize()
{
	char buff[64];
	recv(buff, 64);
	return atoi(buff);
}
	
size_t BaseSocket::send(const char* buffer, size_t len)
{
	size_t sent = 0, res;
	if(len == 0) len = sizeof(buffer);
	while(sent < len)
	{
		res = ::send(_socket, buffer + sent, len - sent, 0);
		if(res > 0) sent += res;
		else return sent;
	}
	return sent;
}

size_t BaseSocket::recv(char* buffer, size_t len)
{
	size_t received = 0, res;
	if(len == 0) len = sizeof(buffer);
	while(received < len)
	{
		res = ::recv(_socket, buffer + received, len - received, 0);
		if(res > 0) received += res;
		else if(res == 0) { // Connection closed on the other side.
			close();
			return received;
		} else return received;
	}
	return received;
}

int BaseSocket::init()
{
#if defined (WIN32)
	WSADATA WSAData;
	return WSAStartup(MAKEWORD(2,2), &WSAData);
#elif defined (linux)
	return 0;
#endif
}

void BaseSocket::cleanup()
{
#if defined (WIN32)
	WSACleanup();
#endif
}

/* ================== TCPSocket =================== */

TCPSocket::TCPSocket() : BaseSocket()
{
}

TCPSocket::TCPSocket(std::string IP, int Port) : BaseSocket(inet_addr(IP.c_str()), Port)
{
}

TCPSocket::~TCPSocket()
{
}

int TCPSocket::connect()
{
	return ::connect(_socket, (SOCKADDR*) &_context, sizeof(_context));
}

/* ================== TCPServerSocket =================== */

TCPServerSocket::TCPServerSocket(int Port, int MaxConnect) : BaseSocket(htonl(INADDR_ANY), Port)
{
	if(bind() == SOCKET_ERROR) std::cerr << "Error bind()" << std::endl;
	if(listen(_socket, MaxConnect) == SOCKET_ERROR) std::cerr << "Error listen()" << std::endl;
}

TCPServerSocket::~TCPServerSocket()
{
	for(size_t i = 0; i < _connections.size(); ++i)
		shutdown(_connections[i]._socket, 2);
	closesocket(_socket);
}

TCPSocket& TCPServerSocket::accept()
{
	// Création d'un nouveau Socket
	size_t NewSocket = _connections.size();
	_connections.resize(NewSocket + 1);
	
	socklen_t ContextSize = sizeof(_connections[NewSocket]._context);
	
	_connections[NewSocket]._socket = ::accept(_socket, (SOCKADDR*) &_connections[NewSocket]._context, &ContextSize);
	
	if(_connections[NewSocket]._socket == INVALID_SOCKET)
		std::cerr << "Error socket : " << strerror(errno) << std::endl;
	
	return _connections[NewSocket];
}


int TCPServerSocket::send(std::string Str)
{
	int r = 0;
	for(size_t i = 0; i < _connections.size(); ++i)
		r = r | BaseSocket::sendStr(Str);
	return r;
}

int TCPServerSocket::send(const char* buffer, size_t len)
{
	int r = 0;
	for(size_t i = 0; i < _connections.size(); ++i)
		r = r | BaseSocket::send(buffer);
	return r;
}
