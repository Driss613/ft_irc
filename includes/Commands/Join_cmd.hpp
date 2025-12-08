/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:37:23 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:37:38 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Join_cmd : public ACmd {
	private:
	
	public:
		Join_cmd();
		~Join_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};