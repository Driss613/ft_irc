/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:51 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:31:31 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Privmsg_cmd.hpp"
#include "../../includes/Server.hpp"

Privmsg_cmd::Privmsg_cmd() {}
		
Privmsg_cmd::~Privmsg_cmd() {}

void Privmsg_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string target;
	std::string message;
	size_t i = 0;

	if (str.empty())
	{
		std::cerr << "Error : no target given." << std::endl;
		return ;
	}

	while (i < str.find(' ') && i < str.size())
	{
		target += str[i];
		i++;
	}

	i++;
	while (i < str.size())
	{
		message += str[i];
		i++;
	}

	if (message.empty())
	{
		std::cerr << "Error : no message given." << std::endl;
		return ;
	}

	std::string nick;
	i = 0;
	while (i < target.find('!') && i < target.find('@') && i < target.find('%') && i < target.size())
	{
		nick += target[i];
		i++;
	}
	
	std::vector<Client> clients = serv.getClients();
	bool nick_exist = 0;
	
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (nick == clients[i].getNickname())
			nick_exist = 1;
	}
	if (!nick_exist)
	{
		std::cerr << "Error : no such nickname on the server." << std::endl;
		return ;
	}

	// ERR_CANNOTSENDTOCHAN //

	// ERR_NOTOPLEVEL //

	// ERR_WILDTOPLEVEL //

	// ERR_TOOMANYTARGETS //




	
	// if (str.empty())
	// {
	// 	Client &client = serv.getFd(main.getFd());
	// 	serv.sendMessageToClient(client, "461 PRIVMSG :Not enough parameters\r\n");
	// 	return;
	// }

	// size_t space_pos = str.find(' ');
	// if (space_pos == std::string::npos)
	// {
	// 	Client &client = serv.getFd(main.getFd());
	// 	serv.sendMessageToClient(client, "412 :No text to send\r\n");
	// 	return;
	// }

	// std::string target = str.substr(0, space_pos);
	// std::string message = str.substr(space_pos + 1);

	// if (!message.empty() && message[0] == ':')
	// 	message.erase(0, 1);

	// Client &sender = serv.getFd(main.getFd());
	// std::vector<Client> &clients = serv.getClients();
	// if (target[0] == '#' || target[0] == '&')
	// {
	// 	Channel *chan = serv.getChannel(target);
	// 	if (!chan)
	// 	{
	// 		serv.sendMessageToClient(sender, "403 " + target + " :No such channel\r\n");
	// 		return;
	// 	}

	// 	if (!chan->isMember(main.getFd()))
	// 	{
	// 		serv.sendMessageToClient(sender, "404 " + target + " :Cannot send to channel\r\n");
	// 		return;
	// 	}

	// 	std::string msg = ":" + sender.getNickname() + "!" + sender.getUsername() + "@server PRIVMSG " + target + " :" + message + "\r\n";

	// 	const std::vector<int> &members = chan->getMembers();
	// 	for (size_t i = 0; i < members.size(); i++)
	// 	{

	// 		Client &member = serv.getFd(members[i]);
	// 		serv.sendMessageToClient(member, msg);
	// 	}
	// }
	// else
	// {
	// 	bool found = false;

	// 	for (size_t i = 0; i < clients.size(); i++)
	// 	{
	// 		if (clients[i].getNickname() == target)
	// 		{
	// 			std::string msg = ":" + sender.getNickname() + "!" + sender.getUsername() + "@server PRIVMSG " + target + " :" + message + "\r\n";
	// 			serv.sendMessageToClient(const_cast<Client &>(clients[i]), msg);
	// 			found = true;
	// 			break;
	// 		}
	// 	}

	// 	if (!found)
	// 	{
	// 		serv.sendMessageToClient(sender, "401 " + target + " :No such nick/channel\r\n");
	// 	}
	// }

	// Lancer la commande PRIVMSG //
}