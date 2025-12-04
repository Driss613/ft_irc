/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:53:17 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 10:15:02 by prosset          ###   ########.fr       */
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
		std::cerr << "Error : need more parameters." << std::endl;
		return ;
	}
	
	std::vector<Client> clients = serv.getClients();
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (args[0] == clients[i].getUsername())
		{
			std::cerr << "Error : username unavailable." << std::endl;
			return ;
		}
	}

	for (size_t i = 0; i < args[1].size(); i++)
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			std::cerr << "Error : usermod should be a numeric." << std::endl;
			return ;
		}
	}

	main.setUsername(args[0]);
	main.setRank(2);
	serv.sendMessageToClient(
		main,
		":irc.example.com " + main.getNickname() + " :USER command received, waiting for PASS command\r\n");
}