/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:00 by prosset           #+#    #+#             */
/*   Updated: 2025/10/14 15:30:08 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Mode_cmd.hpp"
#include "../../includes/Server.hpp"

Mode_cmd::Mode_cmd() {}
		
Mode_cmd::~Mode_cmd() {}

void Mode_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string mods = "itkol";
	std::string chan;
	std::string mod;
	std::string param;
	size_t i = 0;

	while (i < str.find(' ') && i < str.size())
	{
		chan += str[i];
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

	if (mod.empty() || mod.size() != 2 || (mod[0] != '+' && mod[0] != '-'))
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

	Channel *channel = serv.getChannel(chan);
	if (!channel)
	{
		std::cerr << "Error : no such channel as " << channel << "." << std::endl;
		return ;	
	}

	// ERR_CHANOPRIVSNEEDED //
	
	// ERR_NOCHANMODES //

	if (!channel->isMember(main.getFd()))
	{
		std::cerr << "Error : you are not on the channel." << std::endl;
		return ;
	}

	// Lancer la commande MODE //
}