/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_piping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 04:39:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/13 23:51:29 by kdumarai         ###   ########.fr       */
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

/*
**int		*get_pipes(size_t n)
**{
**	int				*ret;
**	unsigned int	shift;
**	size_t			len;
**
**	shift = 0;
**	len = n / 2 + (n % 2);
**	if (!(ret = (int*)malloc(sizeof(int) * (sizeof(int) * len))))
**		return (NULL);
**	while (len--)
**	{
**		pipe(ret + shift);
**		shift += 2;
**	}
**	return (ret);
**}
*/
