/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/12 18:45:56 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc(t_info *info)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = info->cmds;
	while (cmd)
	{
		redir = cmd->redirection;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC
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
	parser(info);
	if (process_heredoc(info))
		return ;
	executor(info, info->cmds);
}

static void	run_shell_loop(t_info *info)
{
	while (1)
	{
		reset_info();
		if (g_signal == SIGINT)
			g_signal = 0;
		info->input = readline("minishell$ ");
		if (!(info->input))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			silent_exit(0);
		}
		if (!((info->input)[0]))
			continue ;
		add_history(info->input);
		if (is_all_whitespace(info->input)
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
