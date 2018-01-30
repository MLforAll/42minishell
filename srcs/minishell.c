/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 00:10:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_readline.h"
#include "minishell.h"

#include <stdio.h>

static void	process_line(char *line, char ***env)
{
	t_cmd	*cmdlst;

	cmdlst = get_cmd_list(line, *env);
	exec_cmds(cmdlst, env);
	ft_cmddel(&cmdlst);
}

static void	interactive_shell(char ***env)
{
	char	*line;
	char	*prompt;

	if (!(prompt = get_env_var(*env, "MSH_PROMPT")))
		prompt = "\033[1;33mminishell@42\033[0;39m$ ";
	while ((line = ft_readline(prompt, *env)))
	{
		//ft_putstr("line is: ");
		//ft_putendl(line);
		process_line(line, env);
		ft_strdel(&line);
	}
}

static void	exec_shell(const char *path, char ***env)
{
	char	*line;
	int		fd;

	if (!path)
		return ;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		process_line(line, env);
		ft_strdel(&line);
	}
	close(fd);
}

int			main(int ac, char **av, char **environ)
{
	char	**env;

	signal(SIGINT, SIG_IGN);
	if (environ)
		env = ft_tabdup((const char**)environ);
	else
	{
		env = (char**)malloc(sizeof(char*));
		*env = NULL;
	}
	chg_env_var(env, "SHELL", av[0]);
	if (ac > 1)
		exec_shell(av[1], &env);
	else
		interactive_shell(&env);
	ft_tabfree(&env);
	return (0);
}
