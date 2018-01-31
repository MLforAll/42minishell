/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/31 20:25:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		msh_err(int errc, const char *bltn, const char *path)
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
		ft_putstr_fd((errc == 4) ? " " : ": ", STDERR_FILENO);
	}
	if (errc == 1)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else if (errc == 2)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	else if (errc == 3)
		ft_putendl_fd("Can't cd to directory", STDERR_FILENO);
	else if (errc == 4)
		ft_putendl_fd("not set", STDERR_FILENO);
	else if (errc == 5)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else if (errc == 6)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	return (1);
}
