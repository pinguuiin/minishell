/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:13:07 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 00:56:50 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *value, int i, int j)
{
	int		in_single_quote;
	int		in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
		}
		else if (value[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
		}
		else
			value[j++] = value[i++];
	}
	value[j] = '\0';
}

void	remove_delimiter(char *expanded_value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (expanded_value[i] == 127)
		i++;
	while (expanded_value[i])
	{
		if (expanded_value[i] == 127)
		{
			expanded_value[j++] = expanded_value[i++];
			while (expanded_value[i] == 127)
				i++;
			continue;
		}
		expanded_value[j++] = expanded_value[i++];
	}
	if (expanded_value[j - 1] == 127)
		expanded_value[j - 1] = '\0';
	else
		expanded_value[j] = '\0';
}

static int	split_cmds(char *str)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*str)
	{
		if (*str == 127)
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

static char	*copy_cmd(char *start, char *end, t_info *info)
{
	int		len;
	char	*result;

	len = end - start;
	result = aalloc(&(info->arena), len + 1);
	if (!result)
		clean_and_exit("memory allocation fails for cmd");
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
	count = split_cmds(value);
	result = aalloc(&(info->arena), sizeof(char *) * (count + 1));
	if (!result)
		clean_and_exit("memory allocation fails for cmds");
	while (value[i])
	{
		if (value[i] == 127)
			i++;
		start = &value[i];
		while (value[i] && value[i] != 127)
			i++;
		result[k++] = copy_cmd(start, &value[i], info);
	}
	result[k] = NULL;
	return (result);
}
