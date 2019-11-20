# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 21:54:19 by zamazzal          #+#    #+#              #
#    Updated: 2019/11/21 00:08:15 by zamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			21sh

FLAGS =			-Wall -Wextra -Werror

SRCS_PATH = 	sources/
OBJ_PATH = 		objects/

TERMCAP = 		-ltermcap
LIBFT_PATH = 	libft/
Libft = 		-L $(LIBFT_PATH) -lft
INCLUDES = 		-I includes/ -I $(LIBFT_PATH)
HEADER = 		includes/mysh.h

builtins_SRCS = 	$(addprefix $(SRCS_PATH), builtins/)
execution_SRCS = 	$(addprefix $(SRCS_PATH), execution/)
expansion_SRCS = 	$(addprefix $(SRCS_PATH), expansion/)
messages_SRCS = 	$(addprefix $(SRCS_PATH), messages/)
readline_SRCS = 	$(addprefix $(SRCS_PATH), readline/)
redirections_SRCS = $(addprefix $(SRCS_PATH), redirections/)
shell_SRCS = 		$(addprefix $(SRCS_PATH), shell/)
terminal_SRCS = 	$(addprefix $(SRCS_PATH), terminal/)
tools_SRCS = 		$(addprefix $(SRCS_PATH), tools/)
validation_SRCS = 	$(addprefix $(SRCS_PATH), validation/)

builtins_OBJ = 		$(addprefix $(OBJ_PATH), builtins/)
execution_OBJ = 	$(addprefix $(OBJ_PATH), execution/)
expansion_OBJ = 	$(addprefix $(OBJ_PATH), expansion/)
messages_OBJ = 		$(addprefix $(OBJ_PATH), messages/)
readline_OBJ = 		$(addprefix $(OBJ_PATH), readline/)
redirections_OBJ = 	$(addprefix $(OBJ_PATH), redirections/)
shell_OBJ = 		$(addprefix $(OBJ_PATH), shell/)
terminal_OBJ = 		$(addprefix $(OBJ_PATH), terminal/)
tools_OBJ = 		$(addprefix $(OBJ_PATH), tools/)
validation_OBJ = 	$(addprefix $(OBJ_PATH), validation/)

builtins = 		builtins.c				\
				cd.c					\
				echo.c					\
				env.c					\
				setenv.c				\
				type.c					\
				unsetenv.c				\

execution = 	commands.c				\
				exec.c					\
				hashtable.c				\

expansion = 	prepare_cmd.c			\
				prepare_cmd2.c			\
				prepare_cmd3.c			\

messages = 		messages1.c				\
				messages2.c				\
				messages3.c				\

readline = 		autocompletion.c 		\
				backslash.c				\
				buffer.c				\
				check_input.c			\
				copy.c					\
				ctrld.c					\
				events.c				\
				get_input.c				\
				get_line.c				\
				input.c					\
				moves.c					\
				moves2.c				\
				moves3.c				\
				moves_inline.c			\
				moves_tools.c			\
				moves_tools2.c			\
				pipe.c					\
				quotes.c				\
				read_tools.c			\
				readline.c				\
				search.c				\
				select.c				\
				show_cmd.c				\

redirections = 	clean_reds_wings.c		\
				exec_ls_red.c			\
				exec_rd_red.c			\
				exec_reds.c				\
				exec_rs_red.c			\
				extract_reds.c			\
				fd_to_close.c			\
				get_clean_cmd.c			\
				red_wings.c				\
				redirection_tools.c		\
				reds_positions.c		\

shell =			cmd_exec.c				\
				exec.c					\
				herdoc_input.c			\
				herdoc_tools.c			\
				main.c					\
				make_fds.c				\
				semicmd_exec.c			\
				shell.c					\
				signals.c				\
				wait_pid.c				\
				pars.c					\

terminal = 		cursor.c				\
				exec_term.c				\
				modes.c					\
				valid.c					\

tools =			tools.c					\
				tools2.c				\
				tools3.c				\
				tools4.c				\
				tools5.c				\

validation =	errors.c				\
				errors2.c				\
				errors3.c				\

SRCS =	$(addprefix $(builtins_SRCS), $(builtins))				\
		$(addprefix $(execution_SRCS), $(execution))			\
		$(addprefix $(expansion_SRCS), $(expansion))			\
		$(addprefix $(messages_SRCS), $(messages))				\
		$(addprefix $(readline_SRCS), $(readline))				\
		$(addprefix $(redirections_SRCS), $(redirections))		\
		$(addprefix $(shell_SRCS), $(shell))					\
		$(addprefix $(terminal_SRCS), $(terminal))				\
		$(addprefix $(tools_SRCS), $(tools))					\
		$(addprefix $(validation_SRCS), $(validation))			\

OBJ =	$(addprefix $(builtins_OBJ), $(builtins:.c=.o))			\
		$(addprefix $(execution_OBJ), $(execution:.c=.o))		\
		$(addprefix $(expansion_OBJ), $(expansion:.c=.o))		\
		$(addprefix $(messages_OBJ), $(messages:.c=.o))			\
		$(addprefix $(readline_OBJ), $(readline:.c=.o))			\
		$(addprefix $(redirections_OBJ), $(redirections:.c=.o))	\
		$(addprefix $(shell_OBJ), $(shell:.c=.o))				\
		$(addprefix $(terminal_OBJ), $(terminal:.c=.o))			\
		$(addprefix $(tools_OBJ), $(tools:.c=.o))				\
		$(addprefix $(validation_OBJ), $(validation:.c=.o))		\

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJ) $(Libft) $(INCLUDES) -o $(NAME) $(TERMCAP)
	@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(builtins_OBJ)%.o: $(builtins_SRCS)%.c $(HEADER)
	@mkdir -p $(builtins_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(execution_OBJ)%.o: $(execution_SRCS)%.c $(HEADER)
	@mkdir -p $(execution_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(expansion_OBJ)%.o: $(expansion_SRCS)%.c $(HEADER)
	@mkdir -p $(expansion_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(messages_OBJ)%.o: $(messages_SRCS)%.c $(HEADER)
	@mkdir -p $(messages_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(readline_OBJ)%.o: $(readline_SRCS)%.c $(HEADER)
	@mkdir -p $(readline_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(redirections_OBJ)%.o: $(redirections_SRCS)%.c $(HEADER)
	@mkdir -p $(redirections_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(shell_OBJ)%.o: $(shell_SRCS)%.c $(HEADER)
	@mkdir -p $(shell_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(terminal_OBJ)%.o: $(terminal_SRCS)%.c $(HEADER)
	@mkdir -p $(terminal_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(tools_OBJ)%.o: $(tools_SRCS)%.c $(HEADER)
	@mkdir -p $(tools_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(validation_OBJ)%.o: $(validation_SRCS)%.c $(HEADER)
	@mkdir -p $(validation_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

clean:
	@make -C $(LIBFT_PATH) clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\x1B[96mObjects Files \x1B[31mDeleted.\x1B[39;0m"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@/bin/rm -f $(NAME)
	@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re: fclean all

.PHONY: all, clean, fclean, re