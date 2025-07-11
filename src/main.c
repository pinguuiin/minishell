/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/11 19:22:09 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int process_heredoc(t_info *info)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = info->cmds;
	while (cmd)
	{
		redir = cmd->redirection;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC \
			|| redir->type == REDIR_HEREDOC_QUOTE)
			{
				redir->fd = open_heredoc(redir);
				if (redir->fd == -2)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

static void	process_input(t_info *info)
{
	info->env_list = envp_to_list(info->env_arr, &(info->arena));
	tokenize_elements(info);
	// print_tokens(info->tokens);
	parser(info);
	// print_cmds(info->cmds);
	if (process_heredoc(info))
		return ;
	executor(info, info->cmds);
	dup2(info->fd_stdio[0], STDIN_FILENO);
	dup2(info->fd_stdio[1], STDOUT_FILENO);
}


static char	*ft_strjoin_and_free(char *buffer, \
		char const *tmp_buffer, int buffer_len, int tmp_len)
{
	int		i;
	char	*new_s;

	buffer_len = ft_strlen(buffer);
	tmp_len = ft_strlen(tmp_buffer);
	new_s = (char *)malloc((buffer_len + tmp_len + 1) * sizeof(char));
	if (!new_s)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < buffer_len)
	{
		new_s[i] = buffer[i];
		i++;
	}
	while (i < buffer_len + tmp_len)
	{
		new_s[i] = tmp_buffer[i - buffer_len];
		i++;
	}
	new_s[i] = '\0';
	free(buffer);
	return (new_s);
}

static void	delete_copied_line(char *buffer, size_t line_len)
{
	int		rest_len;

	rest_len = ft_strlen(buffer + line_len);
	ft_memmove(buffer, buffer + line_len, rest_len + 1);
}

static char	*copy_line(const char *buffer, size_t	*line_len)
{
	char	*line;

	*line_len = 0;
	while (buffer[*line_len] && buffer[*line_len] != '\n')
		(*line_len)++;
	if (buffer[*line_len] == '\n')
		(*line_len)++;
	line = malloc((*line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	*line_len = 0;
	while (buffer[*line_len] && buffer[*line_len] != '\n')
	{
		line[*line_len] = buffer[*line_len];
		(*line_len)++;
	}
	if (buffer[*line_len] && buffer[*line_len] == '\n')
		line[(*line_len)++] = '\n';
	line[*line_len] = '\0';
	return (line);
}

static char	*save_lines(int fd, char *buffer)
{
	int		read_bytes;
	char	*tmp_buffer;

	tmp_buffer = malloc(33);
	if (!tmp_buffer)
		return (free(buffer), NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, tmp_buffer, 32);
		if (read_bytes == -1)
			return (free(tmp_buffer), free(buffer), NULL);
		tmp_buffer[read_bytes] = '\0';
		buffer = ft_strjoin_and_free(buffer, tmp_buffer, 0, 0);
		if (!buffer)
			return (free(tmp_buffer), NULL);
	}
	free(tmp_buffer);
	return (buffer);
}

static char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	size_t		line_len;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = save_lines(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	line = copy_line(buffer, &line_len);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	delete_copied_line(buffer, line_len);
	return (line);
}


static void	run_shell_loop(t_info *info)
{
	while (1)
	{
		reset_info();
		if (g_signal == SIGINT)
			g_signal = 0;
		if (isatty(fileno(stdin)))
			info->input = readline("minishell$ ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			info->input = ft_strtrim(line, "\n");
		}
		if (!(info->input))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			arena_free_all();
			exit(0);
		}
		if (!((info->input)[0]))
			continue ;
		add_history(info->input);
		if (is_all_whitespace(info->input) \
		|| has_syntax_error(info->input, info))
			continue ;
		process_input(info);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = readline_handler;
	(void)argc;
	(void)argv;
	init_info(envp);
	info = get_info();
	run_shell_loop(info);
	arena_free_all();
	return (EXIT_SUCCESS);
}
