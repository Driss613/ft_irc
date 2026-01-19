/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:51:04 by prosset           #+#    #+#             */
/*   Updated: 2026/01/19 14:46:25 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Manager.hpp"
#include "../../includes/Server.hpp"

Manager::Manager() {}

Manager::~Manager() {}

ACmd *Manager::makePass() {
	ACmd* com = new Pass_cmd();
	return com;
}

ACmd *Manager::makeNick() {
	ACmd* com = new Nick_cmd();
	return com;
}

ACmd *Manager::makeUser() {
	ACmd* com = new User_cmd();
	return com;
}

ACmd *Manager::makeJoin() {
	ACmd* com = new Join_cmd();
	return com;
}

ACmd *Manager::makePart() {
	ACmd* com = new Part_cmd();
	return com;
}

ACmd *Manager::makeTopic() {
	ACmd* com = new Topic_cmd();
	return com;
}

ACmd *Manager::makeInvite() {
	ACmd* com = new Invite_cmd();
	return com;
}

ACmd *Manager::makeKick() {
	ACmd* com = new Kick_cmd();
	return com;
}

ACmd *Manager::makeQuit() {
	ACmd* com = new Quit_cmd();
	return com;
}

ACmd *Manager::makeMode() {
	ACmd* com = new Mode_cmd();
	return com;
}

ACmd *Manager::makePrivmsg() {
	ACmd* com = new Privmsg_cmd();
	return com;
}

ACmd *Manager::makeCmd(std::string name, Client *Client, Server &serv) {
	std::string levels[] = {"PASS", "NICK", "USER", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};
	ACmd* (Manager::* functions[])() = {&Manager::makePass, &Manager::makeNick, &Manager::makeUser, &Manager::makeJoin,
				&Manager::makePart, &Manager::makeTopic, &Manager::makeInvite, &Manager::makeKick, &Manager::makeQuit, &Manager::makeMode, &Manager::makePrivmsg};
	
	int rank = Client->getRank();

	int i = 0;
	while (levels[i] != name && i < 11)
		i++;

	if (i == 11)
	{
		serv.sendMessageToClient(Client->getFd(), "421 :" + name + " :Unknown command\r\n");
		return NULL;
	}
	
	if (rank == 0 && i != 0)
	{
		serv.sendMessageToClient(Client->getFd(), "461 :You must first provide the server password with the command PASS.\r\n");
		return NULL;
	}

	if (rank == 1 && i != 1)
	{
		serv.sendMessageToClient(Client->getFd(), "461 :You must now register your nickname with the command NICK.\r\n");
		return NULL;
	}

	if (rank == 2 && i != 2)
	{
		serv.sendMessageToClient(Client->getFd(), "461 :You must now register your username with the command USER.\r\n");
		return NULL;
	}

	if (rank == 3 && i == 0)
	{
		serv.sendMessageToClient(Client->getFd(), "461 :You are already registered. Please provide one of these commands : NICK, USER, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG.\r\n");
		return NULL;
	}
	
	ACmd *com = (this->*functions[i])();
	return com;
}