# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/02/02 20:21:01 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I includes -I libft
LD_FLAGS = -L libft -lft

LIBFT = libft/libft.a

INCDIR = includes
INCFILES = minishell.h \
		msh_data.h \
		msh_debug.h \
		ft_readline.h
INCLUDES = $(addprefix $(INCDIR)/, $(INCFILES))

SRCDIR = srcs
SRCFILES = minishell.c \
	msh_interpret.c \
	msh_cmdexec.c \
	msh_direxp.c \
	msh_err.c \
	msh_misc.c \
	msh_env.c \
	bltns/msh_env_builtins.c \
	bltns/msh_env_bltncmd.c \
	bltns/msh_builtins.c \
	msh_autocompletion.c \
	lists/lst_support.c \
	lists/tlist_support.c \
	ft_readline/ft_readline.c \
	ft_readline/ft_readline_utils.c \
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;36m$(NAME): \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@ printf "\r\033[K$(PROJTEXT)Compiling\n"
	@ make -C $(dir $(LIBFT))
	@ printf "$(PROJTEXT)Linking\n"
	@ gcc -o $(NAME) $(LD_FLAGS) $(OBJS)
	@ printf "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m\n"

noflags:
	@ printf "\033[1;31m----------------------\n"
	@ printf "| CC_FLAGS DISABLED! |\n"
	@ printf "\r----------------------\033[0;39m\n"
	@ make all CC_FLAGS=""

fsanitize:
	@ printf "\033[1;31m------------------------------\n"
	@ printf "\r| ADDRESS SANITIZER ENABLED! |\n"
	@ printf "\r------------------------------\033[0;39m\n"
	@ make all LD_FLAGS="$(LD_FLAGS) -fsanitize=address"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<\033[0;39m\r"
	@ gcc $(CC_FLAGS) $(CC_LIB) -c $< -o $@

clean:
	@ make clean -C $(dir $(LIBFT))
	@ rm -rf $(OBJDIR)
	@ printf "$(PROJTEXT)Removed objects\n"

fclean: clean
	@ make fclean -C $(dir $(LIBFT))
	@ rm -f $(NAME)
	@ printf "$(PROJTEXT)Removed $(NAME)\n"

re: fclean all

.PHONY: all clean fclean re
