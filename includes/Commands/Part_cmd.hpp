/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:34:39 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:37:07 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Part_cmd : public ACmd {
	private:
	
	public:
		Part_cmd();
		~Part_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};