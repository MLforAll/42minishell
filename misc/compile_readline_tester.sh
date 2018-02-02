#!/bin/sh

if [ ! -f ft_readline_tester.c ]; then
	echo "OOPS!"
	echo "Not in right folder!"
	echo "You are here: $PWD"
	exit 1
fi

make -C ../../Libft
gcc -o ft_readline_tester \
				ft_readline_tester.c \
				../srcs/ft_readline/ft_readline.c ../srcs/ft_readline/ft_readline_utils.c \
				../srcs/msh_autocompletion.c \
				../srcs/msh_direxp.c \
				../srcs/msh_misc.c \
				../srcs/msh_env.c \
				../srcs/lists/tlist_support.c \
	-I ../includes -I ../../Libft -L ../../Libft -lft
