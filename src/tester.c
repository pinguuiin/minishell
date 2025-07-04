#include "minishell.h"

#define PLACEHOLDER_QUOTE '1'
#define PLACEHOLDER_ENV   '2'

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


// static int has_only_quote(const char *str) {
// 	int has_single = 0;
// 	int has_double = 0;

// 	while (*str) {
// 		if (*str == '\'')
// 			has_single = 1;
// 		else if (*str == '"')
// 			has_double = 1;
// 		else
// 			return 0;
// 		str++;
// 	}
// 	return (has_single ^ has_double);
// }

static int has_placeholder_char(const char *str, char ch)
{
	while (*str)
	{
		if (*str == ch)
			return 1;
		str++;
	}
	return 0;
}

static void print_escaped_string(const char *str)
{
	while (*str)
	{
		unsigned char ch = *str;
		if (ch < 32 || ch == 127)
			printf("\\x%02x", ch);
		else
			putchar(ch);
		str++;
	}
}


static void print_redirs(t_redir *redir) {
	while (redir) {
		printf("    [Redirection] type: %d, file: ", redir->type);

		if (redir->file == NULL)
			printf("(null)\n");
		else if (has_placeholder_char(redir->file, PLACEHOLDER_QUOTE))
		{
			printf("[quoted empty -> '%c'] -> ", PLACEHOLDER_QUOTE);
			print_escaped_string(redir->file);
			printf("\n");
		}
		else if (has_placeholder_char(redir->file, PLACEHOLDER_ENV))
		{
			printf("[empty env -> '%c'] -> ", PLACEHOLDER_ENV);
			print_escaped_string(redir->file);
			printf("\n");
		}
		else
		{
			print_escaped_string(redir->file);
			printf("\n");
		}
		redir = redir->next;
	}
}

void print_cmds(t_cmd *cmd)
{
	int i = 0;

	while (cmd)
	{
		printf("[Command %d]\n", i++);

		for (int j = 0; cmd->argv && cmd->argv[j]; j++)
		{
			const char *arg = cmd->argv[j];

			if (has_placeholder_char(arg, PLACEHOLDER_QUOTE))
				printf("  argv[%d]: [quoted empty -> '%c'] -> ", j, PLACEHOLDER_QUOTE);
			else if (has_placeholder_char(arg, PLACEHOLDER_ENV))
				printf("  argv[%d]: [empty env -> '%c'] -> ", j, PLACEHOLDER_ENV);
			else
				printf("  argv[%d]: ", j);

			print_escaped_string(arg);
			printf("\n");
		}

		if (cmd->redirection)
			print_redirs(cmd->redirection);

		printf("  is_error: %d\n", cmd->is_error);
		cmd = cmd->next;
	}
}
