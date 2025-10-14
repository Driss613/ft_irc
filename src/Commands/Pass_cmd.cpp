/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:06:49 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 14:33:25 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Pass_cmd.hpp"
#include "../../includes/Server.hpp"

Pass_cmd::Pass_cmd() {}
		
Pass_cmd::~Pass_cmd() {}

void Pass_cmd::parsing(std::string str, Server &serv, Client &main) {
	while (!str.empty() && (str[0] == ' ' || str[0] == '\t'))
		str.erase(0, 1);
	while (!str.empty() && (str[str.size() - 1] == ' ' || str[str.size() - 1] == '\t' || str[str.size() - 1] == '\r' || str[str.size() - 1] == '\n'))
		str.resize(str.size() - 1);
	if (str == serv.getpasswd())
	{

		main.setRank(3);
		serv.sendMessageToClient(
			main,
			":irc.example.com 001 " + main.getNickname() +
				" :Welcome to the Internet Relay Network " +
				main.getNickname() + "!" + main.getUsername() + "@" + main.getIp() + "\r\n");
	}
	else
		std::cerr << "Error : wrong password." << std::endl;
}