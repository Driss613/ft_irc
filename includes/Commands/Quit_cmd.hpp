/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:08 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 14:11:24 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Quit_cmd : public ACmd {
	public:
		Quit_cmd();
		~Quit_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};