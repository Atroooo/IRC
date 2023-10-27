.PHONY:        fclean all clear re

NAME            =	ircserv

CMP             =   c++
FLAG            =   -Wall -Wextra -Werror -std=c++98 -g3
RM              =   rm -rf
BUILD_DIR       =   build/

HEADER_DIR      =   header
HEADER_FILE     =	includes typedef Channel Commands Client Server serverUtils
INC             =   $(addsuffix .hpp, $(addprefix $(HEADER_DIR)/, $(HEADER_FILE)))

SRC_DIR         =   src
SRC_FILE        =   main \
					parsingArgument/parsingArgument \
					setUpSocket/setUpSocket \
					serverLoop/serverLoop \
					serverLoop/checkClient \
					serverLoop/checkServer \
					serverLoop/checkPassword \
					serverLoop/bot \
					class/Channel \
					class/Client \
					class/Server \
					commands/Commands \
					commands/join \
					commands/kick \
					commands/leave \
					commands/mode \
					commands/topic \
					commands/invite \
					commands/sendMessage \

SRC             =   $(addsuffix .cpp, $(addprefix $(SRC_DIR)/, $(SRC_FILE)))

OBJS            =   $(SRC:%.cpp=$(BUILD_DIR)%.o)

$(BUILD_DIR)%.o:	%.cpp $(INC)
					@mkdir -p $(@D)
					@$(CMP) $(FLAG) -I$(HEADER_DIR) -c $< -o $@

all:        		clear $(NAME)

$(NAME):    		$(INC) $(OBJS)
					@$(CMP) $(FLAG) $(OBJS) -I$(HEADER_DIR) -o $(NAME)
					@echo "\033[32m-- $(NAME) compile and create --\033[0m"

clear:
					clear

fclean:
					$(RM) $(NAME)
					$(RM) $(BUILD_DIR)

re:         		fclean all