/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass_cmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:06:49 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:23:38 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass_cmd.hpp"

Pass_cmd::Pass_cmd() {}
		
Pass_cmd::~Pass_cmd() {}

void Pass_cmd::parsing(std::string str, Server &serv, Client &main) {
	if (str == serv.getpasswd())
		;// Lancer la commande Password //
	else
		std::cerr << "Error : wrong password." << std::endl;
}