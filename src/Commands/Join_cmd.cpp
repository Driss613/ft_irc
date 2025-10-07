/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:54:26 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 12:28:09 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Join_cmd.hpp"

Join_cmd::Join_cmd() {}

Join_cmd::~Join_cmd() {}

void Join_cmd::parsing(std::string str, Server &serv, Client &main)
{
	if (str == "0")
	{
		// Lancer la commande PART avec en argument tous les channels du client //
		return;
	}

	std::vector<std::string> chans;
	std::vector<std::string> keys;

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

	i++;
	while (i < str.size())
	{
		if (str[i] == ',')
			i++;
		std::string key;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			key += str[i];
			i++;
		}
		keys.push_back(key);
	}

	if (keys.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return;
	}
	(void)main;
	(void)serv;

	// i = 0;
	// std::vector<Channel> channels = serv.getChannels();
	// while (i <= chans.size())
	// {
	// 	bool chan_exist = 0;
	// 	for (size_t n = 0; n < channels.size(); n++)
	// 	{
	// 		if (chans[i] == channels[n].getChanName())
	// 		{
	// 			chan_exist = 1;
	// 			if (keys[i] != channels[n].getChanKey())
	// 			{
	// 				std::cerr << "Error : wrong channel key for channel " << chans[i] << "." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 			if (channels[n].getInvite())
	// 			{
	// 				std::cerr << "Error : you tried to join an invite only channel : " << chans[i] << "." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 			if (channels[n].getMembers().size() == 20)
	// 			{
	// 				std::cerr << "Error : channel " << chans[i] << " is full." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 		}
	// 	}
	// 	if (!chan_exist)
	// 	{
	// 		std::cerr << "Error : no such channel as " << chans[i] << "." << std::endl;
	// 		chans[i] = "";
	// 	}
	// 	i++;
	// }

	// ERR_BADCHANMASK //

	// ERR_BANNEDFROMCHAN //

	// ERR_TOOMANYTARGETS //

	// ERR_UNAVAILRESOURCE //

	// ERR_TOOMANYCHANNELS //
}