/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:41 by drabarza          #+#    #+#             */
/*   Updated: 2025/10/15 14:45:38 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Wrong arguments : please only specify the listening port then the connection password.");

		std::string port = av[1];
		for (size_t i = 0; i < port.length(); i++)
			if (port[i] < '0' || port[i] > '9')
				throw std::runtime_error("Error : port is not a positive number.");
		if (port.length() > 5 || port < "1024" || port > "65535")
			throw std::runtime_error("Error : port number must be between 1024 and 65535.");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	Server server;

	std::string passwd = av[2];
	server.setpasswd(passwd);
	
	std::cout << "Opening the server" << std::endl;
	try
	{
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		server.serverInit();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		server.closeFds();
	}
	std::cout << "Closing the server" << std::endl;
	return 0;
}
