/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg_cmd.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:41:59 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:42:11 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Privmsg_cmd : public ACmd {
	private:
	
	public:
		Privmsg_cmd();
		~Privmsg_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};