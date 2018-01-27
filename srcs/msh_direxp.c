/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_direxp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/27 22:47:18 by kdumarai         ###   ########.fr       */
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

	if (*path == '/')
		return (ft_strsub(path, 0, 1));
	if (!(rchr_ret = ft_strrchr(path, '/')))
		return (ft_strdup("."));
	if (!(ret = ft_strnew(rchr_ret - path)))
		return (NULL);
	ft_strncpy(ret, path, rchr_ret - path);
	return (ret);
}

static int	is_exec(const char *path, int folder)
{
	struct stat		st;

	if (stat(path, &st) != -1 && (st.st_mode & S_IXUSR
		|| st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
		&& S_ISDIR(st.st_mode) == folder)
		return (1);
	return (0);
}

char	*search_dir_for_exec(const char *path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dird;
	char			*elem_path;

	if (!(dirp = opendir(path)))
		return (NULL);
	elem_path = NULL;
	while ((dird = readdir(dirp)))
	{
		elem_path = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1);
		ft_strcat(elem_path, path);
		ft_strcat(elem_path, "/");
		ft_strcat(elem_path, dird->d_name);
		if (ft_strcmp(dird->d_name, name) == 0 && is_exec(elem_path, NO))
			break ;
		ft_strdel(&elem_path);
	}
	//free(dird);
	closedir(dirp);
	return (elem_path);
}

t_list	*search_execs_begin(const char *path, const char *search_dir)
{
	t_list			*ret;
	DIR				*dirp;
	struct dirent	*dird;
	char			*basedir;
	char			*name;

	basedir = (!search_dir) ? get_basedir(path) : (char*)search_dir;
	name = ft_strrchr(path, '/');
	name = (name) ? name + 1 : (char*)path;
	if (!(dirp = opendir(basedir)))
		return (NULL);
	ret = NULL;
	while ((dird = readdir(dirp)))
	{
		if (ft_strncmp(dird->d_name, name, ft_strlen(name)) == 0)
		{
			ft_lstadd(&ret, ft_lstnew(dird->d_name, dird->d_namlen));
			if (dird->d_type == DT_DIR)
				ft_stradd((char**)&ret->content, "/");
		}
	}
	closedir(dirp);
	if (!search_dir)
		ft_strdel(&basedir);
	return (ret);
}
