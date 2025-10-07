/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:31:23 by lisambet          #+#    #+#             */
/*   Updated: 2025/10/06 13:46:40 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(const std::string &name) : _name(name), _topic("") {}

Channel::~Channel() {}

void Channel::addMember(int fd)
{
	if (!isMember(fd))
		_members.push_back(fd);
}

void Channel::removeMember(int fd)
{
	for (size_t i = 0; i < _members.size(); i++)
	{
		if (_members[i] == fd)
		{
			_members.erase(_members.begin() + i);
			break;
		}
	}
}

bool Channel::isMember(int fd) const
{
	for (size_t i = 0; i < _members.size(); i++)
	{
		if (_members[i] == fd)
			return true;
	}
	return false;
}

const std::vector<int> &Channel::getMembers() const
{
	return _members;
}

const std::string &Channel::getName() const
{
	return _name;
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

const std::string &Channel::getTopic() const
{
	return _topic;
}

void Channel::addOperator(int fd)
{
	if (!isOperator(fd))
		_operators.push_back(fd);
}
void Channel::removeOperator(int fd)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == fd)
		{
			_operators.erase(_operators.begin() + i);
			break;
		}
	}
}
bool Channel::isOperator(int fd) const
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == fd)
			return true;
	}
	return false;
}

Client &Channel::findMember(const std::string &nickname, const std::vector<Client> &clients)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].getNickname() == nickname && isMember(clients[i].getFd()))
			return const_cast<Client &>(clients[i]);
	}
	static Client emptyClient;
	return emptyClient;
}