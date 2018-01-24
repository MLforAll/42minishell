/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_direxp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kelian <Kelian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/23 23:42:32 by Kelian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "minishell.h"

char	*search_dir_for_exec(const char *path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dird;
	char			*elem_path;
	struct stat		st;

	if (!(dirp = opendir(path)))
		return (NULL);
	elem_path = NULL;
	while ((dird = readdir(dirp)))
	{
		elem_path = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1);
		ft_strcat(elem_path, path);
		ft_strcat(elem_path, "/");
		ft_strcat(elem_path, dird->d_name);
		stat(elem_path, &st);
		if ((st.st_mode & S_IXUSR || st.st_mode & S_IXGRP
			|| st.st_mode & S_IXOTH) && ft_strcmp(dird->d_name, name) == 0)
			break ;
		ft_strdel(&elem_path);
	}
	//free(dird);
	closedir(dirp);
	return (elem_path);
}
