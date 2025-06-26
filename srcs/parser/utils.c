/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:11:51 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 00:39:44 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void add_to_argv(t_cmd *cmd, char *expanded_value, t_info *info)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = aalloc(&(info->arena), sizeof(char *) * (count + 2));
	if (!new_argv)
		clean_and_exit("memory allocation failed for new argv");
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

