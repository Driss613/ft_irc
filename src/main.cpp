/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:41 by drabarza          #+#    #+#             */
/*   Updated: 2025/09/12 19:04:49 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int main(void)
{
	Server server;
	std::cout << "Opening the server" << std::endl;
	try
	{
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		server.serverInit();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		server.closeFds();
	}
	std::cout << "Closing the server" << std::endl;
	return 0;
}
