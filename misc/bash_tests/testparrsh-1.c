/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testparrsh-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:44:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/06 17:34:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

int			main(void)
{
	size_t	len;

	len = 150;
	write(STDERR_FILENO, "prg1\n", 5);
	sleep(3);
	while (len--)
	{
		ft_putchar(arc4random_uniform(93) + 33);
		usleep(500);
	}
}
