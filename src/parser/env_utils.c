/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:00:34 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 22:40:05 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	calculate_env_len(const char *value, int *i, int *value_len)
{
	t_env	*env_list;

	env_list = find_env_by_name(value, *i);
	if (!env_list || !env_list->value)
		return ;
	else
		*value_len += ft_strlen(env_list->value);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
}

int	write_exit_code(char *expanded, int *i, int *j)
{
	char	*exit_str;
	int		k;
	t_info	*info;

	info = get_info();
	exit_str = ft_arena_itoa(info->exit_code);
	k = 0;
	while (exit_str[k])
		expanded[(*j)++] = exit_str[k++];
	*i += 2;
	return (1);
}

void	save_env_value_with_del(const char *value, char *expanded, \
int *i, int *j)
{
	t_env	*env_list;
	int		k;

	k = 0;
	env_list = find_env_by_name(value, *i);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (!env_list || !env_list->value)
		return ;
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

int	write_env_with_double_quote(const char *value, \
char *expanded, int *i, int *j)
{
	t_env	*env_list;
	int		k;

	if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
	{
		(*i)++;
		k = 0;
		env_list = find_env_by_name(value, *i);
		while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
			(*i)++;
		if (!env_list || !env_list->value)
			return (1);
		while ((env_list->value)[k])
			expanded[(*j)++] = (env_list->value)[k++];
		return (1);
	}
	return (0);
}

int	write_env(const char *value, \
char *expanded, int *i, int *j)
{
	t_env	*env_list;
	int		k;

	if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		(*i)++;
	else
		return (0);
	k = 0;
	env_list = find_env_by_name(value, *i);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (!env_list || !env_list->value)
		return (1);
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
	return (1);
}
