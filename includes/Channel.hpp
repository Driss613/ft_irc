/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:31:13 by lisambet          #+#    #+#             */
/*   Updated: 2025/10/07 12:27:20 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"
#include "Channel.hpp"

class Channel
{
private:
	std::string _name;
	std::vector<int> _members;
	std::vector<int> _operators;
	std::string _topic;

public:
	Channel(const std::string &name);
	~Channel();

	void addMember(int fd);
	void removeMember(int fd);
	bool isMember(int fd) const;
	Client &findMember(const std::string &nickname, const std::vector<Client> &clients);

	void addOperator(int fd);
	void removeOperator(int fd);
	bool isOperator(int fd) const;
	const std::vector<int> &getMembers() const;
	const std::string &getName() const;
	void setTopic(const std::string &topic);
	const std::string &getTopic() const;
};

#endif