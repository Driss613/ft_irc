/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:25 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 11:52:29 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Part_cmd.hpp"
#include "../../includes/Server.hpp"

Part_cmd::Part_cmd() {}
		
Part_cmd::~Part_cmd() {}

void Part_cmd::parsing(std::string str, Server &serv, Client &main)
{
	
	if (str.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
	}
	
	std::istringstream iss(str);
	std::string chanList;
	std::string message;

	iss >> chanList;
	std::getline(iss, message);
	if (!message.empty() && message[0] == ' ')
	 	message.erase(0, 1);

	if (message.empty())
		message = "Default";

	std::vector<std::string> chans = buildVector(chanList);

	for (size_t i = 0; i < chans.size(); i++)
	{
		Channel *channel = serv.getChannel(chans[i]);
		if (!channel)
		{
			std::cerr << "Error : no such channel as " << chans[i] << "." << std::endl;
			chans.erase(chans.begin() + i);
		}
		if (!channel->isMember(main.getFd()))
		{
			std::cerr << "Error : you are not on channel " << chans[i] << "." << std::endl;
			chans.erase(chans.begin() + i);
		}
	}

	// Lancer la commande PART //
}