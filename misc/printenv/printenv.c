/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:57:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/25 18:58:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	for (; *env; env++)
		puts(*env);
	return (0);
}
