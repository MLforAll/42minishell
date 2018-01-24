/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kelian <Kelian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 23:46:57 by Kelian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

int		exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		exval;

	pid = fork();
	exval = 0;
	if (pid == 0)
	{
		execve(cmd->c_path, cmd->c_argv, NULL);
		exit(127);
	}
	wait4(pid, &exval, 0, NULL);
	return (WEXITSTATUS(exval));
}
