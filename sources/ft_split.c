/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:33:12 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 16:57:24 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_nbrwords(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**ft_refree(char **res, int index)
{
	while (--index > 0)
		free(res[index]);
	free(res);
	return (NULL);
}

static char	**ft_write_words(char **result, int nbrmot,
		const char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	while (s[++i] && k < nbrmot - 1)
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i + j] && s[i + j] != c)
			j++;
		result[++k] = ft_substr(s, i, j);
		if (!result[k])
			return (ft_refree(result, k));
		i = i + j;
	}
	k++;
	result[k] = NULL;
	return (result);
}

char	**ft_split(char	const *s, char c)
{
	char	**result;
	int		nbrmot;

	if (!s)
		return (NULL);
	nbrmot = ft_nbrwords(s, c);
	result = (char **)malloc(sizeof(char *) * (nbrmot + 1));
	if (!result)
		return (NULL);
	return (ft_write_words(result, nbrmot, s, c));
}
