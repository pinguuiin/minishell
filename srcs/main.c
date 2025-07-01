/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:44:11 by piyu              #+#    #+#             */
/*   Updated: 2025/07/02 02:28:16 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(t_info *info)
{
	t_cmd	*cmds;

	envp_to_list(info->env_arr, &(info->arena));
	tokenize_elements(info);
	parser(info);
	executor(info, cmds);
	close_fds(cmds);
}

static void	run_shell_loop(t_info *info)
{
	while (1)
	{
		reset_info();
		info->input = readline("minishell$ ");
		if (!(info->input))
			clean_and_exit("user input");
		if (!((info->input)[0]))
		{
			free(info->input);
			continue ;
		}
		add_history(info->input);
		if (is_all_whitespace(info->input) || has_syntax_error(info->input))
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
