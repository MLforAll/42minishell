/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 18:21:12 by kdumarai         ###   ########.fr       */
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

static char	*get_prompt(char **env)
{
	char	*ret;
	char	*envprompt;
	char	*pwd;
	char	*tmp;

	tmp = NULL;
	if (!(envprompt = get_env_var(env, "MSH_PROMPT")))
	{
		if (!(pwd = get_name_from_path(get_env_var(env, "PWD"))))
		{
			if (!(tmp = getcwd(NULL, 0)))
				pwd = ft_strdup("unknown");
			else
			{
				pwd = ft_strdup(get_name_from_path(tmp));
				ft_strdel(&tmp);
			}
		}
		else
			pwd = ft_strdup(pwd);
		ret = ft_strnew(33 + ft_strlen(pwd));
		ft_strcpy(ret, "\033[1;36mminishell:");
		ft_strcat(ret, "\033[1;33m");
		ft_strcat(ret, pwd);
		ft_strcat(ret, "\033[0;39m$ ");
		ft_strdel(&pwd);
	}
	else
		ret = ft_strdup(envprompt);
	return (ret);
}

static void	interactive_shell(char ***env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = NULL;
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

static void	exec_shell(const char *path, char ***env)
{
	char	*line;
	int		fd;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		process_line(line, env);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
}

int			main(int ac, char **av, char **environ)
{
	char	**env;

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
