/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:51:04 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:00:53 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Manager.hpp"

Manager::Manager() {}

Manager::~Manager() {}

ACmd *Manager::makeNick() {
	ACmd* com = new Nick_cmd();
	return com;
}

ACmd *Manager::makeUser() {
	ACmd* com = new User_cmd();
	return com;
}

ACmd *Manager::makePass() {
	ACmd* com = new Pass_cmd();
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

ACmd *Manager::makeCmd(std::string name, int rank) {
	std::string levels[] = {"NICK", "USER", "PASS", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};
	ACmd* (Manager::* functions[])() = {makeNick, makeUser, makePass, makeJoin, makePart, makeTopic, makeInvite, makeKick, makeQuit, makeMode, makePrivmsg};
	
	int i = 0;
	while (levels[i] != name && i < 11)
		i++;

	if (i == 11)
	{
		std::cerr << "Error : please provide one of these commands : NICK, USER, PASS, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG." << std::endl;
		return NULL;
	}
	
	if (rank == 0 && i != 0)
	{
		std::cerr << "Error : you must register your nickname first with the command NICK." << std::endl;
		return NULL;
	}

	if (rank == 1 && i != 1)
	{
		std::cerr << "Error : you must now register your username with the command USER." << std::endl;
		return NULL;
	}

	if (rank == 2 && i != 2)
	{
		std::cerr << "Error : you must now provide the server password with the command PASS." << std::endl;
		return NULL;
	}

	if (rank == 3 && i < 3)
	{
		std::cerr << "Error : you are already registered. Please provide one of these commands : JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG" << std::endl;
		return NULL;
	}
	
	ACmd *com = (this->*functions[i])();
	return com;
}