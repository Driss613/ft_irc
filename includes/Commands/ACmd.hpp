/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:28 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 20:00:48 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Client.hpp"
#include "../Server.hpp"

class Server;
class Client;

class ACmd {
	public:
		ACmd();
		virtual ~ACmd();
		virtual void parsing(std::string str, Server &serv, Client &main) = 0;
		std::vector<std::string> buildVector(std::string str);
};