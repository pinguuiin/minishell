/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *input, t_alloc *data)
{
	t_token			*tokens;
	t_command_line	*cmd_line;

	tokens = lex_input(input);
	if (!tokens)
		return ;
	cmd_line = parse_tokens(tokens);
	if (!cmd_line)
		return ;
	executor(cmd_line, data);
	free_command_line(cmd_line);
}

static int	run_shell_loop(t_alloc *data)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			data->exit_code = 1;
			continue ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		process_input(input, data);
		free(input);
	}
	return (data->exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_alloc	data;

	(void)argc;
	(void)argv;
	if (init_execution(&data, envp))
		return (EXIT_FAILURE);
	data.exit_code = run_shell_loop(&data);
	free_path_elem(data.paths);
	free_argv(&data.env);
	return (data.exit_code);
}
