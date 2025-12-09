/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:51:40 by prosset           #+#    #+#             */
/*   Updated: 2025/12/09 13:47:00 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Nick_cmd.hpp"
#include "../../includes/Server.hpp"

Nick_cmd::Nick_cmd() {}

Nick_cmd::~Nick_cmd() {}

void Nick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<Client> &clients = serv.getClients();

	if (str.empty())
	{
		serv.sendMessageToClient(main.getFd(), "431 : no nickname given.\r\n");
		return;
	}
	if (str.size() > 9)
	{
		serv.sendMessageToClient(main.getFd(), "432 : please enter a nickname of maximum 9 characters.\r\n");
		return;
	}

	for (size_t i = 0; i < clients.size(); i++)
	{
		if (str == clients[i].getNickname())
		{
			serv.sendMessageToClient(main.getFd(), "433 : nickname unavailable.\r\n");
			return;
		}
	}
	Client &client = serv.getFd(main.getFd());
	client.setNickname(str);
	client.setRank(1);

	serv.sendMessageToClient(
		client,
		":irc.example.com " + client.getNickname() + " :NICK command received, waiting for USER command\r\n");
}