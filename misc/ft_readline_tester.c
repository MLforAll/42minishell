/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_tester.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/18 01:37:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_readline.h"

int		main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt;
	t_history	*hist;

	hist = NULL;
	prompt = "\033[1;31mft_readline\033[0;39m$ ";
	ft_putendl_fd("This tool is used for debug purposes ONLY!", STDIN_FILENO);
	ft_putstr_fd("Type something and check if the returned ", STDIN_FILENO);
	ft_putendl_fd("result is OK", STDIN_FILENO);
	ft_putstr_fd("PS: Autocompletion works for either commands ", STDIN_FILENO);
	ft_putendl_fd("in PATH env var or folders/files", STDIN_FILENO);
	ft_putstr_fd("PS2: Ctrl-D to quit!\n\n", STDIN_FILENO);
	while ((line = ft_readline(prompt, env, &hist)))
	{
		ft_putstr_fd("-----------> ", STDIN_FILENO);
		ft_putstr_fd(line, STDIN_FILENO);
		ft_putstr_fd("\n\n", STDIN_FILENO);
		ft_strdel(&line);
	}
	ft_histdel(&hist);
	return (0);
}
