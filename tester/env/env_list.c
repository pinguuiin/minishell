#include "minishell.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    t_info info;
    info.arena = arena_create(ARENA_BLOCK_SIZE);
	(void)argc;
	(void)argv;
	 copy_envp(envp, &info);
	t_env *env_list = envp_to_list(envp, &(info.arena));
	t_env *cur = env_list;

	while (cur)
	{
		printf("KEY: %s | VALUE: %s\n", cur->key, cur->value ? cur->value : "(null)");
		cur = cur->next;
	}

	arena_free_all();

	return 0;
}
