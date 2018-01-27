/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:27:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void		msh_err(int errc, const char *bltn, const char *path)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	if (bltn)
	{
		ft_putstr_fd(bltn, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(path, STDERR_FILENO);
	if (errc == 1)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (errc == 2)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (errc == 3)
		ft_putendl_fd(": Can't cd to directory", STDERR_FILENO);
}
