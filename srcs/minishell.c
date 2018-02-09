/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/09 07:37:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_readline.h"
#include "minishell.h"

static void	exec_shell(char *shpath, const char *path, char ***env)
{
	char	*line;
	int		fd;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		exec_cmds(line, shpath, env);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
}

static void	launch_rc(char *shpath, char ***env)
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
	exec_shell(shpath, rcpath, env);
	free(rcpath);
}

static void	interactive_shell(char *shpath, char ***env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = NULL;
	launch_rc(shpath, env);
	while (42)
	{
		prompt = get_prompt(*env);
		line = ft_readline(prompt, *env);
		ft_strdel(&prompt);
		if (!line)
			break ;
		exec_cmds(line, shpath, env);
		ft_strdel(&line);
	}
}

static char	*get_shpath(char *shname, char **env)
{
	char	*ret;
	char	*pwd;

	if (*shname != '.')
		return (ft_strdup(shname));
	if (!(pwd = get_env_var(env, "PWD")))
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(pwd);
	if (!pwd)
		return (NULL);
	ret = ft_strnew(ft_strlen(pwd) + ft_strlen(shname) + 1);
	ft_strcpy(ret, pwd);
	ft_strcat(ret, "/");
	ft_strcat(ret, shname);
	free(pwd);
	return (ret);
}

int			main(int ac, char **av, char **environ)
{
	char	**env;
	char	*shpath;

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
	shpath = get_shpath(av[0], env);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exec_shell(shpath, av[1], &env);
	else
		interactive_shell(shpath, &env);
	ft_tabfree(&env);
	ft_strdel(&shpath);
	return (EXIT_SUCCESS);
}
