/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:46:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/04 01:04:00 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_env_key(char *s, int *key_len)
{
	char	*key;

	*key_len = 0;
	while (ft_isalnum(s[*key_len]) || s[*key_len] == '_')
		(*key_len)++;
	key = aalloc(&get_info()->arena, (*key_len) + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, s, (*key_len) + 1);
	return (key);
}

static void	write_expansion(char *start, char *input, int *key_len, int *fd)
{
	char	*key;
	char	*ptr;

	if (ft_strncmp(input, "?", 1) == 0)
	{
		ft_putnbr_fd(get_info()->exit_code, fd[1]);
		get_info()->exit_code = 0;
		*key_len = 1;
		return ;
	}
	key = trim_env_key(input, key_len);
	if (!key)
	{
		close(fd[1]);
		free(start);
		clean_and_exit("heredoc");
	}
	ptr = get_info()->env_arr[get_env_ind(get_info()->env_arr, key)];
	if (ptr && ft_strchr(ptr, '='))
		ft_putstr_fd(ptr + *key_len + 1, fd[1]);
}

static void	write_heredoc_input(char *input, t_redir *redir, int *fd)
{
	int		key_len;
	char	*start;

	start = input;
	if (redir->type == REDIR_HEREDOC_QUOTE)
	{
		ft_putendl_fd(input, fd[1]);
		return ;
	}
	while (*input)
	{
		key_len = 0;
		while (*input && *input != '$')
			ft_putchar_fd(*input++, fd[1]);
		if (*input == '$' && (ft_isalnum(*(input + 1)) ||
		*(input + 1) == '_' || *(input + 1) == '?'))
		{
			input++;
			write_expansion(start, input, &key_len, fd);
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
	redir->fd = pipefd[0];
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
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
