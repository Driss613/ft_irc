/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:00:34 by prosset           #+#    #+#             */
/*   Updated: 2025/12/10 13:36:44 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Invite_cmd.hpp"

Invite_cmd::Invite_cmd() {}
		
Invite_cmd::~Invite_cmd() {}

void Invite_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::istringstream iss(str);
	std::string nick;
	std::string chan;
	
	iss >> nick;
	std::getline(iss, chan);
	if (!chan.empty() && chan[0] == ' ')
	 	chan.erase(0, 1);

	if (chan.empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 INVITE :Need more params.\r\n");
		return;
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
		serv.sendMessageToClient(main.getFd(), "401 :No such client on the server.\r\n");
		return ;
	}

	int fd = client->getFd();
	Channel *channel = serv.getChannel(chan);
	if (!channel)
		return ;
		
	if (!channel->isMember(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "442 :You are not on channel " + chan + ".\r\n");
		return ;
	}
	
	if (channel->isMember(fd))
	{
		serv.sendMessageToClient(main.getFd(), "443 :is already on the channel.\r\n");
		return ;
	}
	
    if (!channel->isOperator(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "482 : invite-only channels require operator privileges to invite a new member.\r\n");
		return ;
	}
	
	channel->addInvited(fd);
	std::string inviteMsg = ":" + main.getNickname() + "!" +
							  main.getUsername() + "@" + main.getIp() + " INVITE " + nick + " " + chan + "\r\n";
	serv.sendMessageToClient(fd, inviteMsg);
	serv.sendMessageToClient(main.getFd(),
							 ":" + main.getNickname() + "!" + main.getUsername() + "@server NOTICE " + main.getNickname() +
								 " :You have invited " + nick + " to join " + chan + "\r\n");
}