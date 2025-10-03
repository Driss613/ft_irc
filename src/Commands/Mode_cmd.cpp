/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:02:00 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:19:30 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode_cmd.hpp"

Mode_cmd::Mode_cmd() {}
		
Mode_cmd::~Mode_cmd() {}

void Mode_cmd::parsing(std::string str, Server &serv, Client &main)
{
	std::string mods = "itkol";
	std::string channel;
	std::string mod;
	std::string param;
	size_t i = 0;

	while (i < str.find(' ') && i < str.size())
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

	// ERR_CHANOPRIVSNEEDED //
	
	// ERR_NOCHANMODES //

	// std::vector<Channel> main_chans = main.getChannels();
	// bool isonchan = 0;
	// for (size_t i = 0; i < main_chans.size(); i++)
	// {
	// 	if (main_chans[i].getChanName() == channel)
	// 		isonchan = 1;	
	// }
	// if (!isonchan)
	// {
	// 	std::cerr << "Error : user is not on channel " << channel << "." << std::endl;
	// 	return ;
	// }

	// Lancer la commande MODE //
}