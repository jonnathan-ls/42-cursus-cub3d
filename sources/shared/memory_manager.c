/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns static pointer to linked list head.
 * @return Pointer to the head of memory node list.
 */
static t_node	**mm_head(void)
{
	static t_node	*node = NULL;

	return (&node);
}

/**
 * Handles memory allocation failure cleanup.
 * @param content Pointer to free if not NULL.
 * @return Always returns NULL.
 */
static void	*mm_fail(void *content)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd("Memory allocation failed", STDERR_FILENO);
	if (content)
		free(content);
	return (NULL);
}

/**
 * Allocates memory and adds to garbage collector list.
 * @param count Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated memory or NULL on failure.
 */
void	*mm_alloc(size_t count, size_t size)
{
	void	*content;
	t_node	*new_node;
	t_node	**head;

	content = ft_calloc(count, size);
	if (!content)
		return (mm_fail(NULL));
	head = mm_head();
	new_node = ft_lstnew(content);
	if (!new_node)
		return (mm_fail(content));
	if (!*head)
		*head = new_node;
	else
		ft_lstadd_front(head, new_node);
	return (content);
}

/**
 * Returns count of allocated memory nodes.
 * @return Number of nodes in allocation list.
 */
size_t	mm_nodes_alloc_length(void)
{
	return (ft_lstsize(*mm_head()));
}

/**
 * Frees all allocated memory in the list.
 */
void	mm_garbage_collector(void)
{
	ft_lstclear(mm_head(), free);
}
