/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/24 22:32:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

#include <stdio.h>

int			main(int ac, char **av, char **env)
{
	char			*line;
	t_cmd			*test;
	int				exval;

	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	while (42)
	{
		line = ft_readline("\033[1;33mminishell@42\033[0;39m$ ");
		if (line)
		{
			//ft_putstr("line is: ");
			//ft_putendl(line);
			test = get_cmd_list(line, env);
			exval = exec_cmds(test, env);
			ft_cmddel(&test);
			//printf("process exited: %i\n", exval);
		}
		if (!line)
			break ;
		ft_strdel(&line);
	}
	return (0);
}
