# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/01/25 01:35:20 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I includes -I libft
LD_FLAGS = -L libft -lft

LIBFT = libft/libft.a

INCDIR = includes
INCFILES = minishell.h
		msh_data.h \
		msh_debug.h
INCLUDES = $(addprefix $(INCDIR)/, $(INCFILES))

SRCDIR = srcs
SRCFILES = minishell.c \
	ft_readline.c \
	msh_interpret.c \
	msh_cmdexec.c \
	msh_direxp.c \
	lst_support.c \
	msh_err.c \
	msh_env.c \
	msh_debug.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;36m$(NAME): \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@ printf "\r\033[K$(PROJTEXT)Compiling\n"
	@ make -C $(dir $(LIBFT))
	@ echo "$(PROJTEXT)Linking"
	@ gcc -o $(NAME) $(LD_FLAGS) $(OBJS)
	@ echo "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m"

noflags:
	@ echo "\033[1;31m----------------------"
	@ echo "CC FLAGS ARE DISABLED!"
	@ echo "----------------------\033[0;39m"
	@ make all CC_FLAGS=""

fsanitize:
	@ echo "\033[1;31m-------------------"
	@ echo "-fsanitize ENABLED!"
	@ echo "-------------------\033[0;39m"
	@ make all LD_FLAGS="$(LD_FLAGS) -fsanitize=address"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<\033[0;39m\r"
	@ gcc $(CC_FLAGS) $(CC_LIB) -c $< -o $@

clean:
	@ make clean -C $(dir $(LIBFT))
	@ rm -rf $(OBJDIR)
	@ echo "$(PROJTEXT)Removed objects"

fclean: clean
	@ make fclean -C $(dir $(LIBFT))
	@ rm -f $(NAME)
	@ echo "$(PROJTEXT)Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
