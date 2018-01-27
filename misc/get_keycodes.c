/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keycodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:49:26 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 18:06:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

struct termios	saved;

static void	restore_quit(int dummy)
{
	(void)dummy;
	puts("\nReverting terminal...");
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	puts("Bye-bye :D");
	exit(0);
}

int		main(void)
{
	struct termios	t;
	char			buff[4];

	puts("Changing terminal...");
	tcgetattr(STDIN_FILENO, &t);
	saved = t;
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	puts("OK! Type stuff...\n");
	signal(SIGINT, &restore_quit);
	while (42)
	{
		bzero(buff, sizeof(buff));
		read(STDIN_FILENO, buff, 4);
		for (int i = 0; i < 4; i++)
			printf("buff[%i]: %i%s", i, buff[i], i < 3 ? " - " : "\n");
	}
	return (0);
}
