/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/26 22:22:26 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

#include <stdio.h>

static void	free_tlist(void *content, size_t size)
{
	(void)size;
	free(content);
}

static void	test_autocompletion(void)
{
	t_list *test = search_execs_begin("/usr/bin", "cl");
	if (!test)
		ft_putendl("null lst!");
	for (t_list *bw = test; bw; bw = bw->next)
		ft_putendl(bw->content);
	ft_lstdel(&test, &free_tlist);
}

int			main(int ac, char **av, char **environ)
{
	char			*line;
	char			**env;
	t_cmd			*cmdlst;

	if (ac > 1)
	{
		ft_putendl("Sorry, msh doesn't support files yet!");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	env = ft_tabdup((const char**)environ);
	chg_env_var(env, "SHELL", av[0]);
	//test_autocompletion();
	(void)test_autocompletion;
	while ((line = ft_readline("\033[1;33mminishell@42\033[0;39m$ ")))
	{
		//ft_putstr("line is: ");
		//ft_putendl(line);
		cmdlst = get_cmd_list(line, env);
		exec_cmds(cmdlst, &env);
		ft_cmddel(&cmdlst);
		ft_strdel(&line);
	}
	ft_tabfree(&env);
	return (0);
}
