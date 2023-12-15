/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:43:35 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/15 21:51:05 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **argv)
{
	parseVector(argv);
}

PmergeMe::~PmergeMe()
{
	
}

void PmergeMe::sortVector()
{
	makeFirstPairs();
}

void PmergeMe::parseVector(char **argv)
{
	long long int value;
	unsigned long i;
	unsigned long j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i]) {
			if (!isdigit(argv[j][i]))
				throw std::logic_error("Error: invalid argument.");
			i++;
		}
		value = std::atoi(argv[j]);
		if (value < 0 || value > std::numeric_limits<int>::max())
			throw std::logic_error("Error: int overflow.");
		_unsorted.push_back(value);
		j++;	
	}
	std::cout << "Before: ";
	for (std::vector<int>::iterator i = _unsorted.begin(); i != _unsorted.end(); i++) {
		std::cout << *i;
		if (i + 1 != _unsorted.end())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::makeFirstPairs()
{
	int first;
	int second;

	for (unsigned long int i = 0; i < _unsorted.size(); i += 2) {
			first = _unsorted[i];
			second = _unsorted[i + 1];

			if (first > second)
				_firstPairs.push_back(std::make_pair(first, second));
			else
				_firstPairs.push_back(std::make_pair(second, first));	
	}
	for (std::vector<std::pair<int, int> >::iterator i = _firstPairs.begin(); i != _firstPairs.end(); i++) {
		std::cout << i->first << " | " << i->second << std::endl;
	}
}

/* std::vector<std::pair<int, int> > make_pairs(std::vector<std::pair<int, int> > _unsorted)
{
	
	make_pairs()
	if (_unsorted.size() == 1)
		return ;
} */