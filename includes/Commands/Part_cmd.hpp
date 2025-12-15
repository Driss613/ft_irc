/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:34:39 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 14:11:15 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Part_cmd : public ACmd {
	public:
		Part_cmd();
		~Part_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};