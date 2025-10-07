/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:21:17 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 12:33:20 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/Quit_cmd.hpp"

Quit_cmd::Quit_cmd() {}

Quit_cmd::~Quit_cmd() {}

void Quit_cmd::parsing(std::string str, Server &serv, Client &main)
{
	// Lancer la commande Quit //
	(void)main;
	(void)serv;
	(void)str;
}