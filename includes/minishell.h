/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 18:00:32 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>

# include "libft.h"
# include "memory.h"
# include "validation.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_info
{
	int			error_code;
	t_env		*env;
	char		**envp_copy;
	t_cmd		*cmds;			// Linked list of piped commands
	int			num_cmds;		// Number of commands in pipeline
	t_arena		*arena;

}	t_info;

void	init_info(char **envp);
t_info	*get_info(void);

#endif
