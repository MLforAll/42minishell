/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 21:09:12 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/15 22:27:57 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PROMPT_H
# define MSH_PROMPT_H

typedef struct	s_prompt
{
	char	*hostname;
	char	*pwd;
	char	*username;
}				t_prompt;

/*
** prompt
*/

char			*get_prompt_from_str(char *s, char **env);
char			*get_prompt(char **env);

#endif
