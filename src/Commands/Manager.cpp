/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:51:04 by prosset           #+#    #+#             */
/*   Updated: 2025/12/09 14:09:13 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Manager.hpp"


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

ACmd *Manager::makeCmd(std::string name, Client *Client, std::string *args) {
	std::string levels[] = {"PASS", "NICK", "USER", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};
	ACmd* (Manager::* functions[])() = {&Manager::makePass, &Manager::makeNick, &Manager::makeUser, &Manager::makeJoin,
				&Manager::makePart, &Manager::makeTopic, &Manager::makeInvite, &Manager::makeKick, &Manager::makeQuit, &Manager::makeMode, &Manager::makePrivmsg};
	
	int rank = Client->getRank();

	int i = 0;
	while (levels[i] != name && i < 11)
		i++;

	if (i == 11)
	{
		std::cerr << "Error : please provide one of these commands : PASS, NICK, USER, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG." << std::endl;
		return NULL;
	}
	
	if (rank == 0 && i != 0)
	{
		std::cerr << "Error : you must first provide the server password with the command PASS." << std::endl;
		return NULL;
	}

	if (rank == 1 && i != 1)
	{
		std::cerr << "Error : you must now register your nickname with the command NICK." << std::endl;
		return NULL;
	}

	if (rank == 2 && i != 2)
	{
		std::cerr << "Error : you must now register your username with the command USER." << std::endl;
		return NULL;
	}

	if (rank == 3 && i < 3)
	{
		std::cerr << "Error : you are already registered. Please provide one of these commands : JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG" << std::endl;
		return NULL;
	}

	if (i == 3 && *args == "0")
	{
		i = 4;
		std::vector<Channel> Chans = Client->getChannels();
		*args = "";
		for (size_t j = 0; j < Chans.size(); i++)
			*args += Chans[i].getName() + ",";
		args->resize(args->size() - 1);
	}
	
	ACmd *com = (this->*functions[i])();
	return com;
}