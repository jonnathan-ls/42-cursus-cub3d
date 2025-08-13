/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/12 20:55:01 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*new_lst_content;

	new_lst_content = (t_node *)malloc(sizeof(t_node));
	if (new_lst_content)
	{
		new_lst_content->content = content;
		new_lst_content->next = NULL;
	}
	return (new_lst_content);
}
