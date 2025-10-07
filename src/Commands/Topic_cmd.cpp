/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:55 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 12:32:44 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Topic_cmd.hpp"

Topic_cmd::Topic_cmd() {}

Topic_cmd::~Topic_cmd() {}

void Topic_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string chan;
	std::string topic;

	if (str.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return;
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
	(void)main;
	(void)serv;
	// if (topic.empty())
	// {
	// 	std::vector<Channel> channels = serv.getChannels();
	// 	for (size_t i = 0; i < channels.size(); i++)
	// 	{
	// 		if (channels[i].getChanName() == chan && channels[i].getChanTopic.empty())
	// 		{
	// 			std::cerr << "Error : channel " << chan << " has no topic." << std::endl;
	// 			return ;
	// 		}
	// 	}
	// }

	// std::vector<Channel> main_chans = main.getChannels();
	// bool isonchan = 0;
	// for (size_t i = 0; i < main_chans.size(); i++)
	// {
	// 	if (main_chans[i].getChanName() == chan)
	// 		isonchan = 1;
	// }
	// if (!isonchan)
	// {
	// 	std::cerr << "Error : you are not on channel " << chan << "." << std::endl;
	// 	return ;
	// }

	// ERR_CHANOPRIVSNEEDED //

	// ERR_NOCHANMODES //

	// Lancer la commande TOPIC //
}