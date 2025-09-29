/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory-manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 22:16:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	mm_nodes_alloc_length(void)
{
	return (ft_lstsize(*mm_head()));
}

void	mm_garbage_collector(void)
{
	ft_lstclear(mm_head(), free);
}
