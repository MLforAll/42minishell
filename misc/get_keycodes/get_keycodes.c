/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keycodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:49:26 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/03 19:22:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <termios.h>

struct termios	saved;
int				lastc;

static void	restore_quit(int dummy)
{
	(void)dummy;
	if (!lastc)
		puts("");
	puts("Reverting terminal...");
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	puts("Bye-bye :D");
	exit(0);
}

static int	chk_space_buff(char *buff, size_t len)
{
	while (len--)
		if (buff[len] != 0 && (!isprint(buff[len]) || buff[len] == 32))
			return (1);
	return (0);
}

int			main(void)
{
	struct termios	t;
	char			buff[4];

	puts("Changing terminal...");
	tcgetattr(STDIN_FILENO, &t);
	saved = t;
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	puts("OK! Type stuff...");
	puts("PS: Ctrl-C to quit\n");
	signal(SIGINT, &restore_quit);
	while (42)
	{
		bzero(buff, sizeof(buff));
		read(STDIN_FILENO, buff, 4);
		if (chk_space_buff(buff, 4))
			puts("");
		for (int i = 0; i < 4; i++)
			printf("buff[%i]: %3i%s", i, buff[i], i < 3 ? " - " : "\n");
		if (chk_space_buff(buff, 4))
		{
			lastc = 1;
			puts("");
		}
		else
			lastc = 0;
	}
	return (0);
}
