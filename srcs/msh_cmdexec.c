/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmdexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/09 08:03:25 by kdumarai         ###   ########.fr       */
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

static void	exec_scpt(t_cmd *cmd, char *shpath, char **env)
{
	char	*av_f[2];
	char	**av;

	if (!shpath)
		return ;
	av_f[0] = shpath;
	av_f[1] = NULL;
	av = ft_tabjoin((const char**)av_f, (const char**)cmd->c_argv);
	execve(shpath, av, env);
}

int			exec_cmd(t_cmd *cmd, char *shpath, char ***env)
{
	pid_t	pid;
	int		exval;
	int		errval;

	if (cmd->builtin)
	{
		return ((cmd->builtin)((int)ft_tablen((const char**)cmd->c_argv), \
			cmd->c_argv, env));
	}
	if ((errval = cmd_chk(cmd->c_path)) >= 0)
		msh_err_ret(errval, NULL, cmd->c_path, 127);
	exval = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGTERM, SIG_DFL);
		set_env_var(env, "_", cmd->c_path);
		execve(cmd->c_path, cmd->c_argv, *env);
		exec_scpt(cmd, shpath, *env);
		exit(127);
	}
	wait4(pid, &exval, 0, NULL);
	if (WIFSIGNALED(exval))
		msh_child_sighandler(WTERMSIG(exval));
	return (WEXITSTATUS(exval));
}

int			exec_cmds(char *line, char *shpath, char ***env)
{
	int		ret;
	t_cmd	*props;
	char	**cmds;
	//char	**pipes;
	char	**bw;

	cmds = ft_strsplit(line, ';');
	bw = cmds;
	while (*bw)
	{
		props = ft_cmdnew();
		interpret_cmd(props, *bw, *env);
		ret = exec_cmd(props, shpath, env);
		bw++;
		ft_cmddel(&props);
	}
	ft_tabfree(&cmds);
	return (ret);
}
