/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:18:46 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/15 13:04:59 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Error: Invalid arguments." << std::endl;
		return (1);
	}
	try {
		RPN rpn;
		rpn.exec(argv[1]);
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}