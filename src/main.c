/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/08 15:09:37 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(t_info *info)
{
	info->env_list = envp_to_list(info->env_arr, &(info->arena));
	tokenize_elements(info);
	// print_tokens(info->tokens);
	parser(info);
	// print_cmds(info->cmds);
	executor(info, info->cmds);
	dup2(info->fd_stdio[0], STDIN_FILENO);
	dup2(info->fd_stdio[1], STDOUT_FILENO);
}

static void	run_shell_loop(t_info *info)
{
	while (1)
	{
		reset_info();
		info->input = readline("minishell$ ");
		if (!(info->input))
		{
			arena_free_all();
			exit(0);
		}
		if (!((info->input)[0]))
		{
			free(info->input);
			continue ;
		}
		add_history(info->input);
		if (is_all_whitespace(info->input) \
|| has_syntax_error(info->input, info))
		{
			free(info->input);
			continue ;
		}
		process_input(info);
		free(info->input);
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
	arena_free_all();
	return (EXIT_SUCCESS);
}
