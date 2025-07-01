/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/01 06:08:36 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *input, t_info *info)
{
	t_token	*tokens;
	t_cmd	*cmds;

	envp_to_list(info->env_arr, &(info->arena));
	tokenize_elements(input);
	parser(info);
	executor(info, cmds);
	close_fds(cmds);
}

static void	run_shell_loop(t_info *info)
{
	char	*input;
	while (1)
	{
		reset_info();
		input = readline("minishell$ ");
		if (!input)
		{
			info->exit_code = 1;
			break ;
		}
		if (!input[0] && has_syntax_error(input))
		{
			free(input);
			input = NULL;
			if (has_syntax_error(input))
				add_history(input);
			continue ;
		}
		add_history(input);
		process_input(input, info);
		free(input);
		input = NULL;
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
	arena_free_all(info->arena);
	//free memory; close fd; clear rl history; return exit code
}
