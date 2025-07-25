/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:16:49 by donheo            #+#    #+#             */
/*   Updated: 2025/07/14 21:27:55 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"
# define ARENA_BLOCK_SIZE	51200
# define ENV_BLOCK_SIZE		1048576
# define ARENA_ALIGNMENT	8

typedef struct s_arena
{
	void			*memory;
	size_t			offset;
	size_t			size;
	struct s_arena	*next;
}	t_arena;

t_arena	*arena_create(size_t size);
void	*aalloc(t_arena **arena_ptr, size_t size);
void	arena_free_all(void);

#endif
