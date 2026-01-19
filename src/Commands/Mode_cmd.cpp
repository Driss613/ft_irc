/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:00 by prosset           #+#    #+#             */
/*   Updated: 2026/01/19 13:49:31 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Mode_cmd.hpp"
#include "../../includes/Server.hpp"

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

	Channel *channel = serv.getChannel(chan);
	if (!channel)
	{
		serv.sendMessageToClient(main.getFd(), "403 :No such channel as " + chan + ".\r\n");
		return ;
	}

	if (mod.empty())
	{
		std::string modeStr = "+";
		std::string params = "";
		
		if (channel->isInviteOnly())
			modeStr += "i";
		if (channel->getTopicOnlyOperator())
			modeStr += "t";
		if (channel->hasKey())
		{
			modeStr += "k";
			params += " " + channel->getKey();
		}
		if (channel->hasLimit())
		{
			modeStr += "l";
			std::ostringstream oss;
			oss << channel->getLimit();
			params += " " + oss.str();
		}
		
		std::string response = "324 " + main.getNickname() + " " + chan + " " + modeStr + params + "\r\n";
		serv.sendMessageToClient(main.getFd(), response);
		return ;
	}

	if (mod.size() != 2 || (mod[0] != '+' && mod[0] != '-'))
	{
		serv.sendMessageToClient(main.getFd(), "472 : wrong mode. Try with i, t, k, o or l.\r\n");
		return ;
	}

	if (!mod.empty() && mods.find(mod[1]) == std::string::npos)
	{
		serv.sendMessageToClient(main.getFd(), "472 : wrong mode. Try with i, t, k, o or l.\r\n");
		return ;
	}

	if (!mod.empty() && (mod == "+l" || mod[1] == 'k' || mod[1] == 'o') && param.empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 MODE :Need more parameters.\r\n");
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
				if (mod[0] == '-' && channel->isOperator(client->getFd()))
				{
					if (channel->getOperators().size() <= 1)
					{
						serv.sendMessageToClient(main.getFd(), "482 :Cannot remove the last operator from the channel\r\n");
						return ;
					}
					channel->removeOperator(client->getFd());
				}
				else if (mod[0] == '+' && !channel->isOperator(client->getFd()))
					channel->addOperator(client->getFd());
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

	std::string modeMsg = ":" + main.getNickname() + "!" + main.getUsername() + "@" + main.getIp() + " MODE " + chan + " " + mod;
	if ((mod[1] == 'k' || mod[1] == 'o' || mod[1] == 'l') && !param.empty())
		modeMsg += " " + param;
	modeMsg += "\r\n";

	const std::vector<int> &members = channel->getMembers();
	for (size_t i = 0; i < members.size(); i++)
	{
		serv.sendMessageToClient(members[i], modeMsg);
	}
}