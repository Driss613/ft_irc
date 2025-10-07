/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/10/07 13:19:17 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <iostream>
#include <vector>
#include <csignal>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr_in
#include <fcntl.h>
#include <arpa/inet.h> //inet_ntoa

#include "Client.hpp"
#include "./Commands/ACmd.hpp"

class Server
{
private:
	const int _port;
	int _serverSocketFd;
	static bool _signal;
	std::vector<Client> _clients;
	std::vector<struct pollfd> _fds;
	std::string password;

public:
	Server(const int port = 4444);
	Server(const Server &cpy);
	~Server();
	// Server& operator=(const Server& rhs);
	void serverInit(void);
	void setupSocket(void);

	static void signalHandler(int signum);
	void closeFds(void);
	void removeClient(int fd);

	void newClient(void);
	void newData(int fd);

	void setpasswd(std::string passwd);
	std::string getpasswd(void) const;

	std::vector<Client> getClients(void) const;

	void parsing(std::string str, int fd);

	void sendMessageToClient(int fd, const std::string &message);
};
