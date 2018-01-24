/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kelian <Kelian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 23:33:08 by Kelian           ###   ########.fr       */
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
	(void)env;
	signal(SIGINT, SIG_IGN);
	char *cmd = search_dir_for_exec("/bin", "ls");
	printf("%s\n", cmd);
	ft_strdel(&cmd);
	while (42)
	{
		line = ft_readline("$> ");
		if (line)
		{
			//ft_putstr("line is: ");
			//ft_putendl(line);
			test = get_cmd_list(line);
			//ft_puttab(test->c_argv, NULL);
			exval = exec_cmd(test);
			printf("process exited: %i\n", exval);
		}
		if (!line)
			break ;
		ft_strdel(&line);
	}
	return (0);
}
