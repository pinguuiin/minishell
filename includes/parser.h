/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:25:25 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 08:15:34 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define DELIMITER 127

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
void	check_only_quote_and_del(const char *expanded_value, \
	int in_single_quote, int in_double_quote, t_cmd *cmd);
t_redir	*allocate_and_connect_redir(t_cmd *cmd, t_info *info);
int		is_quoted_heredoc(const char *value);
int		has_delimiter(const char *expanded_value);
int		is_only_env(const char *value);
t_cmd	*allocate_and_connect_cmd(t_cmd *cmd, t_info *info);
t_env	*find_env_by_name(const char *value, int i, t_info *info);
void	remove_quotes(char *value);
void	add_to_argv(char *expanded_value, t_cmd *cmd, t_info *info);
char	*expand_value(const char *value, t_info *info, t_cmd *cmd);
void	parser(t_info *info);

#endif
