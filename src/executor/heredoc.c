/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:46:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/16 18:52:14 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_expansion(char *start, char *input, int *key_len, int fd)
{
	char	*key;
	char	*ptr;

	if (ft_strncmp(input, "?", 1) == 0)
	{
		ft_putnbr_fd(get_info()->exit_code, fd);
		*key_len = 1;
		return ;
	}
	key = trim_env_key(input);
	if (!key)
	{
		close(fd);
		free(start);
		clean_and_exit("heredoc");
	}
	*key_len = ft_strlen(key);
	ptr = get_info()->env_arr[get_env_ind(get_info()->env_arr, key)];
	if (ptr && ft_strchr(ptr, '='))
		ft_putstr_fd(ptr + *key_len + 1, fd);
}

static void	write_heredoc_input(char *input, t_redir *redir, int fd)
{
	int		key_len;
	char	*start;

	start = input;
	if (redir->type == REDIR_HEREDOC_QUOTE)
	{
		ft_putendl_fd(input, fd);
		return ;
	}
	while (*input)
	{
		key_len = 0;
		while (*input && *input != '$')
			ft_putchar_fd(*input++, fd);
		if (*input == '$' && (ft_isalnum(*(input + 1))
				|| *(input + 1) == '_' || *(input + 1) == '?'))
		{
			input++;
			write_expansion(start, input, &key_len, fd);
			input += key_len;
		}
		else if (*input == '$')
			ft_putchar_fd(*input++, fd);
	}
	ft_putchar_fd('\n', fd);
}

static int	heredoc_clean_up(char *input, int *pipefd)
{
	g_signal = 0;
	rl_event_hook = readline_handler;
	if (input)
		free(input);
	close(pipefd[0]);
	close(pipefd[1]);
	return (-2);
}

int	open_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*input;

	if (pipe(pipefd) == -1)
		return (-1);
	redir->fd = pipefd[0];
	rl_event_hook = rl_heredoc_handler;
	while (1)
	{
		input = readline("> ");
		if (g_signal == SIGINT)
			return (heredoc_clean_up(input, pipefd));
		if (!input || !ft_strncmp(input, redir->file, ft_strlen(input) + 1))
		{
			if (!input)
				write(2, "minishell: warning: heredoc delimited by EOF\n", 45);
			else
				free(input);
			break ;
		}
		write_heredoc_input(input, redir, pipefd[1]);
		free(input);
	}
	close(pipefd[1]);
	return (rl_event_hook = readline_handler, pipefd[0]);
}
