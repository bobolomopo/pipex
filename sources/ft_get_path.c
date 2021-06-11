/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:58:14 by jandre            #+#    #+#             */
/*   Updated: 2021/06/11 15:38:22 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int find_which_path(t_pipex *pipex, char **command, int *fd)
{
    int     temp_fd;
    int     i;
    char    *str;

    i = 0;
    while (pipex->path[i])
    {
        str = ft_strjoin(pipex->path[i], command[0]);
        if (!str)
            return (ft_close(pipex, fd, 0));
        temp_fd = open(str, O_RDONLY);
        if (temp_fd != -1)
            break ;
        free(str);
        close(temp_fd);
        i++;
    }
    if (pipex->path[i] == NULL)
        return (ft_close(pipex, fd, 0));
    return (i);
}

int	get_path(t_pipex *pipex, char **envp, int *fd)
{
    int     i;
    char    *str;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 4) == 0)
        {
            str = ft_strdup(envp[i] + 5);
            if (!str)
                return (ft_close(pipex, fd, 0));
            pipex->path = ft_split(str, ':');
            if (!pipex->path)
                return (ft_close(pipex, fd, 0));
            free(str);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}