/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/12/08 14:21:49 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Topic_cmd.hpp"

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
		serv.sendMessageToClient(main.getFd(), "Error : no such channel as " + chan + ".");
		return ;
	}
	
	if (topic.empty())
	{
		if (channel->getTopic().empty())
			{
				serv.sendMessageToClient(main.getFd(), "Error : channel " + chan + " has no topic.");
				return ;
			}
	}

	if (!channel->isMember(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "Error : you are not on channel " + chan + ".");
		return ;
	}
	
	if (!channel->isOperator(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "Error : you don't have operator privileges for this channel.");
		return ;
	}
	
	if (!channel->getTopicOnlyOperator())
	{
		serv.sendMessageToClient(main.getFd(), "Error : you don't have operator privileges for this channel.");
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