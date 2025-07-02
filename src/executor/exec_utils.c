/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:18:59 by piyu              #+#    #+#             */
/*   Updated: 2025/07/02 19:00:47 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*arena_strjoin(t_arena **arena_ptr, char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new_s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_s = aalloc(arena_ptr, len1 + len2 + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new_s[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		new_s[i] = s2[i - len1];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_up(t_arena **arena_ptr, const char *start, size_t len)
{
	char	*word;

	word = aalloc(arena_ptr, len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static int	copy_word(t_arena **arena_ptr, char const *s, char c, char **split)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			split[i] = word_up(arena_ptr, start, s - start);
			if (!split[i])
				return (1);
			i++;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (0);
}

char	**arena_split(t_arena **arena_ptr, char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = aalloc(arena_ptr, (count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (copy_word(arena_ptr, s, c, split))
		return (NULL);
	return (split);
}
