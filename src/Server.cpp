/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/12 19:08:38 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool Server::_signal = false;

Server::Server(const int port) : _port(port), _serverSocketFd(-1)
{}

Server::Server(const Server& cpy) : _port(cpy._port)
{}

Server::~Server()
{}

/*Server& operator=(const Server& rhs)
{};*/

void Server::setupSocket()
{
	struct sockaddr_in	serverAddress;
	struct pollfd serverPollFd;
	int option;

	_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocketFd == -1)
		throw std::runtime_error("Error : Server cannot create");
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	option = 1;
	if (setsockopt(_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
		throw std::runtime_error("Error : setsockopt");
	if (fcntl(_serverSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error : fcntl");
	if (bind(_serverSocketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		throw std::runtime_error("Error : bind");
	if (listen(_serverSocketFd, SOMAXCONN) == -1)
		throw std::runtime_error("Error : listen");
	serverPollFd.fd = _serverSocketFd;
	serverPollFd.events = POLLIN;
	serverPollFd.revents = 0;
	_fds.push_back(serverPollFd);
}

void Server::signalHandler(int signum)
{
	(void)signum;
	_signal = true;
	std::cout << "Signal" << std::endl;
}

void Server::closeFds()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << "Client" << _clients[i].getFd() << "disconnected." << std::endl;
		close(_clients[i].getFd());
	}
	if (_serverSocketFd != -1)
	{
		std::cout << "Server" << _serverSocketFd << "disconnected." << std::endl;
		close(_serverSocketFd);
	}
}

void Server::serverInit()
{
	setupSocket();
	std::cout << "Server " << _serverSocketFd << " connected" << std::endl;
	std::cout << "Waiting for a new connection !!!" << std::endl;
	while(_signal != true)
	{
		continue;
	}
	closeFds();
}
