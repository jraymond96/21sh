# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:07:15 by mmerabet          #+#    #+#              #
#    Updated: 2018/07/05 03:43:31 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	21sh
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

LIBFTD		=	libft
LIBFT		=	$(LIBFTD)/libft.a

_NTS	=		main.c ft_parser.c ft_getpaths.c shell_begin.c ft_env2.c \
				ft_getcursor.c builtins.c ft_isbuiltin.c builtin_cd.c ft_env.c \
				ft_readraw.c ft_exec.c history.c ft_getopt.c builtin_echo.c ft_astiter.c \
				builtin_setenv.c builtin_env.c shell_init.c ft_astdel.c ft_lexer.c \
				ft_parsepath.c handle_rdrctn.c exp_func.c ft_resolver.c \
				ft_expr.c ft_expr2.c expr_callbacks.c expr_callbacks2.c expr_func.c \
				shell_callbacks.c

SRCD		=	srcs/
ICLD		=	-Iincludes -I$(LIBFTD)/includes
NTS			=	$(patsubst %,$(SRCD)/%,$(_NTS))
_NTO		=	$(_NTS:.c=.o)
NTO			=	$(NTS:.c=.o)

SRCS		=	$(NTS)
_OBJS		=	$(_NTO)
OBJD		=	objs/
OBJS		=	$(addprefix $(SRCD),$(_OBJS))
OBJB		=	$(addprefix $(OBJD),$(_OBJS))

FRAMEWORKS	=

# COLORS
CRED=\033[91m
CGREEN=\033[38;2;0;255;145m
CEND=\033[0m

all: 
	@$(MAKE) lib
	@$(MAKE) $(NAME)

$(NAME): $(LIBFT) $(OBJB)
	@printf "\r\033[K$(CGREEN)Creating executable$(CEND): $(NAME)\n"
	@$(CC) $(CFLAGS) $(OBJB) $(LIBFT) $(FRAMEWORKS) -o $(NAME)
	@echo  "$(NAME): $(CGREEN)done$(CEND)"

$(LIBFT):;

lib:
	@make -C $(LIBFTD)

$(OBJD)%.o: $(SRCD)%.c includes/shell.h
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $@"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

clean:
	@make -C $(LIBFTD) clean
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"
	@rm -f $(OBJB)

fclean: clean
	@make -C $(LIBFTD) fclean
	@echo "$(CRED)Full leaning$(CEND): $(NAME)"
	@/bin/rm -f $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re