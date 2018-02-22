/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/22 04:40:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "libft.h"

int		free_return(void **data, int retv)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (retv);
}

void	switch_signals(int ign)
{
	void	(*act)(int);

	act = (ign) ? SIG_IGN : SIG_DFL;
	signal(SIGINT, act);
	signal(SIGTERM, act);
	signal(SIGTSTP, SIG_IGN);
}