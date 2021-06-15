/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:52:50 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 16:54:09 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Librairies
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

// Prototypes

size_t	ft_strlen(const char *s);
char	**ft_split(char	const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_path(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*find_which_path(char **command, char **path);
char	*get_command(char **command, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		pipe_error(void);
int		fork_error(int *pfd);
int		command_error(char **command);
int		error_infile(char **argv);
int		error_outfile(char **argv);

#endif