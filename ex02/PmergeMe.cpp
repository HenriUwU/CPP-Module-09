/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:43:35 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/18 15:42:12 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	
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

unsigned long long jacobStahl(unsigned long long pos)
{
	if (pos == 0 || pos == 1)
		return (2);
	
	unsigned long long i = 1;
	unsigned long long current = 2;
	unsigned long long prev = 2;
	unsigned long long antePrev = 2;

	while (i < pos)
	{
		antePrev = prev;
		prev = current;
		current = prev + (antePrev * 2);
		i++;
	}
	return (current);
}

void PmergeMe::sortVector(char **argv)
{
	clock_t _starTime = clock();
	
	parseVector(argv);
	makeFirstPairs();
	make_pairs(_firstPairs);
	
	if (_firstPairs.size() % 2 != 0)
		_sorted.insert(_sorted.begin() + binarySearch(_sorted, _firstPairs[_firstPairs.size() - 1].first), _firstPairs[_firstPairs.size() - 1].first);			

	// Insert the minimum of the smallest maximum
	for (size_t i = 0; i < _firstPairs.size(); i++) {
		if (_sorted[0] == _firstPairs[i].first) {
			_sorted.insert(_sorted.begin(), _firstPairs[i].second);
			_firstPairs.erase(_firstPairs.begin() + i);
		}
	}
	
	// Insert each minimum

	// make groups of pairs according to jacobstahl
	// insert the minimum 
	std::vector<int> _maxVector(_sorted);
	_maxVector.erase(_maxVector.begin());
	_maxVector.erase(_maxVector.begin());
	
 	for (size_t i = 0; i < _sorted.size() - 2; i++) {
		size_t size = jacobStahl(i);
		std::vector<int> maxGroup;
		
		if (size > _maxVector.size())
			size = _maxVector.size();

		maxGroup.insert(maxGroup.begin(), _maxVector.begin(), _maxVector.begin() + size);
		_maxVector.erase(_maxVector.begin(), _maxVector.begin() + size);
		std::reverse(maxGroup.begin(), maxGroup.end());

		size_t k = 0;
		
		while (k < maxGroup.size())
		{
			size_t j = 0;
			while (j < _firstPairs.size())
			{
				if (maxGroup[k] == _firstPairs[j].first) {
					_sorted.insert(_sorted.begin() + binarySearch(_sorted, _firstPairs[j].second), _firstPairs[j].second);
				}
				j++;
			}
			k++;
		}

		maxGroup.clear();
	}
 
	//insert(_firstPairs);
	
	std::cout << GREEN << "std::vector | After : ";
	for (std::vector<int>::iterator i = _sorted.begin(); i != _sorted.end(); i++) {
		std::cout << *i;
		if (i + 1 != _sorted.end())
			std::cout << " ";
	}
	std::cout << NONE << std::endl;

	clock_t endTime = clock();
	double duration = (double)(endTime - _starTime) / CLOCKS_PER_SEC * 1000;

	std::cout << std::endl << BLUE << "Time to process a range of " << _unsorted.size() << " elements with std::vector : " << duration << " us" << NONE << std::endl;
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
	std::cout << std::endl << RED << "std::vector | Before: ";
	for (std::vector<int>::iterator i = _unsorted.begin(); i != _unsorted.end(); i++) {
		std::cout << *i;
		if (i + 1 != _unsorted.end())
			std::cout << " ";
	}
	std::cout << NONE << std::endl;
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
	if (_sorted.empty()) {
		_sorted.push_back(pairs[0].first);
		_sorted.insert(_sorted.begin(), pairs[0].second);
		return ;
	}

	size_t i = 0;

	while (i < pairs.size()) {
		if (pairs.size() % 2 != 0 && i == pairs.size() - 1)
			_sorted.insert(_sorted.begin() + binarySearch(_sorted, pairs[i].first), pairs[i].first);			
		_sorted.insert(_sorted.begin() + binarySearch(_sorted, pairs[i].second), pairs[i].second);
		i++;
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
    }

	if (new_pairs.size() != 1) {
		make_pairs(new_pairs);
	}

	insert(new_pairs);	
}