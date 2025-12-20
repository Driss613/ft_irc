/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/12/20 14:28:17 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Topic_cmd.hpp"
#include "../../includes/Server.hpp"

Topic_cmd::Topic_cmd() {}

Topic_cmd::~Topic_cmd() {}

void Topic_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::istringstream iss(str);
	std::string chan;
	std::string topic;

	iss >> chan;
	std::getline(iss, topic);
	if (!topic.empty() && topic[0] == ' ')
	 	topic.erase(0, 1);

	Channel *channel = serv.getChannel(chan);
	if (!channel)
	{
		serv.sendMessageToClient(main.getFd(), "403 :No such channel as " + chan + ".\r\n");
		return ;
	}
	if (!channel->isMember(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "442 :You are not on channel " + chan + ".");
		return ;
	}
	if (topic.empty())
	{
		if (channel->getTopic().empty())
		{
			serv.sendMessageToClient(main.getFd(), "331 :Channel " + chan + " has no topic.\r\n");
			return ;
		}
		else
		{
			serv.sendMessageToClient(main.getFd(), "332 " + main.getNickname() + " " + chan + " :" + channel->getTopic() + "\r\n");
			return ;
		}
	}	
	if (channel->getTopicOnlyOperator() && !channel->isOperator(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "482 :You don't have operator privileges for this channel.\r\n");
		return ;
	}
	
	channel->setTopic(topic);
	std::string topicMsg = ":" + main.getNickname() + "!" +
							  main.getUsername() + "@" + main.getIp() + " TOPIC " + chan;
			
	if (!topic.empty())
		topicMsg += " :" + topic;
	
	topicMsg += "\r\n";

	const std::vector<int> &members = channel->getMembers();
	for (size_t j = 0; j < members.size(); j++)
	{
		serv.sendMessageToClient(members[j], topicMsg);
	}
}