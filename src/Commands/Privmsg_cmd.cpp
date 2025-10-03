/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:51 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:20:54 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg_cmd.hpp"

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

	// Lancer la commande PRIVMSG //
}