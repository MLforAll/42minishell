/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 20:54:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

int		exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		exval;

	pid = fork();
	if (pid == 0)
		execve(cmd->c_path, cmd->c_argv, NULL);
	wait4(pid, &exval, 0, NULL);
	return (exval);
}
