/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:22:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 20:06:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmd_list(char *line)
{
	char		**cmds;
	t_cmd		*ret;
	t_cmd		*new;

	ret = NULL;
	cmds = ft_strsplit(line, ';');
	while (*cmds)
	{
		new = ft_cmdnew();
		new->c_argv = ft_strsplit(*cmds, ' ');
		new->c_path = *new->c_argv;
		ft_cmdpb(&ret, new);
		cmds++;
	}
	return (ret);
}
