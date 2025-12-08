/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:08 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:44:26 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Quit_cmd : public ACmd {
	private:
	
	public:
		Quit_cmd();
		~Quit_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};