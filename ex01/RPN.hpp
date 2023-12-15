/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:15:44 by hsebille          #+#    #+#             */
/*   Updated: 2023/12/15 13:19:39 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <cstdlib>
#include <stack>

class RPN {
		private:
			std::stack<long long> _stack;
			unsigned int 	_digits;
			unsigned int	_tokens;

			RPN& operator=(const RPN& source);
			RPN(const RPN& copy);
			
		public:
			RPN();
			~RPN();

			void exec(std::string arg);
			void verify_arg(std::string arg);
};


#endif