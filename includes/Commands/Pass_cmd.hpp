/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:39:55 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 14:11:19 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Pass_cmd : public ACmd {
	public:
		Pass_cmd();
		~Pass_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};