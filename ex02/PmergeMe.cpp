/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:43:35 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/16 19:49:38 by hsebille         ###   ########.fr       */
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

int binarySearch(std::vector<int> list, int value)
{
    size_t low = 0;
    size_t high = list.size();

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (list[mid] == value)
            return mid;

        if (list[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    return static_cast<int>(low);
}

void PmergeMe::sortVector()
{
	std::vector<std::pair<int, int> > _newPairs;

	makeFirstPairs();
	make_pairs(_firstPairs);
	
	std::cout << "After : ";
	for (std::vector<int>::iterator i = _sorted.begin(); i != _sorted.end(); i++) {
		std::cout << *i;
		if (i + 1 != _sorted.end())
			std::cout << " ";
	}
	std::cout << std::endl;
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
}

void PmergeMe::insert(std::vector<std::pair<int, int> > pairs)
{
	if (_sorted.empty())
		_sorted.push_back(pairs[0].first);
	if (_sorted.size() == 1) {
		_sorted.insert(_sorted.begin(), pairs[0].second);
		return ;
	}
}

void PmergeMe::make_pairs(std::vector<std::pair<int, int> > pairs)
{
	std::vector<std::pair<int, int> > new_pairs;

    for (size_t i = 0; i < pairs.size(); i += 2) {
        std::pair<int, int> pair1 = pairs[i];
        std::pair<int, int> pair2;

        if (i + 1 < pairs.size()) {
            pair2 = pairs[i + 1];

            if (pair1.first > pair2.first)
                new_pairs.push_back(std::make_pair(pair1.first, pair2.first));
            else
                new_pairs.push_back(std::make_pair(pair2.first, pair1.first));
        }
		else
            new_pairs.push_back(pair1);
    }
		
	if (new_pairs.size() > 1) {
    	make_pairs(new_pairs);
	}

	insert(new_pairs);

	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it) {
    	int insertPosition = binarySearch(_sorted, it->second);
    	_sorted.insert(_sorted.begin() + insertPosition, it->second);
	}
}