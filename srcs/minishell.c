/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/22 05:32:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int			main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	signal(SIGINT, SIG_IGN);
	line = readline("$> ");
	ft_putstr("line is: ");
	ft_putendl(line);
	free(line);
	return (0);
}
