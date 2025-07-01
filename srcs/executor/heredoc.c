/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:46:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/02 01:35:41 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_expansion(char *start, char *input, int *key_len, int *fd)
{
	char	*env_var;
	char	*ptr;

	if (ft_strncmp(input, "?", 1))
	{
		ft_putnbr_fd(get_info()->exit_code, fd[1]);
		get_info()->exit_code = 0;
		*key_len = 1;
		return ;
	}
	while (ft_isalnum(input[*key_len]) || input[*key_len] == '_')
		(*key_len)++;
	env_var = aalloc(&get_info()->arena, (*key_len) + 1);
	if (env_var == NULL)
	{
		close(fd[1]);
		free(start);
		clean_and_exit("heredoc");
	}
	ft_strlcpy(env_var, input, (*key_len));
	env_var[*key_len] = '\0';
	ptr = get_info()->env_arr[get_env_ind(get_info()->env_arr, env_var)];
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
		if (*input == '$' && (ft_isalnum(*(input + 1)) || *(input + 1) == '_'))
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
