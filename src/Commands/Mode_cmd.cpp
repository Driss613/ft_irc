/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:00 by prosset           #+#    #+#             */
/*   Updated: 2025/12/06 20:27:25 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Mode_cmd.hpp"

Mode_cmd::Mode_cmd() {}

Mode_cmd::~Mode_cmd() {}

void Mode_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string mods = "itkol";

	std::istringstream iss(str);

	std::string chan;
	std::string mod;
	std::string param;

	iss >> chan >> mod;
	std::getline(iss, param);
	if (!param.empty() && param[0] == ' ')
	 	param.erase(0, 1);

	if (mod.empty() || mod.size() != 2 || (mod[0] != '+' && mod[0] != '-'))
	{
		std::cerr << "Error with mod." << std::endl;
		return ;
	}

	if (mods.find(mod[1]) == std::string::npos)
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

	if (!channel->isOperator(main.getFd()))
	{
		std::cerr << "Error : you don't have operator privileges for this channel." << std::endl;
		return ;
	}

	if (!channel->isMember(main.getFd()))
	{
		std::cerr << "Error : you are not on the channel." << std::endl;
		return ;
	}

	
}