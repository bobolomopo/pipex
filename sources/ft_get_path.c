/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:58:14 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 17:23:20 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_which_path(char **command, char **path)
{
	int		temp_fd;
	int		i;
	char	*str;

	i = 0;
	command[0] = ft_strjoin("/", command[0]);
	while (path[i])
	{
		str = ft_strjoin(path[i], command[0]);
		temp_fd = open(str, O_RDONLY);
		if (temp_fd != -1)
			break ;
		if (temp_fd != -1)
			close(temp_fd);
		i++;
	}
	command[0] = command[0] + 1;
	return (str);
}

char	**get_path(char **envp)
{
	char	**path;
	char	*str;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			str = envp[i] + 5;
			path = ft_split(str, ':');
			if (!path)
				exit(0);
		}
		i++;
	}
	return (path);
}

char	*get_command(char **command, char **envp)
{
	char	**path;

	path = get_path(envp);
	return (find_which_path(command, path));
}
