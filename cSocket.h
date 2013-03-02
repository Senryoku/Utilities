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

size_t sendData(int socket, const char* buffer, size_t len)
{
	size_t sent = 0, res;
	while(sent < len)
	{
		res = ::send(socket, buffer + sent, len - sent, 0);
		if(res > 0) sent += res;
		else {
			perror("Error sending data through socket : ");
			return sent;
		}
	}
	return sent;
}

size_t recvData(int socket, char* buffer, size_t len)
{
	size_t received = 0, res;
	while(received < len)
	{
		res = ::recv(socket, buffer + received, len - received, 0);
		if(res > 0) received += res;
		else if(res == 0) { // Connection closed on the other side.
			fprintf(stderr, "Error receiving data through socket : Connection closed by peer. Closing local socket...\n");
			closesocket(socket);
			return received;
		} else {
			perror("Error receiving data through socket : ");
			return received;
		}
	}
	return received;
}

bool sendSize(size_t size)
{
	char buff[64];
	itoa(size, buff, 10);
	return sendData(buff, 64) == 64;
}
	
size_t recvSize()
{
	char buff[64];
	if(recvData(buff, 64) != 64) fprintf("Error receiving packet size.\n");
	return atoi(buff);
}