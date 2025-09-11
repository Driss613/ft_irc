/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/11 16:20:47 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class Client
{
	private :
		const std::string _ip;
		const int _fd;
	public :
		Client(const std::string& ip, const int fd);
		Client(const Client& cpy);
		~Client();
		//Client& operator=(const Client& rhs);
		const std::string&	getIp(void) const;
		int			getFd(void) const;
};
