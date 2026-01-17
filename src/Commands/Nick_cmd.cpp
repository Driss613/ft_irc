/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:51:40 by prosset           #+#    #+#             */
/*   Updated: 2026/01/17 14:55:50 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Nick_cmd.hpp"
#include "../../includes/Server.hpp"

Nick_cmd::Nick_cmd() {}

Nick_cmd::~Nick_cmd() {}

static bool isdigit(std::string::iterator it)
{
	return (*it >= '0' && *it <= '9');
}

static bool isalpha(std::string::iterator it)
{
	return ((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'));
}


void Nick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<Client> &clients = serv.getClients();
	
	if (str.empty())
	{
		serv.sendMessageToClient(main.getFd(), "431 :No nickname given.\r\n");
		return;
	}

	for (std::string::iterator it = str.begin(); it < str.end(); it++)
	{
		if (!isdigit(it) && !isalpha(it) && *it != '_')
		{
			serv.sendMessageToClient(main.getFd(), "432 " + str + " :Erroneous nickname.\r\n");
			return;	
		}
	}
	if (str.size() > 9)
	{
		serv.sendMessageToClient(main.getFd(), "432 :Please enter a nickname of maximum 9 characters.\r\n");
		return;
	}

	for (size_t i = 0; i < clients.size(); i++)
	{
		if (str == clients[i].getNickname())
		{
			serv.sendMessageToClient(main.getFd(), "433 :Nickname unavailable.\r\n");
			return;
		}
	}
	Client &client = serv.getFd(main.getFd());
	client.setNickname(str);

	if (client.getRank() == 1)
	{
		client.setRank(2);
		serv.sendMessageToClient(
			client,
			":irc.example.com " + client.getNickname() + " :NICK command received, waiting for USER command\r\n");
	}
	else
	{
		serv.sendMessageToClient(
			client,
			":irc.example.com " + client.getNickname() + " :Nickname changed\r\n");
	}
}