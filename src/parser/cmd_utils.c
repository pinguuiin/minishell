/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:13:07 by donheo            #+#    #+#             */
/*   Updated: 2025/07/04 09:54:37 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_delimiter(char *expanded_value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (expanded_value[i] == DELIMITER)
		i++;
	while (expanded_value[i])
	{
		if (expanded_value[i] == DELIMITER)
		{
			expanded_value[j++] = expanded_value[i++];
			while (expanded_value[i] == DELIMITER)
				i++;
			continue ;
		}
		expanded_value[j++] = expanded_value[i++];
	}
	if (j > 0 && expanded_value[j - 1] == DELIMITER)
		expanded_value[j - 1] = '\0';
	else
		expanded_value[j] = '\0';
}

static int	count_tokens_by_delimiter(const char *str)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*str)
	{
		if (*str == DELIMITER)
			in_token = 0;
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*copy_word(const char *start, const char *end, t_info *info)
{
	int		len;
	char	*result;

	len = end - start;
	result = aalloc(&(info->arena), len + 1);
	if (!result)
		clean_and_exit("cmd");
	ft_memcpy(result, start, len);
	result[len] = '\0';
	return (result);
}

char	**divide_by_delimiter(char *value, t_info *info)
{
	int		i;
	int		k;
	char	**result;
	char	*start;
	int		count;

	i = 0;
	k = 0;
	count = count_tokens_by_delimiter(value);
	result = aalloc(&(info->arena), sizeof(char *) * (count + 1));
	if (!result)
		clean_and_exit("words");
	while (value[i])
	{
		if (value[i] == DELIMITER)
			i++;
		if (!value[i])
			break ;
		start = &value[i];
		while (value[i] && value[i] != DELIMITER)
			i++;
		result[k++] = copy_word(start, &value[i], info);
	}
	result[k] = NULL;
	return (result);
}
