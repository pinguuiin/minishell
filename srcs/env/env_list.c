/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:17:16 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 16:56:02 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_key_value(t_env *node, const char *env, const char *equal, t_arena **arena)
{
	size_t key_len = equal - env ;

	node->key = aalloc(arena, key_len + 1);
	node->value = aalloc(arena, ft_strlen(equal + 1) + 1);
	if (!node->key || !node->value)
		return (0);
	ft_memcpy(node->key, env, key_len);
	node->key[key_len] = '\0';
	ft_memcpy(node->value, equal + 1, ft_strlen(equal + 1) + 1);
	return (1);
}

static t_env	*create_env_node(const char *env, t_arena **arena)
{
	t_env		*node;
	const char	*equal;

	node = aalloc(arena, sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (equal)
	{
		if (!set_key_value(node, env, equal, arena))
			return (NULL);
	}
	else
	{
		node->key = aalloc(arena, ft_strlen(env) + 1);
		if (!node->key)
			return (NULL);
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
		new_node = create_env_node(envp[i], arena);
		if (!new_node)
		{
			ft_putstr_fd("fails to allocate t_env node\n", STDERR_FILENO);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
