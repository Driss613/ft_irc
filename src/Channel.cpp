/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:31:23 by lisambet          #+#    #+#             */
/*   Updated: 2025/10/14 15:51:54 by prosset          ###   ########.fr       */
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
	removeOperator(fd);
	removeInvited(fd);
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

void Channel::addInvited(int fd)
{
	if (!isInvited(fd))
		_invited.push_back(fd);
}

void Channel::removeInvited(int fd)
{
	for (size_t i = 0; i < _invited.size(); i++)
	{
		if (_invited[i] == fd)
		{
			_invited.erase(_invited.begin() + i);
			break;
		}
	}
}

bool Channel::isInvited(int fd) const
{
	for (size_t i = 0; i < _invited.size(); i++)
	{
		if (_invited[i] == fd)
			return true;
	}
	return false;
}

void Channel::setKey(const std::string &key)
{
	_key = key;
}

const std::string &Channel::getKey() const
{
	return _key;
}

bool Channel::hasKey() const
{
	return !_key.empty();
}

void Channel::removeKey()
{
	_key = "";
}

// Limit management
void Channel::setLimit(size_t limit)
{
	_limit = limit;
}

size_t Channel::getLimit() const
{
	return _limit;
}

bool Channel::hasLimit() const
{
	return _limit > 0;
}

void Channel::removeLimit()
{
	_limit = 0;
}

// Invite-only mode
void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}