/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/14 08:07:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
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

void	switch_signals(int ign)
{
	void	(*act)(int);

	act = (ign) ? SIG_IGN : SIG_DFL;
	signal(SIGINT, act);
	signal(SIGTERM, act);
	signal(SIGTSTP, SIG_IGN);
}
