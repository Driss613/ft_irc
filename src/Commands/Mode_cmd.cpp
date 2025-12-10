/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:00 by prosset           #+#    #+#             */
/*   Updated: 2025/12/09 14:04:14 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Mode_cmd.hpp"

Mode_cmd::Mode_cmd() {}

Mode_cmd::~Mode_cmd() {}

void Mode_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string mods = "itkol";

	std::istringstream iss(str);

	std::string chan;
	std::string mod;
	std::string param;

	iss >> chan >> mod;
	std::getline(iss, param);
	if (!param.empty() && param[0] == ' ')
	 	param.erase(0, 1);

	if (mod.empty() || mod.size() != 2 || (mod[0] != '+' && mod[0] != '-'))
	{
		serv.sendMessageToClient(main.getFd(), "472 : wrong mode. Try with i, t, k, o or l.\r\n");
		return ;
	}

	if (mods.find(mod[1]) == std::string::npos)
	{
		serv.sendMessageToClient(main.getFd(), "472 : wrong mode. Try with i, t, k, o or l.\r\n");
		return ;
	}

	if ((mod == "+l" || mod[1] == 'k' || mod[1] == 'o') && param.empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 MODE :Need more parameters.\r\n");
		return ;
	}

	Channel *channel = serv.getChannel(chan);
	if (!channel)
	{
		serv.sendMessageToClient(main.getFd(), "403 :No such channel as " + chan + ".\r\n");
		return ;
	}

	if (!channel->isOperator(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "482 :You don't have operator privileges for this channel.\r\n");
		return ;
	}

	if (!channel->isMember(main.getFd()))
	{
		serv.sendMessageToClient(main.getFd(), "442 :You are not on the channel.\r\n");
		return ;
	}
	switch (mod[1])
	{
		case 'i':
			if (mod[0] == '+')
				channel->setInviteOnly(true);
			else
				channel->setInviteOnly(false);
			break;
		case 't':
			if (mod[0] == '+')
				channel->setTopicOnlyOperator(true);
			else
				channel->setTopicOnlyOperator(false);
			break;
		case 'k':
			if (mod[0] == '+')
				channel->setKey(param);
			else
				channel->setKey("");
			break;
		case 'o':
			{
				Client *client = NULL;
				std::vector<Client> clients = serv.getClients();
				for (size_t i = 0; i < clients.size(); i++)
				{
					if (clients[i].getNickname() == param)
					{
						client = &serv.getFd(clients[i].getFd());
						break;
					}
				}
				if (!client || !channel->isMember(client->getFd()))
				{
					serv.sendMessageToClient(main.getFd(), "441 :User " + param + " is not on the channel.\r\n");
					return ;
				}
				if (mod[0] == '+')
					channel->addOperator(client->getFd());
				else
					channel->removeOperator(client->getFd());
			}
			break;
		case 'l':
			if (mod[0] == '+')
				channel->setLimit(static_cast<size_t>(std::atoi(param.c_str())));
			else
				channel->removeLimit();
			break;
		default:
			break;
	}
	
}