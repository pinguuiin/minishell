
#include "minishell.h"
#include <stdio.h>

const char *token_type_str(t_token_type type) {
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

int main(void) {
    t_info	*info;

	info = get_info();

    const char *input = "echo     hello     >           out.txt          |             grep              hi   $ABC      <            in.txt >>               append.txt << EOF | \"g$ABCdf'g'g\"\"sdfsfd\" |'$abc' | $abc$ |\"\"$ABC\"\"  ";

    tokenize_elements(input);

    print_tokens(info->tokens);

    return 0;
}
