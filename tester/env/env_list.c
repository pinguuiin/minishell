#include "minishell.h"
#include <stdio.h>

int main(void)
{
	t_arena *arena = arena_create(ARENA_BLOCK_SIZE);
	char *test_envp[] = {
		"PATH=/usr/bin",
		"USER=testuser",
		"EMPTYVAR=",
		"KEYONLY",
		NULL
	};
	t_env *env_list = envp_to_list(test_envp, &arena);
	t_env *cur = env_list;

	while (cur)
	{
		printf("KEY: %s | VALUE: %s\n", cur->key, cur->value ? cur->value : "(null)");
		cur = cur->next;
	}

	arena_free_all();

	return 0;
}
