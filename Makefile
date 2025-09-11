# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drabarza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:25:07 by drabarza          #+#    #+#              #
#    Updated: 2025/09/11 18:10:58 by drabarza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN := \033[3;32m
GREENS := \033[7;32m
YELLOW := \033[3;33m
RED := \033[3;31m
NC := \033[0m

NAME := ircserv
CPP := c++
FLAGS := -Wall -Werror -Wextra -std=c++98
SRC :=	src/main\
		src/Client.cpp\
		src/Server.cpp
OBJ := $(SRC:.cpp=.o)
CURRENT_DATE = $(shell date +"%d/%m/%Y %H:%M:%S")
MAKEFLAGS += -s

all: header $(NAME)

$(NAME) : $(OBJ)
	@${CPP} ${FLAGS} $(OBJ) -o $(NAME)

header:
	@clear
	@echo "${GREEN}███████╗████████╗     ██╗██████╗  ██████╗"
	@echo "██╔════╝╚══██╔══╝     ██║██╔══██╗██╔════╝"
	@echo "█████╗     ██║        ██║██████╔╝██║"
	@echo "██╔══╝     ██║        ██║██╔══██╗██║"
	@echo "██║        ██║███████╗██║██║  ██║╚██████╗"
	@echo "╚═╝        ╚═╝╚══════╝╚═╝╚═╝  ╚═╝ ╚═════╝"
	@echo "Compilation in progress...${NC}"

%.o : %.cpp
	@${CPP} ${FLAGS} -c $< -o $@
	@echo "${CURRENT_DATE} ${GREENS}[CMD]${NC}${GREEN} - $(basename $<)${NC}"

clean:
	@echo "${RED}Cleaning object files...${NC}"
	@rm -f ${OBJ}
	@echo "${RED}Cleaning completed.${NC}"

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re header