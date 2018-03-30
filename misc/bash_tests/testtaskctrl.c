/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:44:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/05 19:49:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFF_SIZE
# define BUFF_SIZE	32
#endif
#ifndef TIMES
# define TIMES		150
#endif

int		main(void)
{
	size_t	cnt;
	char	buff[BUFF_SIZE + 1];
	ssize_t	rb;

	cnt = TIMES;
	while (cnt--)
	{
		rb = read(STDIN_FILENO, buff, BUFF_SIZE);
		buff[rb] = '\0';
		printf("%s", buff);
	}
	puts("");
	return (0);
}
