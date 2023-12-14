/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:09:57 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/14 16:57:21 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <regex.h>

class BitcoinExchange {
		private:
			std::map<std::string, double> _database;

			BitcoinExchange& operator=(const BitcoinExchange& source);
			BitcoinExchange(const BitcoinExchange& copy);

		public:
			BitcoinExchange();
			~BitcoinExchange();

			
			void search(std::string file);
};

bool verify_date(std::string date);

#endif