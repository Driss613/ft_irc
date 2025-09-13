/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/13 14:16:08 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() : _ip(""), _fd(-1)
{}

Client::Client(const Client& cpy) : _ip(cpy._ip), _fd(cpy._fd)
{}

Client::~Client()
{}

/*Client& operator=(const Client& rhs)
{};*/

const std::string&	Client::getIp(void) const
{
	return _ip;
}

int	Client::getFd(void) const
{
	return _fd;
}

void	Client::setIp(const std::string& ip)
{
	_ip = ip;
}

void	Client::setFd(int fd)
{
	_fd = fd;
}