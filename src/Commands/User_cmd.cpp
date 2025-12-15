/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:53:17 by prosset           #+#    #+#             */
/*   Updated: 2025/12/09 14:10:02 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/User_cmd.hpp"
#include "../../includes/Server.hpp"

User_cmd::User_cmd() {}

User_cmd::~User_cmd() {}

void User_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string args[4];
	std::istringstream iss(str);
	
	iss >> args[0] >> args[1] >> args[2];
	std::getline(iss, args[3]);
	if (!args[3].empty() && args[3][0] == ' ')
		args[3].erase(0, 1);

	if (args[3].empty())
	{
		serv.sendMessageToClient(main.getFd(), "461 USER :Need more parameters.\r\n");
		return ;
	}
	
	std::vector<Client> clients = serv.getClients();
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (args[0] == clients[i].getUsername())
		{
			serv.sendMessageToClient(main.getFd(), "433 :Username unavailable.\r\n");
			return ;
		}
	}

	for (size_t i = 0; i < args[1].size(); i++)
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			serv.sendMessageToClient(main.getFd(), "501 :Usermod should be a numeric.\r\n");
			return ;
		}
	}

	main.setUsername(args[0]);
	main.setRank(3);
	serv.sendMessageToClient(
		main,
		":irc.example.com " + main.getNickname() + " :USER command received, waiting for PASS command\r\n");
}