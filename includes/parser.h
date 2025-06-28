/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:25:25 by donheo            #+#    #+#             */
/*   Updated: 2025/06/28 05:08:04 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Type of redirection(<, >, >>, <<)
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_HEREDOC_QUOTE,
	REDIR_AMB
}	t_redir_type;

// Redirection node
typedef struct s_redir
{
	t_redir_type	type;// Type of redirection
	char			*file;// Target file or heredoc delimiter
	struct s_redir	*next;// Linked list for multiple redirections
	int				fd;//file descriptor from opening the file
}	t_redir;

// Command node (single command in a pipeline)
typedef struct s_cmd
{
	char			**argv;// NULL-terminated array of arguments
	t_redir			*redirection;// Linked list of input/output redirections
	bool			is_error;
	struct s_cmd	*next;// Next command in pipeline
}	t_cmd;

void	remove_delimiter(char *expanded_value);
char	**divide_by_delimiter(char *value, t_info *info);
t_redir	*allocate_and_connect_redir(t_info *info,t_cmd *cmd);
int	is_quoted_heredoc(char *value);
char	*expand_heredoc_value(char *value, t_info *info);
int	is_ambiguous_redir(t_token *token, t_info *info);
t_cmd	*allocate_and_connect_cmd(t_info *info, t_cmd *cmd);
t_env	*get_env_list(char *value, int i, t_info *info);
void	remove_quotes(char *value, int i, int j);
void add_to_argv(t_cmd *cmd, char *expanded_value, t_info *info);
char	*expand_value(char *value, t_info *info);
void	parser(t_info *info);

#endif
