/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic_cmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:40:41 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 14:11:26 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Topic_cmd : public ACmd {
	public:
		Topic_cmd();
		~Topic_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};