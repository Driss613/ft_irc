/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:11:18 by prosset           #+#    #+#             */
/*   Updated: 2025/09/24 13:39:25 by prosset          ###   ########.fr       */
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

void pars_user(std::string str, Server &serv)
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
		index++;
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

void pars_join(std::string str, Server &serv)
{
	if (str == "0")
	{
		// Lancer la commande PART avec en argument tous les channels du client //
		return ;
	}

	std::vector<std::string> chans;
	std::vector<std::string> keys;
	
	size_t i = 0;
	while (i < str.size() && str[i] != ' ')
	{
		if (str[i] == ',')
			i++;
		std::string chan;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			chan += str[i];
			i++;
		}
		chans.push_back(chan);
	}

	i++;
	while (i < str.size())
	{
		if (str[i] == ',')
			i++;
		std::string key;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			key += str[i];
			i++;
		}
		keys.push_back(key);
	}

	// i = 0;
	// std::vector<Channel> channels = serv.getChannels();
	// while (i <= chans.size())
	// {
	// 	bool chan_exist = 0;
	// 	for (size_t n = 0; n < channels.size(); n++)
	// 	{
	// 		if (chans[i] == channels[n].getChanName())
	// 		{
	// 			chan_exist = 1;
	// 			if (keys[i] != channels[n].getChanKey())
	// 			{
	// 				std::cerr << "Error : wrong channel key for channel " << chans[i] << "." << std::endl;
	// 				return ;
	// 			}
	// 			if (channels[n].getInvite())
	// 			{
	// 				std::cerr << "Error : you tried to join an invite only channel : " << channels[n].getChanName() << "." << std::endl;
	// 				return ; 
	// 			}
	// 		}
	// 	}
	// 	if (!chan_exist)
	// 	{
	// 		std::cerr << "Error : no such channel as " << chans[i] << "." << std::endl;
	// 		return ;
	// 	}
	// 	i++;
	// }

	
}

void pars_part(std::string str)
{
	std::vector<std::string> chans;
	
	size_t i = 0;
	while (i < str.size() && str[i] != ' ')
	{
		if (str[i] == ',')
			i++;
		std::string chan;
		while (i < str.size() && str[i] != ' ' && str[i] != ',')
		{
			chan += str[i];
			i++;
		}
		chans.push_back(chan);
	}

	std::string message;
	if (i < str.size())
	{
		i++;
		while (i < str.size())
		{
			message += str[i];
			i++;
		}
	}

	// Lancer la commande PART //
}

void pars_topic(std::string str, Server &serv)
{
	std::string chan;
	std::string topic;

	if (str.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
	}
	
	size_t i = 0;
	while (i < str.size() && str[i] != ' ')
	{
		chan += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		topic += str[i];
		i++;
	}

	// if (topic.empty())
	// {
	// 	std::vector<Channel> channels = serv.getChannels();
	// 	for (size_t i = 0; i < channels.size(); i++)
	// 	{
	// 		if (channels[i].getChanName == chan && channels[i].getChanTopic.empty())
	// 		{
	// 			std::cerr << "Error : channel " << chan << " has no topic." << std::endl;
	// 			return ;
	// 		}
	// 	}
	// }

	// ERR_CHANOPRIVSNEEDED //           
	
	// ERR_NOCHANMODES //

	// ERR_NOTONCHANNEL //

	// Lancer la commande TOPIC //
}

void pars_invite(std::string str, Server &serv)
{
	std::string nick;
	std::string chan;

	size_t i = 0;
	while (i < str.size() && str[i] != ' ')
	{
		nick += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		chan += str[i];
		i++;
	}

	if (chan.empty())
	{
		std::cerr << "Error : need more params." << std::endl;
		return ;
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

	// ERR_NOTONCHANNEL //

	// ERR_USERONCHANNEL //

    // ERR_CHANOPRIVSNEEDED //

	// Lancer la commande INVITE //
}

void pars_kick(std::string str)
{
	 
}

void pars_quit(std::string str)
{
	// Lancer la commande QUIT //
}

void pars_mode(std::string str, Server &serv)
{
	std::string mods = "itkol";
	std::string channel;
	std::string mod;
	std::string param;
	size_t i = 0;

	while (i < str.find(" "))
	{
		channel += str[i];
		i++;
	}
	i++;
	while (i < str.size() && str[i] != ' ')
	{
		mod += str[i];
		i++;
	}
	i++;
	while (i < str.size())
	{
		param += str[i];
		i++;
	}

	if (mod.empty() || mod.size() != 2 || mod[0] != '+' || mod[0] != '-')
	{
		std::cerr << "Error with mod." << std::endl;
		return ;
	}

	if (mods.find(mod[1]) >= mods.size())
	{
		std::cerr << "Error : wrong mode. Try with i, t, k, o or l." << std::endl;
		return ;
	}

	if ((mod == "+l" || mod[1] == 'k' || mod[1] == 'o') && param.empty())
	{
		std::cerr << "Error : need more parameters." << std::endl;
		return ;
	}

	// std::vector<Channel> channels = serv.getChannels();
	// bool chan_exist = 0;
	// for (size_t i = 0; i < channels.size(); i++)
	// {
	// 	if (channel == channels[i].getChanName())
	// 		chan_exist = 1;
	// }
	// if (!chan_exist)
	// {
	// 	std::cerr << "Error : no such channel as " << channel << "." << std::endl;
	// 	return ;
	// }

	// Lancer la commande MODE //
}

void pars_privmsg(std::string str)
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
			pars_join(args, serv);
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
			pars_mode(args, serv);
			break;
		case 10:
			
			break;
		case 11:
			std::cerr << "Error, please provide one of these commands : NICK, USER, PASS, JOIN, PART, TOPIC, INVITE, KICK, QUIT, MODE or PRIVMSG" << std::endl;
			break;
	}
}