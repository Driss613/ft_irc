/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode_cmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:41:09 by prosset           #+#    #+#             */
/*   Updated: 2025/10/03 11:41:21 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ACmd.hpp"

class Mode_cmd : public ACmd {
	private:
	
	public:
		Mode_cmd();
		~Mode_cmd();
		void parsing(std::string str, Server &serv, Client &main);
};