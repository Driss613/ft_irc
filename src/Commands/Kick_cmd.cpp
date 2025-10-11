/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:01:23 by prosset           #+#    #+#             */
/*   Updated: 2025/10/11 20:35:27 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Kick_cmd.hpp"
#include <sstream>

Kick_cmd::Kick_cmd() {}

Kick_cmd::~Kick_cmd() {}
void Kick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::istringstream iss(str);
	std::string channelName, targetNick;
	std::string reason;

	iss >> channelName >> targetNick;
	std::getline(iss, reason);
	if (!reason.empty() && reason[0] == ' ')
		reason.erase(0, 1);
	if (reason.empty())
		reason = "Kicked";

	if (channelName.empty() || targetNick.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return;
	}

	Client &sender = serv.getFd(main.getFd());
	Channel *channel = serv.getChannel(channelName);
	if (!channel)
	{
		serv.sendMessageToClient(sender, "403 " + channelName + " :No such channel\r\n");
		return;
	}

	if (!channel->isOperator(sender.getFd()))
	{
		serv.sendMessageToClient(sender, "482 " + channelName + " :You're not channel operator\r\n");
		return;
	}

	Client *target = NULL;
	std::vector<Client> &clients = serv.getClients();
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].getNickname() == targetNick)
		{
			target = &clients[i];
			break;
		}
	}

	if (!target)
	{
		serv.sendMessageToClient(sender, "401 " + targetNick + " :No such nick\r\n");
		return;
	}

	if (target->getFd() == sender.getFd())
	{
		serv.sendMessageToClient(sender, "484 :You cannot kick yourself\r\n");
		return;
	}

	if (!channel->isMember(target->getFd()))
	{
		serv.sendMessageToClient(sender, "441 " + targetNick + " " + channelName + " :They aren't on that channel\r\n");
		return;
	}

	std::string kickMsg = ":" + sender.getNickname() + "!" + sender.getUsername() +
						  "@server KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";

	const std::vector<int> &members = channel->getMembers();
	for (size_t i = 0; i < members.size(); i++)
	{
		Client &member = serv.getFd(members[i]);
		serv.sendMessageToClient(member, kickMsg);
	}

	channel->removeMember(target->getFd());
}

// ERR_BADCHANMASK //

// ERR_CHANOPRIVSNEEDED //

// ERR_NOTONCHANNEL //

// Lancer la commande KICK //
//}