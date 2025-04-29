/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:03:18 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 13:34:03 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	newnode = malloc(sizeof(t_garbage));
	if (newnode == NULL)
	{
		perror("malloc");
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

	set_fd(-1, -1, 1);
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->adr);
		current->adr = NULL;
		current = next;
	}
}

void	*safe_malloc(int size)
{
	static t_garbage	*garbage;
	t_garbage			*node;
	void				*address;

	address = NULL;
	if (size != -1)
	{
		address = malloc(size);
		if (!address)
		{
			safe_malloc(-1);
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
	else if (size == -1)
		free_list(&garbage);
	return (address);
}
