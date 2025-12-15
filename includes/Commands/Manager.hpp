/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:49:29 by prosset           #+#    #+#             */
/*   Updated: 2025/12/10 09:56:38 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"
#include "Invite_cmd.hpp"
#include "Join_cmd.hpp"
#include "Kick_cmd.hpp"
#include "Mode_cmd.hpp"
#include "Nick_cmd.hpp"
#include "Part_cmd.hpp"
#include "Pass_cmd.hpp"
#include "Privmsg_cmd.hpp"
#include "Quit_cmd.hpp"
#include "Topic_cmd.hpp"
#include "User_cmd.hpp"

class ACmd;

class Manager {
	public:
		Manager();
		~Manager();

		ACmd *makeCmd(std::string name, Client *Client, std::string *args, Server &serv);

		ACmd *makePass();
		ACmd *makeNick();
		ACmd *makeUser();
		ACmd *makeJoin();
		ACmd *makePart();
		ACmd *makeTopic();
		ACmd *makeInvite();
		ACmd *makeKick();
		ACmd *makeQuit();
		ACmd *makeMode();
		ACmd *makePrivmsg();
};