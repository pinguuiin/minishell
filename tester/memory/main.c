#include "minishell.h"

typedef struct s_node
{
    char *value;
    struct s_node *next;
} t_node;

t_node *create_node(t_arena **arena_ptr, const char *str)
{
    t_node *node = (t_node *)aalloc(arena_ptr, sizeof(t_node));
    if (!node)
        return NULL;

    node->value = (char *)aalloc(arena_ptr, strlen(str) + 1);
    if (!node->value)
        return NULL;

    strcpy(node->value, str);
    node->next = NULL;
    return node;
}

void add_node_back(t_node **head, t_node *new_node)
{
    if (!*head)
        *head = new_node;
    else
    {
        t_node *cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = new_node;
    }
}

void print_list(t_node *head)
{
    while (head)
    {
        printf("%s\n", head->value);
        head = head->next;
    }
}

int main(void)
{
    t_arena *arena = arena_create(ARENA_BLOCK_SIZE);
    if (!arena)
    {
        fprintf(stderr, "Failed to create memory arena\n");
        return 1;
    }

    t_node *list = NULL;

    add_node_back(&list, create_node(&arena, "hello"));
    add_node_back(&list, create_node(&arena, "world"));
    add_node_back(&list, create_node(&arena, "minishell"));
    add_node_back(&list, create_node(&arena, "memory arena test"));

    printf("Linked list contents:\n");
    print_list(list);

    arena_free_all(arena);
    return 0;
}
