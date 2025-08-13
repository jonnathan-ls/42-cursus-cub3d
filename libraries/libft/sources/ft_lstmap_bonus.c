/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/12 20:55:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstmap(t_node *node, void *(*f)(void *), void (*del)(void *))
{
	t_node	*new_lst;
	t_node	*lst_aux;
	t_node	*new_lst_content;

	if (!node || !f)
		return (NULL);
	lst_aux = node;
	new_lst = ft_lstnew(f(lst_aux->content));
	if (!new_lst)
		return (NULL);
	lst_aux = lst_aux->next;
	while (lst_aux)
	{
		new_lst_content = ft_lstnew(f(lst_aux->content));
		if (!new_lst_content)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_lst_content);
		lst_aux = lst_aux->next;
	}
	return (new_lst);
}
