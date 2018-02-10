/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 23:08:57 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/10 23:11:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		main(int ac, char **av)
{
	int		exc;

	if (ac == 1)
	{
		printf("Nah!\n");
		return (1);
	}
	exc = atoi(av[1]);
	printf("exiting with code: %i\n", exc);
	return (exc);
}
