/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite_cmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:46:40 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:47:11 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Invite_cmd : public ACmd {
	private:
	
	public:
		Invite_cmd();
		~Invite_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};