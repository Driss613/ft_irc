/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:23 by prosset           #+#    #+#             */
/*   Updated: 2025/12/12 11:21:32 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Kick_cmd.hpp"
#include "../../includes/Server.hpp"

Kick_cmd::Kick_cmd() {}

Kick_cmd::~Kick_cmd() {}
void Kick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::istringstream iss(str);
	std::string channels;
	std::string members;
	std::string comment;
	
	iss >> channels >> members;
	std::getline(iss, comment);
	if (!comment.empty() && comment[0] == ' ')
	 	comment.erase(0, 1);
	if (comment.empty())
		comment = "Kicked";

		
	if (members.empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 KICK :Need more params.\r\n");
		return ;
	}
	
	std::vector<std::string> chans = buildVector(channels);
	std::vector<std::string> users = buildVector(members);

	size_t chanSize = chans.size();

	if (chanSize != 1 && chanSize != users.size())
	{
		serv.sendMessageToClient(main.getFd(), "461 KICK :There must be either one channel or as many channels as users.\r\n");
		return ;
	}
	
	std::vector<Client> clients = serv.getClients();
	
	if (chanSize == 1)
	{
		Channel *channel = serv.getChannel(chans[0]);
		
		if (!channel)
		{
			serv.sendMessageToClient(main, "403 " + chans[0] + " :No such channel\r\n");
			return ;
		}
		if (!channel->isMember(main.getFd()))
		{
			serv.sendMessageToClient(main.getFd(), "442 :You are not on this channel.\r\n");
			return ;
		}
		if (!channel->isOperator(main.getFd()))
		{
			serv.sendMessageToClient(main, "482 " + chans[0] + " :You're not channel operator\r\n");
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
				serv.sendMessageToClient(main.getFd(), "401 :User " + users[i] + " is not on the server.\r\n");
				continue;
			}
			if (!channel->isMember(client->getFd()))
			{
				serv.sendMessageToClient(main, "441 " + users[i] + " " + chans[0] + " :They aren't on that channel\r\n");
				continue;
			}
			if (client->getFd() == main.getFd())
			{
				serv.sendMessageToClient(main, "484 :You cannot kick yourself\r\n");
				return;
			}

			std::string kickMsg = ":" + main.getNickname() + "!" + main.getUsername() +
								  "@server KICK " + chans[0] + " " + users[i] + " :" + comment + "\r\n";
			
			const std::vector<int> &members = channel->getMembers();
			for (size_t i = 0; i < members.size(); i++)
			{
				Client &member = serv.getFd(members[i]);
				serv.sendMessageToClient(member, kickMsg);
			}
			channel->removeMember(client->getFd());
		}
	}
	else
	{
		for (size_t i = 0; i < chanSize; i++)
		{
			Channel *channel = serv.getChannel(chans[i]);
			
			if (!channel)
			{
				serv.sendMessageToClient(main, "403 " + chans[i] + " :No such channel\r\n");
				continue;
			}
			
			Client *client = NULL;	
			for (size_t j = 0; j < clients.size(); j++)
			{
				if (users[i] == clients[j].getNickname())
					client = &serv.getFd(clients[j].getFd());
			}
			
			if (!client)
			{
				serv.sendMessageToClient(main.getFd(), "401 :User " + users[i] + " is not on the server.\r\n");
				continue;
			}
			
			if (!channel->isMember(client->getFd()))
			{
				serv.sendMessageToClient(main, "441 " + users[i] + " " + chans[i] + " :They aren't on that channel\r\n");
				continue;
			}

			if (!channel->isMember(main.getFd()))
			{
				serv.sendMessageToClient(main.getFd(), "442 :You are not on channel " + chans[i] + ".\r\n");
				continue;
			}

			if (!channel->isOperator(main.getFd()))
			{
				serv.sendMessageToClient(main, "482 " + chans[i] + " :You're not channel operator\r\n");
				continue;
			}

			if (client->getFd() == main.getFd())
			{
				serv.sendMessageToClient(main, "484 :You cannot kick yourself\r\n");
				return;
			}

			std::string kickMsg = ":" + main.getNickname() + "!" + main.getUsername() +
									"@server KICK " + chans[i] + " " + users[i] + " :" + comment + "\r\n";
				
			const std::vector<int> &memberList = channel->getMembers();
			for (size_t j = 0; j < memberList.size(); j++)
			{
				Client &member = serv.getFd(memberList[j]);
				serv.sendMessageToClient(member, kickMsg);
			}
			channel->removeMember(client->getFd());
		}
	}
}