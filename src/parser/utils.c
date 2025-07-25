/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:11:51 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 21:52:32 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_and_copy_env_name(const char *value, int i, t_info *info)
{
	int		start_i;
	char	*env_name;

	start_i = i;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		i++;
	env_name = aalloc(&(info->arena), i - start_i + 2);
	if (!env_name)
		clean_and_exit("env name");
	ft_strlcpy(env_name, &value[start_i], i - start_i + 1);
	return (env_name);
}

t_env	*find_env_by_name(const char *value, int i)
{
	t_env	*env_list;
	t_info	*info;
	char	*env_name;

	info = get_info();
	env_name = allocate_and_copy_env_name(value, i, info);
	env_list = info->env_list;
	while (env_list)
	{
		if (ft_strncmp(env_name, env_list->key, ft_strlen(env_name) + 1))
			env_list = env_list->next;
		else
			break ;
	}
	return (env_list);
}

void	remove_quotes(char *value)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;
	int	j;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	j = 0;
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

void	add_to_argv(char *expanded_value, t_cmd *cmd, t_info *info)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	if (cmd->argv)
	{
		while ((cmd->argv)[count])
			count++;
	}
	new_argv = aalloc(&(info->arena), sizeof(char *) * (count + 2));
	if (!new_argv)
		clean_and_exit("new argv");
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = expanded_value;
	new_argv[count + 1] = NULL;
	cmd->argv = new_argv;
}

int	is_empty_string(const char *expanded_value, \
int in_single_quote, int in_double_quote)
{
	int	is_quote;

	is_quote = 0;
	while (*expanded_value)
	{
		if (*expanded_value == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			is_quote = 1;
		}
		else if (*expanded_value == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			is_quote = 1;
		}
		else if (*expanded_value == DELIMITER)
			;
		else
			return (0);
		expanded_value++;
	}
	if (is_quote)
		return (1);
	return (0);
}
