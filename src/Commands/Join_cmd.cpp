/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:54:26 by prosset           #+#    #+#             */
/*   Updated: 2025/12/09 14:01:36 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Join_cmd.hpp"
#include "../../includes/Server.hpp"

Join_cmd::Join_cmd() {}

Join_cmd::~Join_cmd() {}

void Join_cmd::parsing(std::string str, Server &serv, Client &main)
{	
	std::istringstream iss(str);
	std::string chanList;
	std::string keyList;
	
	iss >> chanList;
	std::getline(iss, keyList);
	if (!keyList.empty() && keyList[0] == ' ')
	 	keyList.erase(0, 1);
		 
	if (chanList.empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 " + main.getNickname() + " JOIN :Not enough parameters\r\n");
		return;
	}
	
	std::vector<std::string> chans = buildVector(chanList);
	std::vector<std::string> keys = buildVector(keyList);
	
	for (size_t i = 0; i < chans.size(); i++)
	{
		std::string channel = chans[i];

		while (!channel.empty() && isspace(channel[0]))
			channel.erase(0, 1);
		while (!channel.empty() && isspace(channel[channel.size() - 1]))
			channel.resize(channel.size() - 1);

		if (channel.empty())
			continue;

		if (channel[0] != '#' && channel[0] != '&')
		{
			serv.sendMessageToClient(main.getFd(),
									 "476 " + channel + " :Bad Channel Mask\r\n");
			continue;
		}
		
		Channel *chan = serv.getChannel(channel);
		bool isNewChannel = (chan == NULL);

		if (isNewChannel)
			chan = serv.createChannel(channel);
			
		if (chan->isMember(main.getFd()))
			continue;

		if (!isNewChannel && chan->hasKey())
		{
			std::string providedKey = (i < keys.size()) ? keys[i] : "";
			if (providedKey != chan->getKey())
			{
				serv.sendMessageToClient(main.getFd(),
										 "475 " + channel + " :Cannot join channel (+k) - bad key\r\n");
				continue;
			}
		}

		if (chan->hasLimit() && chan->getMembers().size() >= chan->getLimit())
		{
			serv.sendMessageToClient(main.getFd(),
									 "471 " + channel + " :Cannot join channel (+l) - channel is full\r\n");
			continue;
		}

		if (chan->isInviteOnly() && !chan->isInvited(main.getFd()))
		{
			serv.sendMessageToClient(main.getFd(),
									 "473 " + channel + " :Cannot join channel (+i) - invite only\r\n");
			continue;
		}

		serv.addClientToChannel(channel, main.getFd());

		if (chan->getMembers().size() == 1)
			chan->addOperator(main.getFd());

		std::string joinMsg = ":" + main.getNickname() + "!" +
							  main.getUsername() + "@" + main.getIp() + " JOIN " + channel + "\r\n";

		const std::vector<int> &members = chan->getMembers();
		for (size_t j = 0; j < members.size(); j++)
		{
			serv.sendMessageToClient(members[j], joinMsg);
		}

		if (!chan->getTopic().empty())
			serv.sendMessageToClient(main.getFd(),
									 "332 " + main.getNickname() + " " + channel + " :No topic is set\r\n");

		std::string namesList;
		for (size_t j = 0; j < members.size(); j++)
		{
			Client &member = serv.getFd(members[j]);
			if (j > 0)
				namesList += " ";

			if (chan->isOperator(members[j]))
				namesList += "@";

			namesList += member.getNickname();
		}

		serv.sendMessageToClient(main.getFd(),
								 "353 " + main.getNickname() + " = " + channel + " :" + namesList + "\r\n");
		serv.sendMessageToClient(main.getFd(),
								 "366 " + main.getNickname() + " " + channel + " :End of NAMES list\r\n");
	}
}