/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/12/06 20:09:41 by lisambet         ###   ########.fr       */
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
		std::cerr << "403 : no such channel as " << channel << "." << std::endl;
		return ;
	}
	
	if (topic.empty())
	{
		if (channel->getTopic().empty())
			{
				std::cerr << "Channel " << chan << " has no topic." << std::endl;
				return ;
			}
	}

	if (!channel->isMember(main.getFd()))
	{
		std::cerr << "442 : you are not on channel " << chan << "." << std::endl;
		return ;
	}
	
	if (!channel->isOperator(main.getFd()))
	{
		std::cerr << "482 : you don't have operator privileges for this channel." << std::endl;
		return ;
	}

	//added error codes

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