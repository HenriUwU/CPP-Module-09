/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:18:06 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/15 14:04:30 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _digits(0), _tokens(0)
{
	
}

RPN::~RPN()
{
	
}

bool isToken(char c)
{
	if (c != '+' && c != '-' && c != '/' && c != '*')
		return (false);
	return (true);
}

void RPN::exec(std::string arg)
{
	verify_arg(arg);
	int first;
	int second;

	unsigned long i = 0;

	while (i < arg.size())
	{
		if (isdigit(arg[i]))
		{
			_stack.push(std::atoi(&arg[i]));
			i++;
		}
		if (isToken(arg[i]) && _stack.size() > 1)
		{
			first = _stack.top();
			_stack.pop();
			second = _stack.top();
			_stack.pop();
			
			if (arg[i] == '+')
				_stack.push(second + first);
			if (arg[i] == '-')
				_stack.push(second - first);
			if (arg[i] == '/') {
				if (first == 0)
					throw std::logic_error("Error: division by zero");
				_stack.push(second / first);
			}
			if (arg[i] == '*')
				_stack.push(second * first);
		}
		else if (isToken(arg[i]) && _stack.size() < 2)
			throw std::logic_error("Error: token logical problem.");
		i++;
	}
	std::cout << _stack.top() << std::endl;
}

void RPN::verify_arg(std::string arg)
{
	if (arg.size() < 5 || !isdigit(arg[0]) || !isdigit(arg[2]) || !isToken(arg[arg.size() - 1]))
		throw std::logic_error("Error: non logical argument.");

 	for (unsigned long i = 0; i < arg.size(); i++) {
		if (!isdigit(arg[i]) && !isToken(arg[i]) && arg[i] != ' ')
			throw std::logic_error("Error: forbidden argument (invalid character).");
		if (arg[i] == ' ' && arg[i + 1] == ' ')
			throw std::logic_error("Error: forbidden argument (too many spaces).");
		if (isToken(arg[i]) && isToken(arg[i + 1]))
			throw std::logic_error("Error: forbidden argument (too many tokens)");
		if (isToken(arg[i]))
			_tokens++;
	}

	unsigned long i = 0;

	while (i < arg.size())
	{
		if (isdigit(arg[i]))
		{
			if (isdigit(arg[i + 1]))
				throw std::logic_error("Error: too large a number");
			_digits++;
			i++;
		}
		i++;
	}

	if (_tokens < _digits - 1)
		throw std::logic_error("Error: not enough tokens.");
	if (_tokens > _digits - 1)
		throw std::logic_error("Error: too many tokens.");
}