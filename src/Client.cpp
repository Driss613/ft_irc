/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:53 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/11 16:18:03 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(const std::string& ip, const int fd) : _ip(ip), _fd(fd)
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
