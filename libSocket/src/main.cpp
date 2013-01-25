#include "Socket.hpp"

#include <iostream>

/* Exemple d'utilisation de TCPServerSocket */

int main(int argc, char* argv[])
{
	BaseSocket::init();

	TCPServerSocket Server(2365);
	
	std::cout << "Ouverture serveur : " << inet_ntoa(Server.getContext().sin_addr) << ":" << htons(Server.getContext().sin_port) << std::endl;
	
	TCPSocket& Client = Server.accept();

	std::cout << "[Server] Connexion de " <<  inet_ntoa(Client.getContext().sin_addr) << ":" << htons(Client.getContext().sin_port) << std::endl;
	
	char buffer[256] = "Bienvenue !";
	//Client.send(buffer, 256);
	Client.sendStr("Bienvenue !");
	
	do
	{
		Client.recv(buffer, 256);
		std::cout << "[" << Client.getAddr() << "] " << buffer << std::endl;
	} while(strcmp(buffer, "/quit") != 0);
	
	std::cout << "Deconnexion de " << Client.getAddr() << std::endl;
	
	Client.close();
	
	BaseSocket::cleanup();

	return 0;
}