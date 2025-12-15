/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:06:49 by prosset           #+#    #+#             */
/*   Updated: 2025/12/10 13:43:28 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Pass_cmd.hpp"
#include "../../includes/Server.hpp"

Pass_cmd::Pass_cmd() {}

Pass_cmd::~Pass_cmd() {}

void Pass_cmd::parsing(std::string str, Server &serv, Client &main)
{
	if (str == serv.getpasswd())
	{
		main.setRank(1);
		serv.sendMessageToClient(
			main,
			":irc.example.com 001 " + main.getNickname() +
				" :Welcome to the Internet Relay Network " +
				main.getNickname() + "!" + main.getUsername() + "@" + main.getIp() + "\r\n");
	}
	else
		serv.sendMessageToClient(main.getFd(), "464 :Password incorrect.\r\n");
}