/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:43:35 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/18 18:34:02 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	
}

PmergeMe::~PmergeMe()
{
	
}

/* ------------------------------------------------------------- */
/*            Functions used both in vector and deque            */

template <typename T>
int binarySearch(T& list, int value)
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

/* ------------------------------------------------------------- */
/*                Functions used for std::vector                 */

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
		std::vector<int>::iterator checker = std::find(_unsortedVector.begin(), _unsortedVector.end(), value);
		if (checker != _unsortedVector.end())
			throw std::logic_error("Duplicate in list.");
		_unsortedVector.push_back(value);
		j++;	
	}
	if (_unsortedVector.size() == 1)
		throw std::logic_error("Error: single element in list.");
	std::cout << std::endl << RED << "std::vector | Before: ";
	for (std::vector<int>::iterator i = _unsortedVector.begin(); i != _unsortedVector.end(); i++) {
		std::cout << *i;
		if (i + 1 != _unsortedVector.end())
			std::cout << " ";
	}
	std::cout << NONE << std::endl;
}

void PmergeMe::sortVector(char **argv)
{
	clock_t starTime = clock();
	
	parseVector(argv);
	makeFirstPairsVector();
	makePairsVector(_firstPairsVector);
	
	if (_firstPairsVector.size() % 2 != 0)
		_sortedVector.insert(_sortedVector.begin() + binarySearch(_sortedVector, _firstPairsVector[_firstPairsVector.size() - 1].first), _firstPairsVector[_firstPairsVector.size() - 1].first);			

	for (size_t i = 0; i < _firstPairsVector.size(); i++) {
		if (_sortedVector[0] == _firstPairsVector[i].first) {
			_sortedVector.insert(_sortedVector.begin(), _firstPairsVector[i].second);
			_firstPairsVector.erase(_firstPairsVector.begin() + i);
		}
	}
	
	std::vector<int> _maxVector(_sortedVector);
	_maxVector.erase(_maxVector.begin());
	_maxVector.erase(_maxVector.begin());

 	for (size_t i = 0; i < _sortedVector.size() - 2; i++) {
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
			while (j < _firstPairsVector.size())
			{
				if (maxGroup[k] == _firstPairsVector[j].first) {
					_sortedVector.insert(_sortedVector.begin() + binarySearch(_sortedVector, _firstPairsVector[j].second), _firstPairsVector[j].second);
				}
				j++;
			}
			k++;
		}
		maxGroup.clear();
	}

	if (_unsortedVector.size() % 2 != 0)
		_sortedVector.insert(_sortedVector.begin() + binarySearch(_sortedVector, _unsortedVector.back()), _unsortedVector.back());

	std::cout << GREEN << "std::vector | After : ";
	for (std::vector<int>::iterator i = _sortedVector.begin(); i != _sortedVector.end(); i++) {
		std::cout << *i;
		if (i + 1 != _sortedVector.end())
			std::cout << " ";
	}
	std::cout << NONE << std::endl;

	clock_t endTime = clock();
	double duration = (double)(endTime - starTime) / CLOCKS_PER_SEC * 1000;

	std::cout << std::endl << BLUE << "Time to process a range of " << _unsortedVector.size() << " elements with std::vector : " << duration << " ms" << NONE << std::endl;
}

void PmergeMe::makeFirstPairsVector()
{
	int first;
	int second;

	for (size_t i = 0; i + 1 < _unsortedVector.size(); i += 2) {
			first = _unsortedVector[i];
			second = _unsortedVector[i + 1];

			if (first > second)
				_firstPairsVector.push_back(std::make_pair(first, second));
			else
				_firstPairsVector.push_back(std::make_pair(second, first));	
	}
}

void PmergeMe::makePairsVector(std::vector<std::pair<int, int> > pairs)
{
	if (pairs.size() == 1)
		return ;
	
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
		makePairsVector(new_pairs);
	}

	insertVector(new_pairs);	
}

void PmergeMe::insertVector(std::vector<std::pair<int, int> > pairs)
{
	if (_sortedVector.empty()) {
		_sortedVector.push_back(pairs[0].first);
		_sortedVector.insert(_sortedVector.begin(), pairs[0].second);
		return ;
	}

	size_t i = 0;

	while (i < pairs.size()) {
		if (pairs.size() % 2 != 0 && i == pairs.size() - 1)
			_sortedVector.insert(_sortedVector.begin() + binarySearch(_sortedVector, pairs[i].first), pairs[i].first);			
		_sortedVector.insert(_sortedVector.begin() + binarySearch(_sortedVector, pairs[i].second), pairs[i].second);
		i++;
	}
}

/* ------------------------------------------------------------- */
/*                 Functions used for std::deque                 */

void PmergeMe::parseDeque(char **argv)
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
		std::deque<int>::iterator checker = std::find(_unsortedDeque.begin(), _unsortedDeque.end(), value);
		if (checker != _unsortedDeque.end())
			throw std::logic_error("Error: Duplicate in list.");
		_unsortedDeque.push_back(value);
		j++;	
	}
	if (_unsortedDeque.size() == 1)
		throw std::logic_error("Error: single element in list.");
}

void PmergeMe::sortDeque(char **argv)
{
	clock_t starTime = clock();
	
	parseDeque(argv);
	makeFirstPairsDeque();
	makePairsDeque(_firstPairsDeque);
	
	if (_firstPairsDeque.size() % 2 != 0)
		_sortedDeque.insert(_sortedDeque.begin() + binarySearch(_sortedDeque, _firstPairsDeque[_firstPairsDeque.size() - 1].first), _firstPairsDeque[_firstPairsDeque.size() - 1].first);			

	for (size_t i = 0; i < _firstPairsDeque.size(); i++) {
		if (_sortedDeque[0] == _firstPairsDeque[i].first) {
			_sortedDeque.insert(_sortedDeque.begin(), _firstPairsDeque[i].second);
			_firstPairsDeque.erase(_firstPairsDeque.begin() + i);
		}
	}
	
	std::deque<int> _maxVector(_sortedDeque);
	_maxVector.erase(_maxVector.begin());
	_maxVector.erase(_maxVector.begin());
	
 	for (size_t i = 0; i < _sortedDeque.size() - 2; i++) {
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
			while (j < _firstPairsDeque.size())
			{
				if (maxGroup[k] == _firstPairsDeque[j].first) {
					_sortedDeque.insert(_sortedDeque.begin() + binarySearch(_sortedDeque, _firstPairsDeque[j].second), _firstPairsDeque[j].second);
				}
				j++;
			}
			k++;
		}
		maxGroup.clear();
	}
	
	if (_unsortedDeque.size() % 2 != 0)
		_sortedDeque.insert(_sortedDeque.begin() + binarySearch(_sortedDeque, _unsortedDeque.back()), _unsortedDeque.back());

	clock_t endTime = clock();
	double duration = (double)(endTime - starTime) / CLOCKS_PER_SEC * 1000;

	std::cout << BLUE << "Time to process a range of " << _unsortedDeque.size() << " elements with std::deque : " << duration << " ms" << NONE << std::endl;
}

void PmergeMe::makeFirstPairsDeque()
{
	int first;
	int second;

	for (size_t i = 0; i + 1 < _unsortedDeque.size(); i += 2) {
			first = _unsortedDeque[i];
			second = _unsortedDeque[i + 1];

			if (first > second)
				_firstPairsDeque.push_back(std::make_pair(first, second));
			else
				_firstPairsDeque.push_back(std::make_pair(second, first));	
	}
}

void PmergeMe::makePairsDeque(std::deque<std::pair<int, int> > pairs)
{
	if (pairs.size() == 1)
		return ;
	
	std::deque<std::pair<int, int> > new_pairs;

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
		makePairsDeque(new_pairs);
	}

	insertDeque(new_pairs);	
}

void PmergeMe::insertDeque(std::deque<std::pair<int, int> > pairs)
{
	if (_sortedDeque.empty()) {
		_sortedDeque.push_back(pairs[0].first);
		_sortedDeque.insert(_sortedDeque.begin(), pairs[0].second);
		return ;
	}

	size_t i = 0;

	while (i < pairs.size()) {
		if (pairs.size() % 2 != 0 && i == pairs.size() - 1)
			_sortedDeque.insert(_sortedDeque.begin() + binarySearch(_sortedDeque, pairs[i].first), pairs[i].first);			
		_sortedDeque.insert(_sortedDeque.begin() + binarySearch(_sortedDeque, pairs[i].second), pairs[i].second);
		i++;
	}
}