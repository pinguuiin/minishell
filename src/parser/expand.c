/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:30:25 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 22:40:28 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_expansion(const char *value, \
int *i, int *value_len, t_info *info)
{
	if (value[*i] && value[*i] == '?')
	{
		*value_len += itoa_len(info->exit_code);
		(*i)++;
	}
	else if (value[*i] && (ft_isalpha(value[*i]) || value[*i] == '_'))
		calculate_env_len(value, i, value_len);
}

static int	compute_expanded_len(const char *value, \
int in_single_quote, int in_double_quote, t_info *info)
{
	int	i;
	int	value_len;
	int	old_i;

	i = 0;
	value_len = 0;
	while (value[i])
	{
		update_quote_state(value[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && value[i] == '$')
		{
			i++;
			old_i = i;
			handle_dollar_expansion(value, &i, &value_len, info);
			if (old_i == i)
				value_len++;
			continue ;
		}
		value_len++;
		i++;
	}
	return (value_len);
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
		if (!in_single_quote && value[i] == '$' && value[i + 1] == '?' \
&& write_exit_code(expanded, &i, &j))
			continue ;
		else if (!in_single_quote && in_double_quote && value[i] == '$' \
&& write_env_with_double_quote(value, expanded, &i, &j))
			continue ;
		else if (!in_single_quote && value[i] == '$' \
&& write_env(value, expanded, &i, &j))
			continue ;
		expanded[j++] = value[i++];
	}
	expanded[j] = '\0';
}

char	*expand_value(const char *value, t_info *info)
{
	int		total_value_len;
	char	*expanded_value;
	char	*empty_str;

	total_value_len = compute_expanded_len(value, 0, 0, info);
	expanded_value = aalloc(&(info->arena), total_value_len + 1);
	if (!expanded_value)
		clean_and_exit("expanded value");
	save_expanded_value(value, expanded_value);
	if (is_empty_string(expanded_value, 0, 0))
	{
		empty_str = aalloc(&(info->arena), 2);
		if (!empty_str)
			clean_and_exit("empty string for word");
		empty_str[0] = EMPTY_STR;
		empty_str[1] = '\0';
		return (empty_str);
	}
	remove_quotes(expanded_value);
	remove_delimiter(expanded_value);
	return (expanded_value);
}
