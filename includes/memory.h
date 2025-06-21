/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:16:49 by donheo            #+#    #+#             */
/*   Updated: 2025/06/20 22:19:48 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

#include "minishell.h"

typedef struct s_arena
{
	void			*memory;
	size_t			offset;
	size_t			size;
	struct s_arena	*next;
} t_arena;


t_arena	*arena_create(size_t size);
void	*arena_alloc(t_arena **arena_ptr, size_t size);
void	arena_free_all(t_arena *arena);

#endif
