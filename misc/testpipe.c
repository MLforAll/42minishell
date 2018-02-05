/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:17:48 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/05 20:50:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef PIPEOK
# define PIPEOK	1
#endif
#define OUTFP	"/Users/kdumarai/Desktop/testout.txt"

int		main(int ac, char **av, char **env)
{
	int			ex;
	pid_t		pid;
	int			pfd[2];
	char		sout[32];
	ssize_t		rb;
	int			outfd;

	if (ac == 1)
	{
		puts("Enter command path and args");
		return (1);
	}
	ex = 0;
	if (PIPEOK)
		pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		if(PIPEOK)
		{
			close(pfd[0]);
			close(1);
			dup(pfd[1]);
		}
		execve(av[1], av + 1, env);
		exit(127);
	}
	else
	{
		if (PIPEOK)
		{
			outfd = open(OUTFP, O_WRONLY | O_CREAT, 0644);
			close(pfd[1]);
			while ((rb = read(pfd[0], sout, sizeof(sout))) > 0)
				write(outfd, sout, rb);
			close(outfd);
		}
		wait(&ex);
		printf("exit status: %i\n", WEXITSTATUS(ex));

	}
	return (0);
}
