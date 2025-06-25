/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:30:25 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 00:56:46 by donheo           ###   ########.fr       */
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
	env_name = allocate_and_copy_env_name(value, i, info);
	env_list = get_env_list(info, env_list, env_name);
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

void	save_value(char *value, char *expanded, int *i, int *j, t_info *info)
{
	char	*env_name;
	t_env	*env_list;

	env_name = allocate_and_copy_env_name(value, *i, info);
	env_list = get_env_list(info, env_list, env_name);

}

void	save_expanded_value(char *value, char *expanded, int total_len, t_info *info)
{
	char	new_env_value;
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
			save_value(value, expanded, &i, &j, info);
			continue ;
		}
		expanded[j++] = value[i++];
	}
}

char	*expand_value(char *value, char *file, t_info *info)
{
	int		total_len;
	char	*expanded_value;

	total_len = calculate_total_len_of_value(value);
	expanded_value = aalloc(&(info->arena), total_len);
	if (!expanded_value)
		clean_and_exit("memory allocation failed for expanded value");
	save_expanded_value(value, expanded_value, total_len, info);







	remove_quotes(file);
	return (expanded_value);
}
