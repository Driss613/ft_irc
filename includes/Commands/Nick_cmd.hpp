/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:39:20 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 13:37:58 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Nick_cmd : public ACmd {
	public:
		Nick_cmd();
		~Nick_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};