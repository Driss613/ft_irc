/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:31:13 by lisambet          #+#    #+#             */
/*   Updated: 2025/12/06 14:16:29 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Channel.hpp"
class Client;    
class Channel
{
private:
	std::string _name;
	std::vector<int> _members;
	std::vector<int> _operators;
	std::string _topic;
	std::string _key;
	size_t _limit;
	bool _inviteOnly;
	std::vector<int> _invited;

public:
	Channel(const std::string &name);
	~Channel();

	void addMember(int fd);
	void removeMember(int fd);
	bool isMember(int fd) const;
	Client *findMember(const std::string &nickname,
                   const std::vector<Client*> &clients);
	void addOperator(int fd);
	void removeOperator(int fd);
	bool isOperator(int fd) const;
	const std::vector<int> &getMembers() const;
	const std::string &getName() const;
	void setTopic(const std::string &topic);
	const std::string &getTopic() const;

	void setLimit(size_t limit);
	size_t getLimit() const;
	bool hasLimit() const;
	void removeLimit();

	void addInvited(int fd);
	void removeInvited(int fd);
	bool isInvited(int fd) const;
	void setInviteOnly(bool inviteOnly);
	bool isInviteOnly() const;

	void setKey(const std::string &key);
	const std::string &getKey() const;
	bool hasKey() const;
	void removeKey();
};

#endif