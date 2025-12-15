/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:21:17 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:01:11 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Quit_cmd.hpp"
#include "../../includes/Server.hpp"

Quit_cmd::Quit_cmd() {}

Quit_cmd::~Quit_cmd() {}

void Quit_cmd::parsing(std::string str, Server &serv, Client &main) {
	Client &client = serv.getFd(main.getFd());
	std::string message = str;

	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);

	std::string notify = ":" + client.getNickname() + "!" + client.getUsername() + "@server QUIT :" + message + "\r\n";

	const std::vector<Client> &clients = serv.getClients();
	for (size_t i = 0; i < clients.size(); ++i)
	{
		if (clients[i].getFd() != client.getFd())
			serv.sendMessageToClient(const_cast<Client &>(clients[i]), notify);
	}
	serv.sendMessageToClient(client, "ERROR :Closing Link: " + client.getNickname() + " (" + message + ")\r\n");
	std::cout << "Client " << client.getFd() << " has quit: " << message << std::endl;
	serv.removeClient(client.getFd());
	close(client.getFd());
}