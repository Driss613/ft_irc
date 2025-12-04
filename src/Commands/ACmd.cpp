/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosset <prosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:22:11 by prosset           #+#    #+#             */
/*   Updated: 2025/12/04 09:43:22 by prosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands/ACmd.hpp"

ACmd::ACmd() {}

ACmd::~ACmd() {}

std::vector<std::string> ACmd::buildVector(std::string str) {
	std::vector<std::string> chans;
	std::string chan;

	while (true)
	{
		size_t pos = str.find(',');
		if (pos == std::string::npos)
		{
			chans.push_back(str);
			return chans;
		}
		chan = str.substr(0, pos);
		chans.push_back(chan);
		str.erase(0, pos + 1);
	}
}