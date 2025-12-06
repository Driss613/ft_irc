/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite_cmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:00:34 by prosset           #+#    #+#             */
/*   Updated: 2025/12/06 20:26:40 by lisambet         ###   ########.fr       */
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
	
    if (!channel->isOperator(main.getFd()))
	{
		std::cerr << "Error : invite-only channels require operator privileges to invite a new member." << std::endl;
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