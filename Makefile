# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 12:37:19 by pruangde          #+#    #+#              #
#    Updated: 2023/04/23 01:25:50 by pruangde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = uname -s
ARCH = arch
ifeq ($(UNAME), Linux)
	CC = clang
else
	CC = gcc
endif

CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# ifeq ($(ARCH), arm64)
# 	LDFLAGS	= -L${HOMEBREW_PREFIX}/opt/readline/lib
# 	CPPFLAGS	= -I${HOMEBREW_PREFIX}/opt/readline/include
# else
# 	LDFLAGS	= -L/usr/local/opt/readline/lib
# 	CPPFLAGS	= -I/usr/local/opt/readline/include
# endif

LDFLAGS	= -L${HOMEBREW_PREFIX}/opt/readline/lib
CPPFLAGS = -I${HOMEBREW_PREFIX}/opt/readline/include

PARS = parser_1.c parser_2.c parser_3.c
UTIL = utils_1.c utils_2.c
ERRMSG = err_msg.c

SRCS = minishell.c sig_handle.c $(PARS) $(UTIL) $(ERRMSG)
OBJS = $(SRCS:.c=.o)



.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -lreadline $(LDFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJS) $(BN_OBJS)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

test:
	$(CC) maintest.c parser_1.c -o $(NAME)
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
