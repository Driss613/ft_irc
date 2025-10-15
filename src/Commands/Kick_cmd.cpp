/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:23 by prosset           #+#    #+#             */
/*   Updated: 2025/10/15 13:22:19 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Kick_cmd.hpp"
#include "../../includes/Server.hpp"
#include <sstream>

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

	if (chans.size() == 1)
	{
		std::vector<Client> clients = serv.getClients();
		Channel *channel = serv.getChannel(chans[0]);
		if (!channel)
		{
			std::cerr << "Error : no such channel as " << chans[0] << "." << std::endl;
			return ;
		}
		
		for (size_t i = 0; i < users.size(); i++)
		{
			Client *client = NULL;
			
			for (size_t j = 0; j < clients.size(); j++)
			{
				if (users[i] == clients[j].getNickname())
					client = &serv.getFd(clients[j].getFd());
			}
			if (!client)
			{
				std::cerr << "Error : user " << users[i] << " is not on the server." << std::endl;
				users.erase(users.begin() + i);
			}
			if (!channel->isMember(client->getFd()))
			{
				std::cerr << "Error : user " << users[i] << " is not on channel" << chans[0] << "." << std::endl;
				users.erase(users.begin() + i);
			}

			if (!channel->isMember(main.getFd()))
			{
				std::cerr << "Error : you are not on this channel." << std::endl;
				return ;
			}

			if (!channel->isOperator(main.getFd()))
			{
				std::cerr << "Error : you don't have operator privileges for this channel." << std::endl;
				return ;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < chans.size(); i++)
		{
			std::vector<Client> clients = serv.getClients();
			Channel *channel = serv.getChannel(chans[i]);
			if (!channel)
			{
				std::cerr << "Error : no such channel as " << chans[i] << "." << std::endl;
				chans.erase(chans.begin() + i);
			}
			
			Client *client = NULL;
				
			for (size_t j = 0; j < clients.size(); j++)
			{
				if (users[i] == clients[j].getNickname())
					client = &serv.getFd(clients[j].getFd());
			}
			if (!client)
			{
				std::cerr << "Error : user " << users[i] << " is not on the server." << std::endl;
				users.erase(users.begin() + i);
				chans.erase(chans.begin() + i);
			}
			if (!channel->isMember(client->getFd()))
			{
				std::cerr << "Error : user " << users[i] << " is not on channel" << chans[i] << "." << std::endl;
				users.erase(users.begin() + i);
				chans.erase(chans.begin() + i);
			}

			if (!channel->isMember(main.getFd()))
			{
				std::cerr << "Error : you are not on channel " << chans[i] << "." << std::endl;
				users.erase(users.begin() + i);
				chans.erase(chans.begin() + i);
			}

			if (!channel->isOperator(main.getFd()))
			{
				std::cerr << "Error : you don't have operator privileges for channel " << chans[i] << "." << std::endl;
				users.erase(users.begin() + i);
				chans.erase(chans.begin() + i);
			}
		}
	}

	// ERR_BADCHANMASK //


	// std::istringstream iss(str);
	// std::string channelName, targetNick;
	// std::string reason;

	// iss >> channelName >> targetNick;
	// std::getline(iss, reason);
	// if (!reason.empty() && reason[0] == ' ')
	// 	reason.erase(0, 1);
	// if (reason.empty())
	// 	reason = "Kicked";

	// if (channelName.empty() || targetNick.empty())
	// {
	// 	std::cerr << "Error : need more params." << std::endl;
	// 	return;
	// }

	// Client &sender = serv.getFd(main.getFd());
	// Channel *channel = serv.getChannel(channelName);
	// if (!channel)
	// {
	// 	serv.sendMessageToClient(sender, "403 " + channelName + " :No such channel\r\n");
	// 	return;
	// }

	// if (!channel->isOperator(sender.getFd()))
	// {
	// 	serv.sendMessageToClient(sender, "482 " + channelName + " :You're not channel operator\r\n");
	// 	return;
	// }

	// Client *target = NULL;
	// std::vector<Client> &clients = serv.getClients();
	// for (size_t i = 0; i < clients.size(); i++)
	// {
	// 	if (clients[i].getNickname() == targetNick)
	// 	{
	// 		target = &clients[i];
	// 		break;
	// 	}
	// }

	// if (!target)
	// {
	// 	serv.sendMessageToClient(sender, "401 " + targetNick + " :No such nick\r\n");
	// 	return;
	// }

	// if (target->getFd() == sender.getFd())
	// {
	// 	serv.sendMessageToClient(sender, "484 :You cannot kick yourself\r\n");
	// 	return;
	// }

	// if (!channel->isMember(target->getFd()))
	// {
	// 	serv.sendMessageToClient(sender, "441 " + targetNick + " " + channelName + " :They aren't on that channel\r\n");
	// 	return;
	// }

	// std::string kickMsg = ":" + sender.getNickname() + "!" + sender.getUsername() +
	// 					  "@server KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";

	// const std::vector<int> &members = channel->getMembers();
	// for (size_t i = 0; i < members.size(); i++)
	// {
	// 	Client &member = serv.getFd(members[i]);
	// 	serv.sendMessageToClient(member, kickMsg);
	// }

	// channel->removeMember(target->getFd());
}