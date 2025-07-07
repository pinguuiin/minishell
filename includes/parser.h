/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:25:25 by donheo            #+#    #+#             */
/*   Updated: 2025/07/07 14:02:38 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define EMPTY_STR 1
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
	struct s_cmd	*next;// Next command in pipeline
}	t_cmd;

void	calculate_env_len(const char *value, int *i, int *value_len);
int		itoa_len(int n);
char	*ft_arena_itoa(int n);
void	save_env_value_with_del(const char *value, char *expanded, \
int *i, int *j);
void	remove_delimiter(char *expanded_value);
char	**divide_by_delimiter(char *value, t_info *info, int i, int j);
int		is_empty_string(const char *expanded_value, \
int in_single_quote, int in_double_quote);
char	*get_empty_string(t_info *info);
t_redir	*allocate_and_connect_redir(t_cmd *cmd, t_info *info);
int		is_quoted_heredoc(const char *value);
int		has_only_env(const char *value);
int		has_delimiter(const char *expanded_value);
int		itoa_len(int n);
t_cmd	*allocate_and_connect_cmd(t_cmd *cmd, t_info *info);
t_env	*find_env_by_name(const char *value, int i, t_info *info);
void	remove_quotes(char *value);
void	add_to_argv(char *expanded_value, t_cmd *cmd, t_info *info);
char	*expand_value(const char *value, t_info *info);
void	parser(t_info *info);

#endif
