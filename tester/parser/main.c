#include "minishell.h"

void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf("    [Redirection] type: %d, file: %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("[Command %d]\n", i++);
		for (int j = 0; cmd->argv && cmd->argv[j]; j++)
			printf("  argv[%d]: %s\n", j, cmd->argv[j]);

		if (cmd->redirection)
			print_redirs(cmd->redirection);

		printf("  is_error: %d\n", cmd->is_error);
		cmd = cmd->next;
	}
}

int main(int argc, char **argv, char **envp)
{
    t_info	*info;
	char	*input = "echo 'hello world' | < $a > $USER < sdfg > dsfg | > abc$ | def ghi | < abc ls -la ";

	(void)argc;
	(void)argv;
	init_info(envp);
	info = get_info();
	info->env_list = envp_to_list(envp,&(info->arena));
	if (!check_syntax_error(input))
	{
		printf("syntax error detected");
		return (1);
	}
	tokenize_elements(input);
	parser(info);

	print_cmds(info->cmds);
}
