/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:39:02 by piyu              #+#    #+#             */
/*   Updated: 2025/06/30 05:48:54 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand(char *start, char *input, int *key_len, int *pipefd)
{
	char	*env_var;
	char	*ptr;

	while (ft_isalnum(*input) || *input == '_')
	{
		input++;
		(*key_len)++;
	}
	env_var = aalloc(&get_info()->arena, (*key_len) + 1);
	if (env_var == NULL)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free(start);
		clean_and_exit("heredoc");
	}
	ft_strlcpy(env_var, input, (*key_len));
	env_var[*key_len] = '\0';
	ptr = get_info()->env_arr[get_env_ind(get_info()->env_arr, env_var)];
	if (ptr && !ft_strchr(ptr, '='))
		ptr = NULL;
	else if (ptr && ft_strchr(ptr, '='))
		ptr += *key_len + 1;
	return (ptr);
}

void	write_heredoc_input(char *input, t_redir *redir, int *fd)
{
	int		key_len;
	char	*start;

	key_len = 0;
	start = input;
	if (redir->type == REDIR_HEREDOC_QUOTE)
	{
		ft_putendl_fd(input, fd[1]);
		return ;
	}
	while (*input)
	{
		while (*input && *input != '$')
			ft_putchar_fd(*input++, fd[1]);
		if (*input == '$' && (ft_isalnum(*(input + 1)) || *(input + 1) == '_'))
		{
			input++;
			ft_putstr_fd(heredoc_expand(start, input, &key_len, fd), fd[1]);
			input += key_len;
		}
		else if (*input == '$')
			ft_putchar_fd(*input++, fd[1]);
	}
	ft_putchar_fd('\n', fd[1]);
}

int	open_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*input;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			clean_and_exit("heredoc");
		}
		if (!ft_strncmp(input, redir->file, ft_strlen(input)))
			break ;
		write_heredoc_input(input, redir, pipefd);
		free(input);
		input = NULL;
	}
	free(input);
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	open_file(t_redir *redir)
{
	if (redir->type == REDIR_INPUT)
		redir->fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUTPUT)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		redir->fd = open_heredoc(redir);
	if (redir->fd == -1)
		error_msg("minishell", NULL, redir->file, 1);
	return (redir->fd);
}

int	redirect(t_redir *redir)
{
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	while (redir)
	{
		if (open_file(redir) == -1)
			return (EXIT_FAILURE);
		if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			fd[1] = redir->fd;
		else
			fd[0] = redir->fd;
		redir = redir->next;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
