/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:51:40 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:19:44 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick_cmd.hpp"

Nick_cmd::Nick_cmd() {}
		
Nick_cmd::~Nick_cmd() {}

void Nick_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::vector<Client> clients = serv.getClients();

	if (str.empty())
	{
		std::cerr << "Error : no nickname given." << std::endl;
		return ;
	}

	if (str.size() > 9)
	{
		std::cerr << "Error : please enter a nickname of maximum 9 characters." << std::endl;
		return ;
	}
	
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (str == clients[i].getNickname())
		{
			std::cerr << "Error : nickname unavailable." << std::endl;
			return ;
		}
	}
	
	// Lancer la commande Nickname //
}