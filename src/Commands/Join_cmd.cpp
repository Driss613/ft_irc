/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:54:26 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:00:44 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Join_cmd.hpp"
#include "../../includes/Server.hpp"

Join_cmd::Join_cmd() {}
		
Join_cmd::~Join_cmd() {}

void Join_cmd::parsing(std::string str, Server &serv, Client &main)
{
	if (str == "0")
	{
		// Lancer la commande PART avec en argument tous les channels du client //
		return;
	}

	std::vector<std::string> chans;
	std::vector<std::string> keys;

	size_t spacePos = str.find(' ');
	std::string chanList = (spacePos == std::string::npos) ? str : str.substr(0, spacePos);
	std::string keyList = (spacePos == std::string::npos) ? "" : str.substr(spacePos + 1);

	if (!chanList.empty() && chanList[0] == ':')
		chanList.erase(0, 1);

	size_t start = 0;
	while (start < chanList.size())
	{
		size_t comma = chanList.find(',', start);
		std::string chan = (comma == std::string::npos) ? chanList.substr(start) : chanList.substr(start, comma - start);

		if (!chan.empty())
			chans.push_back(chan);

		if (comma == std::string::npos)
			break;
		start = comma + 1;
	}

	if (!keyList.empty())
	{
		start = 0;
		while (start < keyList.size())
		{
			size_t comma = keyList.find(',', start);
			std::string key = (comma == std::string::npos) ? keyList.substr(start) : keyList.substr(start, comma - start);

			if (!key.empty())
				keys.push_back(key);

			if (comma == std::string::npos)
				break;
			start = comma + 1;
		}
	}

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
		{
			chan = serv.createChannel(channel);
		}
		if (chan->isMember(main.getFd()))
		{
			continue;
		}

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
		// const std::vector<int> &members = chan->getMembers();

		if (chan->getMembers().size() == 1)
		{
			chan->addOperator(main.getFd());
		}

		std::string joinMsg = ":" + main.getNickname() + "!" +
							  main.getUsername() + "@" + main.getIp() + " JOIN " + channel + "\r\n";

		const std::vector<int> &members = chan->getMembers();
		for (size_t j = 0; j < members.size(); j++)
		{
			serv.sendMessageToClient(members[j], joinMsg);
		}

		if (!chan->getTopic().empty())
		{
			serv.sendMessageToClient(main.getFd(),
									 "332 " + main.getNickname() + " " + channel + " :" + chan->getTopic() + "\r\n");
		}

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
	// size_t i = 0;
	// while (i < str.size() && i < str.find(' '))
	// {
	// 	if (str[i] == ',')
	// 		i++;
	// 	std::string chan;
	// 	while (i < str.size() && str[i] != ' ' && str[i] != ',')
	// 	{
	// 		chan += str[i];
	// 		i++;
	// 	}
	// 	chans.push_back(chan);
	// }

	// i++;
	// while (i < str.size())
	// {
	// 	if (str[i] == ',')
	// 		i++;
	// 	std::string key;
	// 	while (i < str.size() && str[i] != ' ' && str[i] != ',')
	// 	{
	// 		key += str[i];
	// 		i++;
	// 	}
	// 	keys.push_back(key);
	// }

	// if (keys.empty())
	// {
	// 	std::cerr << "Error : need more params." << std::endl;
	// 	return;
	// }

	// std::string list = params;
	// if (!list.empty() && list[0] == ':')
	// 	list.erase(0, 1);

	// Client &client = getFd(fd);

	// size_t start = 0;
	// while (start < list.size())
	// {
	// 	size_t comma = list.find(',', start);
	// 	std::string channel = (comma == std::string::npos) ? list.substr(start) : list.substr(start, comma - start);

	// 	while (!channel.empty() && isspace(channel[0]))
	// 		channel.erase(0, 1);
	// 	while (!channel.empty() && isspace(channel[channel.size() - 1]))
	// 		channel.resize(channel.size() - 1);

	// 	if (!channel.empty())
	// 	{
	// 		if (channel[0] != '#' && channel[0] != '&')
	// 		{
	// 			sendMessageToClient(client, "476 " + client.getNickname() + " " + channel + " :Bad Channel Mask\r\n");
	// 		}
	// 		else
	// 		{
	// 			addClientToChannel(channel, fd);

	// 			Channel *chan = getChannel(channel);
	// 			if (chan && chan->getMembers().size() == 1)
	// 			{
	// 				chan->addOperator(fd);
	// 				sendMessageToClient(client, "You are operator of " + channel + "\r\n");
	// 			}

	// 			std::string joinMsg = ":" + client.getNickname() + "!" + client.getUsername() + "@server JOIN " + channel + "\r\n";

	// 			const std::vector<int> &members = chan->getMembers();
	// 			for (size_t i = 0; i < members.size(); ++i)
	// 			{
	// 				Client &member = getFd(members[i]);
	// 				sendMessageToClient(member, joinMsg);
	// 			}

	// 			std::string namesList;
	// 			for (size_t i = 0; i < members.size(); ++i)
	// 			{
	// 				Client &member = getFd(members[i]);
	// 				if (i > 0)
	// 					namesList += " ";
	// 				namesList += member.getNickname();
	// 			}

	// 			sendMessageToClient(client, "353 " + client.getNickname() + " = " + channel + " :" + namesList + "\r\n");
	// 			sendMessageToClient(client, "366 " + client.getNickname() + " " + channel + " :End of NAMES list\r\n");
	// 		}
	// 	}

	// 	if (comma == std::string::npos)
	// 		break;
	// 	start = comma + 1;
	// }

	// i = 0;
	// std::vector<Channel> channels = serv.getChannels();
	// while (i <= chans.size())
	// {
	// 	bool chan_exist = 0;
	// 	for (size_t n = 0; n < channels.size(); n++)
	// 	{
	// 		if (chans[i] == channels[n].getChanName())
	// 		{
	// 			chan_exist = 1;
	// 			if (keys[i] != channels[n].getChanKey())
	// 			{
	// 				std::cerr << "Error : wrong channel key for channel " << chans[i] << "." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 			if (channels[n].getInvite())
	// 			{
	// 				std::cerr << "Error : you tried to join an invite only channel : " << chans[i] << "." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 			if (channels[n].getMembers().size() == 20)
	// 			{
	// 				std::cerr << "Error : channel " << chans[i] << " is full." << std::endl;
	// 				chans[i] = "";
	// 			}
	// 		}
	// 	}
	// 	if (!chan_exist)
	// 	{
	// 		std::cerr << "Error : no such channel as " << chans[i] << "." << std::endl;
	// 		chans[i] = "";
	// 	}
	// 	i++;
	// }

	// ERR_BADCHANMASK //

	// ERR_BANNEDFROMCHAN //

	// ERR_TOOMANYTARGETS //

	// ERR_UNAVAILRESOURCE //

	// ERR_TOOMANYCHANNELS //
}