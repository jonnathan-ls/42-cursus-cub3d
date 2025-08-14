/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory-manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/14 00:53:48 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#define FAILURE_ALLOC_MESSAGE "Error\nMemory allocation failed"

/**
 * Retrieves the head of the linked list tracking allocated memory blocks.
 * @return Pointer to the head node of the list.
 */
static t_node	**get_node_head(void)
{
	static t_node	*node = NULL;

	return (&node);
}

/**
 * Handles memory allocation failures for content.
 * @return NULL.
 */
static void	*failure_alloc_content(void)
{
	ft_putendl_fd(FAILURE_ALLOC_MESSAGE, STDERR_FILENO);
	return (NULL);
}

/**
 * Handles memory allocation failures for linked list nodes.
 * @param content Pointer to the content to free.
 * @return NULL.
 */
static	void	*failure_alloc_node(void *content)
{
	ft_putendl_fd(FAILURE_ALLOC_MESSAGE, STDERR_FILENO);
	free(content);
	return (NULL);
}

/**
 * Allocates memory for generic element and tracks the allocation.
 * @param count Number of elements to allocate.
 * @param size Size of each element.
 * @return Pointer to the allocated memory or NULL on failure.
 */
void	*mm_alloc(size_t count, size_t size)
{
	void	*content;
	t_node	*new_node;
	t_node	**node_head;

	content = ft_calloc(count, size);
	if (!content)
		return (failure_alloc_content());
	node_head = get_node_head();
	if (!*node_head)
	{
		new_node = ft_lstnew(content);
		if (!new_node)
			return (failure_alloc_node(content));
		*node_head = new_node;
	}
	else
	{
		new_node = ft_lstnew(content);
		if (!new_node)
			return (failure_alloc_node(content));
		ft_lstadd_front(node_head, new_node);
	}
	return (content);
}

/**
 * Returns the number of allocated memory blocks.
 * @return Number of allocated blocks.
 */
size_t	mm_nodes_length(void)
{
	t_node	**node_head;
	int		length;

	node_head = get_node_head();
	length = ft_lstsize(*node_head);
	return (length);
}

/**
 * Frees all allocated memory blocks.
 */
void	mm_garbage_collector(void)
{
	t_node	**node_head;

	node_head = get_node_head();
	ft_lstclear(node_head, free);
}
