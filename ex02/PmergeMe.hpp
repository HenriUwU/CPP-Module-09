/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:49:05 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/16 18:54:08 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>

class PmergeMe {
		private:
			std::vector<int> _unsorted;
			std::vector<int> _sorted;
			std::vector<std::pair<int, int> > _firstPairs;

			PmergeMe();
			PmergeMe& operator=(const PmergeMe& source);
			PmergeMe(const PmergeMe& copy);

		public:
			PmergeMe(char **argv);
			~PmergeMe();

			void parseVector(char **argv);
			void sortVector();
			void makeFirstPairs();
			void make_pairs(std::vector<std::pair<int, int> > pairs);
			void insert(std::vector<std::pair<int, int> > pairs);
};


#endif