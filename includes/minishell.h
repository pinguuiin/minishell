/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/20 10:51:32 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ARENA_BLOCK_SIZE (10 * 1024 * 1024)

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../lib/libft/libft.h"

typedef struct s_arena
{
	void			*memory;
	size_t			offset;
	size_t			size;
	struct s_arena	*next;
} t_arena;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;


typedef struct s_info
{
	bool	is_error;
	int		error_code;
	t_env	*env;
	// t_cmd	*cmd;
	t_arena	*arena;

}	t_info;

// Type of redirection
typedef enum e_redir_type
{
	REDIR_INPUT,	// <
    REDIR_OUTPUT,	// >
    REDIR_APPEND,	// >>
    REDIR_HEREDOC	// <<
}   t_redir_type;

// Redirection node
typedef struct s_redir
{
	t_redir_type	type;	// Type of redirection
	char			*file;	// Target file or heredoc delimiter
	struct s_redir	*next;	// Linked list for multiple redirections
}	t_redir;

// Command node (single command in a pipeline)
typedef struct s_cmd
{
	char	**argv;			// NULL-terminated array of arguments
	t_redir	*redirection;	// Linked list of input/output redirections
	int		is_builtin;		// Boolean flag for built-ins
	struct	s_cmd *next;	// Next command in pipeline
}	t_cmd;

// Full command line (could be one or multiple piped commands)
typedef struct s_command_line
{
	t_cmd	*cmds;		// Linked list of piped commands
	int		num_cmds;	// Number of commands in pipeline
}	t_command_line;

// memory management
t_arena	*arena_create(size_t size);
void	*arena_alloc(t_arena **arena_ptr, size_t size);
void	arena_free_all(t_arena *arena);

// input validation
int		validate_quotes(const char *cmd);
int		validate_redirections(const char *cmd);
int		validate_operations(const char *cmd, int expect_command);
int		check_syntax_error(const char *cmd);

#endif
