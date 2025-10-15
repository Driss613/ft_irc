/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:25 by prosset           #+#    #+#             */
/*   Updated: 2025/10/15 13:22:56 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Part_cmd.hpp"
#include "../../includes/Server.hpp"

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

	for (size_t j = 0; j < chans.size(); j++)
	{
		Channel *channel = serv.getChannel(chans[j]);
		if (!channel)
		{
			std::cerr << "Error : no such channel as " << chans[j] << "." << std::endl;
			chans.erase(chans.begin() + j);
		}
		if (!channel->isMember(main.getFd()))
		{
			std::cerr << "Error : you are not on channel " << chans[j] << "." << std::endl;
			chans.erase(chans.begin() + j);
		}
	}

	// Lancer la commande PART //
}