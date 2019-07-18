#include <iostream>
#include "SFML/Network.hpp"
#include <Windows.h>
#include <conio.h>

char message[1024];
char name[1024];
unsigned int port;
std::string namea;
sf::TcpSocket client;
sf::TcpListener server;
sf::Packet messageData;
sf::Packet messageDataa;
std::size_t otherSize;
sf::IpAddress ip;
void getm() {
	while (true) {
		if (client.receive(messageData) == sf::Socket::Done) {
			messageData >> name >> message;
			std::cout << "[" << name << "]: " << message << std::endl << std::endl;
		}
	}
}

void getInput() {
	while (true) {
		std::string c;
		std::getline(std::cin, c);
		messageData << namea.c_str() << c.c_str();
		client.send(messageData);
		std::cout << std::endl << ">> ";
		messageData.clear();
	}
}

void initServer(unsigned short port) {
	server.listen(port);
	if (server.accept(client) == sf::Socket::Done) {
		std::cout << "Client connected" << std::endl;
		sf::Thread t(&getInput);
		t.launch();
		sf::Thread d(&getm);
		d.launch();
	}

}

void initClient() {
	if (client.connect(ip, port) == sf::Socket::Done) {
		std::cout << "--CONNECTION REACHED--" << '\r' << std::endl;
	}
	sf::Thread t(&getInput);
	t.launch();
	sf::Thread d(&getm);
	d.launch();
}

int main() {

	
	server.setBlocking(true);
	client.setBlocking(true);
	
	char c;
	std::cout << ">>> What i am? -Client (C)? -Server (S)?: ";
	std::cin >> c;
	if (c == 'C') {
		std::cout << "What ip?: ";
		std::cin >> ip;
		std::cout << "What port?: ";
		std::cin >> port;
		std::cout << "What is my name?: ";
		std::cin >> namea;
		initClient();

	}else if ('S') {
		std::cout << '\r\r' << "What port should I use?: ";
		std::cin >> port;
		std::cout << "What is my name?: ";
		std::cin >> namea;
		initServer(port);
	}
	server.close();
	return 0;
}
