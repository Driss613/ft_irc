/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/12/04 20:13:41 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() : _ip(""), _fd(-1)
{
}

Client::Client(const Client &cpy) : _ip(cpy._ip), _fd(cpy._fd), username(cpy.username), nickname(cpy.nickname)
{
}

Client::~Client()
{
}

Client &Client::operator=(const Client &rhs)
{
	if (this != &rhs)
	{
		_ip = rhs._ip;
		_fd = rhs._fd;
		nickname = rhs.nickname;
		username = rhs.username;
	}
	return *this;
}

const std::string &Client::getIp(void) const
{
	return _ip;
}

int Client::getFd(void) const
{
	return _fd;
}

std::string Client::getNickname() const
{
	return nickname;
}

std::string Client::getUsername() const
{
	return username;
}

int Client::getRank() const
{
	return _rank;
}

// std::vector<Channel> Client::getChannels() const {
// 	return _channels;
// }

void Client::setIp(const std::string &ip)
{
	_ip = ip;
}

void Client::setFd(int fd)
{
	_fd = fd;
}

void Client::setNickname(std::string str)
{
	nickname = str;
}

void Client::setUsername(std::string str)
{
	username = str;
}

void Client::setRank(int rank)
{
	_rank = rank;
}