/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:00:34 by prosset           #+#    #+#             */
/*   Updated: 2025/10/11 20:16:39 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Invite_cmd.hpp"

Invite_cmd::Invite_cmd() {}

Invite_cmd::~Invite_cmd() {}

void Invite_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string nick;
	std::string chan;

	size_t i = 0;
	while (i < str.size() && i < str.find(' '))
	{
		nick += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		chan += str[i];
		i++;
	}

	if (chan.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return;
	}

	std::vector<Client> &clients = serv.getClients();
	bool nick_exist = 0;

	for (size_t i = 0; i < clients.size(); i++)
	{
		if (nick == clients[i].getNickname())
			nick_exist = 1;
	}
	if (!nick_exist)
	{
		std::cerr << "Error : no such nickname on the server." << std::endl;
		return;
	}

	(void)main;
	(void)serv;

	// std::vector<Channel> channels = serv.getChannels();
	// for (size_t i = 0; i < channels.size(); i++)
	// {
	// 	if (chan == channels[i].getChanName())
	// 	{
	// 		std::vector<Client> chan_members = channels[i].getMembers();
	// 		for (size_t j = 0; j < chan_members.size(); j++)
	// 		{
	// 			if (nick == chan_members[j].getNickname())
	// 			{
	// 				std::cerr << "Error : user is already on the channel." << std::endl;
	// 				return ;
	// 			}
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

	// Lancer la commande INVITE //
}