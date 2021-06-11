/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:52:50 by jandre            #+#    #+#             */
/*   Updated: 2021/06/11 15:37:28 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Librairies
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
//# include <sys/wait.h>
# include <errno.h>

// Define

# define EXIT_SUCCES 0
# define STDOUT 1
# define STDIN 0
# define WRONG_ARG 1
# define PIPE_FAILED 2
# define STDOUT 1
# define STDin 0

// Structures

typedef struct s_pipex {
	char	***commands;
	int		fd_in_file;
	int		fd_out_file;
	char	**path;
}					t_pipex;

// Prototypes

size_t	ft_strlen(const char *s);
char	**ft_split(char	const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_path(t_pipex *pipex, char **envp, int *fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int 	find_which_path(t_pipex *pipex, char **command, int *fd);
int 	ft_pipex(t_pipex *pipex, char**envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_close(t_pipex *pipex, int *fd, int status);

#endif