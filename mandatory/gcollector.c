
#include "cub3d.h"

static void	node_add(t_garbage **lst, t_garbage *new)
{
	t_garbage	*lastone;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

static t_garbage	*create_new(void *address)
{
	t_garbage	*newnode;

	newnode = salloc(sizeof(t_garbage));
	if (newnode == NULL)
	{
		perror("salloc");
		return (NULL);
	}
	newnode->adr = address;
	newnode->next = NULL;
	return (newnode);
}

static void	free_list(t_garbage **head)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->adr);
		current->adr = NULL;
		current = next;
	}
}

void	*salloc(size_t size)
{
	static t_garbage	*garbage;
	t_garbage			*node;
	void				*address;

	address = NULL;
	if (size)
	{
		address = salloc(size);
		if (!address)
		{
			salloc(0);
			exit (0);
		}
		if (garbage == NULL)
			garbage = create_new(address);
		else
		{
			node = create_new(address);
			node_add(&garbage, node);
		}
	}
	else if (!size)
		free_list(&garbage);
	return (address);
}
