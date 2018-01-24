/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:31:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/24 22:48:26 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
	char	*env_var;

	env_var = get_env_var(var, env);
	if (!env_var)
		return ;
	ft_strcpy(env_var, new);
}
