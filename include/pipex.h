/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:52:50 by jandre            #+#    #+#             */
/*   Updated: 2021/06/07 16:30:14 by jandre           ###   ########.fr       */
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
# include <sys/wait.h>
# include <errno.h>

// Define

# define EXIT_SUCCES 0
# define STDOUT 1
# define STDIN 0

// Structures

typedef struct s_pipex {
	int		number_process;
	char	***commands;
	char	*in_file;
	int		fd_in_file;
	char	*out_file;
	int		fd_out_file;
	char	**path;
}					t_pipex;

// Prototypes

size_t	ft_strlen(const char *s);
char	**ft_split(char	const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_path(t_pipex *pipex, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int 	find_which_path(t_pipex *pipex, char **command);
int 	error_malloc(t_pipex *pipex);
int 	error_pipe(t_pipex *pipex, int **pipe);
int		error_execute(t_pipex *pipex, int **pipe);
int		error_fork(t_pipex *pipex, int **pipe);
int 	pipex(t_pipex *pipex, char**envp);

#endif