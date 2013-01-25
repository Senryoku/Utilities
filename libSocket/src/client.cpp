#include "Socket.hpp"

#include <iostream>

/* Exemple d'utilisation de TCPSocket */

int main(int argc, char* argv[])
{
	BaseSocket::init();
	
	TCPSocket Client("127.0.0.1", 2365);
	
	std::cout << "Tentative de connexion de " << Client.getSocket() << " a " <<  Client.getAddr() << ":" << Client.getPort() << std::endl;
	
	if(Client.connect() != 0) std::cout << "Echec de la connexion" << std::endl;
	else {
		std::cout << "Connexion reussie ! Tapez /quit pour quitter." << std::endl;
		char buffer[256];
		Client.recv(buffer, 256);
		std::cout << "[Server] " << buffer << std::endl;
		do
		{
			//std::cin >> buffer;
			std::cin.getline(buffer, 256);
			//Client.send(buffer, 256);
			Client.sendStr(buffer);
			//std::cout << "Sent : " << buffer << std::endl;
		} while(strcmp(buffer, "/quit") != 0);
	}
	
	BaseSocket::cleanup();

	return 0;
}
