/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_piping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 04:39:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 23:02:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

void	dup_out_to_pipe(int outfd, int pfd)
{
	close(outfd);
	dup2(pfd, outfd);
}

/*
**void	write_out_to_file(const char *path, int *pfds)
**{
**	char			buff[32];
**	int				outfd;
**	ssize_t			rb;
**
**	close(pfds[1]);
**	outfd = open(path, O_WRONLY | O_CREAT, 0644);
**	while ((rb = read(pfds[0], buff, sizeof(buff))) > 0)
**		write(outfd, buff, rb);
**	close(outfd);
**}
*/
