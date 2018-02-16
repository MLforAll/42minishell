/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/16 18:59:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_readline.h"
#include "minishell.h"

int			exec_shell(const char *path, char ***env)
{
	char		*line;
	int			fd;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	while (get_next_line(fd, &line) > 0)
	{
		exec_cmds(line, env);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (TRUE);
}

static void	launch_rc(char ***env)
{
	char		*home;
	char		*rcpath;

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

static char	*ishell_get_prompt(char **env)
{
	char		*envprompt;

	if ((envprompt = get_env_var(env, "MSH_PROMPT")))
		return (get_prompt_from_str(envprompt, env));
	return (get_prompt_from_str("\033[1;36m\\h:\033[1;33m\\W\033[0;39m \\u$ ", \
								env));
}

static void	interactive_shell(char ***env)
{
	char		*line;
	char		*prompt;
	t_history	*hist;

	line = NULL;
	prompt = NULL;
	hist = NULL;
	launch_rc(env);
	while (42)
	{
		prompt = ishell_get_prompt(*env);
		line = ft_readline(prompt, *env, hist);
		if (line && *line)
		{
			ft_histdelone(&hist);
			ft_histadd(&hist, line);
			ft_histadd(&hist, "");
		}
		ft_strdel(&prompt);
		if (!line)
			break ;
		exec_cmds(line, env);
		ft_strdel(&line);
	}
	ft_histdel(&hist);
}

int			main(int ac, char **av, char **environ)
{
	char		**env;

	switch_signals(TRUE);
	if (environ)
		env = ft_tabdup((const char**)environ);
	else
	{
		env = (char**)malloc(sizeof(char*));
		*env = NULL;
	}
	set_env_var(&env, "SHELL", av[0]);
	if (!get_env_var(env, "PATH"))
		set_env_var(&env, "PATH", SH_DEFAULT_PATH);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exec_shell(av[1], &env);
	else
		interactive_shell(&env);
	ft_tabfree(&env);
	return (EXIT_SUCCESS);
}
