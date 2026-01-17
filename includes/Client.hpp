/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/12/15 14:37:32 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "Channel.hpp"

class Channel;

class Client
{
	private :
		std::string _ip;
		int _fd;
		int _rank;
		std::string username;
		std::string nickname;
		std::vector<Channel> _channels;
		std::string _buffer;
	public :
		Client();
		Client(const Client& cpy);
		~Client();
		Client& operator=(const Client& rhs);
		
		const std::string&	getIp(void) const;
		int					getFd(void) const;
		std::string			getUsername(void) const;
		std::string			getNickname(void) const;
		int					getRank() const;
		std::vector<Channel> getChannels() const;
		
		void				setIp(const std::string& ip);
		void				setFd(int fd);
		void				setNickname(std::string str);
		void				setUsername(std::string str);
		void				setRank(int rank);

		std::string			getBuffer() const;
		std::string&		getBufferRef();
		void				appendToBuffer(const std::string& data);
		void				clearBuffer();

		void				joinChannel(Channel &chan);
		void				removeChannel(Channel &chan);
};
