/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:17:13 by donheo            #+#    #+#             */
/*   Updated: 2025/07/15 00:43:27 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_ind(char **envp, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && \
(*(envp[i] + len) == '=' || *(envp[i] + len) == '\0'))
			return (i);
		i++;
	}
	return (i);
}

char	*trim_env_key(char *s)
{
	int		key_len;
	char	*key;

	key_len = 0;
	while (ft_isalnum(s[key_len]) || s[key_len] == '_')
		key_len++;
	key = aalloc(&get_info()->arena, key_len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, s, key_len + 1);
	return (key);
}

int	count_envp(char **envp)
{
	size_t	count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

char	**copy_envp_entries(char **envp, \
char **env_arr, int envp_count, t_arena *arena)
{
	int	i;

	i = 0;
	while (i < envp_count)
	{
		env_arr[i] = aalloc(&arena, ft_strlen(envp[i]) + 1);
		if (!env_arr[i])
			clean_and_exit("env_arr entry");
		ft_strlcpy(env_arr[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

char	**copy_envp(char **envp, t_arena *arena)
{
	char	**env_arr;
	int		envp_count;

	envp_count = count_envp(envp);
	env_arr = aalloc(&arena, (envp_count + 1) * sizeof(char *));
	if (!env_arr)
		clean_and_exit("env_arr");
	env_arr = copy_envp_entries(envp, env_arr, envp_count, arena);
	return (env_arr);
}
