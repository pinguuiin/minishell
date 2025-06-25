/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ambiguous.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:24:01 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 02:13:20 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space_in_a_env(const char *value, int i, t_info *info)
{
	t_env	*env_list;

	i++;
	env_list = get_env_list(value, i, info);
	if (!env_list || !env_list->value)
		return (0);
	i = 0;
	while ((env_list->value)[i])
	{
		if ((env_list->value)[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_space_in_value(const char *value, t_info *info)
{
	int		in_double_quote;
	int		in_single_quote;
	int		i;

	i = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while ((value)[i])
	{
		if (value[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (value[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && value[i] == '$' && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			if (check_space_in_a_env(value, i, info))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_empty_in_a_env(char *value, int i, t_info *info)
{
	t_env	*env_list;
	int		i;

	env_list = get_env_list(value, i, info);
	if (!env_list || !env_list->value)
		return (1);
	i = 0;
	while ((env_list->value)[i])
	{
		if ((env_list->value)[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_empty_in_value(char *value, t_info *info)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			if (!check_empty_in_a_env(value, i + 1, info))
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_ambiguous_redir(t_token *token, t_info *info)
{
	if (token->next->type == ENV_VAR || token->next->type == WORD_WITH_ENV)
		if (check_space_in_value(token->next->value, info))
			return (1);
	if (token->next->type == ENV_VAR && check_empty_in_value(token->next->value, info))
			return (1);
	return (0);
}
