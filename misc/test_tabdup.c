/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tabdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:06:42 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 21:11:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	char	**src;
	char	**dest;

	if (ac < 3)
		return (1);
	src = ft_strsplit(av[1], *av[2]);
	ft_puttab(src, "src");
	ft_putendl("---------------");
	dest = ft_tabdup((const char**)src);
	ft_puttab(dest, "dest");
	return (0);
}
