/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/08 22:25:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_readline.h"
#include "minishell.h"

static void	process_line(char *line, char ***env)
{
	t_cmd	*cmdlst;

	cmdlst = get_cmd_list(line, *env);
	exec_cmds(cmdlst, env);
	ft_cmddel(&cmdlst);
}

static void	exec_shell(const char *path, char ***env)
{
	char	*line;
	int		fd;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		process_line(line, env);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
}

static void	launch_rc(char ***env)
{
	char	*home;
	char	*rcpath;

	if (!(home = get_env_var(*env, "HOME")))
		return ;
	if (!(rcpath = ft_strnew(ft_strlen(home) + ft_strlen(SH_RC) + 1)))
		return ;
	ft_strcpy(rcpath, home);
	ft_strcat(rcpath, "/");
	ft_strcat(rcpath, SH_RC);
	exec_shell(rcpath, env);
	free(rcpath);
}

static void	interactive_shell(char ***env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = NULL;
	launch_rc(env);
	while (42)
	{
		prompt = get_prompt(*env);
		line = ft_readline(prompt, *env);
		ft_strdel(&prompt);
		if (!line)
			break ;
		process_line(line, env);
		ft_strdel(&line);
	}
}

int			main(int ac, char **av, char **environ)
{
	char	**env;

	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (environ)
		env = ft_tabdup((const char**)environ);
	else
	{
		env = (char**)malloc(sizeof(char*));
		*env = NULL;
	}
	set_env_var(&env, "SHELL", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exec_shell(av[1], &env);
	else
		interactive_shell(&env);
	ft_tabfree(&env);
	return (EXIT_SUCCESS);
}
