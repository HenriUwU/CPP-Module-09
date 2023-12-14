/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:18:46 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/14 17:01:29 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	try {
		BitcoinExchange btc;
		btc.search(argv[1]);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
}