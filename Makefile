
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
AUTHORS = Bassam aNd Moatasem 

#mention the Team name here
TEAM_NAME =  $(BLUE)ᕙ(🔥 ︹ ́🔥)ᕗ$(GREEN) 𝐁 𝐍 𝐌  $(BLUE)(ง ͡▀̿ ̿  ͟ʖ͡▀̿ ̿  )ง$(GREEN)

#mention the project name here
PROJECT_NAME = MINISHELL

#write down the date you started working on your project
DATE = 29 - 11 - 2021

C_FILES = main.c exit.c cmd_checker.c env_controller.c\
		ft_export.c ft_unset.c shellsplit.c the_ultimate_split.c\
		operators.c sig_handler.c cmd_filter.c ft_exit.c\
		initialize.c wild_card.c ft_wild_split.c check_operators.c \
		pipes.c redirections.c parenthesis.c and_or_ops.c ft_env.c \
		ft_cd.c ft_echo.c ft_pwd.c ft_env.c expand_exit_status.c \
		get_expand_value.c failed_malloc.c w_zero_flag.c is_op.c \
		shell_split_helper.c create_sep_cmd.c assign_q_and_star_arrays.c\
		cmd_checker_utils.c redirections_utils.c ft_export_utils.c \
		wild_card_utils.c expand_wild_card.c ft_cmdcmp.c assigning_ops.c\
		errors.c

B_FILES = main_bonus.c exit_bonus.c cmd_checker_bonus.c env_controller.c\
		ft_export_bonus.c ft_unset_bonus.c shellsplit_bonus.c the_ultimate_split_bonus.c\
		operators_bonus.c sig_handler_bonus.c cmd_filter_bonus.c ft_exit_bonus.c\
		initialize_bonus.c wild_card_bonus.c ft_wild_split_bonus.c check_operators_bonus.c \
		pipes_bonus.c redirections_bonus.c parenthesis_bonus.c and_or_ops_bonus.c ft_env_bonus.c \
		ft_cd_bonus.c ft_echo_bonus.c ft_pwd_bonus.c ft_env_bonus.c expand_exit_status_bonus.c \
		get_expand_value_bonus.c failed_malloc_bonus.c w_zero_flag_bonus.c is_op_bonus.c \
		shell_split_helper_bonus.c create_sep_cmd_bonus.c assign_q_and_star_arrays_bonus.c\
		cmd_checker_utils_bonus.c redirections_utils_bonus.c ft_export_utils_bonus.c \
		wild_card_utils_bonus.c expand_wild_card_bonus.c ft_cmdcmp_bonus.c assigning_ops_bonus.c\
		errors_bonus.c

#These are the .c files for your project
SRC_NAME =  $(addprefix $(SRC_DIR), $(C_FILES))

#These are the .o files that will be created for your project
OBJ_NAME = $(addprefix $(OBJ_DIR), ${C_FILES:%.c=%.o})

#These are the .c files for your project
BONUS_NAME =  $(addprefix $(B_DIR), $(BONUS_FILES))

#These are the .o files that will be created for your project
B_OBJ_NAME = $(addprefix $(OBJ_DIR), ${B_FILES:%.c=%.o})

#mention the compilation flags here
CFLAG = -Wall -Wextra -Werror

#Here is the libft directory
LIBFT_DIR = ./libft/

#Here is the libft library
LIBFT_LIB = libft.a

#Here are all the libraries you have created
LIBS = $(addprefix $(LIBS_DIR), *.a)

#Here is the gnl directory
GNL_DIR = ./gnl/

#Here is the gnl library
GNL_LIB = gnl.a

#Here is the the source directory for .c files of your project
SRC_DIR = ./src/

#Here is the the bonus directory for .c files of your project
B_DIR = ./bonus/

#Here is the the objects directory for .c files of your project
OBJ_DIR = ./objs/

#Here is the headers directory
HEADERS_DIR = ./includes/

#Here is the libraries directory
LIBS_DIR = ./libraries/

#Here is the temporary library that will be created from the source files
NAME = minishell.a

B_NAME = b_minishell.a

#Here is the final library that contains all the objects files needed for this project
ALL_LIBS = $(LIBS_DIR)$(NAME) $(LIBS_DIR)${LIBFT_LIB} $(LIBS_DIR)${GNL_LIB}

B_ALL_LIBS = $(LIBS_DIR)$(B_NAME) $(LIBS_DIR)${LIBFT_LIB} $(LIBS_DIR)${GNL_LIB}

#Here is the name of the executable file
EXEC_NAME = minishell

all: header ${LIBFT_LIB} ${GNL_LIB} $(LIBS_DIR)$(NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)MINISHELL Is Done\n$(NO_COLOR)"
	@gcc $(ALL_LIBS) -lreadline -L/usr/local/Cellar/readline/8.1/lib -o $(EXEC_NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)Compilation Is Done\n$(NO_COLOR)"
	@echo "$(GREEN)*************************************************************************"
	@echo "$(GREEN)*\t\t\t\t$(BYELLOW)READY\t\t\t\t\t$(GREEN)*"
	@echo "$(GREEN)*************************************************************************$(NO_COLOR)"

bonus: header ${LIBFT_LIB} ${GNL_LIB} $(LIBS_DIR)$(B_NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)MINISHELL Is Done\n$(NO_COLOR)"
	@gcc $(B_ALL_LIBS) -lreadline -L/usr/local/Cellar/readline/8.1/lib -o $(EXEC_NAME)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)Compilation Is Done\n$(NO_COLOR)"
	@echo "$(GREEN)*************************************************************************"
	@echo "$(GREEN)*\t\t\t\t$(BYELLOW)READY\t\t\t\t\t$(GREEN)*"
	@echo "$(GREEN)*************************************************************************$(NO_COLOR)"

${LIBS_DIR}${NAME} : $(OBJ_NAME)
	@ar -rc ${LIBS_DIR}$(NAME) $(OBJ_NAME)
	@ranlib $(LIBS_DIR)$(NAME)

${LIBS_DIR}${B_NAME} : $(B_OBJ_NAME)
	@ar -rc ${LIBS_DIR}$(B_NAME) $(B_OBJ_NAME)
	@ranlib $(LIBS_DIR)$(B_NAME)

${LIBFT_LIB}:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) all && cp $(LIBFT_DIR)$(LIBFT_LIB) $(LIBS_DIR)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)LIBFT Is Done\n"

${GNL_LIB}:
	@$(MAKE) --no-print-directory -C $(GNL_DIR) all && cp $(GNL_DIR)$(GNL_LIB) $(LIBS_DIR)
	@echo "\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)GNL Is Done\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@gcc -fcommon ${CFLAG} -c $< -o $@ -I/usr/local/Cellar/readline/8.1/include

$(OBJ_DIR)%.o : $(B_DIR)%.c
	@gcc -fcommon ${CFLAG} -c $< -o $@ -I/usr/local/Cellar/readline/8.1/include

header:
#	@say compile minihell
	@printf "\n%b" "$(PURPLE)"
	@echo
	@echo "\t\t██████╗     ███╗   ██╗    ███╗   ███╗"
	@echo "\t\t██╔══██╗    ████╗  ██║    ████╗ ████║"
	@echo "\t\t██████╔╝    ██╔██╗ ██║    ██╔████╔██║"
	@echo "\t\t██╔══██╗    ██║╚██╗██║    ██║╚██╔╝██║"
	@echo "\t\t██████╔╝    ██║ ╚████║    ██║ ╚═╝ ██║"
	@echo "\t\t╚═════╝     ╚═╝  ╚═══╝    ╚═╝     ╚═╝"
	@echo

	@echo "\t███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
	@echo "\t████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░"
	@echo "\t██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@echo "\t██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
	@echo "\t██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
	@echo "\t╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"
	@echo
	@printf "\n%b" "$(LIGHT_BLUE)"
	@echo "\t\t                  ░░░░░░░░░░"
	@echo "\t\t             ░░░░░░░░░░░░░░░░░░░"
	@echo "\t\t          ░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "\t\t        ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "\t\t      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▄░░"
	@echo "\t\t     ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██▌░░"
	@echo "\t\t    ░░░░░░░░░░░░░░░░░░░░░░░░░░░▄▄███▀░░░░"
	@echo "\t\t   ░░░░░░░░░░░░░░░░░░░░░░░░░░░█████░▄█░░░░"
	@echo "\t\t  ░░░░░░░░░░░░░░░░░░░░░░░░░░▄████████▀░░░░"
	@echo "\t\t  ░░░░░░░░░░░░░░░░░░░░░░░░▄█████████░░░░░░░"
	@echo "\t\t ░░░░░░░░░░░░░░░░░░░░░░░░░░▄███████▌░░░░░░░"
	@echo "\t\t ░░░░░░░░░░░░░░░░░░░░░░░░▄█████████░░░░░░░░"
	@echo "\t\t ░░░░░░░░░░░░░░░░░░░░░▄███████████▌░░░░░░░░"
	@echo "\t\t ░░░░░░░░░░░░░░░▄▄▄▄██████████████▌░░░░░░░░"
	@echo "\t\t ░░░░░░░░░░░▄▄███████████████████▌░░░░░░░░░"
	@echo "\t\t ░░░░░░░░░▄██████████████████████▌░░░░░░░░░"
	@echo "\t\t ░░░░░░░░████████████████████████░░░░░░░░░░"
	@echo "\t\t █░░░░░▐██████████▌░▀▀███████████░░░░░░░░░░"
	@echo "\t\t██░░░▄██████████▌░░░░░░░░░▀██▐█▌░░░░░░░░░░"
	@echo "\t\t ██████░█████████░░░░░░░░░░░▐█▐█▌░░░░░░░░░"
	@echo "\t\t  ▀▀▀▀░░░██████▀░░░░░░░░░░░░▐█▐█▌░░░░░░░░"
	@echo "\t\t     ░░░░▐█████▌░░░░░░░░░░░░▐█▐█▌░░░░░░░"
	@echo "\t\t      ░░░░███▀██░░░░░░░░░░░░░█░█▌░░░░░░"
	@echo "\t\t        ░▐██░░░██░░░░░░░░▄▄████████▄"
	@echo "\t\t         ██▌░░░░█▄░░░░░░▄███████████████████"
	@echo "\t\t         ▐██  ░░░██▄▄███████████████████████"
	@echo "\t\t          ▐██  ▄████████████████████████████"
	@echo "\t\t          ▄▄████████████████████████████████"
	@echo "\t\t████████████████████████████████████████████"
	@echo
	@printf "\t$(LIGHT_BLUE)AUTHORS\t\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)TEAM NAME\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)NAME\t\t:\t$(GREEN)%b\n\t$(LIGHT_BLUE)DATE\t\t:\t$(GREEN)%b\n\n" "$(AUTHORS)" "$(TEAM_NAME)" "$(PROJECT_NAME)" "$(DATE)"
	@echo "\t$(BYELLOW)LOADING...$(RED)\n"
	@mkdir -p $(HEADERS_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIBS_DIR)
clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(GNL_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(GNL_DIR) fclean
	@rm -rf $(LIBS_DIR) $(EXEC_NAME)

re: fclean all

test:
	$(TESTER_COMMAND)

.PHONY: all clean fclean re