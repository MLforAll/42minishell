/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_csrkeys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/23 18:01:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

int			rl_csr_keys(char *buff, t_cursor *csr)
{
	int		ret;
	int		keys[2];

	keys[0] = (ft_strcmp(ESC_RIGHTK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_LEFTK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	ret = -1;
	if (keys[0] && csr->pos < csr->max)
	{
		csr->pos++;
		ret = 1;
	}
	if (keys[1] && csr->pos > 0)
	{
		csr->pos--;
		ret = 1;
	}
	if (ret == 1)
		ft_putstr_fd(buff, STDIN_FILENO);
	return (ret);
}

static void	configure_hekeys(int k[2], size_t *len, char **ckey, t_cursor *csr)
{
	if (!k || !len || !ckey || !csr)
		return ;
	if (k[0] && csr->pos < csr->max)
	{
		*len = csr->max - csr->pos;
		*ckey = ESC_RIGHTK;
		csr->pos = csr->max;
	}
	else if (k[1] && csr->pos > 0)
	{
		*len = csr->pos;
		*ckey = ESC_LEFTK;
		csr->pos = 0;
	}
}

int			rl_home_end_keys(char *buff, t_cursor *csr)
{
	int		keys[2];
	size_t	len;
	char	*ckey;
	char	*seq;

	keys[0] = (ft_strcmp(ESC_ENDK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_HOMEK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	len = 0;
	configure_hekeys(keys, &len, &ckey, csr);
	if (len == 0 || !(seq = ft_strnew(len * ft_strlen(ckey))))
		return (-1);
	while (len--)
		ft_strcat(seq, ckey);
	ft_putstr_fd(seq, STDIN_FILENO);
	free(seq);
	return (1);
}
