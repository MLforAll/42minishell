/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_piping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 04:39:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/09 07:36:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	dup_outs_with_pipe(t_cmd *cmd, int *pfds)
{
	close(pfds[0]);
	close(out);
	dup(pfds[1]);
}

void	write_out_to_file(const char *path, int *pfds)
{
	char			buff[32];
	int				outfd;
	ssize_t			rb;

	close(pfds[1]);
	outfd = open(path, O_WRONLY | O_CREAT, 0644);
	while ((rb = read(pfds[0], buff, sizeof(buff))) > 0)
		write(outfd, buff, rb);
	close(outfd);
}

void	write_outs(t_cmd *cmd, int *pfds, size_t n)
{
	while (n--)
	{
		write_out_to_file()
	}
}

int		*get_pipes(size_t n)
{
	int				*ret;
	unsigned int	shift;
	size_t			len;

	len = n / 2 + (n % 2);
	if (!(ret = (int*)malloc(sizeof(int) * (sizeof(int) * len))))
		return (NULL);
	while (len--)
	{
		pipe(ret + shift);
		shift += 2;
	}
	return (ret);
}
