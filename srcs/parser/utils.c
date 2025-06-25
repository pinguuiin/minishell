/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:11:51 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 02:17:13 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_pair(const char *str, int i)
{
	if (!str[i] || !str[i + 1])
		return (0);
	return ((str[i] == ' ' || str[i] == '\t') &&
			(str[i + 1] == ' ' || str[i + 1] == '\t'));
}

t_cmd	*allocate_and_connect_cmd(t_info *info, t_cmd *cmd)
{
	t_cmd	*new_cmd;

	(info->num_cmds)++;
	new_cmd = aalloc(&(info->arena), sizeof(t_cmd));
	if (!new_cmd)
		clean_and_exit("memory allocation fails for new cmd");
	cmd->next = new_cmd;
	return (new_cmd);
}

char	*allocate_and_copy_env_name(const char *value, int i, t_info *info)
{
	int		start_i;
	char	*env_name;

	start_i = i;
	while (value[i] && ft_isalnum(value[i]) || value[i] == '_')
		i++;
	env_name = aalloc(&(info->arena), i - start_i + 2);
	if (!env_name)
		clean_and_exit("memory allocation fails for env name");
	strlcpy(env_name, &value[start_i], i - start_i + 2);
	return (env_name);
}

t_env	*get_env_list(char *value, int i, t_info *info)
{
	t_env	*env_list;
	char	*env_name;

	env_name = allocate_and_copy_env_name(value, i, info);
	env_list = info->env;
	while (env_list)
	{
		if (ft_strncmp(env_name, env_list->key, ft_strlen(env_name) + 1))
			env_list = env_list->next;
		else
			break ;
	}
	return (env_list);
}
