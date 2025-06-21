/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 12:59:36 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"
#include "memory.h"
#include "validation.h"
#include "env.h"
#include "lexer.h"
#include "parser.h"

typedef struct s_info
{
	bool		is_error;
	int			error_code;
	t_env		*env;
	char		**envp_copy;
	t_cmd_line	*cmd_line;
	t_arena		*arena;

}	t_info;

#endif
