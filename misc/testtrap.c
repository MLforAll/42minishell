/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testtrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:38:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/23 17:43:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static void	putnl(char *s)
{
	if (!s)
		putnl("(null)");
	write(STDOUT_FILENO, s, strlen(s));
	write(STDOUT_FILENO, "\n", 1);
}

int			main(void)
{
	putnl("This prgm will run and trap Ctrl-C");
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (42)
	{
		putnl("running...");
		sleep(1);
	}
	return (EXIT_SUCCESS);
}
