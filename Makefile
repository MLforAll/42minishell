# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/01/23 21:38:12 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I includes -I libft
LD_LIB = -L libft -lft

LIBFT = libft/libft.a

INCDIR = includes
INCFILES = minishell.h
INCLUDES = $(addprefix $(INCDIR)/, $(INCFILES))

SRCDIR = srcs
SRCFILES = minishell.c \
	ft_readline.c \
	msh_interpret.c \
	msh_cmdexec.c \
	msh_direxp.c \
	lst_support.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;36m$(NAME): \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@ printf "\r\033[K$(PROJTEXT)Compiling\n"
	@ make -C $(dir $(LIBFT))
	@ printf "$(PROJTEXT)Linking\n"
	@ gcc -o $(NAME) $(LD_LIB) $(OBJS)
	@ printf "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<\033[0;39m\r"
	@ gcc $(CC_LIB) -c $< -o $@
	@# gcc $(CC_FLAGS) $(CC_LIB) -c $< -o $@

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
