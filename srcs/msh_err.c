/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/07 04:18:13 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static void	msh_puterr(int errc)
{
	if (errc == MSH_ERR_NOCMD)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errc == MSH_ERR_NOENT)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	else if (errc == MSH_ERR_NOCD)
		ft_putendl_fd("Can't cd to directory", STDERR_FILENO);
	else if (errc == MSH_ERR_NOSET)
		ft_putendl_fd("not set", STDERR_FILENO);
	else if (errc == MSH_ERR_TMARG)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else if (errc == MSH_ERR_PERM)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd("Undefined error", STDERR_FILENO);
}

static void	msh_prep_err(int errc, const char *bltn, const char *path)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	if (bltn)
	{
		ft_putstr_fd(bltn, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd((errc == MSH_ERR_NOSET) ? " " : ": ", STDERR_FILENO);
	}
	msh_puterr(errc);
}

int			msh_err(int errc, const char *bltn, const char *path)
{
	msh_prep_err(errc, bltn, path);
	return (1);
}

int			msh_err_ret(int errc, const char *bltn, const char *path, int retv)
{
	msh_prep_err(errc, bltn, path);
	return (retv);
}
