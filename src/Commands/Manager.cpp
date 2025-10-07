/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:51:04 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 12:22:45 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Manager.hpp"

Manager::Manager() {}

Manager::~Manager() {}

ACmd *Manager::makeNick()
{
	ACmd *com = new Nick_cmd();
	return com;
}

ACmd *Manager::makeUser()
{
	ACmd *com = new User_cmd();
	return com;
}

ACmd *Manager::makePass()
{
	ACmd *com = new Pass_cmd();
	return com;
}

ACmd *Manager::makeJoin()
{
	ACmd *com = new Join_cmd();
	return com;
}

ACmd *Manager::makePart()
{
	ACmd *com = new Part_cmd();
	return com;
}

ACmd *Manager::makeTopic()
{
	ACmd *com = new Topic_cmd();
	return com;
}

ACmd *Manager::makeInvite()
{
	ACmd *com = new Invite_cmd();
	return com;
}

ACmd *Manager::makeKick()
{
	ACmd *com = new Kick_cmd();
	return com;
}

ACmd *Manager::makeQuit()
{
	ACmd *com = new Quit_cmd();
	return com;
}

ACmd *Manager::makeMode()
{
	ACmd *com = new Mode_cmd();
	return com;
}

ACmd *Manager::makePrivmsg()
{
	ACmd *com = new Privmsg_cmd();
	return com;
}

ACmd *Manager::makeCmd(std::string name)
{
	std::string levels[] = {"NICK", "USER", "PASS", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};
	ACmd *(Manager::*functions[])() = {
		&Manager::makeNick,
		&Manager::makeUser,
		&Manager::makePass,
		&Manager::makeJoin,
		&Manager::makePart,
		&Manager::makeTopic,
		&Manager::makeInvite,
		&Manager::makeKick,
		&Manager::makeQuit,
		&Manager::makeMode,
		&Manager::makePrivmsg};

	int i = 0;
	while (levels[i] != name && i < 11)
		i++;

	if (i == 11)
	{
		std::cerr << "Error : please provide one of these commands : NICK, USER, PASS, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG" << std::endl;
		return NULL;
	}
	ACmd *com = (this->*functions[i])();
	return com;
}