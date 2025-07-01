/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:24:34 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 02:08:04 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
	{
		ft_putstr_fd("failed to create arena\n", STDERR_FILENO);
		exit(1);
	}
	arena->memory = malloc(size);
	if (!arena->memory)
	{
		free(arena);
		ft_putstr_fd("failed to create memory for arena\n", STDERR_FILENO);
		exit(1);
	}
	arena->offset = 0;
	arena->size = size;
	arena->next = NULL;
	return (arena);
}

static t_arena	*create_new_chunk(t_arena *arena_ptr, size_t size)
{
	t_arena	*new_chunk;

	if (size > (ARENA_BLOCK_SIZE))
		new_chunk = arena_create(size);
	else
		new_chunk = arena_create(ARENA_BLOCK_SIZE);
	if (!new_chunk)
		return (NULL);
	new_chunk->offset = size;
	new_chunk->next = arena_ptr;
	return (new_chunk);
}

void	*aalloc(t_arena **arena_ptr, size_t size)
{
	t_arena	*arena_chunk;
	t_arena	*new_chunk;
	void	*ptr;

	arena_chunk = *arena_ptr;
	while (arena_chunk)
	{
		if (arena_chunk->offset + size <= arena_chunk->size)
		{
			ptr = (char *)arena_chunk->memory + arena_chunk->offset;
			arena_chunk->offset += size;
			return (ptr);
		}
		arena_chunk = arena_chunk->next;
	}
	new_chunk = create_new_chunk(*arena_ptr, size);
	if (!new_chunk)
	{
		arena_free_all();
		return (NULL);
	}
	*arena_ptr = new_chunk;
	return (new_chunk->memory);
}

void	arena_free_all(void)
{
	t_info	*info;
	t_arena	*arena;
	t_arena	*next;

	info = get_info();
	arena = info->arena;
	while (arena)
	{
		next = arena->next;
		free(arena->memory);
		free(arena);
		arena = next;
	}
	if (info->input)
		free(info->input);
}
