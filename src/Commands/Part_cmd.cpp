/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:59:25 by prosset           #+#    #+#             */
/*   Updated: 2026/01/17 13:35:51 by prosset          ###   ########.fr       */
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
		serv.sendMessageToClient(main.getFd(), "461 PART :Need more params.\r\n");
		return ;
	}
	
	std::istringstream iss(str);
	std::string chanList;
	std::string message;

	iss >> chanList;
	std::getline(iss, message);
	if (!message.empty() && message[0] == ' ')
	 	message.erase(0, 1);

	if (message[0] != ':')
	{
		std::istringstream iss(message);
		iss >> message;
	}
	else
		message.erase(0, 1);

	std::vector<std::string> chans = buildVector(chanList);

	for (size_t i = 0; i < chans.size(); i++)
	{
		Channel *channel = serv.getChannel(chans[i]);
		if (!channel)
		{
			serv.sendMessageToClient(main.getFd(), "403 :No such channel as " + chans[i] + ".\r\n");
			continue;
		}
			
		if (!channel->isMember(main.getFd()))
		{
			serv.sendMessageToClient(main.getFd(), "442 :You are not on channel " + chans[i] + ".\r\n");
			continue;
		}
			
		std::string partMsg = ":" + main.getNickname() + "!" +
							  main.getUsername() + "@" + main.getIp() + " PART " + chans[i];
			
		if (!message.empty())
			partMsg += " :" + message;
		
		partMsg += "\r\n";

		const std::vector<int> &members = channel->getMembers();
		for (size_t j = 0; j < members.size(); j++)
		{
			serv.sendMessageToClient(members[j], partMsg);
		}

		channel->removeMember(main.getFd());
		main.removeChannel(*channel);
	}
}