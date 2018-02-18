/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/18 08:48:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "minishell.h"

static void	msh_puterr(int errc)
{
	if (errc == SH_ERR_NOCMD)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errc == SH_ERR_NOENT)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	else if (errc == SH_ERR_NOCD)
		ft_putendl_fd("Can't cd to directory", STDERR_FILENO);
	else if (errc == SH_ERR_NOSET)
		ft_putendl_fd("not set", STDERR_FILENO);
	else if (errc == SH_ERR_TMARG)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else if (errc == SH_ERR_PERM)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	else if (errc == SH_ERR_FORK)
		ft_putendl_fd("Fork failed", STDERR_FILENO);
	else if (errc == SH_ERR_TMLNK)
		ft_putendl_fd("Too many symbolic links", STDERR_FILENO);
	else if (errc == SH_ERR_NOTDIR)
		ft_putendl_fd("Not a directory", STDERR_FILENO);
	else if (errc == SH_ERR_NUMARG)
		ft_putendl_fd("numeric argument required", STDERR_FILENO);
	else if (errc == SH_ERR_INVID)
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	else
		ft_putendl_fd("Undefined error", STDERR_FILENO);
}

int			msh_err(int errc, const char *bltn, const char *path)
{
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (bltn)
	{
		ft_putstr_fd(bltn, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd((errc == SH_ERR_NOSET) ? " " : ": ", STDERR_FILENO);
	}
	msh_puterr(errc);
	return (1);
}

int			msh_err_ret(int errc, const char *bltn, const char *path, int retv)
{
	msh_err(errc, bltn, path);
	return (retv);
}

void		msh_child_sighandler(int sigc)
{
	const char	*errs[] = {"Hangup", NULL, NULL, "Illegal instruction",
		"Trace/BPT trap", "Abort trap", "EMT trap", "Floating point exception",
		"Killed", "Bus error", "Segmentation fault",
		"Bad system call", NULL, "Alarm clock", "Terminated",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Cputime limit exceeded",
		"Filesize limit exceeded", "Virtual timer expired",
		"Profiling timer expired", NULL, NULL,
		"User defined signal 1", "User defined signal 2"};

	ft_putchar('\n');
	if (sigc < 0 || sigc > 31 || !errs[sigc - 1])
		return ;
	ft_putstr_fd(errs[sigc - 1], STDIN_FILENO);
	ft_putstr_fd(": ", STDIN_FILENO);
	ft_putnbr_fd(sigc, STDIN_FILENO);
	ft_putchar_fd('\n', STDIN_FILENO);
}

int			get_errcode_for_path(const char *path, int mode, int dir)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
		return ((lstat(path, &st) == 0) ? SH_ERR_TMLNK : SH_ERR_NOENT);
	if (dir)
	{
		if (stat(path, &st) == -1)
			return (SH_ERR_UNDEFINED);
		if (!S_ISDIR(st.st_mode))
			return (SH_ERR_NOTDIR);
	}
	if (access(path, mode) == -1)
		return (SH_ERR_PERM);
	return (SH_ERR_UNDEFINED);
}
