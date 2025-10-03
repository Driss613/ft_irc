/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:53:17 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:22:30 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User_cmd.hpp"

User_cmd::User_cmd() {}
		
User_cmd::~User_cmd() {}

void User_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<Client> clients = serv.getClients();
	std::string args[4];
	size_t index = 0;
	size_t count = 0;

	for (size_t i = 1; i < str.size(); i++)
	{
		if (str[i] == ' ' && str[i - 1] != ' ')
			count++;
	}
	if (count < 3)
	{
		std::cerr << "Error : need more parameters." << std::endl;
		return ;
	}

	for (int i = 0; i < 3; i++)
	{
		while (index < str.find(' '))
		{
			args[i] += str[index];
			index++;	
		}
		index++;
	}
	while (str[index])
	{
		args[3] += str[index];
		index++;
	}
	
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

	// ERR_ALREADYREGISTRED //

	// Lancer la commande Username //
}