/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/19 10:34:02 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#ifndef MINISHELL_H
# define MINISHELL_H

# define ARENA_BLOCK_SIZE (10 * 1024 * 1024)

typedef struct s_arena
{
	void			*memory;
	size_t			offset;
	size_t			size;
	struct s_arena	*next;
} t_arena;

#endif
