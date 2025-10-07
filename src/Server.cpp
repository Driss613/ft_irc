/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/10/07 13:19:10 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Commands/Manager.hpp"

bool Server::_signal = false;

Server::Server(const int port) : _port(port), _serverSocketFd(-1)
{
}

Server::Server(const Server &cpy) : _port(cpy._port)
{
}

Server::~Server()
{
}

/*Server& operator=(const Server& rhs)
{};*/

void Server::setpasswd(std::string passwd)
{
	password = passwd;
}

std::string Server::getpasswd(void) const
{
	return password;
}

std::vector<Client> Server::getClients(void) const
{
	return _clients;
}

void Server::setupSocket()
{
	struct sockaddr_in serverAddress;
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
	if (bind(_serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
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
		std::cout << "Client " << _clients[i].getFd() << " disconnected." << std::endl;
		close(_clients[i].getFd());
	}
	if (_serverSocketFd != -1)
	{
		std::cout << "Server " << _serverSocketFd << " disconnected." << std::endl;
		close(_serverSocketFd);
	}
}

void Server::newClient()
{
	Client newClient;
	struct sockaddr_in clientAdd;
	struct pollfd newPollFd;
	int clientSocket;
	socklen_t len;

	len = sizeof(clientAdd);
	clientSocket = accept(_serverSocketFd, (struct sockaddr *)&clientAdd, &len);
	if (clientSocket == -1)
	{
		throw std::runtime_error("Error : Accept");
		return;
	}
	if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Error : fcntl");
		return;
	}
	newPollFd.fd = clientSocket;
	newPollFd.events = POLLIN;
	newPollFd.revents = 0;
	newClient.setFd(clientSocket);
	newClient.setIp(inet_ntoa((clientAdd.sin_addr)));
	_clients.push_back(newClient);
	_fds.push_back(newPollFd);
	std::cout << "Client " << clientSocket << " connected." << std::endl;
}

void Server::removeClient(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

void Server::newData(int fd)
{
	char buffer[1024]; //
	int bytes;

	std::memset(buffer, '\0', sizeof(buffer));
	bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client " << fd << " disconnected" << std::endl;
		removeClient(fd);
		close(fd);
	}
	else
	{
		buffer[bytes] = '\0';
		std::cout << "Client " << fd << " Data : " << buffer;
	}
	(void)fd;
}

void Server::serverInit()
{
	setupSocket();
	std::cout << "Server " << _serverSocketFd << " connected" << std::endl;
	std::cout << "Waiting for a new connection !!!" << std::endl;
	while (_signal != true)
	{
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && (_signal != true))
			throw std::runtime_error("Error  poll");
		for (size_t i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == _serverSocketFd)
					newClient();
				else
					newData(_fds[i].fd);
			}
		}
	}
	closeFds();
}

void Server::parsing(std::string str, int fd)
{
	std::string prefix;
	size_t i = 0;

	if (str[0] == ':')
	{
		i++;
		while (str[i] && i < str.find(' '))
		{
			prefix += str[i];
			i++;
		}
		if (i == str.find(' '))
			i++;
	}

	std::string cmd;

	while (str[i] && str[i] != ' ')
	{
		cmd += str[i];
		i++;
	}

	if (!cmd[0])
	{
		std::cerr << "Please provide a command and arguments for your message." << std::endl;
		return;
	}

	std::string args;

	if (str[i] == ' ')
		i++;

	while (str[i])
	{
		args += str[i];
		i++;
	}

	if (!args[0])
	{
		std::cerr << "Please provide arguments for your command." << std::endl;
		return;
	}

	Server serv = *this;
	std::vector<Client> clients = serv.getClients();
	Client main;
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].getFd() == fd)
			main = clients[i];
	}

	Manager manager;
	ACmd *com;

	com = manager.makeCmd(cmd);
	com->parsing(args, serv, main);
}

void Server::sendMessageToClient(int fd, const std::string &message)
{
	if (send(fd, message.c_str(), message.length(), 0) == -1)
		std::cerr << "Error sending message to client " << fd << std::endl;
}