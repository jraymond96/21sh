# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:07:15 by mmerabet          #+#    #+#              #
#    Updated: 2018/09/24 20:17:15 by jraymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	21sh
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3 -fsanitize=address

LIBFTD		=	libft
LIBFT		=	$(LIBFTD)/libft.a
SRCD		=	srcs/

INCLUDES	=	includes/expr.h includes/job_control.h includes/parser.h includes/readraw.h includes/shell.h
_PROMPT_FS	=	ft_readraw.c selectmode.c move_char.c move_history.c reprint_line3.c\
				move_word.c move_end.c printprompt.c
PROMPT_FS	=	$(addprefix $(SRCD)prompt/,$(_PROMPT_FS))
_PROMPT_FSO	=	$(_PROMPT_FS:.c=.o)
PROMPT_FSO	=	$(PROMPT_FS:.c=.o)

_JBCNTRL_FS	=	check_bgend.c info_bg.c handle_bgsign.c handle_bgstatus.c \
				handle_pgid.c exec_cmd_background.c freelst_bg.c ret_astargs.c exec_btin_bin.c
JBCNTRL_FS	=	$(addprefix $(SRCD)job_control/,$(_JBCNTRL_FS))
_JBCNTRL_FSO=	$(_JBCNTRL_FS:.c=.o)
JBCNTRL_FSO	=	$(JBCNTRL_FS:.c=.o)

_BLTN_FS	=	builtins.c builtin_cd.c builtin_echo.c builtin_setenv.c builtin_source.c \
				builtin_bool.c builtin_env.c builtin_jobs.c builtin_fg.c builtin_bg.c \
				ft_isbuiltin.c
BLTN_FS		=	$(addprefix $(SRCD)builtin/,$(_BLTN_FS))
_BLTN_FSO	=	$(_BLTN_FS:.c=.o)
BLTN_FSO	=	$(BLTN_FS:.c=.o)

_PARSER_FS	=	ft_parser.c ft_lexer.c ft_astiter.c ft_resolver.c ft_getopt.c \
				ft_argsdel.c ft_astdel.c newast.c ft_interpret.c utils.c
PARSER_FS	=	$(addprefix $(SRCD)parser/,$(_PARSER_FS))
_PARSER_FSO	=	$(_PARSER_FS:.c=.o)
PARSER_FSO	=	$(PARSER_FS:.c=.o)

_SHCB_FS	=	shell_command.c shell_pipe.c shell_arithmetic.c shell_condition.c shell_error.c \
				shell_expansions.c shell_expansions1.c shell_equal.c shell_redir.c shell_redir1.c \
				shell_hdoc.c shell_seco.c
SHCB_FS		=	$(addprefix $(SRCD)callbacks/,$(_SHCB_FS))
_SHCB_FSO	=	$(_SHCB_FS:.c=.o)
SHCB_FSO	=	$(SHCB_FS:.c=.o)

_EXPR_FS	=	ft_expr.c expr_callbacks.c expr_callbacks2.c
EXPR_FS		=	$(addprefix $(SRCD)expr/,$(_EXPR_FS))
_EXPR_FSO	=	$(_EXPR_FS:.c=.o)
EXPR_FSO	=	$(EXPR_FS:.c=.o)

_MAIN_FS	=	main.c ft_env.c ft_env2.c ft_getcursor.c ft_exec.c ft_getpaths.c \
				ft_parsepath.c list_redirections.c history.c shell_init.c shell_begin.c shell_end.c
MAIN_FS		=	$(addprefix $(SRCD),$(_MAIN_FS))
_MAIN_FSO	=	$(_MAIN_FS:.c=.o)
MAIN_FSO	=	$(MAIN_FSO:.c=.o)

ICLD		=	-Iincludes -I$(LIBFTD)/includes
SRCS		=	$(MAIN_FS) $(PROMPT_FS) $(JBCNTRL_FS) $(BLTN_FS) $(PARSER_FS) $(SHCB_FS) $(EXPR_FS)
_OBJS		=	$(_MAIN_FSO) $(_PROMPT_FSO) $(_JBCNTRL_FSO) $(_BLTN_FSO) $(_PARSER_FSO) $(_SHCB_FSO) $(_EXPR_FSO)
OBJD		=	.objs/
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

$(LIBFT):

lib:
	@make -C $(LIBFTD)

$(OBJD)%.o: $(SRCD)main/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)prompt/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)job_control/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)builtin/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)parser/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)callbacks/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

$(OBJD)%.o: $(SRCD)expr/%.c $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
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
