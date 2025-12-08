/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:38:41 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:38:58 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class User_cmd : public ACmd {
	private:
	
	public:
		User_cmd();
		~User_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};