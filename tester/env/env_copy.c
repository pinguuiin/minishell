#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_info info;
    info.arena = arena_create(ARENA_BLOCK_SIZE);

	(void)argc;
	(void)argv;
    char **env_arr = copy_envp(envp, &info);
    printf("Copied envp:\n");
    for (int i = 0; envp[i]; i++)
    {
        if (strcmp(envp[i], env_arr[i]) != 0)
        {
            printf("❌ Mismatch at index %d:\n", i);
            printf("Original : %s\n", envp[i]);
            printf("Copied   : %s\n", env_arr[i]);
        }
        else
        {
            printf("✅ Match at index %d: %s\n", i, envp[i]);
        }
    }
    arena_free_all(info.arena);
    return 0;
}
