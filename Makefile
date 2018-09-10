# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:07:15 by mmerabet          #+#    #+#              #
#    Updated: 2018/09/09 18:48:55 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	21sh
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3 -fsanitize=address

LIBFTD		=	libft
LIBFT		=	$(LIBFTD)/libft.a

_NTS	=		main.c \
				ft_readraw2.c selectmode.c completion.c \
				ft_parser.c ft_lexer.c ft_astiter.c ft_resolver.c ft_getopt.c \
				ft_argsdel.c ft_astdel.c newast.c \
				ft_env.c ft_env2.c ft_getcursor.c ft_exec.c ft_isbuiltin.c ft_getpaths.c \
				ft_parsepath.c handle_rdrctn.c history.c \
				builtins.c builtin_cd.c builtin_echo.c builtin_setenv.c builtin_source.c \
				builtin_bool.c builtin_env.c builtin_jobs.c builtin_fg.c builtin_bg.c\
				shell_init.c shell_begin.c \
				shell_expansions.c shell_pipe.c shell_arithmetic.c shell_condition.c \
				shell_command.c shell_redir.c shell_redir_printerror.c \
				shell_equal.c shell_expansions1.c \
				ft_expr.c expr_callbacks.c expr_callbacks2.c \
				exec_cmd_background.c handle_bgstatus.c check_bgend.c handle_pgid.c\
				info_bg.c ret_astargs.c exec_btin_bin.c handle_bgsign.c freelst_bg.c\

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
	@$(CC) $(CFLAGS) $(OBJB) $(LIBFT) $(FRAMEWORKS) ./logger/liblogger.a -o $(NAME)
	@echo  "$(NAME): $(CGREEN)done$(CEND)"

$(LIBFT):

lib:
	@make -C $(LIBFTD)

$(OBJD)%.o: $(SRCD)%.c includes/shell.h Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $@"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

clean:
	@make -C $(LIBFTD) clean
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"
	@rm -f $(OBJB)

fclean: clean
	@make -C $(LIBFTD) fclean
	@echo "$(CRED)Full cleaning$(CEND): $(NAME)"
	@/bin/rm -f $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re
