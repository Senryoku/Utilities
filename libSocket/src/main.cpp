#include "Socket.hpp"
#include <SFML/System/Thread.hpp>
#include <iostream>

/* Exemple d'utilisation de TCPServerSocket */

void awaitsMessages(TCPSocket &Client)
{
	std::string buffer;
	
	do
	{
		buffer = Client.recvStr();
		std::cout << "[" << Client.getAddr() << "] " << buffer << std::endl;
	} while(buffer != "/quit");
	
	std::cout << "Deconnexion de " << Client.getAddr() << std::endl;
	
	Client.close();
}

void handleConnections(TCPServerSocket &Server)
{
	while(1)
	{
		TCPSocket& Client = Server.accept();
		if(Client.isValid())
		{
			std::cout << "[Server] Connexion de " <<  inet_ntoa(Client.getContext().sin_addr) << ":" << htons(Client.getContext().sin_port) << std::endl;
			Client.sendStr("Bienvenue !");
			sf::Thread ST(awaitsMessages, Client);
			ST.launch();
		} else break;
	}
}

int main(int argc, char* argv[])
{
	BaseSocket::init();

	TCPServerSocket Server(2365);
	Server.setBlocking();
	
	std::cout << "Ouverture serveur : " << inet_ntoa(Server.getContext().sin_addr) << ":" << htons(Server.getContext().sin_port) << std::endl;
	
	sf::Thread Connections(handleConnections, Server);
	Connections.launch(); // Problème avec le mode bloquant de windows et les threads ?...

	std::string Str;
	do {
		std::cin >> Str;
		Server.sendStr(Str);
	} while(Str != "/quit");
	
	BaseSocket::cleanup();

	return 0;
}