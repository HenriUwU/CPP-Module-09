/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:13:04 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/14 17:03:22 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream database;
	std::string dbLine;
	std::string date;
	std::string strValue;
	double		value;
	
	database.open("data.csv");
	if (!database.is_open() || database.peek() == EOF)
		throw std::logic_error("Error: could not open database.");
	
	getline(database, dbLine);
	if (database.eof() || dbLine != "date,exchange_rate")
		throw std::logic_error("Error: invalid database.");
	
	while (!database.eof())
	{
		getline(database, dbLine);
		size_t delim = dbLine.find(',');
		if (delim != std::string::npos && dbLine.size() > 0)
		{
			date = dbLine.substr(0, delim);
			strValue = dbLine.substr(delim + 1, dbLine.size());
			value = std::atof(strValue.c_str());
			if (strValue[0] != '0' && value == 0)
				throw std::logic_error("Error: invalid value in database.");
		}
		if (dbLine.size() > 0 && (delim == std::string::npos || !verify_date(date))) {
			throw std::logic_error("Error: invalid database.");
		}
		_database[date]=value;
	}
	database.close();
}

BitcoinExchange::~BitcoinExchange()
{
	
}

void BitcoinExchange::search(std::string file)
{
	std::ifstream infile;
	regex_t regex;
	std::string line;
	std::string date;
	std::string strValue;
	double value;

	infile.open(file.c_str());
	if (!infile.is_open() || infile.peek() == EOF)
		throw std::logic_error("Error: could not open file.");

	getline(infile, line);
	if (infile.eof() || line != "date | value") {
		std::cout << line;
		throw std::logic_error("Invalid file format");
	}
	
	regcomp(&regex, "^[0-9]{0,}-[0-9]{2}-[0-9]{2} \\| (-?[0-9]+|[0-9]+\\.[0-9]+)$", REG_EXTENDED);
	while (!infile.eof())
	{
		getline(infile, line);
		if (regexec(&regex, line.c_str(), 0, NULL, 0) != 0) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		size_t delim = line.find('|');
		if (delim != std::string::npos && line.size() > 0)
		{
			date = line.substr(0, delim - 1);
			if (!verify_date(date)) {
				std::cout << "Error: invalid date." << std::endl;
				continue;
			}
			strValue = line.substr(delim + 1, line.size());
			value = std::atof(strValue.c_str());
			if (value < 0) {
				std::cout << "Error: not a positive number." << std::endl;
				continue;
			}
			else if (value > 1000) {
				std::cout << "Error: too large a number." << std::endl;
				continue;
			}
			std::map<std::string, double>::iterator iterator = _database.find(date);
			if (iterator == _database.end()) {
				iterator = _database.lower_bound(date);
				if (iterator != _database.begin())
					--iterator;
			}
			std::cout << date << " => " << value << " = " << value * iterator->second << std::endl;
		}
	}
	infile.close();
	regfree(&regex);
}

bool verify_date(std::string date)
{
	int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	regex_t regex;
	int year;
	int month;
	int day;
	
 	regcomp(&regex, "^[[:digit:]]{0,}-[[:digit:]]{2}-[[:digit:]]{2}$", REG_EXTENDED);
	if (regexec(&regex, date.c_str(), 0, NULL, 0) != 0) {
		regfree(&regex);
		return (false);
	}

	size_t first = date.find('-');
	size_t second = date.find_last_of('-');

	year = std::atoi(date.substr(0, first).c_str());
	month = std::atoi(date.substr(first + 1, second - (first + 1)).c_str());
	day = std::atoi(date.substr(second + 1).c_str());

	regfree(&regex);

	if (year < 0 || month > 12)
		return (false);
	if (year % 4 == 0 && day == 29 && month == 2)
		return (true);
	if (day > days[month])
		return (false);


	return (true);
}