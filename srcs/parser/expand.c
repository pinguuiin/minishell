/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:30:25 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 04:02:48 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_env_len(char *value, int	i, int *value_len)
{
	int		key_len;
	char	*env_name;
	t_info	*info;
	t_env	*env_list;

	key_len = 1;
	info = get_info();
	env_list = get_env_list(value, i, info);
	if (!env_list || !env_list->value)
		return (0);
	*value_len = ft_strlen(env_list->value);
	*value_len += 2; // for quote
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
	{
		i++;
		key_len++;
	}
	return (key_len);
}

int	calculate_total_len_of_value(char *value)
{
	int	i;
	int	value_len;
	int	key_len;
	int	in_double_quote;
	int	in_single_quote;

	i = 0;
	value_len = 0;
	key_len = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while(value[i])
	{
		if (value[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (value[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && value[i] == '$' && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
			key_len += calculate_env_len(value, i + 1, &value_len);
		i++;
	}
	return (i + value_len - key_len);
}

void	save_env_value_with_quote(char *value, char *expanded, int *i, int *j, t_info *info)
{
	t_env	*env_list;
	int		k;

	k = 0;
	env_list = get_env_list(value, i, info);
	if (env_list && env_list->value)
		expanded[(*j)++] = '\'';
	else
		return ;
	if ((env_list->value)[k] == ' ' || (env_list->value)[k] == '\t')
		expanded[(*j)++] = (env_list->value[k++]);
	k = skip_spaces(env_list->value, k);
	while((env_list->value)[k])
	{
		if (is_space_pair(env_list->value, k))
		{
			k++;
			continue ;
		}
		expanded[(*j)++] = (env_list->value)[k++];
	}
	expanded[(*j)++] = '\'';
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
}

void	save_expanded_value(char *value, char *expanded, int total_len, t_info *info)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (value[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && value[i] == '$' && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			i++;
			save_env_value_with_quote(value, expanded, &i, &j, info);
			continue ;
		}
		expanded[j++] = value[i++];
	}
	expanded[j] = '\0';
}

void	process_initial_space(char *result, int *result_i, char *src, int *src_i, char *value)
{
	t_info	*info;
	t_env	*env_list;

	info = get_info();
	if (value[0] == '$' && (ft_isalnum(value[1]) || value[1] == '_'))
	{
		env_list = get_env_list(value, 1, info);
		if (!env_list || !env_list->value || env_list->value[0] == '\0')
			return ;
		else if (is_only_whitespaces(env_list->value))
		{
			(*src_i)++;
			while (src[*src_i] && (src[*src_i] == ' ' || src[*src_i] == '\t'))
				(*src_i)++;
			(*src_i)++;
			return ;
		}
		(*src_i)++;
		while (src[*src_i] && (src[*src_i] == ' ' || src[*src_i] == '\t'))
			(*src_i)++;
		*(src_i)--;
		src[*src_i] = '\'';
	}
}

void	remove_quotes(char *src, t_info *info, char *value, char *result)
{
	int		src_i;
	int		result_i;
	int		in_single_quote;
	int		in_double_quote;

	src_i = 0;
	result_i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	process_initial_space(result, &result_i, src, &src_i, value);
	while (src[src_i])
	{
		if (src[src_i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (src[src_i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			result[result_i++] = src[src_i];
		src_i++;
	}
	result[result_i] = '\0';
}

char	*expand_value(char *value, t_info *info)
{
	int		total_value_len;
	char	*expanded_value;
	char	*result;

	total_value_len = calculate_total_len_of_value(value);
	expanded_value = aalloc(&(info->arena), total_value_len + 1);
	if (!expanded_value)
		clean_and_exit("memory allocation failed for expanded value");
	save_expanded_value(value, expanded_value, total_value_len, info);
	result = aalloc(&info->arena, total_value_len + 1);
	if (!result)
		clean_and_exit("memory allocation failed in expand result");
	remove_quotes(expanded_value, info, value, result);
	return (result);
}
