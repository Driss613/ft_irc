/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:24:55 by drabarza          #+#    #+#             */
/*   Updated: 2025/12/04 20:13:13 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class Client
{
private:
	std::string _ip;
	int _fd;
	int _rank;
	std::string username;
	std::string nickname;
	//std::vector<Channel> _channels;

public:
	Client();
	Client(const Client &cpy);
	~Client();
	Client &operator=(const Client &rhs);

	const std::string &getIp(void) const;
	int getFd(void) const;
	std::string getUsername(void) const;
	std::string getNickname(void) const;
	int getRank() const;
//	std::vector<Channel> getChannels() const;

	void setIp(const std::string &ip);
	void setFd(int fd);
	void setNickname(std::string str);
	void setUsername(std::string str);
	void setRank(int rank);
};
