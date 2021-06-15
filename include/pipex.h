/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:52:50 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 15:36:01 by jandre           ###   ########.fr       */
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
# define WRONG_ARG 1
# define PIPE_FAILED 2
# define STDOUT 1
# define STDin 0

// Prototypes

size_t	ft_strlen(const char *s);
char	**ft_split(char	const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_path(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char 	*find_which_path(char **command, char **path);
char 	*get_command(char **command, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif