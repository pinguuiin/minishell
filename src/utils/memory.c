/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:24:34 by donheo            #+#    #+#             */
/*   Updated: 2025/07/14 23:01:18 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		clean_and_exit("arena");
	arena->memory = malloc(size);
	if (!arena->memory)
	{
		free(arena);
		clean_and_exit("arena memory");
	}
	ft_bzero(arena->memory, size);
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

static size_t	align_up(size_t offset)
{
	return ((offset + (ARENA_ALIGNMENT - 1)) & ~(ARENA_ALIGNMENT -1));
}

void	*aalloc(t_arena **arena_ptr, size_t size)
{
	t_arena	*arena_chunk;
	t_arena	*new_chunk;
	void	*ptr;
	size_t	aligned_offset;

	arena_chunk = *arena_ptr;
	while (arena_chunk)
	{
		aligned_offset = align_up(arena_chunk->offset);
		if (aligned_offset + size <= arena_chunk->size)
		{
			ptr = (char *)arena_chunk->memory + aligned_offset;
			arena_chunk->offset = aligned_offset + size;
			return (ptr);
		}
		arena_chunk = arena_chunk->next;
	}
	new_chunk = create_new_chunk(*arena_ptr, size);
	if (!new_chunk)
		return (NULL);
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
	arena = info->envp_arena;
	while (arena)
	{
		next = arena->next;
		free(arena->memory);
		free(arena);
		arena = next;
	}
	if (info->input)
		free(info->input);
	rl_clear_history();
}
