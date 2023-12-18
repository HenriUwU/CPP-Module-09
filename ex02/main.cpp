/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:59:04 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/18 18:28:37 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << "Error: not enough argument." << std::endl;
		return (1);
	}
	try {
		PmergeMe sort;
		sort.sortVector(argv);
		sort.sortDeque(argv);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);	
}