# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 17:30:06 by bsirikam          #+#    #+#              #
#    Updated: 2023/05/30 00:17:05 by pruangde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = uname -s
ARCH = arch
ifeq ($(UNAME), Linux)
	CC = clang
else
	CC = gcc
endif

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# ifeq ($(ARCH), arm64)
# 	LDFLAGS	= -L${HOMEBREW_PREFIX}/opt/readline/lib
# 	CPPFLAGS	= -I${HOMEBREW_PREFIX}/opt/readline/include
# else
# 	LDFLAGS	= -L/usr/local/opt/readline
# 	CPPFLAGS	= -I/usr/local/opt/readline/include
# endif

LDFLAGS = -L${HOMEBREW_PREFIX}/opt/readline/lib
CPPFLAGS = -I${HOMEBREW_PREFIX}/opt/readline/include

# LDFLAGS		= -L/usr/local/opt/readline/
# CPPFLAGS	= -I/usr/local/opt/readline/include/

PARS = parser_1.c parser_2.c parser_3.c parser_4.c parser_5.c parser_6.c
UTIL = utils_1.c utils_2.c utils_3.c utils_4.c utils_5.c
ERRMSG = err_msg.c

EXECUTE = test_execute.c
#BUILTIN = builtin_export.c builtin_env.c builtin_export_utils.c builtin_pwd.c

SRCS = minishell.c sig_handle.c env.c $(PARS) $(UTIL) $(ERRMSG) $(EXECUTE) #$(BUILTIN)
OBJ_C = $(SRCS:.c=.o)
OBJ_DIR = obj
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ_C))

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< ${CPPFLAGS} -o $@

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -lreadline $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJS) $(BN_OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

# test:
#	$(CC) maintest.c $(NAME)
#	valgrind --vgdb=no --leak-check=full --show-leak-kinds=all ./a.out

leak:
	leaks --atExit -- ./push_swap

san:
	$(CC) -fsanitize=address -fno-omit-frame-pointer maintest.c

norm:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo ""
	@norminette -R CheckForbiddenSourceHeader *.c
	@echo ""
	@echo ""
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"

normhead:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo " !!!!!!!   ONLY  HEADER   !!!!!!!!"
	@echo ""
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"
