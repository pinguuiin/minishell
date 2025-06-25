/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:16:49 by donheo            #+#    #+#             */
/*   Updated: 2025/06/24 20:55:02 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"
# define ARENA_BLOCK_SIZE	10485760 // 10MB

typedef struct s_arena
{
	void			*memory;
	size_t			offset;
	size_t			size;
	struct s_arena	*next;
}	t_arena;

t_arena	*arena_create(size_t size);
void	*aalloc(t_arena **arena_ptr, size_t size);
void	arena_free_all(t_arena *arena);
void	clean_and_exit(char *err_msg);
#endif
