#include "minishell.h"

static const char *token_type_str(t_token_type type) {
    switch (type) {
        case WORD: return "WORD";
        case IN: return "IN";
        case OUT: return "OUT";
        case APPEND: return "APPEND";
        case HEREDOC: return "HEREDOC";
        case PIPE: return "PIPE";
        default: return "UNKNOWN";
    }
}

void print_tokens(t_token *token) {
    while (token) {
        printf("[Token] type: %-14s | value: %s\n",
               token_type_str(token->type),
               token->value ? token->value : "(null)");
        token = token->next;
    }
}

static void	print_redirs(t_redir *redir)
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
