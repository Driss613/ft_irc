/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:20:28 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 16:22:53 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Client.hpp"
#include "../Server.hpp"

class ACmd {
	private:
		
	public:
		ACmd();
		virtual ~ACmd();
		virtual void parsing(std::string str, Server &serv, Client &main) = 0;
};