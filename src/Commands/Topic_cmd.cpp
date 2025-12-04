/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 13:59:25 by prosset          ###   ########.fr       */
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
		std::cerr << "Error : no such channel as " << channel << "." << std::endl;
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
		std::cerr << "Error : you are not on channel " << chan << "." << std::endl;
		return ;
	}
	
	if (!channel->isOperator(main.getFd()))
	{
		std::cerr << "Error : you don't have operator privileges for this channel." << std::endl;
		return ;
	}

	// Lancer la commande TOPIC //
}