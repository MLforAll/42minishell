/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_direxp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/26 22:17:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "minishell.h"

char	*get_basedir(const char *path)
{
	char	*ret;
	char	*rchr_ret;

	if (!(rchr_ret = ft_strrchr(path, '\n')))
		return (ft_strdup("."));
	if (!(ret = ft_strnew(rchr_ret - path)))
		return (NULL);
	ft_strncpy(ret, path, rchr_ret - path);
	return (ret);
}

char	*search_dir_for_exec(const char *path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dird;
	char			*elem_path;
	struct stat		st;
	int				stat_ret;

	if (!(dirp = opendir(path)))
		return (NULL);
	elem_path = NULL;
	while ((dird = readdir(dirp)))
	{
		elem_path = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1);
		ft_strcat(elem_path, path);
		ft_strcat(elem_path, "/");
		ft_strcat(elem_path, dird->d_name);
		stat_ret = stat(elem_path, &st);
		if (stat_ret != -1 && (st.st_mode & S_IXUSR || st.st_mode & S_IXGRP
			|| st.st_mode & S_IXOTH) && ft_strcmp(dird->d_name, name) == 0)
			break ;
		ft_strdel(&elem_path);
	}
	//free(dird);
	closedir(dirp);
	return (elem_path);
}

t_list	*search_execs_begin(const char *path, const char *name)
{
	t_list			*ret;
	DIR				*dirp;
	struct dirent	*dird;
	char			*elem_path;
	struct stat		st;

	if (!(dirp = opendir(path)))
		return (NULL);
	ret = NULL;
	while ((dird = readdir(dirp)))
	{
		elem_path = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1);
		ft_strcat(elem_path, path);
		ft_strcat(elem_path, "/");
		ft_strcat(elem_path, dird->d_name);
		if (stat(elem_path, &st) != -1 && (st.st_mode & S_IXUSR
			|| st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
			&& ft_strncmp(dird->d_name, name, ft_strlen(name)) == 0)
			ft_lstadd(&ret, ft_lstnew(elem_path, ft_strlen(elem_path)));
		ft_strdel(&elem_path);
	}
	closedir(dirp);
	return (ret);
}
