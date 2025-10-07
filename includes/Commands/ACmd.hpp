/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:28 by prosset           #+#    #+#             */
/*   Updated: 2025/10/07 11:37:43 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Client.hpp"
#include "../Server.hpp"

class Server;

class ACmd
{
private:
public:
	ACmd();
	virtual ~ACmd();
	virtual void parsing(std::string str, Server &serv, Client &main) = 0;
};