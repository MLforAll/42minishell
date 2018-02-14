/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/14 07:03:36 by kdumarai         ###   ########.fr       */
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
		return (SH_ERR_UNDEFINED);
	noent_msg = ft_strchr(path, '/') ? SH_ERR_NOENT : SH_ERR_NOCMD;
	if (access(path, F_OK) == -1)
		return (noent_msg);
	if (access(path, X_OK) == -1)
		return (SH_ERR_PERM);
	return (-1);
}

static int	exec_bincmd(t_cmd *cmd, char ***env)
{
	pid_t	pid;
	int		exval;

	exval = 0;
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		(!cmd->prev) ? close(cmd->c_pfd[0]) \
			: dup_out_to_pipe(STDIN_FILENO, cmd->prev->c_pfd[0]);
		(cmd->next) ? dup_out_to_pipe(STDOUT_FILENO, cmd->c_pfd[1]) \
			: close(cmd->c_pfd[1]);
		switch_signals(FALSE);
		set_env_var(env, "_", cmd->c_path);
		execve(cmd->c_path, cmd->c_argv, *env);
		exit(exec_shell(cmd->c_path, env) ? 0 : 127);
	}
	if (cmd->next)
		return (EXIT_SUCCESS);
	wait4(pid, &exval, 0, NULL);
	if (WIFSIGNALED(exval))
		msh_child_sighandler(WTERMSIG(exval));
	return (WEXITSTATUS(exval));
}

int			exec_cmd(t_cmd *cmd, char ***env)
{
	int		errval;
	int		exval;

	if (cmd->builtin)
		exval = (cmd->builtin)((int)ft_tablen((const char**)cmd->c_argv), \
			cmd->c_argv, env, (cmd->next) ? cmd->c_pfd[1] : STDOUT_FILENO);
	else
	{
		if ((errval = cmd_chk(cmd->c_path)) >= 0)
			return (msh_err_ret(errval, NULL, cmd->c_path, 127));
		exval = exec_bincmd(cmd, env);
	}
	(!cmd->next) ? close(cmd->c_pfd[0]) : 0;
	(cmd->next) ? close(cmd->c_pfd[1]) : 0;
	return (exval);
}

int			exec_cmds(char *line, char ***env)
{
	int		ret;
	t_cmd	*cmdp;
	t_cmd	*cbw;
	char	**cmds;
	char	**bw;

	cmds = ft_strsplit(line, ';');
	bw = cmds;
	ret = EXIT_SUCCESS;
	while (*bw)
	{
		cmdp = interpret_cmd(*bw, *env);
		cbw = cmdp;
		while (cbw)
		{
			if ((ret = exec_cmd(cbw, env)) > 0)
				break ;
			cbw = cbw->next;
		}
		bw++;
		ft_cmddel(&cmdp);
	}
	ft_tabfree(&cmds);
	return (ret);
}
