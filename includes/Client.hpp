/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/13 14:16:15 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class Client
{
	private :
		std::string _ip;
		int _fd;
	public :
		Client();
		Client(const Client& cpy);
		~Client();
		//Client& operator=(const Client& rhs);
		const std::string&	getIp(void) const;
		int					getFd(void) const;
		void				setIp(const std::string& ip);
		void				setFd(int fd);
};
