/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:30:25 by donheo            #+#    #+#             */
/*   Updated: 2025/07/04 11:37:50 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dollar_expansion(const char *value, \
	int *i, int *value_len, t_info *info)
{
	int	key_len;

	key_len = 0;
	if (value[*i + 1] == '?')
	{
		*value_len += itoa_len(info->exit_code);
		(*i)++;
		return (2);
	}
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
	{
		(*i)++;
		key_len = calculate_env_len(value, i, value_len);
		return (key_len);
	}
	return (0);
}

static int	compute_expanded_len(const char *value, \
	int in_single_quote, int in_double_quote, t_info *info)
{
	int	i;
	int	value_len;
	int	key_len;

	i = 0;
	value_len = 0;
	key_len = 0;
	while (value[i])
	{
		update_quote_state(value[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && value[i] == '$')
		{
			key_len += handle_dollar_expansion(value, &i, &value_len, info);
		}
		i++;
	}
	return (i + value_len - key_len);
}

static int	write_dollar_expansion(const char *value, \
	char *expanded, int *i, int *j)
{
	char	*exit;
	int		k;
	t_info	*info;

	info = get_info();
	if (value[*i + 1] == '?')
	{
		exit = ft_arena_itoa(info->exit_code);
		k = 0;
		while (exit[k])
			expanded[(*j)++] = exit[k++];
		*i += 2;
		return (1);
	}
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
	{
		(*i)++;
		save_env_value_with_del(value, expanded, i, j);
		return (1);
	}
	return (0);
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
		if (!in_single_quote && value[i] == '$' \
			&& write_dollar_expansion(value, expanded, &i, &j))
			continue ;
		expanded[j++] = value[i++];
	}
	expanded[j] = '\0';
}

char	*expand_value(const char *value, t_cmd *cmd, t_info *info)
{
	int		total_value_len;
	char	*expanded_value;

	total_value_len = compute_expanded_len(value, 0, 0, info);
	expanded_value = aalloc(&(info->arena), total_value_len + 1);
	if (!expanded_value)
		clean_and_exit("expanded value");
	save_expanded_value(value, expanded_value);
	if (is_empty_string(expanded_value, 0, 0, cmd))
		return (get_empty_string(info));
	remove_quotes(expanded_value);
	remove_delimiter(expanded_value);
	return (expanded_value);
}
