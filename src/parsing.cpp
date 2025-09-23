/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:11:18 by prosset           #+#    #+#             */
/*   Updated: 2025/09/23 11:41:49 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


void pars_nick(std::string str, Server &serv)
{
	std::vector<Client> clients = serv.getClients();

	if (str.size() > 9)
	{
		std::cerr << "Please enter a nickname of maximum 9 characters." << std::endl;
		return ;
	}
	
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (str == clients[i].getNickname())
		{
			std::cerr << "Nickname unavailable." << std::endl;
			return ;
		}
	}
	
	// Lancer la commande Nickname //
}

bool pars_user(std::string str, Server &serv)
{
	std::vector<Client> clients = serv.getClients();
	std::string args[4];
	size_t index = 0;
	size_t count = 0;

	for (size_t i = 1; i < str.size(); i++)
	{
		if (str[i] == ' ' && str[i - 1] != ' ')
			count++;
	}
	if (count < 3)
	{
		std::cerr << "Need more parameters." << std::endl;
		return ;
	}

	for (int i = 0; i < 3; i++)
	{
		while (str[index] != ' ')
		{
			args[i] += str[index];
			index++;	
		}
	}
	while (str[index])
	{
		args[3] += str[index];
		index++;
	}
	
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (args[0] == clients[i].getUsername())
		{
			std::cerr << "Username unavailable." << std::endl;
			return ;
		}
	}

	for (size_t i = 0; i < args[1].size(); i++)
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			std::cerr << "Usermod should be a numeric." << std::endl;
			return ;
		}
	}

	
	
	// Lancer la commande Username //
}

bool pars_join(std::string str)
{
	 
}

bool pars_part(std::string str)
{
	 
}

bool pars_topic(std::string str)
{
	 
}

bool pars_invite(std::string str)
{
	 
}

bool pars_kick(std::string str)
{
	 
}

bool pars_quit(std::string str)
{
	 
}

bool pars_mode(std::string str, Client &c)
{
	std::string mods = "iwroOs";
	std::string nickname;
	std::string mod;
	size_t i;

	while (i < str.find(" "))
	{
		nickname += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		mod += str[i];
		i++;
	}

	if (mod.empty() || mod.size() != 2 || mod[0] != '+' || mod[0] != '-')
	{
		std::cerr << "Error with mod parameter." << std::endl;
		return ;
	}

	if (nickname != c.getNickname() || mod == "+o" || mod == "+O" || mod == "-r")
		return ;

	// Lancer la commande MODE //
}

bool pars_privmsg(std::string str)
{
	 
}


void parsing(std::string str, Server &serv)
{
	std::string prefix;
	size_t i = 0;

	if (str[0] == ':')
	{
		i++;
		while (str[i] && str[i] != ' ')
		{
			prefix += str[i];
			i++;
		}
		if (str[i] == ' ')
			i++;
	}

	std::string cmd;
	
	while (str[i] && str[i] != ' ')
	{
		cmd += str[i];
		i++;
	}

	if (!cmd[0])
	{
		std::cerr << "Please provide a command and arguments for your message." << std::endl;
		return ;
	}
	
	std::string args;

	if (str[i] == ' ')
		i++;
		
	while (str[i])
	{
		args += str[i];
		i++;
	}

	if (!args[0])
	{
		std::cerr << "Please provide arguments for your command." << std::endl;
		return ;
	}

	std::string levels[] = {"NICK", "USER", "PASS", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};
	int j = 0;
	while (levels[j] != cmd && j < 11)
		i++;

	switch (j) {
		case 0:
			pars_nick(args, serv);
			break;
		case 1:
			pars_user(args, serv);
			break;
		case 2:
			if (args == serv.getpasswd())
				// Lancer la commande Password //
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			
			break;
		case 7:
			
			break;
		case 8:
			
			break;
		case 9:
			
			break;
		case 10:
			
			break;
		case 11:
			std::cerr << "Error, please provide one of these commands : NICK, USER, PASS, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG" << std::endl;
			break;
	}
}