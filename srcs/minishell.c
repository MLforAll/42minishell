/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/21 18:26:40 by kdumarai         ###   ########.fr       */
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
	int			ret;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	while (get_next_line(fd, &line) > 0)
	{
		ret = exec_cmds(line, env);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (ret);
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
	char		*mshp_entry;
	char		*pr;

	if ((mshp_entry = get_env_var(env, "MSH_PROMPT")))
		pr = get_prompt_from_str(mshp_entry, env);
	else
		pr = get_prompt_from_str("\\u:\\W$ ", env);
	return ((pr) ? pr : ft_strdup("msh-1.0$ "));
}

static int	interactive_shell(char ***env)
{
	int			ret;
	char		*line;
	char		*prompt;
	t_history	*history;

	line = NULL;
	prompt = NULL;
	history = NULL;
	ret = EXIT_SUCCESS;
	launch_rc(env);
	while (42)
	{
		prompt = ishell_get_prompt(*env);
		line = ft_readline(prompt, *env, history);
		if (line && *line)
			ft_histadd(&history, line);
		ft_strdel(&prompt);
		if (!line)
			break ;
		ret = exec_cmds(line, env);
		ft_strdel(&line);
	}
	ft_histdel(&history);
	return (ret);
}

int			main(int ac, char **av, char **environ)
{
	char		**env;
	int			exval;

	switch_signals(TRUE);
	env = (environ) ? ft_tabdup((const char**)environ) : ft_tabnew();
	set_env_var(&env, "SHELL", av[0]);
	getset_pwd_env(&env);
	if (!get_env_var(env, "PATH"))
		set_env_var(&env, "PATH", SH_DEFAULT_PATH);
	set_env_var(&env, "_", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL, &env);
	else
		exval = interactive_shell(&env);
	ft_tabfree(&env);
	return (exval);
}
