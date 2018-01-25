/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 17:31:48 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void		msh_err(int errc, const char *path)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (errc == 1)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (errc == 2)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}
