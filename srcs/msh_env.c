/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:31:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/30 20:18:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*get_env_var(char **env, const char *var)
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

static int		chg_env_var(char **env, const char *var, char *new)
{
	char	*tmp;

	if (!env)
		return (0);
	while (*env)
	{
		if ((tmp = ft_strstart(*env, (char*)var)) && *tmp == '=')
			break ;
		env++;
	}
	if (!*env)
		return (0);
	ft_strdel(env);
	*env = ft_strnew(ft_strlen(var) + ft_strlen(new) + 1);
	ft_strcat(*env, var);
	ft_strcat(*env, "=");
	ft_strcat(*env, new);
	return (1);
}

void	set_env_var(char ***env, const char *var, char *value)
{
	char		**old;
	char		*new_entry[2];
	char		entry_str[ft_strlen(var) + ft_strlen(value) + 2];

	if (chg_env_var(*env, var, value))
		return ;
	ft_strcpy(entry_str, var);
	ft_strcat(entry_str, "=");
	ft_strcat(entry_str, value);
	new_entry[0] = entry_str;
	new_entry[1] = NULL;
	old = *env;
	*env = ft_tabjoin((const char**)*env, (const char**)new_entry);
	ft_tabfree(&old);
}

void	set_env_from_str(char ***env, char *str)
{
	char	*eq;
	char	*var;
	char	*value;

	if (!(eq = ft_strchr(str, '=')))
		return ;
	var = ft_strnew(eq - str);
	ft_strncpy(var, str, eq - str);
	value = str + (eq - str) + 1;
	set_env_var(env, (const char*)var, value);
	ft_strdel(&var);
}

void	del_env_var(char ***env, const char *var)
{
	char	*tmp;
	char	**new_env;
	char	**bw;
	char	**bwn;

	new_env = (char**)malloc(sizeof(char*) * \
		(ft_tablen((const char**)*env) + 1));
	bwn = new_env;
	bw = *env;
	while (*bw)
	{
		if (!(tmp = ft_strstart(*bw, (char*)var)) || *tmp != '=')
			*(bwn++) = ft_strdup(*bw);
		bw++;
	}
	*bwn = NULL;
	ft_tabfree(env);
	*env = new_env;
}
