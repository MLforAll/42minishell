/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_misc_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 23:54:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	get_last_strc(char *s)
{
	if (!s)
		return ('\0');
	while (*s)
		s++;
	return (*s);
}

char	*get_last_tabitem(char **tab)
{
	while (*tab)
	{
		if (!*(tab + 1))
			break ;
		tab++;
	}
	return (*tab);
}

char	*get_last_component(const char *str, char c)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = ft_strrchr(str, c);
	return ((tmp) ? tmp + 1 : (char*)str);
}

char	*get_name_from_path(const char *path)
{
	if (!path)
		return (NULL);
	if (ft_strcmp((char*)path, "/") == 0)
		return ((char*)path);
	return (get_last_component(path, '/'));
}

char	*get_name_from_path_2(const char *path)
{
	char	*tmp;
	char	*chr;
	size_t	len;
	size_t	len_to_slash;

	if ((tmp = get_name_from_path(path)) && *tmp)
		return (ft_strdup(tmp));
	if (!tmp)
		return (NULL);
	if ((len = ft_strlen(path)) == 0)
		return (NULL);
	tmp = (char*)path + len - 1;
	while (len--)
	{
		if (*tmp == '/' && tmp[1])
			break ;
		tmp--;
	}
	tmp++;
	if (!(chr = ft_strchr(tmp, '/')))
		return (ft_strdup(tmp));
	len_to_slash = chr - tmp;
	return (ft_strsub(tmp, 0, len_to_slash));
}
