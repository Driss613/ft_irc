/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:06:49 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 12:32:59 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Pass_cmd.hpp"

Pass_cmd::Pass_cmd() {}

Pass_cmd::~Pass_cmd() {}

void Pass_cmd::parsing(std::string str, Server &serv, Client &main)
{
	if (str == serv.getpasswd())
		; // Lancer la commande Password //
	else
		std::cerr << "Error : wrong password." << std::endl;

	(void)main;
	(void)serv;
}