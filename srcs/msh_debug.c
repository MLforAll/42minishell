/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:20:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/24 21:23:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nums_debug(char *buff)
{
	ft_putstr("< ");
	while (*buff)
	{
		ft_putnbr(*buff);
		if (*(buff + 1))
			ft_putstr(" ; ");
		buff++;
	}
	ft_putstr(" >");
}
