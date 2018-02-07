/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/07 07:40:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

static int	cmd_chk(char *path)
{
	int		noent_msg;

	if (!path)
		return (MSH_ERR_UNDEFINED);
	noent_msg = ft_strchr(path, '/') ? MSH_ERR_NOENT : MSH_ERR_NOCMD;
	if (access(path, F_OK) == -1)
		return (noent_msg);
	if (access(path, X_OK) == -1)
		return (MSH_ERR_PERM);
	return (-1);
}

int			exec_cmd(t_cmd *cmd, char ***env)
{
	pid_t	pid;
	int		exval;
	int		errval;
	//int		pipes;

	if (cmd->builtin)
	{
		return ((cmd->builtin)((int)ft_tablen((const char**)cmd->c_argv), \
			cmd->c_argv, env));
	}
	if ((errval = cmd_chk(cmd->c_path)) >= 0)
		msh_err_ret(errval, NULL, cmd->c_path, 127);
	//pipes = create_pipes(cmd);
	exval = 0;
	pid = fork();
	if (pid == 0)
	{
		set_env_var(env, "_", cmd->c_path);
		execve(cmd->c_path, cmd->c_argv, *env);
		exit(127);
	}
	wait4(pid, &exval, 0, NULL);
	return (WEXITSTATUS(exval));
}

int			exec_cmds(t_cmd *allcmds, char ***env)
{
	int		ret;

	while (allcmds)
	{
		ret = exec_cmd(allcmds, env);
		allcmds = allcmds->next;
	}
	return (ret);
}
