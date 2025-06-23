/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/06/23 04:53:31 by piyu             ###   ########.fr       */
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
	executor(info, &cmds);
	free_command_line(cmds);
}

static void	run_shell_loop(t_info *info)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			info->exit_code = 1;
			continue ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		process_input(info, input);
		free(input);
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
	return (info->exit_code);
}
