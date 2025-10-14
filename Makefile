# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prosset <prosset@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:25:07 by drabarza          #+#    #+#              #
#    Updated: 2025/10/14 14:58:58 by prosset          ###   ########.fr        #
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
SRC :=	src/main.cpp\
		src/Client.cpp\
		src/Server.cpp \
		src/Channel.cpp \
		src/Commands/ACmd.cpp \
		src/Commands/Manager.cpp \
		src/Commands/Nick_cmd.cpp \
		src/Commands/Join_cmd.cpp \
		src/Commands/Kick_cmd.cpp \
		src/Commands/Invite_cmd.cpp \
		src/Commands/Mode_cmd.cpp \
		src/Commands/Part_cmd.cpp \
		src/Commands/Pass_cmd.cpp \
		src/Commands/Privmsg_cmd.cpp \
		src/Commands/Quit_cmd.cpp \
		src/Commands/Topic_cmd.cpp \
		src/Commands/User_cmd.cpp
BUILD := .build
OBJ := $(SRC:src/%.cpp=$(BUILD)/%.o)
DEP := $(OBJ:.o=.d)
CURRENT_DATE = $(shell date +"%d/%m/%Y %H:%M:%S")
MAKEFLAGS += -s

all: header $(NAME)

$(NAME) : $(OBJ)
	@${CPP} ${FLAGS} $(OBJ) -o $(NAME)
	@echo "${GREEN}ircserv built successfully.${NC}"

header:
	@clear
	@echo "${GREEN}███████╗████████╗     ██╗██████╗  ██████╗"
	@echo "██╔════╝╚══██╔══╝     ██║██╔══██╗██╔════╝"
	@echo "█████╗     ██║        ██║██████╔╝██║"
	@echo "██╔══╝     ██║        ██║██╔══██╗██║"
	@echo "██║        ██║███████╗██║██║  ██║╚██████╗"
	@echo "╚═╝        ╚═╝╚══════╝╚═╝╚═╝  ╚═╝ ╚═════╝"
	@echo "Compilation in progress...${NC}"

$(BUILD)/%.o : src/%.cpp
	@mkdir -p $(@D)
	@${CPP} ${FLAGS} -MMD -MP -c $< -o $@
	@echo "${CURRENT_DATE} ${GREENS}[CMD]${NC}${GREEN} - $(basename $<)${NC}"

clean:
	@echo "${RED}Cleaning object and dep files...${NC}"
	@rm -rf ${BUILD}
	@echo "${RED}Cleaning completed.${NC}"

fclean: clean
	@rm -f ${NAME}

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re header