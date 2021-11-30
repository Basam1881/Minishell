
PURPLE = \033[1;35m
BLUE   = \033[1;34m
WHITE   = \033[1;37m
LIGHT_BLUE  = \033[1;36m
GREEN    = \033[1;32m
RED = \033[1;31m
BYELLOW  = \033[1;33m
IYELLOW  = \033[3;33m
NO_COLOR    = \033[m

#TESTER_COMMAND = #write the command you want to run the tester you have

#Mention the Authors names over here
AUTHORS = Bassam aNd MUTASEM 

#mention the Team name here
TEAM_NAME =  $(BLUE)٩◔̯◔۶$(GREEN) 𝕭 𝕹 𝕸  $(BLUE)ఠ ͟ಠ$(GREEN)

#mention the project name here
PROJECT_NAME = MINISHELL

#write down the date you started working on your project
DATE = 29 - 11 - 2021

C_FILES = main.c cmd_checker.c

#These are the .c files for your project
SRC_NAME =  $(addprefix $(SRC_DIR), $(C_FILES))

#These are the .o files that will be created for your project
OBJ_NAME = $(addprefix $(OBJ_DIR), ${C_FILES:%.c=%.o})

#mention the compilation flags here
CFLAG = -Wall -Wextra -Werror

#Here is the libft directory
LIBFT_DIR = ./libft/

#Here is the libft library
LIBFT_LIB = libft.a

#Here are all the libraries you have created
LIBS = $(addprefix $(LIBS_DIR), *.a)

#Here is the the source directory for .c files of your project
SRC_DIR = ./src/

#Here is the the objects directory for .c files of your project
OBJ_DIR = ./objs/

#Here is the headers directory
HEADERS_DIR = ./includes/

#Here is the libraries directory
LIBS_DIR = ./libraries/

#Here is the temporary library that will be created from the source files
NAME = ft_minishell.a

#Here is the final library that contains all the objects files needed for this project
NAME_ALL = minishell.a

#Here is the name of the executable file
EXEC_NAME = minishell

all: header $(LIBS_DIR)${NAME} ${LIBFT_LIB} $(LIBS_DIR)${NAME_ALL}
	@gcc $(LIBS_DIR)$(NAME_ALL) -lreadline -o $(EXEC_NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)Compilation Is Done\n"
	@echo "$(GREEN)*************************************************************************"
	@echo "$(GREEN)*\t\t\t\t$(BYELLOW)READY\t\t\t\t\t$(GREEN)*"
	@echo "$(GREEN)*************************************************************************"

${LIBS_DIR}${NAME} : $(OBJ_NAME)
	@ar -rc ${LIBS_DIR}$(NAME) $(OBJ_NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)MINISHELL Is Done\n"

${LIBFT_LIB}:
	@$(MAKE) -C $(LIBFT_DIR) all && mv $(LIBFT_DIR)$(LIBFT_LIB) $(LIBS_DIR)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)LIBFT Is Done\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@gcc ${CFLAG} -c $< -o $@

$(LIBS_DIR)${NAME_ALL} :
	@libtool -static -o $(LIBS_DIR)$(NAME_ALL) $(LIBS_DIR)$(NAME) $(LIBS_DIR)$(LIBFT_LIB)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)Final Library Is Done\n"

header:
	@printf "\n%b" "$(PURPLE)"
	@echo
	@echo "\t██████╗     ███╗   ██╗    ███╗   ███╗"
	@echo "\t██╔══██╗    ████╗  ██║    ████╗ ████║"
	@echo "\t██████╔╝    ██╔██╗ ██║    ██╔████╔██║"
	@echo "\t██╔══██╗    ██║╚██╗██║    ██║╚██╔╝██║"
	@echo "\t██████╔╝    ██║ ╚████║    ██║ ╚═╝ ██║"
	@echo "\t╚═════╝     ╚═╝  ╚═══╝    ╚═╝     ╚═╝"
	@echo
	@printf "\n%b" "$(GREEN)"
	@echo "\t\t              o    o"
	@echo "\t\t   _$(WHITE)MINISHELL$(GREEN)_ )  ("
	@echo "\t\t{(((((((((((( ( o_o)"
	@echo "\t\t  /\/\/\/\/\/\ \`--"
	@echo
	@printf "\t$(LIGHT_BLUE)AUTHORS\t\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)TEAM NAME\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)NAME\t\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)DATE\t\t:\t$(GREEN)%b\n\n" "$(AUTHORS)" "$(TEAM_NAME)" "$(PROJECT_NAME)" "$(DATE)"
	@echo "\t$(BYELLOW)LOADING...$(RED)\n"
	@mkdir -p $(HEADERS_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIBS_DIR)
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_NAME) $(OBJ_DIR)

fclean: clean
	@rm -rf $(LIBS_DIR) $(EXEC_NAME)

re: fclean all

test:
	$(TESTER_COMMAND)

.PHONY: all clean fclean re