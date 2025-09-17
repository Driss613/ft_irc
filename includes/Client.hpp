/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/16 14:59:07 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class Client
{
	private :
		std::string _ip;
		int _fd;
		std::string username;
		std::string nickname;
	public :
		Client();
		Client(const Client& cpy);
		~Client();
		//Client& operator=(const Client& rhs);
		const std::string&	getIp(void) const;
		int					getFd(void) const;
		std::string			getUsername(void) const;
		std::string			getNickname(void) const;
		void				setIp(const std::string& ip);
		void				setFd(int fd);
		void				setNickname(std::string str);
		void				setUsername(std::string str);
};
