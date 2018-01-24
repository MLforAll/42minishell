/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/24 22:43:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

int		exec_cmd(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		exval;

	exval = 0;
	pid = fork();
	if (pid == 0)
	{
		chg_env_var("_", cmd->c_path, env);
		execve(cmd->c_path, cmd->c_argv, env);
		msh_err(1, cmd->c_path);
		exit(127);
	}
	wait4(pid, &exval, 0, NULL);
	return (WEXITSTATUS(exval));
}

int		exec_cmds(t_cmd *allcmds, char **env)
{
	int		ret;

	while (allcmds)
	{
		ret = exec_cmd(allcmds, env);
		allcmds = allcmds->next;
	}
	return (ret);
}
