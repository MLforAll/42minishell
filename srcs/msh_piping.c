/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_piping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 04:39:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/08 19:53:25 by kdumarai         ###   ########.fr       */
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

	if (!(ret = (int*)malloc(sizeof(int) * (sizeof(int) * n * 2))))
		return (NULL);
	idx = 0;
	while (n--)
	{
		pipe(ret + shift);
		shift += 2;
	}
	return (ret);
}

size_t	get_plen(t_cmd *cmd)
{
	size_t			npipes;
	int				chks;
	char			**ptr;

	npipes = 0;
	chks = 3;
	ptr = &cmd->c_in;
	while (chks--)
	{
		if (*ptr)
			npipes++;
		ptr++;
	}
	return (npipes);
}
