# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 18:31:08 by hsebille          #+#    #+#              #
#    Updated: 2023/12/15 14:11:03 by hsebille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	PmergeMe

#-------------------------------#
#          INGREDIENTS          #
#-------------------------------#

SRC				:=	main.cpp			\

SRC_OBJS		:=	$(SRC:%.cpp=.build/%.o)
DEPS			:=	$(SRC_OBJS:%.o=%.d)

CC				:=	c++
CFLAGS			:=	-Wall -Wextra -Werror -std=c++98 -Iinclude -g3


#----------------------------#
#          UTENSILS          #
#----------------------------#

MAKEFLAGS		+= --silent --no-print-directory

#---------------------------#
#          RECIPES          #
#---------------------------#

all: $(NAME)

$(NAME): $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $(NAME)
	$(info CREATED $(NAME))

.build/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	$(info CREATED $@)

-include $(DEPS)

clean:
	rm -rf .build

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------#
#          SPEC          #
#------------------------#

.PHONY: all clean fclean re
.DELETE_ON_ERROR: