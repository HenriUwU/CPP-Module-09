/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:05 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/18 16:35:51 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>
#include <deque>
#include <ctime>

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define BLUE	"\033[34m"
#define NONE	"\033[0m"

class PmergeMe {
		private:
			std::vector<int> _unsortedVector;
			std::vector<int> _sortedVector;
			std::vector<std::pair<int, int> > _firstPairsVector;

			std::deque<int> _unsortedDeque;
			std::deque<int> _sortedDeque;
			std::deque<std::pair<int, int> > _firstPairsDeque;

			PmergeMe& operator=(const PmergeMe& source);
			PmergeMe(const PmergeMe& copy);

		public:
			PmergeMe();
			~PmergeMe();

			void parseVector(char **argv);
			void parseDeque(char **argv);
			
			void sortVector(char **argv);
			void sortDeque(char **argv);
			
			void makeFirstPairsVector();
			void makeFirstPairsDeque();
			
			void makePairsVector(std::vector<std::pair<int, int> > pairs);
			void makePairsDeque(std::deque<std::pair<int, int> > pairs);
			
			void insertVector(std::vector<std::pair<int, int> > pairs);
			void insertDeque(std::deque<std::pair<int, int> > pairs);
};


#endif