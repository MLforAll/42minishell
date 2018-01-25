/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:31:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 19:38:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

char	*get_env_var(const char *var, char **env)
{
	char	*ret;

	if (!env)
		return (NULL);
	while (*env)
	{
		if ((ret = ft_strstart(*env, (char*)var)) && *ret == '=')
			return (ret + 1);
		env++;
	}
	return (NULL);
}

void	chg_env_var(const char *var, char *new, char **env)
{
	char	*tmp;

	while (*env)
	{
		if ((tmp = ft_strstart(*env, (char*)var)) && *tmp == '=')
			break ;
		env++;
	}
	if (!env)
		return ;
	ft_strdel(env);
	*env = ft_strnew(ft_strlen(var) + ft_strlen(new) + 1);
	ft_strcat(*env, var);
	ft_strcat(*env, "=");
	ft_strcat(*env, new);
}
