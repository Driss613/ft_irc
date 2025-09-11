/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/11 19:16:26 by drabarza         ###   ########.fr       */
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
{}

void Server::serverInit()
{
	setupSocket();
}
