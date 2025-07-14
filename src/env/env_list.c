/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:17:16 by donheo            #+#    #+#             */
/*   Updated: 2025/07/14 22:41:27 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env_node_fields(t_env *node, const char *env, \
const char *equal, t_arena **arena)
{
	size_t	key_len;

	key_len = equal - env;
	node->key = aalloc(arena, key_len + 1);
	if (!node->key)
		clean_and_exit("node key");
	node->value = aalloc(arena, ft_strlen(equal + 1) + 1);
	if (!node->value)
		clean_and_exit("node value");
	ft_memcpy(node->key, env, key_len);
	node->key[key_len] = '\0';
	ft_memcpy(node->value, equal + 1, ft_strlen(equal + 1) + 1);
	return (1);
}

static t_env	*new_env_node_from_string(const char *env, t_arena **arena)
{
	t_env		*node;
	const char	*equal;

	node = aalloc(arena, sizeof(t_env));
	if (!node)
		clean_and_exit("env node");
	equal = ft_strchr(env, '=');
	if (equal)
	{
		if (!init_env_node_fields(node, env, equal, arena))
			return (NULL);
	}
	else
	{
		node->key = aalloc(arena, ft_strlen(env) + 1);
		if (!node->key)
			clean_and_exit("node key in create function");
		ft_memcpy(node->key, env, strlen(env) + 1);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*envp_to_list(char	**envp, t_arena **arena)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_env_node_from_string(envp[i], arena);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
