/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:36:35 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 14:11:03 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Kick_cmd : public ACmd {
	public:
		Kick_cmd();
		~Kick_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};