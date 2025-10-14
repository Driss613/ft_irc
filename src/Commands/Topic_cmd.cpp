/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:39:50 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Topic_cmd.hpp"
#include "../../includes/Server.hpp"

Topic_cmd::Topic_cmd() {}
		
Topic_cmd::~Topic_cmd() {}

void Topic_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string chan;
	std::string topic;

	if (str.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
	}
	
	size_t i = 0;
	while (i < str.size() && i < str.find(' '))
	{
		chan += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		topic += str[i];
		i++;
	}

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
	
	// ERR_CHANOPRIVSNEEDED //           
	
	// ERR_NOCHANMODES //

	// Lancer la commande TOPIC //
}