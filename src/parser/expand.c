/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:30:25 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 16:48:07 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_env_len(const char *value, int i, int *value_len)
{
	int		key_len;
	t_info	*info;
	t_env	*env_list;

	key_len = 1;
	info = get_info();
	env_list = find_env_by_name(value, i, info);
	if (!env_list || !env_list->value)
	{
		(*value_len)++;
		return (0);
	}
	*value_len = ft_strlen(env_list->value);
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
	{
		i++;
		key_len++;
	}
	return (key_len);
}

static int	compute_expanded_len(const char *value)
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
	while (value[i])
	{
		update_quote_state(value[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && value[i] == '$' && value[i + 1] && \
(ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			i++;
			key_len += calculate_env_len(value, i, &value_len);
		}
		i++;
	}
	return (i + value_len - key_len);
}

static void	save_env_value_with_del(const char *value, char *expanded, \
int *i, int *j)
{
	t_env	*env_list;
	int		k;
	t_info	*info;

	k = 0;
	info = get_info();
	env_list = find_env_by_name(value, *i, info);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (!env_list || !env_list->value)
	{
		expanded[(*j)++] = DELIMITER;
		return ;
	}
	while ((env_list->value)[k])
	{
		if ((env_list->value)[k] == ' ' || (env_list->value)[k] == '\t')
		{
			expanded[(*j)++] = DELIMITER;
			k = skip_spaces(env_list->value, k);
			continue ;
		}
		expanded[(*j)++] = (env_list->value)[k++];
	}
}

static void	save_expanded_value(const char *value, char *expanded)
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
		update_quote_state(value[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && value[i] == '$' && \
(ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			i++;
			save_env_value_with_del(value, expanded, &i, &j);
			continue ;
		}
		expanded[j++] = value[i++];
	}
	expanded[j] = '\0';
}

char	*expand_value(const char *value, t_info *info, t_cmd *cmd)
{
	int		total_value_len;
	char	*expanded_value;

	total_value_len = compute_expanded_len(value);
	expanded_value = aalloc(&(info->arena), total_value_len + 1);
	if (!expanded_value)
		clean_and_exit("expanded value");
	save_expanded_value(value, expanded_value);
	check_only_quote_and_del(expanded_value, 0, 0, cmd);
	remove_quotes(expanded_value);
	remove_delimiter(expanded_value);
	return (expanded_value);
}
