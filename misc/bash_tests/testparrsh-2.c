/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testparrsh-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:44:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/06 17:34:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			main(void)
{
	ssize_t	rb;
	char	buff[32];

	write(STDERR_FILENO, "prg2\n", 5);
	sleep(2);
	while ((rb = read(STDIN_FILENO, buff, sizeof(buff))))
		write(STDOUT_FILENO, buff, rb);
}
