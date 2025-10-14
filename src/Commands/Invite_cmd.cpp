/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:00:34 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:20:29 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Invite_cmd.hpp"
#include "../../includes/Server.hpp"

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
		return ;
	}

	std::vector<Client> clients = serv.getClients();
	Client *client = NULL;
	
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (nick == clients[i].getNickname())
			client = &serv.getFd(clients[i].getFd());
	}
	if (!client)
	{
		std::cerr << "Error : no such client on the server." << std::endl;
		return ;
	}

	int fd = client->getFd();
	Channel *channel = serv.getChannel(chan);
	if (!channel)
		return ;
		
	if (!channel->isMember(main.getFd()))
	{
		std::cerr << "Error : you are not on channel " << chan << "." << std::endl;
		return ;
	}
	
	if (channel->isMember(fd))
	{
		std::cerr << "Error : user is already on the channel." << std::endl;
		return ;
	}
	
    if (channel->isInviteOnly() && !channel->isOperator(main.getFd()))
	{
		std::cerr << "Error : invite-only channels require operator privileges to invite a new member." << std::endl;
		return ;
	}

	// Lancer la commande INVITE //
}