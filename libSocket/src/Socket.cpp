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
	if(_socket != INVALID_SOCKET) close();
}

void BaseSocket::setBlocking(bool b)
{
#if defined (WIN32)
	unsigned long int arg = (b) ? 0 : 1;
	ioctlsocket(_socket, FIONBIO, &arg);
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
	return ::send(_socket, Str.c_str(), Str.length() + 1, 0);
}

int BaseSocket::send(const char* buffer, size_t len)
{
	return ::send(_socket, buffer, (len > 0) ? len : sizeof(buffer), 0);
}

int BaseSocket::recv(char* buffer, size_t len)
{
	return ::recv(_socket, buffer, (len > 0) ? len : sizeof(buffer), 0);
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
	
	return _connections[NewSocket];
}


int TCPServerSocket::send(std::string Str)
{
	int r = 0;
	for(size_t i = 0; i < _connections.size(); ++i)
		r = r | ::send(_socket, Str.c_str(), Str.length(), 0);
	return r;
}

int TCPServerSocket::send(const char* buffer, size_t len)
{
	int r = 0;
	for(size_t i = 0; i < _connections.size(); ++i)
		r = r | ::send(_socket, buffer, (len > 0) ? len : sizeof(buffer), 0);
	return r;
}
