/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/12 20:55:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_node *node, void (*f)(void *))
{
	t_node	*lst_aux;

	if (!node || !f)
		return ;
	lst_aux = node;
	while (lst_aux)
	{
		f(lst_aux->content);
		lst_aux = lst_aux->next;
	}
}
