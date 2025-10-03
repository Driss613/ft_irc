/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:23 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:19:16 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick_cmd.hpp"

Kick_cmd::Kick_cmd() {}
		
Kick_cmd::~Kick_cmd() {}

void Kick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<std::string> chans;

	size_t i = 0;
	while (i < str.size() && i < str.find(' '))
	{
		if (str[i] == ',')
			i++;
		std::string chan;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			chan += str[i];
			i++;
		}
		chans.push_back(chan);
	}

	std::vector<std::string> users;

	i++;
	while (i < str.size() && i < str.find(' '))
	{
		if (str[i] == ',')
			i++;
		std::string user;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			user += str[i];
			i++;
		}
		users.push_back(user);
	}

	std::string comment;
	i++;
	while (i < str.size())
	{
		comment += str[i];
		i++;
	}

	if (users.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
	}
	
	if (chans.size() != 1 && chans.size() != users.size())
	{
		std::cerr << "Error : there must be either one channel or as many channels as users." << std::endl;
		return ;
	}

	// if (chans.size() == 1)
	// {
	// 	std::vector<Channel> channels = serv.getChannels();
	// 	bool chan_exist = 0;
	// 	for (size_t i = 0; i < channels.size(); i++)
	// 	{
	// 		if (chans[0] == channels[i].getChanName())
	// 		{
	// 			chan_exist = 1;
	// 			std::vector<Client> chan_members = channels[i].getMembers();
	// 			for (size_t n = 0; n < users.size(); n++)
	// 			{
	// 				bool user_exist = 0;
	// 				for (size_t j = 0; j < chan_members.size(); j++)
	// 				{
	// 					if (users[n] == chan_members[j].getNickname())
	// 						user_exist = 1;
	// 				}
	// 				if (!user_exist)
	// 				{
	// 					std::cerr << "Error : user " << users[n] << " is not on channel" << chans[0] << "." << std::endl;
	// 					users[n] = "";
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// else
	// {
	// 	for (size_t j = 0; j < chans.size(); j++)
	// 	{
	// 		std::vector<Channel> channels = serv.getChannels();
	// 		bool chan_exist = 0;
	// 		for (size_t i = 0; i < channels.size(); i++)
	// 		{
	// 			if (chans[j] == channels[i].getChanName())
	// 			{
	// 				chan_exist = 1;
	// 				std::vector<Client> chan_members = channels[i].getMembers();
	// 				bool user_exist = 0;
	// 				for (size_t n = 0; n < chan_members.size(); n++)
	// 				{
	// 					if (users[j] == chan_members[n].getNickname())
	// 						user_exist = 1;
	// 				}
	// 				if (!user_exist)
	// 				{
	// 					std::cerr << "Error : user " << users[j] << " is not on channel" << chans[j] << "." << std::endl;
	// 					users[j] = "";
	// 					chans[j] = "";
	// 				}
	// 			}
	// 		}
	// 		if (!chan_exist)
	// 		{
	// 			std::cerr << "Error : no such channel as " << chans[j] << "." << std::endl;
	// 			users[j] = "";
	// 			chans[j] = "";
	// 		}
	// 	}
	// }

	// ERR_BADCHANMASK //

	// ERR_CHANOPRIVSNEEDED //
	
	// ERR_NOTONCHANNEL //

	// Lancer la commande KICK //
}