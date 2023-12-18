/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:05 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/18 15:22:20 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <limits>
#include <ctime>

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define BLUE	"\033[34m"
#define NONE	"\033[0m"

class PmergeMe {
		private:
			std::vector<int> _unsorted;
			std::vector<int> _sorted;
			std::vector<std::pair<int, int> > _firstPairs;

			PmergeMe& operator=(const PmergeMe& source);
			PmergeMe(const PmergeMe& copy);

		public:
			PmergeMe();
			~PmergeMe();

			void parseVector(char **argv);
			void sortVector(char **argv);
			void makeFirstPairs();
			void make_pairs(std::vector<std::pair<int, int> > pairs);
			void insert(std::vector<std::pair<int, int> > pairs);
};


#endif