/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory-manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/28 21:46:56 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static t_node	**mm_head(void)
{
	static t_node	*node = NULL;

	return (&node);
}

static void	*mm_fail(void *content)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd("Memory allocation failed", STDERR_FILENO);
	if (content)
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
 * Returns the number of allocated memory blocks.
 * @return Number of allocated blocks.
 */
size_t	mm_nodes_alloc_length(void)
{
	return (ft_lstsize(*mm_head()));
}

/**
 * Frees all allocated memory blocks.
 */
void	mm_garbage_collector(void)
{
	ft_lstclear(mm_head(), free);
}
