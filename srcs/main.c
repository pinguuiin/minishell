/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/06/28 04:38:15 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(t_info *info, char *input)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lex_input(input);
	if (!tokens)
		return ;
	cmds = parse_tokens(tokens);
	if (!cmds)
		return ;
	executor(info, cmds);
	close_fds(cmds);
}

static void	run_shell_loop(t_info *info)
{
	while (1)
	{
		info->exit_code = 0;
		info->input = readline("minishell$ ");
		if (!info->input)
		{
			info->exit_code = 1;
			break ;
		}
		if (!*info->input)
		{
			free(info->input);
			info->input = NULL;
			continue ;
		}
		add_history(info->input);
		process_input(info, info->input);
		free(info->input);
		info->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	init_info(envp);
	info = get_info();
	run_shell_loop(info);
	//free memory; close fd; clear rl history; return exit code
}
