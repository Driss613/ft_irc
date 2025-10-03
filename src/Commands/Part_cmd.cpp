/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:25 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:20:24 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part_cmd.hpp"

Part_cmd::Part_cmd() {}
		
Part_cmd::~Part_cmd() {}

void Part_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<std::string> chans;
	
	if (str.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
	}

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

	std::string message;
	if (i < str.size())
	{
		i++;
		while (i < str.size())
		{
			message += str[i];
			i++;
		}
	}

	// std::vector<Channel> main_chans = main.getChannels();
	// std::vector<Channel> channels = serv.getChannels();
	// for (size_t j = 0; j < chans.size(); j++)
	// {
	// 	bool chan_exist = 0;
	// 	for (size_t i = 0; i < channels.size(); i++)
	// 	{
	// 		if (chans[j] == channels[i].getChanName())
	// 			chan_exist = 1;
	// 	}
	// 	if (!chan_exist)
	// 	{
	// 		std::cerr << "Error : no such channel as " << chans[j] << "." << std::endl;
	// 		chans[j] = "";
	// 	}
	// 	else
	// 	{
	// 		bool isonchan = 0;
	// 		for (size_t i = 0; i < main_chans.size(); i++)
	// 		{
	// 			if (main_chans[i].getChanName() == chans[j])
	// 				isonchan = 1;
	// 		}
	// 		if (!isonchan)
	// 		{
	// 			std::cerr << "Error : you are not on channel " << chans[j] << "." << std::endl;
	// 			chans[j] = "";
	// 		}
	// 	}
	// }

	// Lancer la commande PART //
}