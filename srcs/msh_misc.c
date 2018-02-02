/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/02 23:02:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdiff(char *base, char *check)
{
	if (!base || !check)
		return (NULL);
	while (*base && *check && *base == *check)
	{
		base++;
		check++;
	}
	return (base);
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
